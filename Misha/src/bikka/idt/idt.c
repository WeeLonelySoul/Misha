#include "../../libraries/bikka/idt.h"
#include "../../libraries/common.h"
#include "../../libraries/bikka/isr.h"
#include "../../libraries/bikka/irq.h"
#include "../../libraries/bikka/memory.h"

void IDT_INSTALL(void){
    IDT_REG.limit = sizeof(idt_gate_t) * 256 - 1;
    IDT_REG.base = (u32)&IDT;

    memset(&IDT, 0, sizeof(idt_gate_t)*256);
    
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

    IDT_SET_GATE(0, (u32)isr0, 0x08, 0x8E);
    IDT_SET_GATE(1, (u32)isr1, 0x08, 0x8E);
    IDT_SET_GATE(2, (u32)isr2, 0x08, 0x8E);
    IDT_SET_GATE(3, (u32)isr3, 0x08, 0x8E);
    IDT_SET_GATE(4, (u32)isr4, 0x08, 0x8E);
    IDT_SET_GATE(5, (u32)isr5, 0x08, 0x8E);
    IDT_SET_GATE(6, (u32)isr6, 0x08, 0x8E);
    IDT_SET_GATE(7, (u32)isr7, 0x08, 0x8E);
    IDT_SET_GATE(8, (u32)isr8, 0x08, 0x8E);
    IDT_SET_GATE(9, (u32)isr9, 0x08, 0x8E);
    IDT_SET_GATE(10, (u32)isr10, 0x08, 0x8E);
    IDT_SET_GATE(11, (u32)isr11, 0x08, 0x8E);
    IDT_SET_GATE(12, (u32)isr12, 0x08, 0x8E);
    IDT_SET_GATE(13, (u32)isr13, 0x08, 0x8E);
    IDT_SET_GATE(14, (u32)isr14, 0x08, 0x8E);
    IDT_SET_GATE(15, (u32)isr15, 0x08, 0x8E);
    IDT_SET_GATE(16, (u32)isr16, 0x08, 0x8E);
    IDT_SET_GATE(17, (u32)isr17, 0x08, 0x8E);
    IDT_SET_GATE(18, (u32)isr18, 0x08, 0x8E);
    IDT_SET_GATE(19, (u32)isr19, 0x08, 0x8E);
    IDT_SET_GATE(20, (u32)isr20, 0x08, 0x8E);
    IDT_SET_GATE(21, (u32)isr21, 0x08, 0x8E);
    IDT_SET_GATE(22, (u32)isr22, 0x08, 0x8E);
    IDT_SET_GATE(23, (u32)isr23, 0x08, 0x8E);
    IDT_SET_GATE(24, (u32)isr24, 0x08, 0x8E);
    IDT_SET_GATE(25, (u32)isr25, 0x08, 0x8E);
    IDT_SET_GATE(26, (u32)isr26, 0x08, 0x8E);
    IDT_SET_GATE(27, (u32)isr27, 0x08, 0x8E);
    IDT_SET_GATE(28, (u32)isr28, 0x08, 0x8E);
    IDT_SET_GATE(29, (u32)isr29, 0x08, 0x8E);
    IDT_SET_GATE(30, (u32)isr30, 0x08, 0x8E);
    IDT_SET_GATE(31, (u32)isr31, 0x08, 0x8E);

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


void IDT_SET_GATE(int Num, u32 Base, u16 Sel, u8 Flags){
    IDT[Num].low_offset = Base & 0xFFFF;
    IDT[Num].high_offset = (Base >> 16) & 0xFFFF;
    IDT[Num].sel = Sel;
    IDT[Num].always0 = 0; /* Woooooooow */
    IDT[Num].flags = Flags | 0x60;
}