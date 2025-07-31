//! REL relinker. This expects a relocatable ELF file as the input,
//! and generates a REL file as the output.
//!
//! # Nits
//! - Rewrite to be a bit more modern C++.
#include <fcntl.h>
#include <libelf.h>
#include <sys/file.h>
#include <unistd.h>

#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "rel_format.hpp"
#include "types.hpp"

/// Per-section data structure which
/// holds the data as well for easy access
struct SectionData {
	Elf_Scn* scn { nullptr };
	Elf32_Shdr* shdr { nullptr };
	Elf_Data* data { nullptr };

	/// If not nullptr, this provides data on the section that will relocate
	SectionData* reloc { nullptr };
};

struct ExtendedSectionHeader {
	rel::SectionHeader sectionHeader;
	SectionData* data;
};

struct RelLinker {
	RelLinker() {
		// Initalize libelf
		elf_version(EV_CURRENT);

		// This is probbaly TOO much.
		programCoreSections.reserve(32);
		relocSections.reserve(32);
	}

	~RelLinker() {
		if(elf != nullptr)
			elf_end(elf);
		if(inElfFd != -1)
			close(inElfFd);
		if(outRelFd != -1)
			close(outRelFd);
	}

	Elf_Data* getShStrtab() {
		// NOTE: init() catches the case of a ELF which may have a zero shstrndx, which should mean
		// we don't have to worry about this? I think? Idk.
		auto shstr = elf_getscn(elf, elf_header->e_shstrndx);
		auto shstr_data = elf_getdata(shstr, nullptr);
		assert(shstr_data != nullptr && "how did you even hit this what");
		return shstr_data;
	}

	std::string getSectionName(const SectionData& si) {
		return std::string(&static_cast<char*>(getShStrtab()->d_buf)[si.shdr->sh_name]);
	}

	std::string getSectionName(u32 index) {
		auto sh = elf_getscn(elf, index);
		if(!sh)
			return "(unknown section)";

		auto shdr = elf32_getshdr(sh);
		return std::string(&static_cast<char*>(getShStrtab()->d_buf)[shdr->sh_name]);
	}

	/// Obtains the sections which are part of the program core
	/// (i.e: they are loaded into memory)
	void initProgramCoreSections() {
		for(u32 i = 1; i < (elf_header->e_shnum - 1); ++i) {
			auto scn = elf_getscn(elf, i);
			auto shdr = elf32_getshdr(scn);
			auto sdat = elf_rawdata(scn, nullptr);

			if((shdr->sh_flags & SHF_ALLOC) || shdr->sh_type == SHT_NOBITS) {
				programCoreSections.push_back(SectionData {
				.scn = scn,
				.shdr = shdr,
				.data = sdat,
				.reloc = nullptr });
			}
		}
	}

	void initRelocationSections() {
		std::vector<u32> relocLinks;

		for(u32 i = 1; i < (elf_header->e_shnum - 1); ++i) {
			auto scn = elf_getscn(elf, i);
			auto shdr = elf32_getshdr(scn);
			auto sdat = elf_rawdata(scn, nullptr);

			if(shdr->sh_type == SHT_REL) {
				// sh_info points to the section we will be relocating.
				auto relocLink = shdr->sh_info;

				relocSections.push_back(SectionData {
				.scn = scn,
				.shdr = shdr,
				.data = sdat,
				.reloc = nullptr });

				for(auto i = 0; i < programCoreSections.size(); ++i) {
					if(elf_getscn(elf, relocLink) == programCoreSections[i].scn) {
						// printf("found matching SectionInfo for reloc section \"%s\": \"%s\"\n", getSectionName(relocSections.back()).c_str(), getSectionName(programCoreSections[i]).c_str());
						programCoreSections[i].reloc = &relocSections.back();
					}
				}
			}
		}
	}

	int init(const char* input_elf_path, const char* output_rel_path) {
		inElfFd = open(input_elf_path, O_RDONLY);
		if(inElfFd == -1) {
			std::fprintf(stderr, "could not open input ELF file \"%s\": %s\n", input_elf_path, strerror(errno));
			return 1;
		}

		elf = elf_begin(inElfFd, ELF_C_READ, nullptr);
		if(elf == nullptr) {
			std::fprintf(stderr, "libelf elf_begin() failed: %s\n", elf_errmsg(elf_errno()));
			return 1;
		}

		// Make sure the input ELF is actually an ELF file
		if(elf_kind(elf) != ELF_K_ELF) {
			std::fprintf(stderr, "libelf doesn't recognize your input. Make sure you're pointing this to an actual ELF file\n");
			return 1;
		}

		// .. and that it's ELF32.
		elf_header = elf32_getehdr(elf);
		if(elf_header == nullptr) {
			std::fprintf(stderr, "Input ELF must be ELF32.\n");
			return 1;
		}

		// Do some checks to verify the ELF is applicable
		// (it's relocatable, MIPS, and has the e_flags that EE-GCC outputs)

		if(elf_header->e_type != ET_REL) {
			std::fprintf(stderr, "Input ELF must be relocatable.\n");
			return 1;
		}

		if(elf_header->e_machine != EM_MIPS && (elf_header->e_flags & 0x2092'0000) == 0) {
			std::fprintf(stderr, "Input ELF is not for the EE.\n");
			return 1;
		}

		if(elf_header->e_shstrndx == 0) {
			std::fprintf(stderr, "Input ELF does not have a .shstrtab\n");
			return 1;
		}

		// Once we've verified the input ELF is usable, create and open the output REL file.
		outRelFd = open(output_rel_path, O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP));
		if(outRelFd == -1) {
			std::fprintf(stderr, "could not open output \"%s\": %s\n", output_rel_path, strerror(errno));
			return 1;
		}

		// Destroy the original output. This makes sure that we
		// always end up writing new data to the file.
		ftruncate(outRelFd, 0);

		// initalize section data tables.
		initProgramCoreSections();
		initRelocationSections();
		return 0;
	}

