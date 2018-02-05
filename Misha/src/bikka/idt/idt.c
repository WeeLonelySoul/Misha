#include "../../libraries/bikka/idt.h"
#include "../../libraries/common.h"


void SET_IDT_GATE(int N, u32 Handler){
    IDT[N].low_offset = low_16(Handler);
    IDT[N].sel = KERNEL_CS;
    IDT[N].always0 = 0; /* Woooooooow */
    IDT[N].flags = 0x8E;
    IDT[N].high_offset = high_16(Handler);
}


void SET_IDT(void){
    IDT_REG.base = (u32) &IDT;
    IDT_REG.limit = IDT_ENTRIES * sizeof(idt_gate_t) -1;
    asm volatile("lidtl (%0)" : : "r" (&IDT_REG));
}