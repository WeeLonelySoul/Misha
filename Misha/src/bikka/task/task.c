#include "../../libraries/bikka/task.h"
#include "../../libraries/bikka/memory.h"
#include "../../libraries/common.h"

extern page_directory_t *CurrentDirectory;
extern page_directory_t *KernelDirectory;
extern u32 InitialEsp;
volatile task_t *CurrentTask;
volatile task_t *ReadyQueue;
u32 NextPid = 1;

void TASK_INSTALL(void){
    asm volatile("cli");
    TASK_MOVE_STACK((void*)0xE0000000, 0x2000);

    CurrentTask = ReadyQueue = (task_t*)kmalloc(sizeof(task_t));
    CurrentTask->id = NextPid++;
    CurrentTask->esp = CurrentTask->ebp = 0;
    CurrentTask->eip = 0;
    CurrentTask->page_directory = CurrentDirectory;
    CurrentTask->next = 0;
    CurrentTask->kernel_stack = kmalloc_a(KERNEL_STACK_SIZE);

    asm volatile("sti");
}

void TASK_MOVE_STACK(void *NewStackStart, u32 StackSize){
    u32 i;
    for (i = (u32)NewStackStart; i >= ((u32)NewStackStart-StackSize); i -= 0x1000){
        MEMORY_FRAME_ALLOC(MEMORY_PAGING_GET_PAGE(i, 1, CurrentDirectory), 0, 1);
    }
    u32 PdAddr;
    asm volatile("mov %%cr3, %0" : "=r" (PdAddr));
    asm volatile("mov %0, %%cr3" : : "r" (PdAddr)); 

    u32 OldStackPointer;
    asm volatile("mov %%esp, %0" : "=r" (OldStackPointer));
    
    u32 OldBasePointer;
    asm volatile("mov %%ebp, %0" : "=r" (OldBasePointer)); 

    u32 Offset = (u32)NewStackStart - InitialEsp;

    u32 NewStackPointer = OldStackPointer + Offset;
    u32 NewBasePointer = OldBasePointer + Offset;

    MEM_CPY((void*)NewStackPointer, (void*)OldStackPointer, InitialEsp - OldStackPointer);

    for (i = (u32)NewStackStart; i > (u32)NewStackStart - StackSize; i -= 4){
        u32 TMP = * (u32*)i;
        if ((OldStackPointer < TMP) && (TMP < InitialEsp)){
            TMP += Offset;
            u32 *TMP2 = (u32*)i;
            *TMP2 = TMP;
        }
    }

    asm volatile("mov %0, %%esp" : : "r" (NewStackPointer));
    asm volatile("mov %0, %%ebp" : : "r" (NewBasePointer));
}

int TASK_FORK(void){
    asm volatile("cli");

    task_t *ParentTask = (task_t*)CurrentTask;
    page_directory_t *Directory = MULTITASKING_CLONE_DIRECTORY(CurrentDirectory);

    task_t *NewTask = (task_t*)kmalloc(sizeof(task_t));
    NewTask->id = NextPid++;
    NewTask->esp = NewTask->ebp = 0;
    NewTask->eip = 0;
    NewTask->page_directory = Directory;
    NewTask->next = 0;

    task_t *TmpTask = (task_t*)ReadyQueue;
    while(TmpTask->next){ TmpTask = TmpTask->next; }
    TmpTask->next = NewTask;

    u32 eip = TASK_READ_EIP(); /* Asm function */

    if (CurrentTask == ParentTask){
        u32 esp;
        asm volatile("mov %%esp, %0" : "=r"(esp));

        u32 ebp;
        asm volatile("mov %%ebp, %0" : "=r"(ebp));

        NewTask->esp = esp;
        NewTask->ebp = ebp;
        NewTask->eip = eip;
        asm volatile("sti");
        return NewTask->id;
    }else{
        return 0;
    }
}

void TASK_SWITCH(){
    if (!CurrentTask){ return; }

    u32 esp, ebp, eip;

    asm volatile("mov %%esp, %0" : "=r"(esp));
    asm volatile("mov %%ebp, %0" : "=r"(ebp));

    eip = TASK_READ_EIP();

    if (eip == 0x12345){ return; }
    
    CurrentTask->eip = eip;
    CurrentTask->esp = esp;
    CurrentTask->ebp = ebp;

    CurrentTask = CurrentTask->next;

    if (!CurrentTask){ CurrentTask = ReadyQueue; }
    esp = CurrentTask->esp;
    ebp = CurrentTask->ebp;

    asm volatile("         \
    cli;                 \
    mov %0, %%ecx;       \
    mov %1, %%esp;       \
    mov %2, %%ebp;       \
    mov %3, %%cr3;       \
    mov $0x12345, %%eax; \
    sti;                 \
    jmp *%%ecx           "
                : : "r"(eip), "r"(esp), "r"(ebp), "r"(CurrentDirectory->physicalAddr));
}