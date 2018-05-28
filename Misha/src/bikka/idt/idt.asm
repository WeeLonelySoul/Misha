; Asm file for the code in idt.c

[global IDT_FLUSH]

IDT_FLUSH:
    mov eax, [esp+4]
    lidt [eax]
    ret