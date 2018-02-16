#ifndef IDT_H
#define IDT_H 1

#define IDT_ENTRIES 256

#include "../common.h"

typedef struct{
    u16 low_offset;
    u16 sel;
    u8 always0;
    u8 flags;
    u16 high_offset;
} __attribute__((packed)) idt_gate_t;

typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_registers_t;

idt_gate_t IDT[IDT_ENTRIES];
idt_registers_t IDT_REG;


/* Functions */
void IDT_SET_GATE(int Num, u32 Base, u16 Sel, u8 Flags);
void IDT_INSTALL(void);
extern void IDT_FLUSH(u32 IDT_PTR); /* Look in the idt.asm file */
#endif