.ps2

.create "bin/ssxog/us/systeminit_patch.bin", 0x0018a7e0
.org 0x0018a7e0
patch:
    j MLSTART_ADDRESS
.close