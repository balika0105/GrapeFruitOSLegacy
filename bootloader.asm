[org 0x7c00]                            ;Sets the 'origin' of program (offset)

mov [BOOT_DISK], dl                     ;Moves the value of BOOT_DISK to dl


mov bp, 0x7c00                          ;Setting stack pointer, so program starts at 0x7c00
mov sp, bp

mov bx, BootLoaderSplash                ;Moves the address of 'BootLoaderSplash' into bx (bx can be used as a pointer of sorts)
call PrintString                        ;jumps to PrintString, this should make our lives easier

call ReadDisk							;calls ReadDisk Function


jmp PROGRAM_SPACE                       ;Jumps to the extended space thing

%include "print.asm"					;This should include our print thing
%include "DiskRead.asm"					;Include the DiskRead program code


times 510-($-$$) db 0

dw 0xaa55                               ;Signifies to BIOS that this code is a bootable one