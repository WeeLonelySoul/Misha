#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H 1

/*

Calling this file low_level, even though the file that are using it are called
port_byte_in_or_out.c && port_word_in_or_out.c
And that's because this is low level stuff in a OS


The difference between a byte and a word is it's length. A byte is 8 bits while a word is 16 bits
*/


/* Functions */
unsigned char PORT_BYTE_IN(unsigned short Port); /* Recieve byte */
void PORT_BYTE_OUT(unsigned short Port, unsigned char Data); /* Send byte */
unsigned short PORT_WORD_IN(unsigned short Port); /* Recieve word */
void PORT_WORD_OUT(unsigned short Port, unsigned short Data);  /* Send word */
#endif