#include "TextPrint.cpp" //Our text printing thingy

//extern "C" is needed for linker script. It doesn't like C++
extern "C" void _start(){
    SetCursorPosition(PositionFromCoords(0,0));
    PrintString("Hello GrapeFruitOS!\n\n\rComing Soon!");
    return;
}