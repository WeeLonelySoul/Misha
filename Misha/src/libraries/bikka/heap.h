#ifndef HEAP_H
#define HEAP_H 1

/* 

Courtesy of James Molloy
-> http://www.jamesmolloy.co.uk/tutorial_html/7.-The%20Heap.html

*/

#include "../common.h"
#include "ordered_array_algorithm.h"

#define KHEAP_START         0xC0000000
#define KHEAP_INITIAL_SIZE  0x100000
#define HEAP_INDEX_SIZE   0x20000
#define HEAP_MAGIC        0x123890AB
#define HEAP_MIN_SIZE     0x70000


typedef struct {
    u32 magic; /* Magic number, used for error checking and identification */
    u8 is_hole; /* 1 if it's a hole, 0 if it's a block */
    u32 size; /* Size of the block , including this and the footer */
} header_t;

typedef struct{
    u32 magic; /* Same as in header_t */
    header_t *header; /* Pointer to the block header */
} footer_t;

typedef struct{
    ordered_array_t index;
    u32 start_address; /* The start of our allocated space */
    u32 end_address;  /* The end of our allocated space, may be expanded up to max_address */
    u32 max_address; /* The maximum address the heap can be expanded to */
    u8 supervisor; 
    u8 readonly;
} heap_t;

heap_t *HEAP_CREATE_HEAP(u32 Start, u32 EndAddr, u32 Max, u8 SuperVisor, u8 ReadOnly);
void *HEAP_ALLOC(u32 Size, u8 PageAlign, heap_t *Heap);
void HEAP_FREE(void *P, heap_t *Heap);
static s32 HEAP_FIND_SMALLES_HOLE(u32 Size, u8 PageAlign, heap_t *Heap);
static s8 HEAP_HEADER_T_LESS_THAN(void *a, void *b);
static void HEAP_EXPAND(u32 NexSize, heap_t *heap);
static u32 HEAP_CONTRACT(u32 NewSize, heap_t *heap);
void *HEAP_ALLOC(u32 Size, u8 PageAlign, heap_t *heap);
void HEAP_FREE(void *p, heap_t *heap);

#endif