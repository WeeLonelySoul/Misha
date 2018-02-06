#include "../../libraries/bikka/gdt.h"



void GDT_INSTALL(void){
    /* Install the Global Descriptor Table */
  GDT_PTR.limit = sizeof(GDT_ENTRIES) -1;
  GDT_PTR.base = (uint32_t)GDT_ENTRIES;

    GDT_SET_ENTRY(0, 0, 0, 0, 0); /* Null 'pointer' needed for gdt to work*/
    GDT_SET_ENTRY(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    GDT_SET_ENTRY(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    GDT_SET_ENTRY(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    GDT_SET_ENTRY(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    GDT_FLUSH((uint32_t)(&GDT_PTR));
}

void GDT_SET_ENTRY(int Index, uint32_t Base, uint32_t Limit, uint8_t Access, uint8_t Gran){
    gdt_entry_t *GDT_ENTRY = &GDT_ENTRIES[Index];

    GDT_ENTRY->base_low = Base & 0xFFFF;
    GDT_ENTRY->base_middle = (Base >> 16) & 0xFF;
    GDT_ENTRY->base_high = (Base >> 24 & 0xFF);

    GDT_ENTRY->limit_low = Limit & 0xFFFF;
    GDT_ENTRY->granularity = (Limit >> 16) & 0x0F;

    GDT_ENTRY->access = Access;

    GDT_ENTRY->granularity = GDT_ENTRY->granularity | (Gran & 0xF0);
}