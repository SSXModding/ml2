//! REL relinker. This expects a relocatable ELF file as the input,
//! and generates a REL file as the output.
//!
//! # Nits
//! - Rewrite to be a bit more modern C++.
#include <elf.h>
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

#include "diagman.hpp"
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

	/// Overrides ELF data if this is not empty.
	std::vector<uint8_t> overrideData;

	std::uint8_t* getData() {
		if(overrideData.empty())
			return static_cast<std::uint8_t*>(data->d_buf);
		return overrideData.data();
	}

	std::size_t getDataSize() {
		if(overrideData.empty())
			return data->d_size;
		return overrideData.size();
	}
};

struct ExtendedSectionHeader {
	rel::SectionHeader sectionHeader;
	SectionData* data;
};

rel::cDiagnosticMan gDiagMan("rellink");

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
		auto shstr = elf_getscn(elf, elf_header->e_shstrndx);
		auto shstr_data = elf_getdata(shstr, nullptr);
		return shstr_data;
	}

	std::string getSectionName(const SectionData& si) {
		return std::string(&static_cast<char*>(getShStrtab()->d_buf)[si.shdr->sh_name]);
	}

	std::string getSymbolName(const Elf32_Sym& sym) {
		auto* strtab = getSectionData(".strtab");
		if(!strtab)
			gDiagMan.emitFatalError("no .strtab in binary");
		return std::string(&static_cast<char*>(strtab->d_buf)[sym.st_name]);
	}

	Elf_Data* getSectionData(const std::string_view sectionName) {
		// this is not at all performant but this code should hopefully NEVER
		// EVER be hot. never.
		for(u32 i = 1; i < (elf_header->e_shnum); ++i) {
			auto scn = elf_getscn(elf, i);
			auto shdr = elf32_getshdr(scn);
			auto name = std::string(&static_cast<char*>(getShStrtab()->d_buf)[shdr->sh_name]);

			if(name == sectionName)
				return elf_rawdata(scn, nullptr);
		}

		return nullptr;
	}

	Elf32_Shdr* getSectionHeader(u32 sectionIndex) {
		return elf32_getshdr(elf_getscn(elf, sectionIndex));
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
		for(u32 i = 1; i < (elf_header->e_shnum); ++i) {
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

		for(u32 i = 1; i < (elf_header->e_shnum); ++i) {
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
			gDiagMan.emitError("could not open input ELF file \"%s\": %s", input_elf_path, strerror(errno));
			return 1;
		}

		elf = elf_begin(inElfFd, ELF_C_READ, nullptr);
		if(elf == nullptr) {
			gDiagMan.emitError("libelf elf_begin() failed: %s", elf_errmsg(elf_errno()));
			return 1;
		}

		// Make sure the input ELF is actually an ELF file
		if(elf_kind(elf) != ELF_K_ELF) {
			gDiagMan.emitError("libelf doesn't recognize your input. Make sure you're pointing this to an actual ELF file");
			return 1;
		}

		// .. and that it's ELF32.
		elf_header = elf32_getehdr(elf);
		if(elf_header == nullptr) {
			gDiagMan.emitError("Input ELF must be ELF32.");
			return 1;
		}

		// Do some checks to verify the ELF is applicable
		// (it's relocatable, MIPS, and has the e_flags that EE-GCC outputs)

		if(elf_header->e_type != ET_REL) {
			gDiagMan.emitError("Input ELF must be relocatable.");
			return 1;
		}

		if(elf_header->e_machine != EM_MIPS && (elf_header->e_flags & 0x2092'0000) == 0) {
			gDiagMan.emitError("Input ELF is not for the EE.");
			return 1;
		}

		if(elf_header->e_shstrndx == 0) {
			gDiagMan.emitError("Input ELF does not have a .shstrtab");
			return 1;
		}

		auto symtab = getSectionData(".symtab");

		if(!symtab) {
			// how the fuck do you even DO that? no like seriously
			gDiagMan.emitError("Input ELF does not have a symbol table??? What?");
			return 1;
		}

		elf_symbol_table = static_cast<Elf32_Sym*>(symtab->d_buf);
		elf_symbol_table_length = symtab->d_size / sizeof(Elf32_Sym);

		auto sectab = getSectionData(".symtab");

		if(!symtab) {
			// how the fuck do you even DO that? no like seriously
			gDiagMan.emitError("Input ELF does not have a symbol table??? What?");
			return 1;
		}

		elf_symbol_table = static_cast<Elf32_Sym*>(symtab->d_buf);
		elf_symbol_table_length = symtab->d_size / sizeof(Elf32_Sym);

		// Once we've verified the input ELF is usable, create and open the output REL file.
		outRelFd = open(output_rel_path, O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP));
		if(outRelFd == -1) {
			gDiagMan.emitFatalError("could not open output \"%s\": %s\n", output_rel_path, strerror(errno));
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
		sh.size = section.getDataSize();

		if(section.shdr->sh_flags & SHF_ALLOC) {
			sh.flags |= rel::kSection_Load;
			sh.loadAddress = section.shdr->sh_addr;
		}

		if(section.shdr->sh_type == SHT_NOBITS) {
			// This is the .bss section
			sh.flags |= rel::kSection_AllocZeroed;
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
			convertRelocation(*section.reloc);

			// "recurse" and make the relocation section too
			// This honors the above expectation as well.
			initSectionHeaderFromInfo(*section.reloc);
		}
	}

	/// Convert relocation information from depending on symbol table to
	/// a simpler structure based on the destination VMA address.
	void convertRelocation(SectionData& relocSection) {
		// ELF relocation table
		auto pElfRelocs = reinterpret_cast<Elf32_Rel*>(relocSection.data->d_buf);
		auto nElfRelocs = relocSection.data->d_size / sizeof(Elf32_Rel);

		// working buffer for converted REL relocations
		std::vector<rel::RelocationEntry> relocTemp;

		gDiagMan.emitWarning("TODO: Convert relocation information");

		for(auto i = 0; i < nElfRelocs; ++i) {
			if(ELF32_ST_TYPE(elf_symbol_table[ELF32_R_SYM(pElfRelocs[i].r_info)].st_info) != STT_SECTION) {
				gDiagMan.emitError("Unhandled non-local relocation. Please make sure the input ELF is fully linked.");
			}

			printf("Reloc %d: type ", i);
			switch(ELF32_R_TYPE(pElfRelocs[i].r_info)) {
#define REL_CASE(c)                                                                                                        \
	case c: {                                                                                                             \
		auto& sym = elf_symbol_table[(elf_header->e_shnum) + ELF32_R_SYM(pElfRelocs[i].r_info)];                            \
		auto st_index = sym.st_shndx;                                                                                     \
		auto* shdr = getSectionHeader(st_index); \
		printf(#c " target VMA %08x symbol %d (%s @ %08x)", pElfRelocs[i].r_offset, ELF32_R_SYM(pElfRelocs[i].r_info), getSymbolName(sym).c_str(), shdr->sh_addr + sym.st_value); \
	} break;
				REL_CASE(R_MIPS_32);
				REL_CASE(R_MIPS_26);
				REL_CASE(R_MIPS_HI16);
				REL_CASE(R_MIPS_LO16);
#undef REL_CASE
				default:
					gDiagMan.emitFatalError("unhandled relocation type 0x%08x", ELF32_R_TYPE(pElfRelocs[i].r_info));
			}

			printf("\n");
		}
	}

	/// Does the actual relinking.
	int relinkBinary() {
		// Set up the module header.
		modhdr.magic = REL_MAGIC;
		modhdr.entrypoint = elf_header->e_entry;

		// Create section data
		for(auto& pcs : programCoreSections) {
			initSectionHeaderFromInfo(pcs);
		}

		modhdr.nrSections = sectionHeaders.size();

		if(auto len = write(outRelFd, &modhdr, sizeof(modhdr)); len != sizeof(modhdr)) {
			gDiagMan.emitFatalError("Short write of module header (%zu, should be %zu)\n", len, sizeof(modhdr));
			return 1;
		}

		u32 offset = sizeof(modhdr) + (modhdr.nrSections * sizeof(rel::SectionHeader));

		for(auto& s : sectionHeaders) {
			if((s.sectionHeader.flags & rel::SectionFlags::kSection_AllocZeroed) == 0)
				s.sectionHeader.offset = offset;

			if(auto len = write(outRelFd, &s.sectionHeader, sizeof(s.sectionHeader)); len != sizeof(s.sectionHeader)) {
				gDiagMan.emitFatalError("Short write of section header (%zu, should be %zu)\n", len, sizeof(s.sectionHeader));
				return 1;
			}

			if((s.sectionHeader.flags & rel::SectionFlags::kSection_AllocZeroed) == 0)
				offset += s.sectionHeader.size;
		}

		for(auto& s : sectionHeaders) {
			lseek(outRelFd, s.sectionHeader.offset, SEEK_SET);
			if((s.sectionHeader.flags & rel::SectionFlags::kSection_AllocZeroed) == 0) {
				std::printf("writing section \"%s\" to rel\n", getSectionName(*s.data).c_str(), s.sectionHeader.offset);
				if(auto len = write(outRelFd, s.data->getData(), s.data->getDataSize()); len != s.data->getDataSize()) {
					gDiagMan.emitFatalError("Short write of section data (%zu, should be %u)\n", len, s.data->getDataSize());
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

	Elf32_Shdr* elf_section_table;
	std::size_t elf_section_table_length;

	Elf32_Sym* elf_symbol_table;
	std::size_t elf_symbol_table_length;

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