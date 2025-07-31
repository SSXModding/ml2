//! REL dumper. Mostly written for debugging purposes, but could be useful if expanded
//! (to also disassemble text sections. Do note that we don't currently mark that though)
#include <fcntl.h>
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

int main(int argc, char** argv) {
	if(argc != 2) {
		std::fprintf(stderr, "usage: %s [rel file]\n", argv[0]);
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		std::fprintf(stderr, "could not open input REL file \"%s\": %s\n", argv[1], strerror(errno));
		return 1;
	}

	rel::ModuleHeader header;
	std::vector<rel::SectionHeader> sections;

	if(auto len = read(fd, &header, sizeof(header)); len != sizeof(header)) {
		std::fprintf(stderr, "Failed to read header\n");
		return 1;
	}

	if(header.magic != REL_MAGIC) {
		std::fprintf(stderr, "This is not a REL file\n");
		return 1;
	}

	sections.resize(header.nrSections);
	if(auto len = read(fd, &sections[0], header.nrSections * sizeof(rel::SectionHeader)); len != header.nrSections * sizeof(rel::SectionHeader)) {
		std::printf("Short read of section table (%zu expected, got %zu)\n", header.nrSections * sizeof(rel::SectionHeader), len);
		return 1;
	}

	printf("rel file %s\n", argv[1]);
	printf("    %u sections\n", header.nrSections);
	printf("    entry 0x%08x\n", header.entrypoint);

	for(u32 i = 0; i < header.nrSections; ++i) {
		const auto& s = sections[i];
		std::string flags = "(none)";

		if(s.flags != 0) {
			flags = "";

			if((s.flags & rel::kSection_Load) != 0)
				flags += "load ";
			if((s.flags & rel::kSection_AllocZeroed) != 0)
				flags += "bss ";
			if((s.flags & rel::kSection_Reloc) != 0)
				flags += "reloc ";
		}

		printf("section #%d: ", i);
		printf("flags %s ", flags.c_str());
		printf("offset 0x%08x ", s.offset);
		printf("size 0x%08x ", s.size);

		if((s.flags & rel::kSection_Load) != 0 || (s.flags & rel::kSection_AllocZeroed) != 0 )
			printf("relative load address 0x%08x ", s.loadAddress);
		if((s.flags & rel::kSection_Reloc) != 0)
			printf("reloc section %d", s.relocationLink);

		printf("\n");
	}

	return 0;
}