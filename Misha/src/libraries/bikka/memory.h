#ifndef MEMORY_H
#define MEMORY_H 1


extern int LOW_MEMORY_DETECT(); /* Look in the memory_detect.asm file */
extern int HIGH_MEMORY_DETECT(); /* Look in the memory_detect.asm file */


void MEM_CPY(char *Source, char *Dest, int Bytes);

#endif