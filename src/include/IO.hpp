#pragma once
#include "Typedefs.hpp"

//PIC Chip commands
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

//Initializing PIC chips
//Initialization Control Word
#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

void outByte(unsigned short port, unsigned char val){
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

unsigned char inByte(unsigned short port){
    unsigned char returnVal;
    asm volatile ("inb %1, %0":"=a"(returnVal) : "Nd"(port));
    return returnVal;
}

void RemapPIC(){
    //For storing PIC masks
    uint_8 a1, a2;

    a1=inByte(PIC1_DATA);
    a2=inByte(PIC2_DATA);

    //Start the initialization procedure
    outByte(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outByte(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    //Setting up PIC offsets
    outByte(PIC1_DATA, 0);
    outByte(PIC2_DATA, 8);
    outByte(PIC1_DATA, 4);
    outByte(PIC2_DATA, 2);

    outByte(PIC1_DATA, ICW4_8086);
    outByte(PIC2_DATA, ICW4_8086);

    //Restore stored PIC masks
    outByte(PIC1_DATA, a1);
    outByte(PIC2_DATA, a2);
}