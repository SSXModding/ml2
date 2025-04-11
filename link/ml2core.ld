
SECTIONS {
	/* Include symbols. */
	#include "symbols.ld"

	. = CORE_LOAD_ADDRESS;
	_begin = CORE_LOAD_ADDRESS;

	.text CORE_LOAD_ADDRESS : {
		*(.text)
		*(.text.*)
    	*(.gnu.linkonce.t*)
	}

	.ctors : {
		KEEP (*crtbegin.o(.ctors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
	    KEEP (*(SORT(.ctors.*)))
		KEEP (*(.ctors))	
	}
	
  	.dtors : {
		KEEP (*crtbegin.o(.dtors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
		KEEP (*(SORT(.dtors.*)))
		KEEP (*(.dtors))
  	}

	/DISCARD/ : {
		/* Ignore .reginfo. It is not needed and adds bloat */
		*(.reginfo)
	}

	.data : { 
		*(.data)
	    	*(.data.*)
    		*(.gnu.linkonce.d*)
	 }
	.rodata : {
		*(.rodata)
		*(.rodata.*)
		*(.gnu.linkonce.r*)
	}
	.rdata : { *(.rdata) }
	.lit8 : { *(.lit8) }
	.lit4 : { *(.lit4) }
	.sdata : { *(.sdata) }
	.sbss : { _fbss = .; *(.sbss) *(.scommon) }
	.bss : { *(.bss) }

	_end = .;
}
