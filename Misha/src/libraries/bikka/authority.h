#ifndef AUTHORITY_H
#define AUTHORITY_H 1

#include "../common.h"

typedef struct {
    string ProcessName; /* The name of the program allocating */
    long ProcessNumber;
    long Size; /* The Size allocated */
    int Unallocated; /* Default should be 0 as 1 means that it's 'unallocated' */
}__attribute__((packed)) authority_memory_t;


/* Memory */
bool AUTHORITY_REGISTER_MEMORY(string ProcessName, long ProcessNumber, long Size, char *MemoryAddress);
bool AUTHORITY_UNREGISTER_MEMORY(string ProcessName, string ProcessNumber, long Size, char *MemoryAddress);
void AUTHORITY_SHOW_REGISTERED(void);
void *AUTHORITY_ALLOC_MEMORY(void *Buffer, int Value, long Size);



#endif