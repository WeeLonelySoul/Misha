#include "../libraries/bikka/bikka.h"
#include "../libraries/bikka/video.h"
#include "../libraries/bikka/gdt.h"
#include "../libraries/bikka/isr.h"
#include "../libraries/bikka/irq.h"
#include "../libraries/bikka/idt.h"
#include "../libraries/bikka/printsyssetup.h"
#include "../libraries/bikka/memory.h"
#include "../libraries/bikka/task.h"


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

u32 InitialEsp;

void BIKKA_MAIN(u32 InitialStack){    
    InitialEsp = InitialStack; /* Get the "original" stack */

    /* Core functions for pretty much every operating systems */
    GDT_INSTALL(); /* Global Descriptor Table */
    IDT_AND_ISR_INSTALL();
    IRQ_INSTALL(); /* Interrupt request */

    /* Less but still important functions */
    TERMINAL_INSTALL(); /* Install the terminal */
    MEMORY_PAGING_INSTALL(); /* Install paging */
    TASK_INSTALL();

    // FILESYSTEM_FIND_DISK(); /* Find the disks */
    // FILESYSTEM_SETUP_DISK(); /* Make sure the disc are set and ready for use */
    // FILESYSTEM_SETUP_PATH(); /* Set the path for our shell */

    /* Setup is done, init Misha */
    GeoPrint("Kernel-Mode", 68, 0); /* Shows that the user is currently in kernel-land */
    GeoPrint(Logo , 20, 1); /* New print function */
    SYS_SETUP_PRINT(); /* Print out the details regarding the system */
    INPUT(); /* Start the keyboard */
    for(;;){}
}