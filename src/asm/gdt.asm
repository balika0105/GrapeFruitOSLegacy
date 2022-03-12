gdt_nulldesc:
    dd 0
    dd 0

gdt_codedesc:
    dw 0xFFFF       ;GDT LIMIT
    dw 0x0000       ;GDT base (low)
    db 0x00         ;GDT base (medium)
    db 10011010b    ;ACCESS BYTE (valid, kernel priv., readable)
    db 11001111b    ;FLAGS and upper limit
    db 0x00         ;base (high)

gdt_datadesc:
    dw 0xFFFF       ;GDT LIMIT
    dw 0x0000       ;GDT base (low)
    db 0x00         ;GDT BASE (medium)
    db 10010010b    ;ACCESS BYTE (valid, kernel priv., readable)
    db 11001111b    ;FLAGS and upper limit
    db 0x00         ;base (high)

gdt_end:

gdt_descriptor:
    gdt_size:
        dw gdt_end - gdt_nulldesc - 1
        dq gdt_nulldesc

;Defining constants
codeseg equ gdt_codedesc - gdt_nulldesc
dataseg equ gdt_datadesc - gdt_nulldesc


[bits 32]
;This should edit our GDT to be 64-bit
EditGDT:
    mov [gdt_codedesc + 6], byte 10101111b
    mov [gdt_datadesc + 6], byte 10101111b
    ret

[bits 16]