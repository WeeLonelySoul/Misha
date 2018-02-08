#include "../../libraries/bikka/low_level.h"




unsigned char PORT_BYTE_IN(unsigned short Port){
    /* Recieve byte */
    unsigned char Result;
    __asm__("inb %%dx , %%al" : "=a" (Result) : "d" (Port));
    return Result;
}

void PORT_BYTE_OUT(unsigned short Port, unsigned char Data){
    /* Send byte */
    asm("outb %%al , %%dx" : :"a" (Data), "d" (Port));
}