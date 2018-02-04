#include "../../libraries/common.h"


void PANIC(string ReasonForPanic){
    /**/
    printf(ReasonForPanic);
    for (;;) {} /* Forever loop */
}