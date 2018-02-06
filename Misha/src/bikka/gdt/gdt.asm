; These functions are used in gdt.c
; Courtesy of szhou42 on github
; Check out his/her project
; -> https://github.com/szhou42/osdev

global GDT_FLUSH

GDT_FLUSH:
    mov eax, [esp + 4]
    lgdt [eax]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss,ax

    jmp 0x08:flush

flush:
    ret