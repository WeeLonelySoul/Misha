#include "../../libraries/bikka/tss.h"
#include "../../libraries/bikka/gdt.h"
#include "../../libraries/bikka/memory.h"
#include "../../libraries/common.h"

tss_entry_t tss_entry_;

void TSS_WRITE(s32 Num, u16 SS0, u32 Esp0){
    u32 Base = (u32) &tss_entry_;
    u32 Limit = Base + sizeof(tss_entry_);

    GDT_SET_ENTRY(Num, Base, Limit, 0xE9, 0x00);
    memset(&tss_entry_, 0, sizeof(tss_entry_));
    tss_entry_.ss0 = SS0;
    tss_entry_.esp0 = Esp0;

    tss_entry_.cs = 0x0b;
    /* What even is this */
    tss_entry_.ss = tss_entry_.ds = tss_entry_.es = tss_entry_.fs = tss_entry_.gs = 0x13; 
}

void BIKKA_SET_KERNEL_STACK(u32 Stack){
    tss_entry_.esp0 = Stack;
}