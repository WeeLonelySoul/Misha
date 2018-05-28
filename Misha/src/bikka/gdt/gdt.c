#include "../../libraries/bikka/gdt.h"
#include "../../libraries/bikka/tss.h"
#include "../../libraries/bikka/memory.h"

gdt_entry_t gdt_entries[6]; /* This is the amount of GDT_SET_ENTRY below */
gdt_ptr_t gdt_ptr;
/*
GDT, IRQ and IDE are things that can quite quickly get out of hand
Therefore I recommend James Malloy's tutorial on this
-> http://www.jamesmolloy.co.uk/tutorial_html/
*/

void GDT_INSTALL(void){
    /* Install the Global Descriptor Table */
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 6) -1; 
    gdt_ptr.base = (u32)&gdt_entries;

    GDT_SET_ENTRY(0, 0, 0, 0, 0); /* Null segment */
    GDT_SET_ENTRY(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
    GDT_SET_ENTRY(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
    GDT_SET_ENTRY(4, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User mode code segment */
    GDT_SET_ENTRY(5, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User mode data segment */
    TSS_WRITE(5, 0x10, 0x0); /* Sets the TSS segment */

    GDT_FLUSH((u32)&gdt_ptr);
    TSS_FLUSH();
}


void GDT_SET_ENTRY(s32 Index, u32 Base, u32 Limit, u8 Access, u8 Gran){

    gdt_entries[Index].base_low = (Base & 0xFFFF);
    gdt_entries[Index].base_middle = (Base >> 16) & 0xFF;
    gdt_entries[Index].base_high = (Base >> 24) & 0xFF;

    gdt_entries[Index].limit_low = (Limit & 0xFFFF);
    gdt_entries[Index].granularity = (Limit >> 16) & 0x0F;

    gdt_entries[Index].granularity |= (Gran & 0xF0);
    gdt_entries[Index].access = Access;

}