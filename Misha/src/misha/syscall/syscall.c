#include "../../libraries/misha/syscall.h"
#include "../../libraries/bikka/isr.h"
#include "../../libraries/bikka/video.h"

/*

Courtesy of James Molloy
-> http://www.jamesmolloy.co.uk/tutorial_html/10.-User%20Mode.html
*/

static void SYSCALL_HANDLER(registers_t *Regs);

DEFN_SYSCALL1(printf, 0, const char*);
DEFN_SYSCALL1(USERMODE_TERMINAL_INSTALL, 1, const char*);

u32 SYSCALLS_NUM = 2;

static void *SYSCALLS[2] = {
    &printf,
    &USERMODE_TERMINAL_INSTALL,
};

void SYSCALL_INSTALL(){
    ISR_REGISTER_INTERRUPT_HANDLER(0x80, &SYSCALL_HANDLER);
}

void SYSCALL_HANDLER(registers_t *Regs){
    if (Regs->eax >= SYSCALLS_NUM){ return; }
    int Ret;

    void *Location = SYSCALLS[Regs->eax];

    asm volatile (" \
        push %1; \
        push %2; \
        push %3; \
        push %4; \
        push %5; \
        call *%6; \
        pop %%ebx; \
        pop %%ebx; \
        pop %%ebx; \
        pop %%ebx; \
        pop %%ebx; \
    " : "=a" (Ret) : "r" (Regs->edi), "r" (Regs->esi), "r" (Regs->edx), "r" (Regs->ecx), "r" (Regs->ebx), "r" (Location));
    Regs->eax = Ret;

}

