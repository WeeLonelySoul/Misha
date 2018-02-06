#include "../libraries/bikka/video.h"
#include "../libraries/bikka/printsyssetup.h"
#include "../libraries/bikka/bikka.h"
#include "../libraries/bikka/memory.h"





void _PrintSysSetup(void){
    /* Prints out basic information regarding our system */
    printf("Operating system: Misha\n->> Version: %s\n", LATEST_VERSION); /* Current version */
    printf("\nHigh Memory detected: "); /* Extern asm function */
    //printf(HIGH_MEMORY_DETECT());
    printf("\nLow Memory detected: "); /* Extern asm function */
    //printf(LOW_MEMORY_DETECT());
}