#include "../../libraries/bikka/heap.h"
#include "../../libraries/bikka/ordered_array_algorithm.h"
#include "../../libraries/bikka/memory.h"

/*

Courtesy of James Molloy
-> http://www.jamesmolloy.co.uk/tutorial_html/7.-The%20Heap.html
*/

extern KernelDirectory;
heap_t *kheap = 0;

static s32 HEAP_FIND_SMALLES_HOLE(u32 Size, u8 PageAlign, heap_t *Heap){
    u32 iterator = 0;
    while (iterator < Heap->index.size){
        header_t *header = (header_t*)lookup_ordered_array(iterator, &Heap->index);
        if (PageAlign > 0){
            u32 Location = (u32)header;
            s32 Offset = 0;
            if ((Location+sizeof(header_t)) & 0xFFFFF000 != 0){ Offset = 0x1000 - (Location + sizeof(header_t))%0x1000; }
            s32 HoleSize = (s32)header->size - Offset;

            if (HoleSize >= (s32)Size){ break; }
        }else if(header->size >= Size){ break;}
        iterator++;
    }
    if (iterator == Heap->index.size){ return -1; }
    else{ return iterator; }
}

static s8 HEAP_HEADER_T_LESS_THAN(void *a, void *b){
    return (((header_t*)a)->size < ((header_t*)b)->size)?1:0;
}

heap_t *HEAP_CREATE_HEAP(u32 Start, u32 EndAddr, u32 Max, u8 SuperVisor, u8 ReadOnly){
    heap_t *heap = (heap_t*)kmalloc(sizeof(heap_t));
    ASSERT(Start%0x1000 == 0);
    ASSERT(EndAddr%0x1000 == 0);

    heap->index = place_ordered_array((void*)Start, HEAP_INDEX_SIZE, &HEAP_HEADER_T_LESS_THAN);

    Start += sizeof(type_t)*HEAP_INDEX_SIZE;

    if (Start & 0xFFFFF000 != 0){ Start &= 0xFFFFF000; Start += 0x1000;}
    heap->start_address = Start;
    heap->end_address = EndAddr;
    heap->max_address = Max;
    heap->supervisor = SuperVisor;
    heap->readonly = ReadOnly;

    header_t *hole = (header_t*)Start;
    hole->size = EndAddr-Start;
    hole->magic = HEAP_MAGIC;
    hole->is_hole = 1;
    insert_ordered_array((void*)hole, &heap->index);

    return heap;
}

static void HEAP_EXPAND(u32 NewSize, heap_t *heap){
    ASSERT(NewSize > heap->end_address - heap->start_address);

    if (NewSize&0xFFFFF000 != 0){ NewSize &= 0xFFFFF000; NewSize += 0x1000; }

    ASSERT(heap->start_address+NewSize <= heap->max_address);

    u32 OldSize = heap->end_address-heap->start_address;
    u32 i = OldSize;
    while (i < NewSize){
        MEMORY_FRAME_ALLOC(MEMORY_PAGING_GET_PAGE(heap->start_address+1, 1 ,KernelDirectory), (heap->supervisor)?1:0, (heap->readonly)?0:1);
        i += 0x1000;
    }
    heap->end_address = heap->start_address+NewSize;
}


static u32 HEAP_CONTRACT(u32 NewSize, heap_t *heap){
    ASSERT(NewSize < heap->end_address-heap->start_address);

    if (NewSize&0x1000){ NewSize &= 0x1000; NewSize += 0x1000; }

    if (NewSize < HEAP_MIN_SIZE){ NewSize = HEAP_MIN_SIZE; }

    u32 OldSize = heap->end_address-heap->start_address;
    u32 i = OldSize - 0x1000;

    while(NewSize < i){
        MEMORY_FRAME_FREE(MEMORY_PAGING_GET_PAGE(heap->start_address+i, 0, KernelDirectory));
        i -= 0x1000;
    }
    heap->end_address = heap->start_address + NewSize;
    return NewSize;
}

