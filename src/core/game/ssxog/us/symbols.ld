/* This linker script provides references for game symbols
   that we want the hook or rels to be able to use. 
   This script is intended to be shared so that we don't need to 
   write this out a billionty trillion times. */

/* These symbols are used in the primary linker script to put everything
   hopefully into the correct place. */

/* Original value of _end symbol/end of loaded ELF data
   before we came along to fuck that up */
ORIGINAL_END = 0x002D8807;

/* Start address of the core; needs to be word-aligned */
CORE_LOAD_ADDRESS = 0x002d8900;

/* libc */
memset = 0x0023bbd0;
memcpy = 0x0023bac0;
strcmp = 0x0025baa0;

/* REAL Memory */
MEM_alloc = 0x0023a448;
MEM_free = 0x0023a998;