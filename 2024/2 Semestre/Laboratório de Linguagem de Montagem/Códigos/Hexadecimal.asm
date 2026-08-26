.model small
.stack 100h
.data
    prompt1 db 'Digite um digito hexadecimal (0-9, A-F): $'
    prompt2 db 'Deseja continuar? (S/N): $'
    msg_error db 'Entrada fora do intervalo hexadecimal. $'
    newline db 0Dh, 0Ah, '$'

    input db ?
    continue db ?
    value db ?

.code
main proc 
    mov ax, @data
    mov ds, ax

start:
    lea dx, prompt1
    mov ah, 09h
    int 21h

    mov ah, 01h
    int 21h
    mov input, al

    cmp input, '0'
    jb invalid_input
    cmp input, '9'
    jbe convert_to_decimal
    cmp input, 'A'
    jb invalid_input
    cmp input, 'F'
    jbe convert_to_decimal

invalid_input:
    lea dx, msg_error
    mov ah, 09h
    int 21h
    lea dx, newline
    mov ah, 09h
    int 21h
    jmp start

convert_to_decimal:
    mov al, input
    sub al, '0'
    cmp al, 9
    jbe done_conversion
    sub al, 7  
done_conversion:
    lea dx, newline
    mov ah, 09h
    int 21h

    mov al, dl
    add dl, '0'
    mov ah, 02h
    int 21h

    lea dx, newline
    mov ah, 09h
    int 21h

    lea dx, prompt2
    mov ah, 09h
    int 21h

    mov ah, 01h
    int 21h
    mov continue, al

    cmp continue, 'S'
    je start

    mov ah, 4Ch
    int 21h

main endp
end main