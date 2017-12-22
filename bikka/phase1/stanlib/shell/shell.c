#include "shell.h"
#include "../isr/isr.h"
#include "../idt/idt.h"
#include "../commands_src/help/help.h"
#include "../commands_src/info/info.h"
#include "../commands_src/about/about.h"
#include "../common/common.h"


void Input(char *Input){
/* Takes user input, and uses strcmp to check if it exists in our if or else */

    if (Strcmp(Input, "PV") == 0){
            info();
    }else if (Strcmp(Input, "EXIT") == 0){
            Say("The exit function does not exit Qemu, it just 'halts' the CPU\nstopping it from executing any additional code\nYou can try typing on the keyboard and you'll see that it doesn't work\nPress the 'x' to exit the program");
            asm volatile("hlt");
    }else if (Strcmp(Input, "ABOUT") == 0){
            about();
    }else if (Strcmp(Input, "CLS") == 0 || Strcmp(Input, "CLEAR") == 0){
            ClearScreen();
    }else if (Strcmp(Input, "HELP") == 0){
            help();
    }else if(Strcmp(Input, "PN") == 0){
            pn();
    }else if (Strcmp(Input, "REBOOT") == 0){
        Say("Rebooting!");
        port_byte_out(0x64, 0xFE);        
    }
    Say("\n> ");
}