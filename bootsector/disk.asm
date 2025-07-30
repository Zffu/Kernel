; load 'dh' sectors from drive 'dl' into ES:BX
disk_load:
    mov ah, 0x02
    mov al, 5
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80

    mov bx, 0x1000
    mov es, bx
    xor bx, bx

    int 0x13
    jc .fail
    ret

.fail:
    mov bx, fail_msg
    call print
    mov dh, ah ; ah = error code, dl = disk drive that dropped the error
    call print_hex ; check out the code at http://stanislavs.org/helppc/int_13-1.html


loading_msg db "Loading kernel...", 0
fail_msg    db "Disk read failed!", 0