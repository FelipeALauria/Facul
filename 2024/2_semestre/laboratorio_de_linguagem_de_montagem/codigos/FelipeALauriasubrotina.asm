main:   
    mov al, 2                                                            
    mov bl, 3
    add al, 30h
    add bl, 30h
    mov cl, al
    
    mov dl, al     
    mov ah, 02h
    int 21h
    mov dl, bl
    mov ah, 02h
    int 21h
    mov al, cl
    
    call subrotina 
    
    mov dl, al
    mov ah, 02h
    int 21h
    mov dl, bl
    mov ah, 02h
    int 21h
    

subrotina: 
    push ax
    push bx
    
    pop ax
    pop bx
           
    ret       

    