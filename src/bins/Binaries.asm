;This assembly code will help us include binaries in our OS

;New macro, IncBin = Include Binaries, take 2 params
;Section for read-only data
;param 1 is global
%macro IncBin 2
    SECTION .rodata
    GLOBAL %1 

%1:
    incbin %2
    db 0
    %1_size: dq %1_size - %1 ;This will extract the size of the loaded binary
%endmacro

;IncBin Test, "test.txt"
IncBin Splash, "splash.txt"