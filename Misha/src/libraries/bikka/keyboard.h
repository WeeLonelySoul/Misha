#ifndef KEYBOARD_H
#define KEYBOARD_H 1

char KeyBuffer[256]; /* Buffer for the keyboard */
#define BACKSPACE 0x0e
#define ENTER 0x1c
#define ServiceCodeMax 57


static void KEYBOARD_CALLBACK(registers_t Regs);
void KEYBOARD_INIT(void);

#endif