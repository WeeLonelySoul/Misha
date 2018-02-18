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