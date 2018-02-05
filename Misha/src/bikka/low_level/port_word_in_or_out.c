#include "../../libraries/bikka/low_level.h"


unsigned short PORT_WORD_IN(unsigned short Port){
    /* Recieve word */
    unsigned short Result;
    asm("in %%dx , %%ax" : "=a" (Result) : "d" (Port));
    return Result;
}
void PORT_WORD_OUT(unsigned short Port, unsigned short Data){
    /* Send word */
    asm("out %%ax , %%dx" : :"a" (Data), "d" (Port));
}