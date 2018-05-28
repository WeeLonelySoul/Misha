#include "../../libraries/common.h"
#include "../../libraries/bikka/video.h"
#include "../../libraries/bikka/low_level.h"


bool FirstRun = false; /* The functions spits out a random S on first run, this prevents it from happening */

void INPUT(char *Input){
/* Takes user input, and uses strcmp to check if it exists in our if or else */

    if (STR_CMP(Input, "PV") == 0){
            //info();
    }else if (STR_CMP(Input, "EXIT") == 0){
            printf("The exit function does not exit Qemu, it just 'halts' the CPU\nstopping it from executing any additional code\nYou can try typing on the keyboard and you'll see that it doesn't work\nPress the 'x' to exit the program");
            asm volatile("hlt");
    }else if (STR_CMP(Input, "ABOUT") == 0){
           // about();
    }else if (STR_CMP(Input, "CLS") == 0 || STR_CMP(Input, "CLEAR") == 0){
            //ClearScreen();
    }else if (STR_CMP(Input, "HELP") == 0){
          //  help();
    }else if(STR_CMP(Input, "PN") == 0){
          //  pn();
    }else if (STR_CMP(Input, "REBOOT") == 0){
        printf("Rebooting!");
        PORT_BYTE_OUT(0x64, 0xFE);        
    }
    printf("\n>> ");
    if (!FirstRun){ FirstRun = true; }
    else{printf("Unknown value %s", Input); }
}