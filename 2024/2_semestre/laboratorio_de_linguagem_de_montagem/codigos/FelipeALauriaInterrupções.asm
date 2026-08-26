.model small
.stack 100h
.data
    msgA db 'Tecla A pressionada!$'
    msgB db 'Tecla B pressionada!$'
    msgEnd db 'Programa finalizado.$'
    buffer db 5 dup('$')

.code
main:
    mov ax, @data
    mov ds, ax

loop:
    mov ah, 1
    int 21h
    cmp al, 'A'
    je teclaA
    cmp al, 'B'
    je teclaB
    cmp al, 27 
    je fim
    jmp loop

teclaA:
    mov ah, 09h
    lea dx, msgA
    int 21h
    call store_char
    jmp loop

teclaB:
    mov ah, 09h
    lea dx, msgB
    int 21h
    call store_char
    jmp loop

store_char:
    mov di, offset buffer
    mov cx, 5
store_loop:
    cmp byte ptr [di], '$'
    je store_here
    inc di
    loop store_loop
    ret

store_here:
    mov [di], al
    ret

fim:
    mov ah, 09h
    lea dx, msgEnd
    int 21h
    mov ah, 4Ch
    int 21h
    
end main