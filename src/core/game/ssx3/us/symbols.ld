/* This linker script provides references for game symbols
   that we want the hook or rels to be able to use. 
   This script is intended to be shared so that we don't need to 
   write this out a billionty trillion times. */

/* These symbols are used in the primary linker script to put everything
   hopefully into the correct place. */

/* Original value of _end symbol/end of loaded ELF data
   before we came along to fuck that up */
ORIGINAL_END = 0x53f115;

/* Start address of the core; needs to be word-aligned
   (I guess 118 could be used but NO) */
CORE_LOAD_ADDRESS = 0x53f140;

/* libc */
memset = 0x00416210;
memcpy = 0x0041605c;

scePrintf = 0x00425c60;

/* Interesting globals */
SSXApp = 0x004a28a8;


/* cGame */
cGame_load = 0x0022ebc8;
cGame_purge = 0x0022fa98;
cGame_update = 0x002306b8;
cGame_render = 0x0022b008;

/* cFont */
text__5cFontffPCc = 0x00391cb0;

/* Memory */
memAlloc = 0x00317d70;
memFree = 0x00317e50;

/* REAL file functions */
FILE_loadat = 0x003e1b68;

/* BX REAL file functions */
BXFILE_size = 0x00317f98;

/* FILESYS_ */
FILESYS_getopts = 0x003de928;
FILESYS_setopts = 0x003de9b8;

/* ASYNCFILE_ */
ASYNCFILE_setcurrentpath = 0x003dde78;