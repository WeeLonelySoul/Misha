; GDT
gdt_start:

gdt_null: ; this is needed
    dd 0x0 ; 'dd' means define double word (i.e. 4 bytes)
    dd 0x0

gdt_code: ; the code segment descriptor
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data: ; the data segment descriptor
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start -1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start ; Global "variable"
DATA_SEG equ gdt_data - gdt_start ; Global "variable"