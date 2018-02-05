#include "../../libraries/bikka/isr.h"
#include "../../libraries/bikka/idt.h"
#include "../../libraries/bikka/irq.h"
#include "../../libraries/bikka/low_level.h"


isr_t InterruptHandler[256]; /* Global baby */

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

    SET_IDT_GATE(0, (u32)isr0);
    SET_IDT_GATE(1, (u32)isr1);
    SET_IDT_GATE(2, (u32)isr2);
    SET_IDT_GATE(3, (u32)isr3);
    SET_IDT_GATE(4, (u32)isr4);
    SET_IDT_GATE(5, (u32)isr5);
    SET_IDT_GATE(6, (u32)isr6);
    SET_IDT_GATE(7, (u32)isr7);
    SET_IDT_GATE(8, (u32)isr8);
    SET_IDT_GATE(9, (u32)isr9);
    SET_IDT_GATE(10, (u32)isr10);
    SET_IDT_GATE(11, (u32)isr11);
    SET_IDT_GATE(12, (u32)isr12);
    SET_IDT_GATE(13, (u32)isr13);
    SET_IDT_GATE(14, (u32)isr14);
    SET_IDT_GATE(15, (u32)isr15);
    SET_IDT_GATE(16, (u32)isr16);
    SET_IDT_GATE(17, (u32)isr17);
    SET_IDT_GATE(18, (u32)isr18);
    SET_IDT_GATE(19, (u32)isr19);
    SET_IDT_GATE(20, (u32)isr20);
    SET_IDT_GATE(21, (u32)isr21);
    SET_IDT_GATE(22, (u32)isr22);
    SET_IDT_GATE(23, (u32)isr23);
    SET_IDT_GATE(24, (u32)isr24);
    SET_IDT_GATE(25, (u32)isr25);
    SET_IDT_GATE(26, (u32)isr26);
    SET_IDT_GATE(27, (u32)isr27);
    SET_IDT_GATE(28, (u32)isr28);
    SET_IDT_GATE(29, (u32)isr29);
    SET_IDT_GATE(30, (u32)isr30);
    SET_IDT_GATE(31, (u32)isr31);    

    PORT_BYTE_OUT(0x20, 0x11);
    PORT_BYTE_OUT(0xA0, 0x11);
    PORT_BYTE_OUT(0x21, 0x20);
    PORT_BYTE_OUT(0xA1, 0x28);
    PORT_BYTE_OUT(0x21, 0x04);
    PORT_BYTE_OUT(0xA1, 0x02);
    PORT_BYTE_OUT(0x21, 0x01);
    PORT_BYTE_OUT(0xA1, 0x01);
    PORT_BYTE_OUT(0x21, 0x0);
    PORT_BYTE_OUT(0xA1, 0x0);

    SET_IDT_GATE(32, (u32)irq0);
    SET_IDT_GATE(33, (u32)irq1);
    SET_IDT_GATE(34, (u32)irq2);
    SET_IDT_GATE(35, (u32)irq3);
    SET_IDT_GATE(36, (u32)irq4);
    SET_IDT_GATE(37, (u32)irq5);
    SET_IDT_GATE(38, (u32)irq6);
    SET_IDT_GATE(39, (u32)irq7);
    SET_IDT_GATE(40, (u32)irq8);
    SET_IDT_GATE(41, (u32)irq9);
    SET_IDT_GATE(42, (u32)irq10);
    SET_IDT_GATE(43, (u32)irq11);
    SET_IDT_GATE(44, (u32)irq12);
    SET_IDT_GATE(45, (u32)irq13);
    SET_IDT_GATE(46, (u32)irq14);
    SET_IDT_GATE(47, (u32)irq15);

    /* And finally */
    SET_IDT(); 
}

void ISR_HANDLER(registers_t R){
    printf("received interrupt: ");
    char s[3];
    INT_TO_ASCII(R.int_no, s);
    printf(s);
    printf("\n");
    printf(exception_messages[R.int_no]);
    printf("\n");
}

void REGISTER_INTERRUPT_HANDLER(u8 N, isr_t Handler){
    InterruptHandler[N] = Handler;
}