#pragma once

// This file currently serves as the authorative source
// of information on the relutils .rel relocatable module format.

#include "types.hpp"

namespace rel {
#define REL_MAGIC  0x01'6d'6c'6d

	/// Flags for sections.
	enum SectionFlags : u32 {
		/// This section should be allocated and loaded as a part of the program core.
		/// Data is pressent in the rel file.
		kSection_Load = (1 << 0),

		/// This section should be allocated as a part of the program core,
		/// and initalized to all zeroes. No data is pressent in the .rel file.
		kSection_AllocZeroed = (1 << 1),

		/// This section provides relocation data for another section.
		/// [relocationLink] will contain a link to the section that this
		/// section will relocate. 
		kSection_Reloc = (1 << 2)
	};

	/// This is a simplified version of the relocation information
	/// Unlike ELF which relocates by symbol, we relocate by offset.
	struct RelocationEntry {
		u16 info; // r_info
		u32 offset;
		u32 targetValue;
	};

	struct SectionHeader {
		u32 flags; // flags
		u32 relocationLink;
		u32 loadAddress; // expected relative load address (or SEC_NOLOAD if section should not be loaded)
		u32 offset;		 // offset in rel file to section data
		u32 size;		 // size of section data (how large the program core should increase by)
	};

	struct ModuleHeader {
		u32 magic;		// 'mlm\x01', final byte acts as version byte
		u32 entrypoint; // module entrypoint
		u32 nrSections;
		// SectionHeader sections[nrSections];
	};

	/**
		Layout of a relinked .rel file

		| ModuleHeader |
		| SectionHeader[nrSections] |
		| section 0 data |
		| section 1 data |
		| section ... data |
	 **/

} // namespace relld