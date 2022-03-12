PrintString:
    mov ah, 0x0e                        ;"Magic Number" into ah
    .Loop:
    cmp [bx], byte 0                    ;If value at bx is 0
    je .Exit                            ;Jump to .Exit if value is equal to 0
        mov al, [bx]                    ;Move value of bx into al
        int 0x10                        ;Print interrupt
        inc bx                          ;Increment the address of bx
        jmp .Loop                       ;Jump back to .Loop
    .Exit:
    ret

BootLoaderSplash:
    db 'GrapeFruit OS Legacy Bootloader ', 0        ;Defined message

TestString:
    db 'This is a test string',0        ;Defined message