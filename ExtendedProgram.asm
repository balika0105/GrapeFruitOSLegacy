jmp EnterProtectedMode

%include "gdt.asm"
%include "print.asm"


EnterProtectedMode:
	call EnableA20
	cli		;Disables interrupts
	lgdt [gdt_descriptor] ;Loads GDT (Global Descriptor Table)
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp codeseg:StartProtectedMode ;Far jump, flush CPU pipeline

EnableA20:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret


[bits 32]

%include "CPUID.asm"
%include "SimplePaging.asm"

StartProtectedMode:
	;Updating segment registers
	mov ax, dataseg
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax


	;mov [0xb8000], byte 'H'  ; Print an H to screen, increment address by 2 for each char
	call DetectCPUID
	call DetectLongMode
	call SetUpIdentityPaging
	call EditGDT
	jmp codeseg:Start64bit

;Starting a 64-bit function so the CPU will actually be in 64-bit mode
[bits 64]
[extern _start]
Start64bit:
	mov edi, 0xB8000			;Moving VIDMEM addr to destination reg
	mov rax, 0x1f201f201f201f20	;New register due to change to 64-bit mode
	mov ecx, 500
	rep stosq
	call _start
	jmp $

times 2048-($-$$) db 0