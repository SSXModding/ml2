; Adjust the start of the heap so that we have enough space
; to store the core.

.ps2

.expfunc wordAlign(addr), (addr + 3) & 0xfffffffc
END_ADDRESS equ wordAlign(NEW_END_ADDRESS + 0x1000)

.create "bin/ssxog/us/libkernl_patch.bin",0x002a6a9c
.org 0x002a6a9c
    dw END_ADDRESS
.close

