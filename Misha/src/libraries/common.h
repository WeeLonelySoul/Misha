#ifndef COMMON_H
#define COMMON_H 1

/* And now we have booleans */
#include <stddef.h>
typedef int bool; 
#define true 1;
#define false 0;

#define EOF '\0'

typedef char* string;

size_t STRLEN(const char *String);

#endif