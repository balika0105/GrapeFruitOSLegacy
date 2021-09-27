//Interrupt Descriptor Table
#pragma once
#include "Typedefs.hpp"
#include "IO.hpp"
#include "TextPrint.hpp"
#include "KBScanCode.hpp"

struct IDT64{
    uint_16 offset_low;
    uint_16 selector;
    uint_8 ist;
    uint_8 types_attr;
    uint_16 offset_mid;
    uint_32 offset_high;
    uint_32 zero;
};

extern IDT64 _idt[256];
extern uint_64 isr1;
extern "C" void LoadIDT();


void InitializeIDT(){
    /*for (uint_64 t = 0; t < 256; t++)
    {
        _idt[t].zero = 0;
        _idt[t].offset_low = (uint_16)(((uint_64)&isr1 & 0x000000000000FFFF));
        _idt[t].offset_mid = (uint_16)(((uint_64)&isr1 & 0x00000000FFFF0000) >> 16);
        _idt[t].offset_high = (uint_32)(((uint_64)&isr1 & 0xFFFFFFFF00000000) >> 32);
        _idt[t].ist = 0;
        _idt[t].selector = 0x08;
        _idt[t].types_attr = 0x8e;
    }*/

    _idt[1].zero = 0;
    _idt[1].offset_low = (uint_16)(((uint_64)&isr1 & 0x000000000000FFFF));
    _idt[1].offset_mid = (uint_16)(((uint_64)&isr1 & 0x00000000FFFF0000) >> 16);
    _idt[1].offset_high = (uint_32)(((uint_64)&isr1 & 0xFFFFFFFF00000000) >> 32);
    _idt[1].ist = 0;
    _idt[1].selector = 0x08;
    _idt[1].types_attr = 0x8e;

    RemapPIC();


    //Reprogramming the PIC chip
    outByte(0x21, 0xfd);
    outByte(0xa1, 0xff);
    LoadIDT();
    
}

void (*MainKBHandler)(uint_8 scanCode, uint_8 chr);

extern "C" void isr1_handler(){
    //ISR1 is for keyboard input, thus this function is dedicated to that
    uint_8 scanCode = inByte(0x60);
    uint_8 chr = 0;


    if(scanCode < 0x3A){
        //This part is a mess, the Lookup tables are hardcoded.
        //This is not optimal
        //Too bad

        //(will be fixed in a later update)


        //chr = ENUS_Querty::ScanCodeLookupTable[scanCode];
        chr = HU_Qwertz::ScanCodeLookupTable[scanCode];
    }
    if(MainKBHandler != 0){
        MainKBHandler(scanCode, chr);
    }


    //Signal PIC chip that interrupts are done
    outByte(0x20, 0x20);
    outByte(0xa0, 0x20);
}