; This file is used in irq.c
; Which should be located in the same directory as this .asm file
; The contents of this file is taking from my older version of Misha
; -> https://github.com/WeeLonelySoul/Misha/blob/master/Misha_phase1/stanlib/interrupt/interrupt.asm
; And will remain pretty much the smae

[extern IRQ_HANDLER]


; This function works much like the IRS_COMMON_STUB found in isr.asm
IRQ_COMMON_STUB:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call IRQ_HANDLER

    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
    add esp, 8
    sti
    iret


; First make the IRQs global
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15




; IRQ handlers
irq0:
	cli
	push byte 0
	push byte 32
	jmp IRQ_COMMON_STUB

irq1:
	cli
	push byte 1
	push byte 33
	jmp IRQ_COMMON_STUB

irq2:
	cli
	push byte 2
	push byte 34
	jmp IRQ_COMMON_STUB

irq3:
	cli
	push byte 3
	push byte 35
	jmp IRQ_COMMON_STUB

irq4:
	cli
	push byte 4
	push byte 36
	jmp IRQ_COMMON_STUB

irq5:
	cli
	push byte 5
	push byte 37
	jmp IRQ_COMMON_STUB

irq6:
	cli
	push byte 6
	push byte 38
	jmp IRQ_COMMON_STUB

irq7:
	cli
	push byte 7
	push byte 39
	jmp IRQ_COMMON_STUB

irq8:
	cli
	push byte 8
	push byte 40
	jmp IRQ_COMMON_STUB

irq9:
	cli
	push byte 9
	push byte 41
	jmp IRQ_COMMON_STUB

irq10:
	cli
	push byte 10
	push byte 42
	jmp IRQ_COMMON_STUB

irq11:
	cli
	push byte 11
	push byte 43
	jmp IRQ_COMMON_STUB

irq12:
	cli
	push byte 12
	push byte 44
	jmp IRQ_COMMON_STUB

irq13:
	cli
	push byte 13
	push byte 45
	jmp IRQ_COMMON_STUB

irq14:
	cli
	push byte 14
	push byte 46
	jmp IRQ_COMMON_STUB

irq15:
	cli
	push byte 15
	push byte 47
	jmp IRQ_COMMON_STUB