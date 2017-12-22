[bits 32]
VIDEO_MEMORY equ 0xb8000 ; Video memory equal to 0xb8000? 
WHITE_ON_BLACK equ 0x0f ; White on black equal to 0x0f?

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY ; Sets edx to the start of video memory

print_string_pm_loop:
    mov al, [ebx] ; stores the character at ebx in al
    mov ah, WHITE_ON_BLACK
    cmp al, 0  ; compares al to 0
    je print_string_pm_done ; if al is equal to 0 jump to print_string_pm_done
    mov [edx], ax
    add ebx, 1
    add edx, 2

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret