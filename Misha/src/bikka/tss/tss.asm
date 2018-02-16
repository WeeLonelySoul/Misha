global TSS_FLUSH

TSS_FLUSH:
    mov ax, 0x2B

    ltr ax
    ret