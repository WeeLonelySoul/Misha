/*

This code contains the print functions used through out the system

Code inspired by/taken from:
    -> https://wiki.osdev.org/Meaty_Skeleton
*/

#include "../../libraries/bikka/video.h"
#include "../../libraries/bikka/panic.h"
#include "../../libraries/common.h"
#include <stdarg.h>
#include <limits.h>

int PutChar(int IC){
    /* Even smaller print function */
    char C = (char) IC;
    TERMINAL_WRITE(&C, sizeof(C));
    return IC;
}

static bool print(const char *Data, size_t Length){
    /* Smaller print function */
    const unsigned char *Bytes = (const unsigned char*) Data;
    for (size_t i = 0; i < Length; i++){
        if (PutChar(Bytes[i]) == EOF){ return false; }
    }
    return true;
}

int printf(const char *restrict Format, ...){
    /* Standard printf function */
    va_list _PARAMETERS;
    va_start(_PARAMETERS, Format);
    int Written = 0;

    while (*Format != '\0'){
        size_t MaxRem = INT_MAX - Written;
        if (Format[0] != '%' || Format[1] == '%'){
            if (Format[0] == '%') { Format++; }
            size_t Amount = 1;
            while (Format[Amount] && Format[Amount] != '%') { Amount++; }
            if (MaxRem < Amount ) { PANIC("Error on function printf! Amount was bigger than MaxRem"); } /* Shit, what the fuck happend */
            if (!print(Format, Amount)){ return -1; }
            Format += Amount;
            Written += Amount;
            continue;
        }
        const char *FormatBegunAt = Format++;

        if (*Format == 'c'){
            Format++;
            char C = (char) va_arg(_PARAMETERS, const char *);
            if (!MaxRem){ PANIC("Error on function printf! MaxRem was negative!"); }
            if (!print(&C, sizeof(C))){ return -1; }
            Written++;
        }else if(*Format == 's'){
            Format++;
            const char *STR = va_arg(_PARAMETERS, const char*);
            size_t Len = STR_LEN(STR);
            if (MaxRem < Len) { PANIC("Error on function printf! Len (Length) was bigger than MaxRem (1)"); }
            if (!print(STR, Len)) { return -1; }
            Written += Len;
        }else if(*Format == 'd'){
                
        }else{
            Format = FormatBegunAt;
            size_t Len = STR_LEN(Format);
            if (MaxRem < Len){ PANIC("Error on function printf! Len (Length) was bigger than MaxRem (2)"); }
            if (!print(Format, Len)){ return -1; }
            Written += Len;
            Format += Len;
        }
    }
    va_end(_PARAMETERS);
    return Written;
}

void println(const char *CharacterToPrint, ...){
    /* printf wrapper that ends a newline after each print */
    printf("%s\n", CharacterToPrint);
}