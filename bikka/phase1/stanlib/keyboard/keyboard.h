#ifndef KEYBOARD_H
//#define static 
#define BACKSPACE 0x0e
#define ENTER 0x1c
#define SC_MAX 57
#include "../isr/isr.h"
#include "../common/function.h"
#endif 

// Global keyboard functions
static void KeyboardCallback(registers_t regs);
void InitKeyboard();