#include "../../libraries/bikka/isr.h"
#include "../../libraries/bikka/irq.h"
#include "../../libraries/bikka/keyboard.h"
#include "../../libraries/bikka/video.h"
#include "../../libraries/bikka/low_level.h"
#include "../../libraries/bikka/shell.h"
#include "../../libraries/common.h"

char KeyBuffer[256]; /* Buffer for the keyboard */


const char *ServiceCodeName[] = {
    "Error",
    "Esc",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    "-",
    "=",
    "Backspace",
    "Tab",
    "Q",
    "W",
    "E",
    "R",
    "T",
    "Y",
    "U",
    "I",
    "O",
    "P",
    "[",
    "]",
    "Enter",
    "Lctrl",
    "A",
    "S",
    "D",
    "F",
    "G",
    "H",
    "J",
    "K",
    "L",
    ";",
    "'",
    "`",
    "LShift",
    "\\",
    "Z",
    "X",
    "C",
    "V",
    "B",
    "N",
    "M",
    ",",
    ".",
    "/",
    "RShift",
    "Keypad *",
    "LAlt",
    "Spacebar"
};

/* Keyboard layout */
const char ServiceCodeAscii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};


void KEYBOARD_CALLBACK(registers_t Regs){
    do{
        u8 ScanCode = PORT_BYTE_IN(0x60); /* Get the keyboard input */

        if (ScanCode > ServiceCodeMax){ printf("Error Scancode > ServiceCodeMax!"); return; }

        if (ScanCode == BACKSPACE){ BACKSPACE_(KeyBuffer); TERMINAL_BACKSPACE(); }

        else if (ScanCode == ENTER){
            printf("\n");
            INPUT(KeyBuffer);
            KeyBuffer[0] = '\0';

        }else{
            char Letter = ServiceCodeAscii[(int)ScanCode];
            char Str[2] = {Letter, '\0'};
            APPEND(KeyBuffer, Letter);
            printf(Str);
        }
        UNUSED(Regs);
    }while(1);
}

void KEYBOARD_INIT(void){ ISR_REGISTER_INTERRUPT_HANDLER(IRQ1, KEYBOARD_CALLBACK); }