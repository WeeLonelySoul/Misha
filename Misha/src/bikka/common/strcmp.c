#include "../../libraries/common.h"



int STR_CMP(char String1[], char String2[]){
    /* Compares the two strings */
    int i;
    for (i = 0; String1[i] == String2[i]; i++){
        if (String1[i] == '\0' || String2[i] == '\0'){ return 0; } /* We have reached the end of either String1 or String2 */
    }
    return String1[i] - String2[i];
}