#ifndef IDT_H
#define IDT_H 1

#define KERNEL_CS 0x08
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
void SET_IDT_GATE(int N, u32 Handler);
void SET_IDT(void);

#endif