#ifndef MEMORY_H
#define MEMORY_H 1

#include "../common.h"
#include "isr.h"

/* Courtesy of James Molloy 
-> http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html
*/

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

typedef struct page
{
   u32 present    : 1;   // Page present in memory
   u32 rw         : 1;   // Read-only if clear, readwrite if set
   u32 user       : 1;   // Supervisor level only if clear
   u32 accessed   : 1;   // Has the page been accessed since last refresh?
   u32 dirty      : 1;   // Has the page been written to since last refresh?
   u32 unused     : 7;   // Amalgamation of unused and reserved bits
   u32 frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory{
    page_table_t *tables[1024];
    u32 tablePhysical[1024];
    u32 physicalAddr;
} page_directory_t;


#define MAX_PAGE_ALIGNED_ALLOCS 32

extern int MEMORY_DETECT_LOW(); /* Look in the memory_detect.asm file */
extern int MEMORY_DETECT_HIGH(); /* Look in the memory_detect.asm file */


/* Memory functions */
void *MEM_CPY(char *Src, char *Dest, int Bytes); /* Memory copy */
int MEM_CMP(const void *CompareA, const void *CompareB, long Size); /* Memory compare */
void *MEM_ALC(void *Buffer, int Value, long Size); /* Memory allocate */
void MEM_DLC(void *MemoryBlock, long MemoryBlockSize); /* Memory deallocate */
void *malloc(void *Buffer, int Value, long Size); /* Wrapper function for MEM_ALC */
void mdelloc(void *MemoryBlock, long MemoryBlockSize); /* Wrapper function for MEM_DLC */
void* memset(void* bufptr, int value, size_t size);

u32 kmalloc(u32 Sz);
u32 kmalloc_int(u32 Sz, int Align, u32 *Phys);
u32 kmalloc_a(u32 Sz);
u32 kmalloc_ap(u32 sz, u32 *phys);

void MEMORY_PAGING_INSTALL(void);
void MEMORY_PAGING_SWITCH_DIRECTORY(page_directory_t *New);
page_t *MEMORY_PAGING_GET_PAGE(u32 Address, int Make, page_directory_t *Dir);
void MEMORY_PAGING_FAULT(registers_t Regs);

static void MEMORY_FRAME_SET(u32 FrameAddr);
static void MEMORY_FRAME_CLEAR(u32 FrameAddr);
static u32 MEMORY_FRAME_TEST(u32 FrameAddr);
static u32 MEMORY_FRAME_FIRST(void);
void MEMORY_FRAME_ALLOC(page_t *Page, int IsKernel, int IsWriteable);
void MEMORY_FRAME_FREE(page_t *Page);

void page_fault(registers_t regs); 
#endif