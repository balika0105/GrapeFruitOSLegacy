;Used for interrupt descriptor table

[extern _idt]
idt_descriptor:
    dw 4095
    dq _idt

;pusha replacements, since pusha isn't available in 64-bit mode
%macro PUSHALL 0
    push rax
    push rcx
    push rdx
    push r8
    push r9
    push r10
    push r11
%endmacro

%macro POPALL 0
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rax
%endmacro

[extern isr1_handler]
isr1:
    PUSHALL
    ;Interrupt Service Routine 1
    call isr1_handler
    POPALL
    iretq ;Interrupt return Quad
    GLOBAL isr1

LoadIDT:
    lidt[idt_descriptor] ;Load IDT from IDT Descriptor
    sti ;Enable interrupts with IDT
    ret
    GLOBAL LoadIDT