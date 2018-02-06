#include "../../libraries/bikka/time.h"
#include "../../libraries/bikka/low_level.h"
#include "../../libraries/bikka/isr.h"
#include "../../libraries/bikka/irq.h"

u32 tick = 0;

static void TIMER_CALLBACK(registers_t Regs){
    tick++;
    (void)(Regs);
}


void INIT_TIMER(u32 Freq){
    REGISTER_INTERRUPT_HANDLER(IRQ0, TIMER_CALLBACK);

    u32 Divisor = 1193180 / Freq;
    u8 Low = (u8)(Divisor & 0xFF);
    u8 High = (u8)((Divisor >> 8)& 0xFF);

    PORT_BYTE_OUT(0x43, 0x36);
    PORT_BYTE_OUT(0x40, Low);
    PORT_BYTE_OUT(0x40, High);
}