PROGRAM_SPACE equ 0x7e00

ReadDisk:
	mov ah, 0x02
	mov bx, PROGRAM_SPACE	;Defines the program space for the BIOS
	mov al, 4				;Reads 4 sectors (512B)
	mov dl, [BOOT_DISK]		;Set drive
	mov ch, 0x00			;Cylinder 0
	mov dh, 0x00			;Head 0
	mov cl, 0x02			;Sector 2

	int 0x13				;BIOS interrupt for reading disk from these params

	jc DiskReadFailed
	ret

BOOT_DISK:
	db 0

DiskReadErrorString:
	db 'Disk Read Failed! Please reboot!', 0

DiskReadFailed:
	mov bx, DiskReadErrorString
	call PrintString

	jmp $