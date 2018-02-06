#include "../libraries/bikka/bikka.h"
#include "../libraries/bikka/video.h"
#include "../libraries/bikka/isr.h"
#include "../libraries/bikka/irq.h"
#include "../libraries/bikka/printsyssetup.h"
#include "../libraries/bikka/gdt.h"
#include "../libraries/bikka/time.h"

/*

Bikka main entry

*/

/* Tab space of doom, atleast make this into a function in the future */
string Logo ="\n"
"\t\t                              $$\\                 \n" \
"\t\t   $$$\\    $$$ |$$|           $$ |                \n" \
"\t\t   $$$$\\  $$$$ |$$\\  $$$$$$$\\ $$$$$$$\\   $$$$$$\\  \n"\
"\t\t   $$\\$$\\$$ $$ |$$ |$$  _____|$$  __$$\\  \\____$$\\ \n"\
"\t\t   $$ \\$$$  $$ |$$ |\\$$$$$$\\  $$ |  $$ | $$$$$$$ |\n" \
"\t\t   $$ |\\$  /$$ |$$ | \\____$$\\ $$ |  $$ |$$  __$$ |\n" \
"\t\t   $$ | \\_/ $$ |$$ |$$$$$$$  |$$ |  $$ |\\$$$$$$$ |\n"\
"\t\t   \\__|     \\__|\\__|\\_______/ \\__|  \\__| \\_______|\n";

void BIKKA_MAIN(void){
    /* Core functions for pretty much every operatingsystems */
     IRQ_INSTALL(); /* Interrupt request */
     GDT_INSTALL(); /* Global Descriptor Table */
     ISR_INSTALL(); /* Interrupt handler */

    /* Less but still important functions */
    TERMINAL_INSTALL(); /* Install the terminal */
    // MEMORY_INSTALL(); /* Install the memory management */
    // AUTHORITY_INSTALL(); /* Install the Auhority */
    // FILESYSTEM_FIND_DISK(); /* Find the disks */
    // FILESYSTEM_SETUP_DISK(); /* Make sure the disc are set and ready for use */
    // FILESYSTEM_SETUP_PATH(); /* Set the path for our shell */

    /* Setup is done, init Misha */
    GeoPrint(Logo , 20, 0, true); /* New print function */
    _PrintSysSetup(); /* Print out the details regarding the system */
    // _Sleep(30); /* Sleep for 30 secs */
    // START_MISHA(); /* Start Misha */
    // for(;;){}

}
