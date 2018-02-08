; This file is used to detect the amount of high/low memory

[extern PANIC] ; Look into Panic.c for this function

; Making the functions global, this means that they can be reached in the C code
global MEMORY_DETECT_LOW
global MEMORY_DETECT_HIGH

; Returns the amount of low memory detected, aka everything below 1MB
MEMORY_DETECT_LOW:
    clc
    int 0x12 ; Requesting low memory size
    jc PANIC_ASM
    ret ; This holds the amount of low memory

; Returns the amount of low memory detected, aka everything above 1MB
MEMORY_DETECT_HIGH:
   xor cx, cx
   xor dx, dx
   mov ax, 0xE8001
   int 0x15
   jc short PANIC_ASM
   cmp ah, 0x86
   je short PANIC_ASM
   cmp ah, 0x80
   je short PANIC_ASM
   
   mov ax, cx
   mov bx, dx
   ret

PANIC_ASM: ; Things didn't go as expected
    call PANIC