.MODEL SMALL
.STACK 100h

.DATA
    vetor DB 'e', 'a', 'f', 'j', 'z'
    n EQU 5
    msg_desordenado DB 'Vetor desordenado: $'
    msg_ordenado DB 'Vetor ordenado: $'
    buffer DB n + 1 DUP(?)

.CODE
START:
    ; Inicia a execução
    MOV AX, @DATA
    MOV DS, AX

    ; Exibe a mensagem "Vetor desordenado: "
    LEA DX, msg_desordenado
    MOV AH, 09h
    INT 21h

    CALL print_vetor

    ; Inicia a ordenação por bubble sort
    MOV CX, n
    DEC CX

ordena_bubble:
    XOR BX, BX
    LEA SI, vetor
    MOV DI, CX

compara:
    MOV AL, [SI]
    MOV AH, [SI+1]
    CMP AL, AH
    JBE no_swap

    ; Faz a troca
    MOV [SI], AH
    MOV [SI+1], AL

no_swap:
    INC SI
    DEC DI
    JNZ compara

    DEC CX
    JNZ ordena_bubble

    ; Exibe a mensagem "Vetor ordenado: "
    LEA DX, msg_ordenado
    MOV AH, 09h
    INT 21h

    CALL print_vetor

    ; Termina o programa
    MOV AH, 4Ch
    INT 21h

print_vetor PROC
    XOR BX, BX
    LEA SI, vetor
    MOV CX, n

print_loop:
    MOV AL, [SI]
    MOV [buffer+BX], AL
    INC BX
    INC SI
    DEC CX
    JNZ print_loop

    ; Adiciona uma nova linha ao final do buffer
    MOV BYTE PTR [buffer+BX], '$'  ; Terminador de string para o DOS
    MOV AH, 09h
    LEA DX, buffer
    INT 21h
    RET
print_vetor ENDP

END START  ; Define o ponto de entrada do programa
