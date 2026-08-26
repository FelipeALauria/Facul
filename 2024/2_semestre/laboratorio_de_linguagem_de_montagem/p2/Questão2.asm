org 100h

msg db "Enter a number (max 10): $"
newline db 0Dh, 0Ah  
fib db 10 dup(0)  

start:
    mov ah, 09h
    lea dx, msg
    int 21h

    mov ah, 01h
    int 21h
    sub al, '0'       
    mov bl, al       
    mov bh, 0         
    cmp bx, 10        
    ja end           

    mov byte ptr [fib], 1
    mov byte ptr [fib+1], 1

    mov cx, 2         
calc_fib:
    mov si, cx        
    dec si            
    mov al, [fib + si] 
    dec si            
    add al, [fib + si] 
    mov si, cx        
    mov [fib + si], al 
    inc cx
    cmp cx, bx        
    jb calc_fib

    mov cx, 0
print_fib:
    mov si, cx      
    mov al, [fib + si] 
    add al, '0'      
    mov dl, al
    mov ah, 02h       
    int 21h

    mov dl, 0Dh       
    mov ah, 02h
    int 21h

    mov dl, 0Ah       
    mov ah, 02h
    int 21h

    inc cx
    cmp cx, bx        
    jb print_fib

end:
    mov ah, 4Ch
    int 21h
