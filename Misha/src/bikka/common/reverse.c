#include "../../libraries/common.h"


void REVERSE(char S[]){
    int c, j;
    for (int i = 0, j = STRLEN(S)-1; i < j; i++, j--){
        c = S[i];
        S[i] = S[j];
        S[j] = c;
    }
}