#pragma once
#include "TextPrint.hpp"
#include "Typedefs.hpp"

bool LeftShiftHeld = false;
bool RightShiftHeld = false;

uint_8 LastScanCode;

void StdKeyBoardHandler(uint_8 scanCode, uint_8 chr){
    if(chr != 0){
        switch (LeftShiftHeld | RightShiftHeld)
        {
        case true:
            Print(chr - 32);
            break;

        case false:
            Print(chr);
            break;
        }
    }
    else{
        switch (scanCode)
        {
        case 0x8E:
            //Backspace
            SetCursorPosition(CursorPosition - 1);
            Print(' ');
            SetCursorPosition(CursorPosition - 1);
            break;
        
        case 0x2A:
            //Left Shift Held
            LeftShiftHeld = true;
            break;

        case 0xAA:
            //Left Shift Released
            LeftShiftHeld = false;
            break;

        case 0x36:
            //Right Shift Held
            RightShiftHeld = true;
            break;

        case 0xB6:
            //Right Shift Released
            RightShiftHeld = false;
            break;

        case 0x9C:
            //Return key
            PrintLn();
            break;
        }
    }
}

void E0Handler(uint_8 scanCode){
    switch(scanCode){
        case 0x50:
            //Up arrow "suffix"
            SetCursorPosition(CursorPosition + VGA_WIDTH);
            break;

        case 0x48:
            //Down arrow "suffix"
            SetCursorPosition(CursorPosition - VGA_WIDTH);
            break;

        case 0x4b:
            //Left arrow "suffix"
            CursorPosition-=CursorPosition;
            break;

        case 0x4d:
            //Right arrow "suffix"
            CursorPosition+=CursorPosition;
            break;

        default:
            break;
    }
}

void KeyBoardHandler(uint_8 scanCode, uint_8 chr){
    
    switch(LastScanCode){
        case 0xE0:
            //Arrow "prefix"
            E0Handler(scanCode);
            break;
        default:
            StdKeyBoardHandler(scanCode, chr);
        break;
    }
    LastScanCode = scanCode;
}