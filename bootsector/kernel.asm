[bits 32]
[extern main] ; Kernel main function, Originates from the C Kernel.
call main ; kernel startup
jmp $