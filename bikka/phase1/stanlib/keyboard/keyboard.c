#include "keyboard.h"
#include "../common/common.h"
#include "../isr/isr.h"

char KeyBuffer[256];

const char *SCName[] = {
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
    "Spacebar",
    "Ö",
    "Ä",
    "Å"};

// Keyboard layout
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void KeyboardCallback(registers_t regs){
    u8 ScanCode = port_byte_in(0x60);

    if (ScanCode > SC_MAX){
        return;
    }
    if (ScanCode == BACKSPACE){
        backspace(KeyBuffer);
        Backspace();
    }else if (ScanCode == ENTER){
        Say("\n");
        Input(KeyBuffer, 0,0);
        KeyBuffer[0] = '\0';
    }else{
        char Letter = sc_ascii[(int)ScanCode];
        char Str[2] = {Letter, '\0'};
        Append(KeyBuffer, Letter);
        Say(Str);
    }
    UNUSED(regs);
}

void InitKeyboard(){
    register_interrupt_handler(IRQ1, KeyboardCallback);
}