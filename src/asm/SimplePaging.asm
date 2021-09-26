;This program will set up Memory Paging as "identity paging"

;Page Table Entry macro
PageTableEntry equ 0x1000

SetUpIdentityPaging:
    mov edi, PageTableEntry ;destination index
    mov cr3, edi            ;move destination index to control register 3 -> tells MMU the page table addr

    ;Creating first 3 entries
    mov dword [edi], 0x2003
    add edi, 0x1000

    mov dword [edi], 0x3003
    add edi, 0x1000

    mov dword [edi], 0x4003
    add edi, 0x1000


    ;Last part: 512 entries
    mov ebx, 0x00000003
    mov ecx, 512

    .SetEntry:
        mov dword [edi], ebx
        add ebx, 0x1000
        add edi, 8
        loop .SetEntry

    ;Activate physical address extension paging
    mov eax, cr4
    or eax, 1<<5
    mov cr4, eax

    ;Set long-mode bit in EFER module-specific reg
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1<<8
    wrmsr

    ;Enable paging
    mov eax, cr0
    or eax, 1<<31
    mov cr0, eax

ret
;Paging should be set up