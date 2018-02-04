#include "../../libraries/bikka/video.h"
#include "../../libraries/common.h"

size_t _TerminalRow;
size_t _TerminalColumn;
uint8_t _TerminalColor;


volatile uint16_t *_TerminalBuffer;


void TERMINAL_INSTALL(void){
    /* Sets up and installs the terminal */
    _TerminalRow = 0;
    _TerminalColumn = 0;
    _TerminalColor = VGAEntryColor(COLOR_WHITE, COLOR_RED); /* Communist red, hehe */
    _TerminalBuffer = (uint16_t*) 0xB8000; /* Point the buffer to our video address */
    for (size_t Y_Axis = 0; Y_Axis < _VGAHeight; Y_Axis++){  /* Y_axis */
        for (size_t X_Axis = 0; X_Axis < _VGAWidth; X_Axis++){ /* X_axis */
            const size_t Index = ((Y_Axis * _VGAWidth) + X_Axis);
            _TerminalBuffer[Index] = VGAEntry(' ', _TerminalColor); /* Clean the screen and set the color */
        }
    }
}

void TERMINA_SET_COLOR(uint8_t Color){
    /* Just a function to set the global variable '_TerminalColor' */
    _TerminalColor = Color; /* Nice */
}

void TERMINAL_PUT_ENTRY_AT(char C, uint8_t Color, size_t X_Axis, size_t Y_Axis){
    /* Kinda the same as the above, this only sets the entry point for printing */
    const size_t Index = ((Y_Axis * _VGAWidth) + X_Axis);
    _TerminalBuffer[Index] = VGAEntry(C, Color);
}

void TERMINAL_PUT_CHAR(char Character){
    /* One of the 'core functions' used to print */
    TERMINAL_PUT_ENTRY_AT(Character, _TerminalColor, _TerminalColumn, _TerminalRow);
    if (++_TerminalColumn == _VGAWidth){
        _TerminalColumn = 0;
        if (++_TerminalRow == _VGAHeight){
            _TerminalRow = 0;
        }
    }
}

void TERMINAL_WRITE(const char *Data, size_t Size){
    /**/
    for (size_t i = 0; i < Size; i++){ TERMINAL_PUT_CHAR(Data[i]); }
}

void TERMINAL_WRITE_STRING(const char *Data){
    /**/
    TERMINAL_WRITE(Data, STRLEN(Data));
}