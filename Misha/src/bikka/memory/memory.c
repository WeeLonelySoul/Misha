#include "../../libraries/bikka/memory.h"



void MEM_CPY(char *Source, char *Dest, int Bytes){
    for (int i = 0; i < Bytes; i++){
        *(Dest + i) = *(Source + i);
    }
}

void MEM_MV(){

}

void MEM_ALC(){

}

void MEM_DLC(){

}