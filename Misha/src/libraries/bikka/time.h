#ifndef TIME_H
#define TIME_H 1
#include "../../libraries/bikka/isr.h"


static void TIMER_CALLBACK(registers_t Regs);
void TIME_INIT(u32 Freq);

#endif