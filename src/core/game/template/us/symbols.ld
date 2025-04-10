/* This linker script provides references for game symbols
   that we want the hook or rels to be able to use. 
   This script is intended to be shared so that we don't need to 
   write this out a billionty trillion times. */

/* These symbols are used in the primary linker script to put everything
   hopefully into the correct place. */
   
/* Original value of _end symbol/end of loaded ELF data
   before we came along to fuck that up
   Typically you can break around 0x00100190,
   a0 will be completed value of _end symbol */
ORIGINAL_END = [end address];

/* Start address of the core; needs to be word-aligned. */
CORE_LOAD_ADDRESS = [decided upon core load address];

/* Put game symbols in here for this particular region so you can idk access them? 
   or dont i'm not your dad */