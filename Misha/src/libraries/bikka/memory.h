#ifndef MEMORY_H
#define MEMORY_H 1


extern int MEMORY_DETECT_LOW(); /* Look in the memory_detect.asm file */
extern int MEMORY_DETECT_HIGH(); /* Look in the memory_detect.asm file */


void *MEM_CPY(char *Src, char *Dest, int Bytes);
int MEM_CMP(const void *CompareA, const void *CompareB, long Size);
void *MEM_ALC(void *Buffer, int Value, long Size);

#endif