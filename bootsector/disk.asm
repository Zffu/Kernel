disk_load:
	pusha

	; Backup dx
	push dx
	
	mov ah, 0x02
	mov ah, dh
	mov cl, 0x02
	
	mov ch, 0x00

	mov dh, 0x00

	int 0x13
	jc disk_err

	pop dx
	cmp al, dh
	jne sector_err
	popa 
	ret

; TODO: Add logging error here
disk_err:
	jmp disk_loop

; TODO: Add logging error here
sector_err:
	ret

disk_loop:
	jmp $