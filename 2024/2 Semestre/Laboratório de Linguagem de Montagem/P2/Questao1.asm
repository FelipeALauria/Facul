.model small
.stack 100h

.data
    msg1 db 'Digite uma palavra (max 10 caracteres): $'
    msg2 db ' e palindromo.$'
    msg3 db ' Nao e palindromo.$'
    palavra db 11 dup('$')
    inversa db 11 dup('$')

.code
main proc
    mov ax, @data
    mov ds, ax

    lea dx, msg1
    mov ah, 09h
    int 21h

    lea dx, palavra
    mov ah, 0Ah
    int 21h

    lea si, palavra
    mov cl, [si + 1]
    mov ch, 0
    mov bx, cx
    lea si, palavra + 2
    lea di, inversa
    add si, cx
    dec si

palindrome_loop:
    mov al, [si]
    mov [di], al
    dec si
    inc di
    loop palindrome_loop
    mov byte ptr [di], '$'

    lea si, palavra + 2
    lea di, inversa
    mov cx, bx

compare_loop:
    mov al, [si]
    mov ah, [di]
    cmp al, ah
    jne not_palindrome
    inc si
    inc di
    loop compare_loop

    lea dx, msg2
    jmp display_message

not_palindrome:
    lea dx, msg3

display_message:
    mov ah, 09h
    int 21h

    mov ah, 4Ch
    int 21h
main endp
end main