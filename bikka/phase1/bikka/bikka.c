#include "../stanlib/bikka/bikka.h"
#include "../stanlib/common/common.h"



int main(void){
    isr_install();
    irq_install();

    /* Main function */


    ClearScreen();
    Say("Welcome to the bikka kernel interface\nFrom here you can see info about bikka");
    Say("\nRun help to get started!\n");
    Say("\nNotice! All input will appear as uppercase characters\n");
    Input();
    return 0;
}
