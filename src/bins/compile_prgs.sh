#!/bin/bash
/usr/local/x86_64elfgcc/bin/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "gfsh.cpp" -o "prgs/gfsh.o"