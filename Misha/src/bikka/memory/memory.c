#include "../../libraries/bikka/memory.h"



void *MEM_CPY(char *Src, char *Dest, int Bytes){
    /* Moves Src to Dest in memory */
    unsigned char *Destination = (unsigned char*)Dest;
    const unsigned char *Source = (unsigned char*)Src;
    for (long i = 0; i < Bytes; i++){ Destination[i] = Source[i]; }
    return Dest;
}

int MEM_CMP(const void *CompareA, const void *CompareB, long Size){
    /* Compares the two values */
    const unsigned char *A = (const unsigned char *)CompareA;
    const unsigned char *B = (const unsigned char *)CompareB;
    for (long i = 0; i < Size; i++){
        if (A[i] < B[i]){ return -1; } /* B is bigger than A */
        else if (A[i] > B[i]){ return 1; } /* A is bigger than B*/
    }
    return 0;
}

void *MEM_ALC(void *Buffer, int Value, long Size){
    /* Allocates, returns a void pointer to Buffer */
    unsigned char *Buff = (unsigned char*)Buffer;
    for (long i = 0; i < Size; i++){ Buff[i] == (unsigned char) Value; }
    return Buffer;
}

void MEM_DLC(){

}