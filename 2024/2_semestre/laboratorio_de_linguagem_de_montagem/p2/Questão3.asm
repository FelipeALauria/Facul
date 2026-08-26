org 100h

msg_input db "Digite um numero decimal (0-255): $"
msg_output db "Representacao binaria (8 bits): $"
buffer db 3, 0
binario db 8 dup('0')
newline db 0Dh, 0Ah, '$'
divisor db 2

start:
    mov ah, 09h
    lea dx, msg_input
    int 21h

    lea dx, buffer
    mov ah, 0Ah
    int 21h

    lea si, buffer + 1
    xor cx, cx
conv_num:
    lodsb
    cmp al, 0Dh
    je convert_done
    sub al, '0'
    mov ax, cx
    mov bx, 10
    mul bx
    add ax, bx
    mov cx, ax
    jmp conv_num
convert_done:
    cmp cx, 255
    ja invalid_input

    mov ax, cx
    lea di, binario + 7
    mov cl, 8
convert_binary:
    xor dx, dx
    mov bl, [divisor]
    div bl
    add ah, '0'
    mov [di], ah
    dec di
    dec cl
    mov ax, 0
    mov al, ah
    jnz convert_binary

    mov ah, 09h
    lea dx, newline
    int 21h
    lea dx, msg_output
    int 21h
    lea dx, newline
    int 21h

    lea dx, binario
    mov ah, 09h
    int 21h
    jmp exit

invalid_input:
    mov ah, 09h
    lea dx, newline
    int 21h
    lea dx, msg_input
    int 21h

exit:
    mov ah, 4Ch
    int 21h
