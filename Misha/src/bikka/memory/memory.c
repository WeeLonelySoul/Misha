#include "../../libraries/bikka/memory.h"
#include "../../libraries/bikka/heap.h"
#include "../../libraries/bikka/authority.h"
#include "../../libraries/bikka/panic.h"
#include "../../libraries/bikka/isr.h"
#include "../../libraries/bikka/multitasking.h"

extern u32 end; /* Exist in the link.ld */
u32 PlacementAddress = (u32)&end;
u32 *Frames;
u32 nFrames;
extern heap_t *kheap;

page_directory_t *KernelDirectory = 0;
page_directory_t *CurrentDirectory = 0;


void *MEM_CPY(char *Dest, char *Src, int Bytes){
    /* Moves Src to Dest in memory */
    /*unsigned char *Destination = (unsigned char*)Dest;
    const unsigned char *Source = (unsigned char*)Src;
    for (long i = 0; i < Bytes; i++){ Destination[i] = Source[i]; }
    return Dest;*/

    const u8 *sp = (const u8 *)Src;
    u8 *dp = (u8 *)Dest;
    
    for(; Bytes != 0; Bytes--) *dp++ = *sp++;
}

void *MEM_CPY_2(char *Src, char *Dest, int Bytes){
    /* Moves Src to Dest in memory */
    unsigned char *Destination = (unsigned char*)Dest;
    const unsigned char *Source = (unsigned char*)Src;
    for (long i = 0; i < Bytes; i++){ Destination[i] = Source[i]; }
    return Dest;
}

int MEM_CMP(const void *CompareA, const void *CompareB, long Size){
    /* Compares the two values */
    const unsigned char *A = (const unsigned char *)CompareA;
    const unsigned char *B = (const unsigned char *)CompareB;
    for (long i = 0; i < Size; i++){
        if (A[i] < B[i]){ return -1; } /* B is bigger than A */
        else if (A[i] > B[i]){ return 1; } /* A is bigger than B*/
    }
    return 0;
}

void *MEM_ALC(void *Buffer, int Value, long Size){
    /* Allocates, returns a void pointer to Buffer */
    return Buffer;
}

void MEM_DLC(void *MemoryBlock, long MemoryBlockSize){
    /* 'Deallocates MemoryBlock'

        Okay want me to tell you what this actually does?? Because it isn't as simple as deallocating a place in memory.
        What we do is that we tell the entire system that the area *MemoryBlock with the size of MemoryBlockSize is ready to be allocated
        by another program so that when the next allocation occurs it simply just allocated the area previously marked 'unallocated' 
    */
}

void *malloc(void *Buffer, int Value, long Size){ return MEM_ALC(Buffer, Value, Size); } /* Wrapper function for those who prefer to type malloc */
void mdelloc(void *MemoryBlock, long MemoryBlockSize){ MEM_DLC(MemoryBlock, MemoryBlockSize); } /* Wrapper function for those who prefer to type mdelloc */


void* memset(u8* Dest, int value, u32 Size) {
	/*unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;*/

    u8 *Temp = (u8*)Dest;
    for (; Size != 0; Size--){ *Temp++ = value; }
}

u32 kmalloc_int(u32 Sz, int Align, u32 *Phys){
    /* Allocation for the kernel */
    if (Align == 1 && (PlacementAddress & 0xFFFFF000)){
        PlacementAddress &= 0xFFFFF000;
        PlacementAddress += 0x1000;
    }
    if (Phys){
        *Phys = PlacementAddress;
    }
    u32 TMP = PlacementAddress;
    PlacementAddress += Sz;
    return TMP;
}

u32 kmalloc(u32 Sz){
    u32 TMP = PlacementAddress;
    PlacementAddress += Sz;
    return TMP;
}


u32 kmalloc_a(u32 Sz){ return kmalloc_int(Sz, 1, 0); }
u32 kmalloc_ap(u32 sz, u32 *phys){ return kmalloc_int(sz, 1, phys); }


static void MEMORY_FRAME_SET(u32 FrameAddr){
    /* Function to set a bit in the frames bitset */
    u32 Frame = FrameAddr/0x1000;
    u32 Idx = INDEX_FROM_BIT(Frame);
    u32 Off = OFFSET_FROM_BIT(Frame);
    Frames[Idx] |= (0x1 << Off);
}

static void MEMORY_FRAME_CLEAR(u32 FrameAddr){
    u32 Frame = FrameAddr/0x1000;
    u32 Idx = INDEX_FROM_BIT(Frame);
    u32 Off = OFFSET_FROM_BIT(Frame);
    Frames[Idx] &= ~(0x1 << Off);
}

static u32 MEMORY_FRAME_TEST(u32 FrameAddr){
    u32 Frame = FrameAddr/0x1000;
    u32 Idx = INDEX_FROM_BIT(Frame);
    u32 Off = OFFSET_FROM_BIT(Frame);
    return (Frames[Idx] & (0x1 << Off));
}

static u32 MEMORY_FRAME_FIRST(void){
    u32 i, j;
    for (i = 0; i < INDEX_FROM_BIT(nFrames); i++){
        if (Frames[i] != 0xFFFFFFFF){
            for (j = 0; j < 32; j++){
                u32 toTest = 0x1 << j;
                if (!(Frames[i]&toTest)){ return i*4*8+j; }
            }
        }
    }
}

void MEMORY_FRAME_ALLOC(page_t *Page, int IsKernel, int IsWriteable){
    if (Page->frame != 0){ return; } /* Frame is already allocated */
    else{
        u32 IDX = MEMORY_FRAME_FIRST();
        if (IDX == (u32)-1){ PANIC("No Free Frames!"); }
        MEMORY_FRAME_SET(IDX*0x1000);
        Page->present = 1;
        Page->rw = (IsWriteable)?1:0;
        Page->user = (IsKernel)?0:1;
        Page->frame = IDX;
    }
}


