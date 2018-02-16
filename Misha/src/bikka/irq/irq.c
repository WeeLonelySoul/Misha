#include "../../libraries/bikka/irq.h"
#include "../../libraries/bikka/isr.h"
#include "../../libraries/bikka/low_level.h"
#include "../../libraries/bikka/video.h"
#include "../../libraries/bikka/time.h"
#include "../../libraries/bikka/keyboard.h"

extern InterruptHandler[];

void IRQ_HANDLER(registers_t R){
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (R.int_no >= 40) { PORT_BYTE_OUT(0xA0, 0x20); } /* Slave */

    PORT_BYTE_OUT(0x20, 0x20); /* Master */

    if (InterruptHandler[R.int_no] != 0){
        isr_t Handler = InterruptHandler[R.int_no];
        Handler(R);
    }
}

void IRQ_INSTALL(void){
    /* Enable interruptions */
    asm volatile("sti");
    /* You can now init the keyboard */
    TIME_INIT(50);
    KEYBOARD_INIT(); /* Start the keyboard */
}

bool ARE_INTERRUPTS_ENABLED(void){
    /* Returns either True or False depending on if interrupts are enabled 
    
    -> https://wiki.osdev.org/Inline_Assembly/Examples
    */
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}