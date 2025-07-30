; Professional Bootloader with multi-sector reading capability
[org 0x7c00]
[bits 16]

; Constants
KERNEL_OFFSET equ 0x1000    ; Where we'll load the kernel in memory
KERNEL_SECTORS equ 32       ; Maximum number of sectors to read (adjustable)

; Initialize segments and stack
cli                         ; Disable interrupts
xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7c00
sti                         ; Enable interrupts

; Save boot drive number
mov [BOOT_DRIVE], dl

; Print boot message
mov si, MSG_BOOT
call print_string

; Load kernel from disk
call load_kernel

; Switch to protected mode
call switch_to_pm

; Error handler
disk_error:
    mov si, MSG_DISK_ERROR
    call print_string
    jmp $

; Load kernel routine
load_kernel:
    mov si, MSG_LOAD_KERNEL
    call print_string

    mov ah, 0x02           ; BIOS read sector function
    mov al, KERNEL_SECTORS ; Number of sectors to read
    mov ch, 0x00          ; Cylinder 0
    mov dh, 0x00          ; Head 0
    mov cl, 0x02          ; Start from sector 2
    mov dl, [BOOT_DRIVE]  ; Drive number
    mov bx, KERNEL_OFFSET ; Buffer to load into

    ; Attempt to read
    int 0x13
    jc disk_error         ; Jump if error (carry flag set)
    
    ; Compare sectors read
    cmp al, KERNEL_SECTORS
    jne disk_error
    ret

; Print string routine (SI = string pointer)
print_string:
    pusha
    mov ah, 0x0E          ; BIOS teletype output
.loop:
    lodsb                 ; Load next character
    test al, al           ; Check for null terminator
    jz .done
    int 0x10             ; Print character
    jmp .loop
.done:
    popa
    ret

; Switch to protected mode
switch_to_pm:
    cli                   ; Disable interrupts
    lgdt [gdt_descriptor] ; Load GDT

    ; Enable protected mode
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    ; Far jump to flush CPU pipeline
    jmp CODE_SEG:init_pm

[bits 32]
init_pm:
    ; Initialize segment registers for protected mode
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Set up stack
    mov ebp, 0x90000
    mov esp, ebp

    ; Jump to kernel
    jmp KERNEL_OFFSET

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

; Variables
BOOT_DRIVE: db 0

; Messages
MSG_BOOT db 'Booting...', 0
MSG_LOAD_KERNEL db 'Loading kernel...', 0
MSG_DISK_ERROR db 'Disk read error!', 0

; Padding and boot signature
times 510-($-$$) db 0
dw 0xAA55