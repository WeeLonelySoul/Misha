#include "../../libraries/bikka/irq.h"
#include "../../libraries/bikka/isr.h"


void IRQ_HANDLER(registers_t R){
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (R.int_no >= 40) { PORT_BYTE_OUT(0xA0, 0x20); }
    PORT_BYTE_OUT(0x20, 0x20);

    if (InterruptHandler[R.int_no] != 0){
        isr_t Handler = InterruptHandler[R.int_no];
        Handler(R);
    }
}

void IRQ_INSTALL(void){
    /* Enable interruptions */

    asm volatile("sti");
    /* You can now init the keyboard */
    //INIT_TIMER(50);
    //_INIT_KEYBOARD(); /* Start the keyboard */
}