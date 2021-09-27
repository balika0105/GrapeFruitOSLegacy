#!/bin/bash
cd src

nasm bootloader.asm -f bin -o ../bin/bootloader.bin
nasm ExtendedProgram.asm -f elf64 -o ../bin/ExtendedProgram.o
cd bins
nasm Binaries.asm -f elf64 -o ../../bin/Binaries.o
cd ..

/usr/local/x86_64elfgcc/bin/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Kernel.cpp" -o "../bin/Kernel.o"

cd ../bin
ld -T"link.ld"

cat bootloader.bin kernel.bin > GrapeFruitOS.flp