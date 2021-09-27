#pragma once
#include "IO.hpp"
#include "Typedefs.hpp"
#include "TextModeColorCodes.hpp"

#define VGA_MEMORY (unsigned char*)0xB8000 //Hard-coding our VGA memory
#define VGA_WIDTH 80 //Setting up screen width

uint_16 CursorPosition;
uint_64 CurrentColor = BACKGROUND_BLACK | FOREGROUND_WHITE;




void SetCursorPosition(uint_16 position){
    //Initialization
    outByte(0x3D4, 0x0F);
    outByte(0x3D5, (unsigned char)(position & 0xFF));
    outByte(0x3D4, 0x0E);
    outByte(0x3D5, (unsigned char)((position >> 8) & 0xFF));
    //This part keeps the cursor from running out of bounds
    if(CursorPosition > 2000)
        CursorPosition = 2000;
    if(CursorPosition < 0)
        CursorPosition=0;
    else
        CursorPosition = position;
}

uint_16 PositionFromCoords(uint_8 x, uint_8 y){
    //This code will return a value which helps us set the cursor based on coordinates
    return y*VGA_WIDTH+x;
}

void Print(const char* string, uint_8 color = CurrentColor){
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
                *(VGA_MEMORY + index * 2 + 1) = color;
                index++;
                break;

        }
        
        charPtr++;
    }

    SetCursorPosition(index);
}

void PrintLn(const char* string, uint_8 color = CurrentColor){
    Print(string, color);
    Print("\n\r", color);
}

void PrintLn(){
    //This version of the function is used when you want to print and empty line
    Print("\n\r", CurrentColor);
}

//This section is for printing chars
void Print(char chr, uint_8 color = CurrentColor){

    *(VGA_MEMORY + CursorPosition * 2) = chr;
    *(VGA_MEMORY + CursorPosition * 2 + 1) = color;
    SetCursorPosition(CursorPosition + 1);
}
void PrintLn(char chr, uint_8 color = CurrentColor){
    Print(chr, color);
    PrintLn();
}

char hexToStringOutput[128];
template<typename T>
const char* HexToString(T value){
    T* valPtr = &value;
    uint_8* ptr;
    uint_8 temp; //Used for extracting values
    uint_8 size = (sizeof(T)) * 2 - 1;
    uint_8 i;
    for (i = 0; i < size; i++)
    {
        ptr = ((uint_8*)valPtr + i);

        //First part of the hex value
        temp = ((*ptr & 0xF0) >> 4);
        hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48); //Converting hex value to ASCII

        //Second part of the hex value
        temp = ((*ptr & 0x0F));
        hexToStringOutput[size - (i * 2)] = temp + (temp > 9 ? 55 : 48); //Converting hex value to ASCII
    }
    hexToStringOutput[size + 1] = 0;
    return hexToStringOutput;
}

char intToString[128];
template<typename T>
const char* IntToString(T value){
    //This function helps us putting decimal values to the screen
    uint_8 size = 0;
    uint_8 isNegative = 0;

    if(value < 0){
        isNegative = 1;
        value *= -1;
        intToString[0] = '-';
    }

    uint_64 sizeTester = (uint_64)value;
    while(sizeTester / 10 > 0){
        sizeTester /= 10;
        size++;
    }

    uint_8 index = 0;
    //Casting our value into an unsigned 64-bit int
    uint_64 newValue = (uint_64)value;
    while(newValue / 10 > 0){
        uint_8 remainder = newValue % 10;
        newValue /= 10;
        intToString[isNegative + size - index] = remainder + 48; // +48 is needed to get the right ascii value
        index++;
    }

    uint_8 remainder = newValue % 10;
    intToString[isNegative + size - index] = remainder + 48;
    intToString[isNegative + size + 1] = 0; //Null-terminating string
    return intToString;
}

void ClearScreen(uint_64 ClearColor = BACKGROUND_BLACK | FOREGROUND_WHITE){
    uint_64 value = 0;
    value += ClearColor << 8;
    value += ClearColor << 24;
    value += ClearColor << 40;
    value += ClearColor << 56;

    for(uint_64* i = (uint_64*)VGA_MEMORY; i < (uint_64*)(VGA_MEMORY + 4000); i++) //VGA_MEMORY+4000 = size of vram
    {
        *i = value;
    }
    CurrentColor = ClearColor;
    SetCursorPosition(PositionFromCoords(0,0));
}