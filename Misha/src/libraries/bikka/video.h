#ifndef VIDEO_H

#define VIDEO_H 1

/* Imports */
#include <stdint.h>
#include <stddef.h>
#include "../common.h"

/* Static */
static const size_t _VGAWidth = 80;
static const size_t _VGAHeight = 25;


enum _VGA_COLOR_ {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_BROWN = 13,
    COLOR_WHITE = 15
};

static inline uint8_t VGAEntryColor(enum _VGA_COLOR_ ForeGround, enum _VGA_COLOR_ BackGround){
    return ForeGround | BackGround << 4;
}

static inline uint16_t VGAEntry(unsigned char UC, uint8_t Color){
    return (uint16_t) UC | (uint16_t) Color << 8;
}

void TERMINAL_INSTALL(void);
void TERMINAL_SET_COLOR(uint8_t Color);
void TERMINAL_PUT_ENTRY_AT(char c, uint8_t Color, size_t X_Axis, size_t Y_Axis);
void TERMINAL_PUT_CHAR(char Character);
void TERMINAL_WRITE(const char *Data, size_t Size);
void TERMINAL_WRITE_STRING(const char *Data);

/* Print functions */
int PutChar(int IC);
static bool print(const char *Data, size_t Length);
int printf(const char *restrict Format, ...);

#endif