	void initSectionHeaderFromInfo(SectionData& section) {
		rel::SectionHeader sh {};
		sh.size = section.shdr->sh_size;

		if(section.shdr->sh_flags & SHF_ALLOC) {
			sh.flags |= rel::kSection_Load;
			sh.loadAddress = section.shdr->sh_addr;
		}

		if(section.shdr->sh_type == SHT_NOBITS) {
			// This is the .bss section
			sh.flags = rel::kSection_AllocZeroed;
		}

		// This section has a relocation section.
		// For simplicity, we assume relocation entries are located
		// directly after a relocated section. This isn't ideal per se,
		// but should work. Which is all I really care about.
		if(section.reloc != nullptr) {
			sh.flags |= rel::kSection_Reloc;
			sh.relocationLink = sectionHeaders.size() + 1;
		}

		sectionHeaders.push_back(ExtendedSectionHeader {
		.sectionHeader = sh,
		.data = &section });

		if(section.reloc != nullptr) {
			// "recurse" and make the relocation section too
			// This honors the above expectation as well.
			initSectionHeaderFromInfo(*section.reloc);
		}
	}

	/// Does the actual relinking.
	int relinkBinary() {
		// Set up the module header.
		modhdr.magic = REL_MAGIC;
		modhdr.entrypoint = elf_header->e_entry;

		for(auto& pcs : programCoreSections) {
			initSectionHeaderFromInfo(pcs);
		}

		modhdr.nrSections = sectionHeaders.size();

		if(auto len = write(outRelFd, &modhdr, sizeof(modhdr)); len != sizeof(modhdr)) {
			std::fprintf(stderr, "Short write of module header (%zu, should be %zu)\n", len, sizeof(modhdr));
			return 1;
		}

		u32 offset = sizeof(modhdr) + (modhdr.nrSections * sizeof(rel::SectionHeader));

		for(auto& s : sectionHeaders) {
			if((s.sectionHeader.flags & rel::SectionFlags::kSection_AllocZeroed) == 0)
				s.sectionHeader.offset = offset;

			if(auto len = write(outRelFd, &s.sectionHeader, sizeof(s.sectionHeader)); len != sizeof(s.sectionHeader)) {
				std::fprintf(stderr, "Short write of section header (%zu, should be %zu)\n", len, sizeof(s.sectionHeader));
				return 1;
			}

			if((s.sectionHeader.flags & rel::SectionFlags::kSection_AllocZeroed) == 0)
				offset += s.sectionHeader.size;
		}

		for(auto& s : sectionHeaders) {
			lseek(outRelFd, s.sectionHeader.offset, SEEK_SET);
			if((s.sectionHeader.flags & rel::SectionFlags::kSection_AllocZeroed) == 0) {
				std::printf("writing section \"%s\" to rel\n", getSectionName(*s.data).c_str(), s.sectionHeader.offset);
				if(auto len = write(outRelFd, &reinterpret_cast<const char*>(s.data->data->d_buf)[0], s.sectionHeader.size); len != s.sectionHeader.size) {
					std::fprintf(stderr, "Short write of section data (%zu, should be %u)\n", len, s.sectionHeader.size);
					return 1;
				}
			}
		}

		return 0;
	}

   private:
	int inElfFd { -1 };
	int outRelFd { -1 };

	Elf* elf { nullptr };
	Elf32_Ehdr* elf_header;

	std::vector<SectionData> programCoreSections;
	std::vector<SectionData> relocSections;

	rel::ModuleHeader modhdr;
	std::vector<ExtendedSectionHeader> sectionHeaders;
};

int main(int argc, char** argv) {
	RelLinker linker;

	if(argc != 3) {
		std::fprintf(stderr, "usage: %s [input ELF file] [output REL file]\n", argv[0]);
		return 1;
	}

	// Initalize the rel linker.
	if(linker.init(argv[1], argv[2]) != 0) {
		return 1;
	}

	// Relink the ELF to a REL binary.
	linker.relinkBinary();
	return 0;
}