#ifndef GDT_H
#define GDT_H 1

#include "../common.h"

typedef struct GDT {
   u16 limit_low;
   u16 base_low;
   u8 base_middle;
   u8 access;
   u8 granularity;
   u8 base_high;
}__attribute((packed)) gdt_entry_t;

typedef struct GDT_PTR{
    u16 limit;
    u32 base;
}__attribute__((packed)) gdt_ptr_t;


void GDT_INSTALL(void);
void GDT_SET_ENTRY(s32 Index, u32 Base, u32 Limit, u8 Access, u8 Gran);
extern void GDT_FLUSH(u32 GDT_PTR); /* Located in gdt.asm file */

#endif