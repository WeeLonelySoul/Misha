#include "../libraries/bikka/video.h"
#include "../libraries/bikka/printsyssetup.h"
#include "../libraries/bikka/bikka.h"
#include "../libraries/bikka/memory.h"





void SYS_SETUP_PRINT(void){
    /* Prints out basic information regarding our system */
    printf("Operating system: Misha\n->> Version: %s\n", LATEST_VERSION); /* Current version */
    printf("\nHigh Memory detected: "); /* Extern asm function */
    //printf(MEMORY_DETECT_HIGH());
    printf("\nLow Memory detected: "); /* Extern asm function */
    //printf(MEMORY_DETECT_LOW());
}