# Documentation for GrapeFruit OS (Legacy Boot)

This code is meant for internal use. Project based on AbsurdPoncho's tutorial series, wiki.osdev.org will most likely expand it

IMPORTANT: This OS will only run on x86-64 machines, which support CPUID and Long Mode

### How the Bootloading procedure works:

1. bootloader.asm: Initializes BIOS, it contains code to make the BIOS detect that we have a bootable media
2. bootloader.asm calls DiskRead.asm, which reads more sectors of the disk, which contains the "ExtendedProgram"

ExtendedProgram will handle further operations
3. Enable A20
4. Enter 32-bit protected mode
5. Detect CPUID support     -> halt if fails
6. Detect Long Mode support -> halt if fails
7. Enable paging; physical memory will be identically mapped to virtual memory

Memory mapping table will reside in memory between the bootloader and the kernel

## Functions defined in kernel
- Print()
    - Print("blah") : Prints "blah" to screen
    - Print("blah", BACKGROUND | FOREGROUND): Will print text with set colors

- PrintLn()
    - PrintLn() : Prints an empty line
    - PrintLn("blah") : Prints "blah", adds newline and carriage return
    - PrintLn("blah", BACKGROUND | FOREGROUND): Prints "blah" with specified colors, adds newline and carriage return

- ClearScreen()
    - ClearScreen() : Clears screen and sets colors to BACKGROUND_BLACK, FOREGROUND_WHITE
    - ClearScreen(BACKGROUND | FOREGROUND) : Clears screen and sets colors defined

*For colors, see include/TextModeColorCodes.cpp*