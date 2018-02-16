#include "../../libraries/bikka/usermode.h"
#include "../../libraries/bikka/tss.h"
#include "../../libraries/bikka/task.h"
#include "../../libraries/shell.h"

extern task_t *CurrentTask;

void SWITCH_TO_USERMODE(void){

  BIKKA_SET_KERNEL_STACK(CurrentTask->kernel_stack+KERNEL_STACK_SIZE);

  asm volatile("  \
    cli; \
    mov $0x23, %ax; \
    mov %ax, %ds; \
    mov %ax, %es; \
    mov %ax, %fs; \
    mov %ax, %gs; \
                   \
    mov %esp, %eax; \
    pushl $0x23; \
    pushl %eax; \
    pushf; \
    pushl $0x1B; \
    push $1f; \
    iret; \
  1: \
     ");
}