#include "../libraries/bikka/bikka.h"
#include "../libraries/bikka/video.h"
#include "../libraries/bikka/isr.h"
#include "../libraries/bikka/irq.h"
#include "../libraries/bikka/printsyssetup.h"

/*

Bikka main entry

*/


void BIKKA_MAIN(void){
    /* Core functions for pretty much every operatingsystems */
     IRQ_INSTALL(); /* Interrupt request */
    // GDT_INSTALL(); /* Global Descriptor Table */
     ISR_INSTALL(); /* Interrupt handler */

    /* Less but still important functions */
    TERMINAL_INSTALL(); /* Install the terminal */
    // MEMORY_INSTALL(); /* Install the memory management */
    // AUTHORITY_INSTALL(); /* Install the Auhority */
    // FILESYSTEM_FIND_DISK(); /* Find the disks */
    // FILESYSTEM_SETUP_DISK(); /* Make sure the disc are set and ready for use */
    // FILESYSTEM_SETUP_PATH(); /* Set the path for our shell */

    /* Setup is done, init Misha */
    _PrintSysSetup(); /* Print out the details regarding the system */
    // _Sleep(30); /* Sleep for 30 secs */
    // START_MISHA(); /* Start Misha */
    // for(;;){}
    //_INIT_KEYBOARD(); /* Start the keyboard */
}