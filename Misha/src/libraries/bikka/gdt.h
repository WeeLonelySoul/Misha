#ifndef GDT_H
#define GDT_H 1

#include "../common.h"

struct gdt_entry_struct {
   u16 limit_low;
   u16 base_low;
   u8 base_middle;
   u8 access;
   u8 granularity;
   u8 base_high;
}__attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct{
    u16 limit;
    u32 base;
}__attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;


void GDT_INSTALL(void);
void GDT_SET_ENTRY(s32 Index, u32 Base, u32 Limit, u8 Access, u8 Gran);
extern void GDT_FLUSH(u32 GDT_PTR); /* Located in gdt.asm file */

#endif