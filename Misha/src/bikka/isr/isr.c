#include "../../libraries/bikka/isr.h"
#include "../../libraries/bikka/idt.h"
#include "../../libraries/bikka/irq.h"
#include "../../libraries/bikka/low_level.h"


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

    IDT_SET_GATE(0, (u32)isr0);
    IDT_SET_GATE(1, (u32)isr1);
    IDT_SET_GATE(2, (u32)isr2);
    IDT_SET_GATE(3, (u32)isr3);
    IDT_SET_GATE(4, (u32)isr4);
    IDT_SET_GATE(5, (u32)isr5);
    IDT_SET_GATE(6, (u32)isr6);
    IDT_SET_GATE(7, (u32)isr7);
    IDT_SET_GATE(8, (u32)isr8);
    IDT_SET_GATE(9, (u32)isr9);
    IDT_SET_GATE(10, (u32)isr10);
    IDT_SET_GATE(11, (u32)isr11);
    IDT_SET_GATE(12, (u32)isr12);
    IDT_SET_GATE(13, (u32)isr13);
    IDT_SET_GATE(14, (u32)isr14);
    IDT_SET_GATE(15, (u32)isr15);
    IDT_SET_GATE(16, (u32)isr16);
    IDT_SET_GATE(17, (u32)isr17);
    IDT_SET_GATE(18, (u32)isr18);
    IDT_SET_GATE(19, (u32)isr19);
    IDT_SET_GATE(20, (u32)isr20);
    IDT_SET_GATE(21, (u32)isr21);
    IDT_SET_GATE(22, (u32)isr22);
    IDT_SET_GATE(23, (u32)isr23);
    IDT_SET_GATE(24, (u32)isr24);
    IDT_SET_GATE(25, (u32)isr25);
    IDT_SET_GATE(26, (u32)isr26);
    IDT_SET_GATE(27, (u32)isr27);
    IDT_SET_GATE(28, (u32)isr28);
    IDT_SET_GATE(29, (u32)isr29);
    IDT_SET_GATE(30, (u32)isr30);
    IDT_SET_GATE(31, (u32)isr31);    

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

    IDT_SET_GATE(32, (u32)irq0);
    IDT_SET_GATE(33, (u32)irq1);
    IDT_SET_GATE(34, (u32)irq2);
    IDT_SET_GATE(35, (u32)irq3);
    IDT_SET_GATE(36, (u32)irq4);
    IDT_SET_GATE(37, (u32)irq5);
    IDT_SET_GATE(38, (u32)irq6);
    IDT_SET_GATE(39, (u32)irq7);
    IDT_SET_GATE(40, (u32)irq8);
    IDT_SET_GATE(41, (u32)irq9);
    IDT_SET_GATE(42, (u32)irq10);
    IDT_SET_GATE(43, (u32)irq11);
    IDT_SET_GATE(44, (u32)irq12);
    IDT_SET_GATE(45, (u32)irq13);
    IDT_SET_GATE(46, (u32)irq14);
    IDT_SET_GATE(47, (u32)irq15);

    /* And finally */
    IDT_SET(); 
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