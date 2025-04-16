; Adjust the start of the heap so that we have enough space
; to store the core.

.ps2

.expfunc wordAlign(addr), (addr + 3) & 0xfffffffc
END_ADDRESS equ wordAlign(NEW_END_ADDRESS + 0x1000)

; This portion adjusts the _end address beyond its original limit
; (to hold the ML2 Core), by patching the EE crt0.s directly. 
; Is this nasty? Probably. Does it work? Uhhh fuck idk man ask Harold he will know
.create "bin/ssxog/us/crt0_patch.bin",0x00100068
.org 0x00100068
    lui a0, hi(END_ADDRESS)
    lui a1, 0
    addiu a0, a0, lo(END_ADDRESS)
.close

