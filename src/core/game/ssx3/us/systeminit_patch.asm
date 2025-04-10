
; This portion patches the end of the SSX3 systemInit() function to, instead of returning,
; call the ML2 Core start function. By this point, the function has initalized a number of things
; (including, half annoyingly, the file system), but it *also* has initalized the heap 
; and other fun things that the patched core blob can now use.

.ps2

.create "bin/ssx3/us/systeminit_patch.bin", 0x0031af74
.org 0x0031af74
patch:
    j 0x0053f140
.close