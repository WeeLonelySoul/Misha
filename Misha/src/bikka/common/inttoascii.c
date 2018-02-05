#include "../../libraries/common.h"


void INT_TO_ASCII(int N, char STR[]){
    int i = 0, Sign;
    if ((Sign = N) < 0) { N = -N; }

    do {
        STR[i++] = N % 10 + '0';
    }while ((N /= 10) > 0);

    if (Sign < 0){ STR[i++] = '-'; }
    STR[i] = '\0'; /* We are done here */
    REVERSE(STR);
}