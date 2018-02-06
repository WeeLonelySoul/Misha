#ifndef GDT_H
#define GDT_H 1

#include <stdint.h>
#define NUM_DESCRIPTORS 8

typedef struct GDT {
   uint16_t limit_low;
   uint16_t base_low;
   uint8_t base_middle;
   uint8_t access;
   uint8_t granularity;
   uint8_t base_high;
}__attribute((packed)) gdt_entry_t;

typedef struct GDT_PTR{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) gdt_ptr_t;


static gdt_entry_t GDT_ENTRIES[NUM_DESCRIPTORS];
static gdt_ptr_t GDT_PTR;

void GDT_INSTALL(void);
void GDT_SET_ENTRY(int Index, uint32_t Base, uint32_t Limit, uint8_t Access, uint8_t Gran);
extern void GDT_FLUSH(uint32_t GDT_PTR); /* Located in gdt.asm file */

#endif