#ifndef COMMON_H
#define COMMON_H 1

/* And now we have booleans */
#include <stddef.h>
#include "bikka/panic.h"
typedef int bool; 
#define true 1
#define false 0
#define EOF '\0'
#define low_16(address) (u16)((address) & 0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)

typedef char* string; /* You want strings? You get char * instead */


typedef unsigned int u32;
typedef          int s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char u8;
typedef char s8;


#define UNUSED(x)(void)(x)
#define ARRAY_LENGTH(X) sizeof(X)/sizeof(*X) /* Returns the array length */

#define ASSERT(b) ((b) ? (void)0 : PANIC_ASSERT())


/* Functions */
size_t STR_LEN(const char *String); /* String length */
void INT_TO_ASCII(int N, char STR[]); /* Turns int to ascii value, which also happens to be int */
void REVERSE(char S[]); /* Reverses the order of S[] so hello would be olleh */
int STR_CMP(char String1[], char String2[]); /* Compares String1 to String2 and returns the result */
void APPEND(char String1[], char CharacterToAdd); /* Adds CharacterToAdd to the end of String1 */
void BACKSPACE_(char String[]);

#endif