void MEMORY_FRAME_FREE(page_t *Page){
    u32 Frame;
    if (!(Frame=Page->frame)){ return; } /* The page didn't actually have an allocated frame */
    else{
        MEMORY_FRAME_CLEAR(Frame);
        Page->frame = 0x0;
    }
}


void MEMORY_PAGING_INSTALL(void){

    int i = 0;
    u32 MEM_END_PAGE = 0x1000000;

    nFrames = MEM_END_PAGE / 0x1000;
    Frames = (u32*)kmalloc(INDEX_FROM_BIT(nFrames));
    memset(Frames, 0 , INDEX_FROM_BIT(nFrames));
    u32 Phys;

    KernelDirectory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
    memset(KernelDirectory, 0 , sizeof(page_directory_t));
    KernelDirectory->physicalAddr = (u32)KernelDirectory->tablePhysical;

    for (i = KHEAP_START ; i < KHEAP_START+KHEAP_INITIAL_SIZE; i += 0x1000){ MEMORY_PAGING_GET_PAGE(i, 1, KernelDirectory); }

    i = 0;
    while (i < 0x400000){
        MEMORY_FRAME_ALLOC(MEMORY_PAGING_GET_PAGE(i, 1, KernelDirectory), 0, 0);
        i += 0x1000;
    }

    for (i = KHEAP_START; i < KHEAP_START+KHEAP_INITIAL_SIZE; i += 0x1000){ MEMORY_FRAME_ALLOC(MEMORY_PAGING_GET_PAGE(i, 1, KernelDirectory), 0, 0); }


    ISR_REGISTER_INTERRUPT_HANDLER(14, page_fault);
    MEMORY_PAGING_SWITCH_DIRECTORY(KernelDirectory);

    kheap = HEAP_CREATE_HEAP(KHEAP_START, KHEAP_START+KHEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);


    CurrentDirectory = MULTITASKING_CLONE_DIRECTORY(KernelDirectory);
    MEMORY_PAGING_SWITCH_DIRECTORY(CurrentDirectory);
}


void MEMORY_PAGING_SWITCH_DIRECTORY(page_directory_t *Dir){
    CurrentDirectory = Dir;
    asm volatile("mov %0, %%cr3":: "r"(Dir->tablePhysical));
    u32 cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}


page_t *MEMORY_PAGING_GET_PAGE(u32 Address, int Make, page_directory_t *Dir){
    Address /= 0x1000;

    u32 TableIDX = Address / 1024;
    if (Dir->tables[TableIDX]){ return &Dir->tables[TableIDX]->pages[Address%1024]; }
    else if (Make){
        u32 TMP;
        Dir->tables[TableIDX] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &TMP);
        memset(Dir->tables[TableIDX], 0, 0x1000);
        Dir->tablePhysical[TableIDX] = TMP | 0x7;
        return &Dir->tables[TableIDX]->pages[Address%1024];
        
    }else{ return 0; }
}


void page_fault(registers_t regs){
    u32 FaultingAddress;
    asm volatile("mov %%cr2, %0" : "=r" (FaultingAddress));
    int present   = !(regs.err_code & 0x1); // Page not present
    int rw = regs.err_code & 0x2;           // Write operation?
    int us = regs.err_code & 0x4;           // Processor was in user-mode?
    int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
    int id = regs.err_code & 0x10;          // Caused by an instruction fetch?
    PANIC("Page fault");
}


page_directory_t *MULTITASKING_CLONE_DIRECTORY(page_directory_t *SRC){
    u32 Phys;
    page_directory_t *Dir = (page_directory_t*)kmalloc_ap(sizeof(page_directory_t), &Phys);
    memset(Dir, 0, sizeof(page_directory_t));

    u32 Offset = (u32)Dir->tablePhysical - (u32)Dir;
    Dir->physicalAddr = Phys +  Offset;
    int i;
    for (i = 0; i < 1024; i++){
        if (!SRC->tables[i]){ continue; }

        if (KernelDirectory->tables[i] == SRC->tables[i]){
            Dir->tables[i] = SRC->tables[i];
            Dir->tablePhysical[i] = SRC->tablePhysical[i];
        }else{
            u32 Phys;
            Dir->tables[i] = MULTITASKING_CLONE_TABLE(SRC->tables[i], &Phys);
            Dir->tablePhysical[i] = Phys | 0x07;
        }
    }
    return Dir;
}

static page_table_t *MULTITASKING_CLONE_TABLE(page_table_t *SRC, u32 *PhysAddr){
    page_table_t *Table = (page_table_t*)kmalloc_ap(sizeof(page_table_t), PhysAddr);
    memset(Table, 0, sizeof(page_directory_t));

    for (int i = 0; i < 1024; i++){
        if (!SRC->pages[i].frame){ continue; }
        else{
            MEMORY_FRAME_ALLOC(&Table->pages[i], 0, 0);
            if (SRC->pages[i].present){ Table->pages[i].present = 1; }
            if (SRC->pages[i].rw){ Table->pages[i].rw = 1; }
            if (SRC->pages[i].user){ Table->pages[i].user = 1; }
            if (SRC->pages[i].accessed){ Table->pages[i].accessed = 1; }
            if (SRC->pages[i].dirty){ Table->pages[i].dirty = 1; }

            MULTITASKING_COPY_PHYSICAL_PAGE(SRC->pages[i].frame*0x1000, Table->pages[i].frame*0x1000);
        }
    }
    return Table;
}