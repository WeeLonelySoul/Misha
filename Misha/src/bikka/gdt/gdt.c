#include "../../libraries/bikka/gdt.h"
#include "../../libraries/bikka/tss.h"
#include "../../libraries/bikka/memory.h"

gdt_entry_t GDT_ENTRIES[6]; /* This is the amount of GDT_SET_ENTRY below */
gdt_ptr_t GDT_PTR;
/*
GDT, IRQ and IDE are things that quite quickly go out of hand
Therefore I recommend James Malloy's tutorial on this
-> http://www.jamesmolloy.co.uk/tutorial_html/
*/

void GDT_INSTALL(void){
    /* Install the Global Descriptor Table */
    GDT_PTR.limit = (sizeof(gdt_entry_t) * 6) -1; 
    GDT_PTR.base = (u32)&GDT_ENTRIES;

    GDT_SET_ENTRY(0, 0, 0, 0, 0); /* Null segment */
    GDT_SET_ENTRY(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
    GDT_SET_ENTRY(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
    GDT_SET_ENTRY(4, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User mode code segment */
    GDT_SET_ENTRY(5, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User mode data segment */
    TSS_WRITE(5, 0x10, 0x0); /* Sets the TSS segment */

    GDT_FLUSH((u32)&GDT_PTR);
    TSS_FLUSH();
}


void GDT_SET_ENTRY(s32 Index, u32 Base, u32 Limit, u8 Access, u8 Gran){

    GDT_ENTRIES[Index].base_low = (Base & 0xFFFF);
    GDT_ENTRIES[Index].base_middle = (Base >> 16) & 0xFF;
    GDT_ENTRIES[Index].base_high = (Base >> 24) & 0xFF;

    GDT_ENTRIES[Index].limit_low = (Limit & 0xFFFF);
    GDT_ENTRIES[Index].granularity = ((Limit >> 16) & 0x0F);

    GDT_ENTRIES[Index].granularity |= (Gran & 0xF0);
    GDT_ENTRIES[Index].access = Access;

}