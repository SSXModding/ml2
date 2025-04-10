; Adjust the start of the heap so that we have enough space
; to store the core.

.ps2

; This portion adjusts the _end address beyond its original limit
; (to hold the ML2 Core), by patching the EE crt0.s directly. 
; Is this nasty? Probably. Does it work? Uhhh fuck idk man ask Harold he will know
.create "bin/ssx3/us/extend_end_address.bin",0x00100180
.org 0x00100180
    lui a0, hi(0x0053f2c8)
    lui a1, 0
    addiu a0, a0, lo(0x0053f2c8)
.close

