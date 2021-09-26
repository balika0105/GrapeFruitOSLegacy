#include "include/TextPrint.hpp" //Our text printing thingy
#include "include/IDT.hpp"
#include "include/KBHandler.hpp"
#include "include/version.hpp"

extern const char Splash[];



//extern "C" is needed for linker script. It doesn't like C++
extern "C" void _start(){
    /*SetCursorPosition(PositionFromCoords(0,0));
    ClearScreen(BACKGROUND_GREEN | FOREGROUND_WHITE);
    PrintString("Screen cleared!");*/

    ClearScreen(BACKGROUND_BLUE | FOREGROUND_WHITE);
    PrintLn(Splash);
    PrintLn(OSVERSION);
    PrintLn("Testing grounds\n\r");

    //Actually loading stuff
    Print("Loading...");
    InitializeIDT();
    PrintLn("\n\rDone!");


    PrintLn("\n\rKeyboard input scancode test");

    MainKBHandler = KeyBoardHandler;
    return;
}