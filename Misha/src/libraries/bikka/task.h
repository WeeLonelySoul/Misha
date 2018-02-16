#ifndef TASK_H
#define TASK_H 1

#define KERNEL_STACK_SIZE 2048 

#include "../common.h"
#include "memory.h"

typedef struct task{
    int id; /* Process ID */
    u32 esp, ebp; /* Stack and base pointer */
    u32 eip; /* Instruction pointer */
    page_directory_t *page_directory; /* Page Directory */
    u32 kernel_stack; /* Kernel stack location */
    struct task *next; /* The next task in a linked list */
} task_t;


void TASK_INSTALL(void);
void TASK_SWITCH();
int TASK_FORK(void);
int TASK_GET_PID();
void TASK_MOVE_STACK(void *NewStackStart, u32 StackSize);
extern TASK_READ_EIP();
#endif