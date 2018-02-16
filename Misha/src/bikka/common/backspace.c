#include "../../libraries/common.h"


/*

Removes 1 space from String
and adds '\0' to the removed space
*/

void BACKSPACE_(char String[]){
    int Len = STR_LEN(String);
    String[Len-1] = '\0';
}