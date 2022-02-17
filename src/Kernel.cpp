#include "include/TextPrint.hpp" //Our text printing thingy
#include "include/IDT.hpp"
#include "include/KBHandler.hpp"
#include "include/version.hpp"


extern const char Splash[];
//extern const void* Shell;

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

    PrintLn("Keyboard INIT");

    MainKBHandler = KeyBoardHandler;

    PrintLn("\n\rDone!");
    //Loading stuff DONE

    //Shell;

    return;
}