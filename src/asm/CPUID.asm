;This code detects CPUID
;Flipping a bit, copy it and if it stays flipped, CPUID is supported
DetectCPUID:
    pushfd              ;Push flags to stack
    pop eax             ;Pop value to eax

    mov ecx, eax        ;move eax into ecx (ecx now has the flag value)
    xor eax, 1 << 21    ;Flip eax

    push eax            ;push eax into stack
    popfd               ;Pop flags

    pushfd              ;Did it stay flipped?
    pop eax

    push ecx            ;Restore "old version" of flags
    popfd

    xor eax, ecx
    jz NoCPUID      ;If previous op is 0, CPUID is not supported
    ret

DetectLongMode:
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz NoLongMode
    ret

NoLongMode:
    hlt ;No Long Mode Support

NoCPUID:
    hlt ;No CPUID support, can't tell if we have long mode