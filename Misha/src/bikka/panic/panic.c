#include "../../libraries/common.h"
#include "../../libraries/bikka/video.h"


void PANIC(string ReasonForPanic){
    /**/
    printf(ReasonForPanic);
    for (;;) {} /* Forever loop */
}