#pragma once
#include "IO.cpp"
#include "Typedefs.cpp"
#define VGA_MEMORY (unsigned char*)0xB8000 //Hard-coding our VGA memory
#define VGA_WIDTH 80 //Setting up screen width

uint_16 CursorPosition;


void SetCursorPosition(uint_16 position){
    //Initialization
    outByte(0x3D4, 0x0F);
    outByte(0x3D5, (unsigned char)(position & 0xFF));
    outByte(0x3D4, 0x0E);
    outByte(0x3D5, (unsigned char)((position >> 8) & 0xFF));
    //This part keeps the cursor from running out of bounds
    if(CursorPosition > 2000)
        CursorPosition = 2000;
    if(CursorPosition < 2000)
        CursorPosition=0;
    else
        CursorPosition = position;
}

uint_16 PositionFromCoords(uint_8 x, uint_8 y){
    //This code will return a value which helps us set the cursor based on coordinates
    return y*VGA_WIDTH+x;
}

void PrintString(const char* string){
    //Our printer function
    uint_8* charPtr = (uint_8*)string;
    uint_16 index = CursorPosition;
    while(*charPtr != 0){
        //Implementing newline and carriage return
        switch (*charPtr){
            case 10:
                //Newline
                index+=VGA_WIDTH;
            break;

            case 13:
                //CR
                index -= index % VGA_WIDTH;
            break;
            

            default:
                *(VGA_MEMORY + index * 2) = *charPtr;
                index++;
                break;

        }
        
        charPtr++;
    }

    SetCursorPosition(index);
}