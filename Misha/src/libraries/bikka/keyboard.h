#ifndef KEYBOARD_H
#define KEYBOARD_H 1

#define BACKSPACE 0x0e
#define ENTER 0x1c
#define ServiceCodeMax 57


void KEYBOARD_CALLBACK(registers_t Regs);
void KEYBOARD_INIT(void);

#endif