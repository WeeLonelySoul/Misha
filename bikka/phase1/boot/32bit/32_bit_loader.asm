[org 0x7c00]
KERNEL_OFFSET equ 0x1000 ; memory offset to which we will load our kernel
mov [BOOT_DRIVE], dl


mov bp, 0x9000
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

call load_kernel
call switch_to_pm

jmp $

%include "16_bit_files/disk_load.asm"
%include "16_bit_files/print_string.asm"
%include "GDT.asm"
%include "print.asm"
%include "switch_to_pm.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string
    mov bx, KERNEL_OFFSET
    mov dh, 15 ; Load the first 15 sectors of our hdd
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret


[bits 32]

BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    call KERNEL_OFFSET

    jmp $

; Global variables
; 13, 10, = "newline"
BOOT_DRIVE db 0
MSG_REAL_MODE db "Successfully launched 16-bit Real Mode",13, 10, 0
MSG_PROT_MODE db "Successfully launched 32-bit Protected Mode",0
MSG_LOAD_KERNEL db "Loading Kernel into memory.", 0

times 510-($-$$) db 0
dw 0xaa55