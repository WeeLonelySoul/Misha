#include "../../libraries/bikka/isr.h"
#include "../../libraries/bikka/idt.h"
#include "../../libraries/bikka/irq.h"
#include "../../libraries/bikka/low_level.h"
#include "../../libraries/bikka/video.h"
#include "../../libraries/bikka/keyboard.h"
#include "../../libraries/bikka/time.h"
#include "../../libraries/bikka/memory.h"



isr_t InterruptHandler[256];

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void ISR_INSTALL(void){
    /* Install our ISRs 
        This code makes me wanna puke. but I'm not changing it now and dooming the future me (5/2/2018)

    */

    /* Remap */
    PORT_WORD_OUT(0x20, 0x11);
    PORT_WORD_OUT(0xA0, 0x11);
    PORT_WORD_OUT(0x21, 0x20);
    PORT_WORD_OUT(0xA1, 0x28);
    PORT_WORD_OUT(0x21, 0x04);
    PORT_WORD_OUT(0xA1, 0x02);
    PORT_WORD_OUT(0x21, 0x01);
    PORT_WORD_OUT(0xA1, 0x01);
    PORT_WORD_OUT(0x21, 0x0);
    PORT_WORD_OUT(0xA1, 0x0);

    IDT_SET_GATE(32, (u32)irq0, 0x08, 0x8E);
    IDT_SET_GATE(33, (u32)irq1, 0x08, 0x8E);
    IDT_SET_GATE(34, (u32)irq2, 0x08, 0x8E);
    IDT_SET_GATE(35, (u32)irq3, 0x08, 0x8E);
    IDT_SET_GATE(36, (u32)irq4, 0x08, 0x8E);
    IDT_SET_GATE(37, (u32)irq5, 0x08, 0x8E);
    IDT_SET_GATE(38, (u32)irq6, 0x08, 0x8E);
    IDT_SET_GATE(39, (u32)irq7, 0x08, 0x8E);
    IDT_SET_GATE(40, (u32)irq8, 0x08, 0x8E);
    IDT_SET_GATE(41, (u32)irq9, 0x08, 0x8E);
    IDT_SET_GATE(42, (u32)irq10, 0x08, 0x8E);
    IDT_SET_GATE(43, (u32)irq11, 0x08, 0x8E);
    IDT_SET_GATE(44, (u32)irq12, 0x08, 0x8E);
    IDT_SET_GATE(45, (u32)irq13, 0x08, 0x8E);
    IDT_SET_GATE(46, (u32)irq14, 0x08, 0x8E);
    IDT_SET_GATE(47, (u32)irq15, 0x08, 0x8E);

    IDT_FLUSH((u32)&IDT_REG);
}

void ISR_HANDLER(registers_t R){
    printf("\n\nError Received interrupt: ");
    char s[3];
    INT_TO_ASCII(R.int_no, s);
    printf(s);
    printf("\n");
    printf(exception_messages[R.int_no]);
    printf("\n");
}

void ISR_REGISTER_INTERRUPT_HANDLER(u8 N, isr_t Handler){
    InterruptHandler[N] = Handler;
}