# GrapeFruit OS Legacy

Project started by Balázs György Markgruber as a hobby OS, based on [AbsurdPoncho](https://github.com/AbsurdPoncho)'s [tutorial series](https://www.youtube.com/playlist?list=PLxN4E629pPnKKqYsNVXpmCza8l0Jb6l8-)

This OS aims to implement some crucial functions that will make it usable as a daily driver eventually.

### This repo contains the source code for GrapeFruit OS to be booted on BIOS/"Legacy Boot" machines

- Kernel source code
- Bootloader source code
- Compilation/linker scripts
- Environment setup script

------

### Bochs instructions

*This software can only be run in a Bochs Emulator at the moment*

*Setup instructions are as follows*

- Bootable media setup
    - Disk Options -> First Floppy Drive
    - 5.25" 1.2M
    - File: GrapeFruitOS.flp
    - Type: 1.2M
    - No write-protection
    - Inserted
- Optional
    - Set VGA Refresh frequency to 60

**NOTE:** On Linux hosts, you have to type in "continue" when it gives you a `<bochs:1> ` prompt
