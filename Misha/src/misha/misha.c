#include "../libraries/misha/misha.h"
#include "../libraries/misha/syscall.h"
#include "../libraries/bikka/usermode.h"


void MISHA_START(void){
    SWITCH_TO_USERMODE(); /* Switch to the user mode */
    syscall_USERMODE_TERMINAL_INSTALL("COLOR_BLUE"); /* Install the terminal */
    syscall_printf("Hello, World!"); /* Print to the screen */
    //INPUT();
}