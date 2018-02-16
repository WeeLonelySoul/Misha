#include "../../libraries/common.h"
#include "../../libraries/bikka/video.h"


void PANIC(char *ReasonForPanic){
    /**/
    printf(ReasonForPanic);
    for (;;) {} /* Forever loop */
}

void PANIC_ASSERT(){
    PANIC("Error on Assert");
}