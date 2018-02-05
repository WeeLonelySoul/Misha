#include "../../libraries/bikka/irq.h"
#include "../../libraries/bikka/isr.h"


void IRQ_HANDLER(registers_t R){
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */

}

void IRQ_INSTALL(void){
    /* Enable interruptions */

    asm volatile("sti");
    //INIT_TIMER(50);
}