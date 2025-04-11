; Adjust the start of the heap so that we have enough space
; to store the core.

.ps2

.expfunc wordAlign(addr), (addr + 3) & 0xfffffffc
END_ADDRESS equ wordAlign(NEW_END_ADDRESS + 0x1000)

.create "bin/ssx3/us/libkernl_extend_heap.bin",0x0045516c
.org 0x0045516c
    dw END_ADDRESS
.close

