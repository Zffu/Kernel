; Global Descriptor Table
gdt_start:
    dq 0x0000000000000000 ; Null descriptor

gdt_code:
    dw 0xFFFF             ; Limit (bits 0-15)
    dw 0x0000             ; Base (bits 0-15)
    db 0x00               ; Base (bits 16-23)
    db 10011010b          ; Flags
    db 11001111b          ; Flags + Limit (bits 16-19)
    db 0x00               ; Base (bits 24-31)

gdt_data:
    dw 0xFFFF             ; Limit (bits 0-15)
    dw 0x0000             ; Base (bits 0-15)
    db 0x00               ; Base (bits 16-23)
    db 10010010b          ; Flags
    db 11001111b          ; Flags + Limit (bits 16-19)
    db 0x00               ; Base (bits 24-31)

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; GDT size
    dd gdt_start               ; GDT address

; Constants
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start