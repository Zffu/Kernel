[BITS 16]

section .text
	global e820_fetch

e820_fetch:
	push bx
	push si 

	mov si, 0
	mov ax, 0
	mov bx, 0
	mov dx, 0x534D     
	mov cx, 20

	mov di, di

	xor ax, ax

.e820_loop:
	mov ax, 0xE820         
	mov cx, 20
	int 0x15
	jc .err 

	cmp eax, 0x534D        
	jne .err

	add di, 20
	inc ax

	cmp bx, 0
	jne .more_entries

	jmp .done

.more_entries:
	cmp ax, cx
	jae .done

	jmp .e820_loop

.err:
	stc 
	pop si 
	pop bx
	ret

.done:
	clc
	pop si 
	pop bx
	ret