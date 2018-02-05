; This file is used in isr.c
; Which should be located in the same directory as this .asm file
; The contents of this file is taking from my older version of Misha
; -> https://github.com/WeeLonelySoul/Misha/blob/master/Misha_phase1/stanlib/interrupt/interrupt.asm
; And will remain pretty much the smae


[extern ISR_HANDLER] ; Extern function



ISR_COMMON_STUB:
    ; Save our current CPU state
    pusha ; Pushes edi, esi, ebp, esp, ebx, edx, ecx, eax
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call ISR_HANDLER ; Call the C function, again defined in the isr.c file

    ; Restore the CPU state
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8 ; Cleans up the pushed error code/ISR number
    sti
    iret

    ; This function can pretty muched summed up with three words

    ; Save
    ; Fuckup
    ; Restore
    
    ; Yeah yeah I made fuckup into one word, who cares >:D

; First make the ISRs global
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31


; 0: Divide By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp ISR_COMMON_STUB

; 1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp ISR_COMMON_STUB

; 2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp ISR_COMMON_STUB

; 3: Int 3 Exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp ISR_COMMON_STUB

; 4: INTO Exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp ISR_COMMON_STUB

; 5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp ISR_COMMON_STUB

; 6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6
    jmp ISR_COMMON_STUB

; 7: Coprocessor Not Available Exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp ISR_COMMON_STUB

; 8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push byte 8
    jmp ISR_COMMON_STUB

; 9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp ISR_COMMON_STUB

; 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push byte 10
    jmp ISR_COMMON_STUB

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push byte 11
    jmp ISR_COMMON_STUB

; 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push byte 12
    jmp ISR_COMMON_STUB

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push byte 13
    jmp ISR_COMMON_STUB

; 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push byte 14
    jmp ISR_COMMON_STUB

; 15: Reserved Exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp ISR_COMMON_STUB

; 16: Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp ISR_COMMON_STUB

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp ISR_COMMON_STUB

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp ISR_COMMON_STUB

; 19: Reserved
isr19:
    cli
    push byte 0
    push byte 19
    jmp ISR_COMMON_STUB

; 20: Reserved
isr20:
    cli
    push byte 0
    push byte 20
    jmp ISR_COMMON_STUB

; 21: Reserved
isr21:
    cli
    push byte 0
    push byte 21
    jmp ISR_COMMON_STUB

; 22: Reserved
isr22:
    cli
    push byte 0
    push byte 22
    jmp ISR_COMMON_STUB

; 23: Reserved
isr23:
    cli
    push byte 0
    push byte 23
    jmp ISR_COMMON_STUB

; 24: Reserved
isr24:
    cli
    push byte 0
    push byte 24
    jmp ISR_COMMON_STUB

; 25: Reserved
isr25:
    cli
    push byte 0
    push byte 25
    jmp ISR_COMMON_STUB

; 26: Reserved
isr26:
    cli
    push byte 0
    push byte 26
    jmp ISR_COMMON_STUB

; 27: Reserved
isr27:
    cli
    push byte 0
    push byte 27
    jmp ISR_COMMON_STUB

; 28: Reserved
isr28:
    cli
    push byte 0
    push byte 28
    jmp ISR_COMMON_STUB

; 29: Reserved
isr29:
    cli
    push byte 0
    push byte 29
    jmp ISR_COMMON_STUB

; 30: Reserved
isr30:
    cli
    push byte 0
    push byte 30
    jmp ISR_COMMON_STUB

; 31: Reserved
isr31:
    cli
    push byte 0
    push byte 31
    jmp ISR_COMMON_STUB