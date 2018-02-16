#include "../libraries/bikka/video.h"
#include "../libraries/bikka/printsyssetup.h"
#include "../libraries/bikka/bikka.h"
#include "../libraries/bikka/memory.h"
#include "../libraries/common.h"





void SYS_SETUP_PRINT(void){
    /* Prints out basic information regarding our system */
    string Value;
    printf("Operating system: Misha\n->> Version: %s\n", LATEST_VERSION); /* Current version */
    //printf("\nHigh Memory detected: "); /* Extern asm function */
    //printf(MEMORY_DETECT_HIGH());
    //printf("\nLow Memory detected: "); /* Extern asm function */
    //printf(MEMORY_DETECT_LOW());
    if (ARE_INTERRUPTS_ENABLED()){ Value = "True";}
    else{ Value = "False"; }

    //printf("\nAre Interrupts enabled? %s", Value);
}