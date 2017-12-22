#include "memory.h"


void MemoryCopy(char* Source, char* Dest, int NoBytes){
    for (int i=0; i < NoBytes; i++){
        *(Dest + i) = *(Source + i);
    }
}