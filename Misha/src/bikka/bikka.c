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
const string Logo ="\n"
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
    GDT_INSTALL(); /* Global Descriptor Table */
    ISR_INSTALL(); /* Interrupt handler */
    IRQ_INSTALL(); /* Interrupt request */


    /* Less but still important functions */
    TERMINAL_INSTALL(); /* Install the terminal */
    // MEMORY_INSTALL(); /* Install the memory management */
    // AUTHORITY_INSTALL(); /* Install the Auhority */
    // FILESYSTEM_FIND_DISK(); /* Find the disks */
    // FILESYSTEM_SETUP_DISK(); /* Make sure the disc are set and ready for use */
    // FILESYSTEM_SETUP_PATH(); /* Set the path for our shell */
    /* Setup is done, init Misha */
    GeoPrint("Kernel-Mode", 68, 0, true); /* Shows that the user is currently in kernel-land */
    GeoPrint(Logo , 20, 1, true); /* New print function */
    SYS_SETUP_PRINT(); /* Print out the details regarding the system */
    // SYS_CPU_STAT(); /* Printo out cpu information */
    // _Sleep(30); /* Sleep for 30 secs */
    // START_MISHA(); /* Enter usermode and start Misha */
    // for(;;){}
    //INPUT();
}