void *HEAP_ALLOC(u32 Size, u8 PageAlign, heap_t *heap){
    u32 NewSize = Size + sizeof(header_t) + sizeof(footer_t);
    s32 iterator = HEAP_FIND_SMALLES_HOLE(NewSize, PageAlign, heap);

    if (iterator == -1){
            u32 OldLength = heap->end_address - heap->start_address;
            u32 OldEndAddress = heap->end_address;

            HEAP_EXPAND(OldLength+NewSize, heap);
            u32 NewLength = heap->end_address-heap->start_address;

            iterator = 0;
            u32 IDX = -1, Value = 0x0;
            while(iterator < heap->index.size){
                u32 TMP = (u32)lookup_ordered_array(iterator, &heap->index);
                if (TMP > Value){
                    Value = TMP;
                    IDX = iterator;
                }
                iterator++;
            }

            if (IDX == -1){
                header_t *header = (header_t*)OldEndAddress;
                header->magic = HEAP_MAGIC;
                header->size = NewLength - OldLength;
                header->is_hole = 1;
                
                footer_t *footer = (footer_t *)(OldEndAddress+header->size-sizeof(footer_t));
                footer->magic = HEAP_MAGIC;
                footer->header = header;
                insert_ordered_array((void*)header, &heap->index);
            }else{
                header_t *header = lookup_ordered_array(IDX, &heap->index);
                header->size += NewLength - OldLength;
                
                footer_t *footer = (footer_t*)((u32)header + header->size - sizeof(footer_t));
                footer->header = header;
                footer->magic = HEAP_MAGIC;
            }
            return HEAP_ALLOC(Size, PageAlign, heap);
    }

    header_t *OrigHoleHeader = (header_t*)lookup_ordered_array(iterator, &heap->index);
    u32 OrigHolePos = (u32)OrigHoleHeader;
    u32 OrigHoleSize = OrigHoleHeader->size;

    if (OrigHoleSize < sizeof(header_t)+sizeof(footer_t)){
        Size += OrigHoleSize-NewSize;
        NewSize = OrigHoleSize;
    }

    if (PageAlign && OrigHolePos&0xFFFFF000){
        u32 NewLocation = OrigHolePos + 0x1000 - (OrigHolePos&0xFFF) - sizeof(header_t);
        header_t *hole_header = (header_t *)OrigHolePos;
        hole_header->size = 0x1000 - (OrigHolePos&0xFFF) - sizeof(header_t);
        hole_header->magic = HEAP_MAGIC;
        hole_header->is_hole = 1;
        
        footer_t *hole_footer = (footer_t*)((u32)NewLocation - sizeof(footer_t));
        hole_footer->magic = HEAP_MAGIC;
        hole_footer->header = hole_header;

        OrigHolePos = NewLocation;
        OrigHoleSize -= hole_header->size;
    }else{
        remove_ordered_array(iterator, &heap->index);
    }

    header_t *block_header = (header_t*)OrigHolePos;
    block_header->magic = HEAP_MAGIC;
    block_header->is_hole = 0;
    block_header->size = NewSize;

    footer_t *block_footer = (footer_t*)(OrigHolePos+sizeof(header_t)+Size);
    block_footer->magic = HEAP_MAGIC;
    block_footer->header = block_header;

    if (OrigHoleSize - NewSize > 0){
        header_t *hole_header = (header_t*)(OrigHolePos+sizeof(header_t)+Size+sizeof(footer_t));
        hole_header->magic = HEAP_MAGIC;
        hole_header->is_hole = 1;
        hole_header->size = OrigHoleSize - NewSize;

        footer_t *hole_footer = ((footer_t*)((u32)hole_header+OrigHoleSize-NewSize-sizeof(footer_t)));

        if ((u32)hole_footer < heap->end_address){ hole_footer->magic = HEAP_MAGIC; hole_footer->header = hole_header; }
        insert_ordered_array((void*)hole_header, &heap->index);
    }
    return (void*)((u32)block_header+sizeof(header_t));
}

void HEAP_FREE(void *p, heap_t *heap){
    if (p == 0){ return; }

    header_t *header = (header_t*)((u32)p-sizeof(header_t));
    footer_t *footer = (footer_t*)((u32)header+header->size-sizeof(footer_t));

    ASSERT(header->magic == HEAP_MAGIC);
    ASSERT(footer->magic == HEAP_MAGIC);

    header->is_hole = 0;
    char DoAdd = 1;

    footer_t *test_footer = (footer_t*)((u32)header - sizeof(footer_t));
    if (test_footer->magic == HEAP_MAGIC && test_footer->header->is_hole == 1){
        u32 CacheSize = header->size;
        header = test_footer->header;
        footer->header = header;
        header->size += CacheSize;
        DoAdd = 0;
    }

    header_t *test_header = (header_t*)((u32)footer+sizeof(footer_t));
    if (test_header->magic == HEAP_MAGIC && test_header->is_hole){
        header->size += test_header->size;
        test_footer = (footer_t*)((u32)test_header+test_header->size-sizeof(footer_t));
        footer = test_footer;
        u32 iterator = 0;
        while ((iterator < heap->index.size) && (lookup_ordered_array(iterator, &heap->index) != (void*)test_header)){ iterator++; }

        ASSERT(iterator < heap->index.size);
        remove_ordered_array(iterator, &heap->index);
    }

    if ((u32)footer+sizeof(footer_t) == heap->end_address){
        u32 OldLength = heap->end_address-heap->start_address;
        u32 NewLength = HEAP_CONTRACT((u32)header - heap->start_address, heap);
        if (header->size - (OldLength - NewLength) > 0){
            header->size -= OldLength - NewLength;
            footer = (footer_t*)((u32)header+ header->size - sizeof(footer_t));
            footer->magic = HEAP_MAGIC;
            footer->header = header;
        }else{
            u32 iterator = 0;
            while ((iterator < heap->index.size) && (lookup_ordered_array(iterator, &heap->index) != (void*)test_header)){ iterator++; }

            if (iterator < heap->index.size){ remove_ordered_array(iterator, &heap->index); }
        }
    }
    if (DoAdd == 1){ insert_ordered_array((void*)header, &heap->index); }
}