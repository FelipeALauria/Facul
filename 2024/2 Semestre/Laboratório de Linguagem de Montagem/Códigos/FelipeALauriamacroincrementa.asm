inc_by_one macro reg
    inc reg
    mov dl, al
    mov ah, 02h
    int 21h
ENDM
    
    mov al, 5
    add al, 30h
    mov dl, al
    mov ah, 02h
    int 21h
    inc_by_one al
    inc_by_one al 
    inc_by_one al 
    