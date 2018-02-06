; This file is used to detect the amount of high/low memory

[extern PANIC] ; Look into Panic.c for this function

; Making the functions global, this means that they can be reached in the C code
global LOW_MEMORY_DETECT
global HIGH_MEMORY_DETECT

; Returns the amount of low memory detected, aka everything below 1MB
LOW_MEMORY_DETECT:
    clc
    int 0x12 ; Requesting low memory size
    jc PANIC_ASM
    ret ; This holds the amount of low memory

; Returns the amount of low memory detected, aka everything above 1MB
HIGH_MEMORY_DETECT:
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