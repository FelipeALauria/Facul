.MODEL SMALL
.STACK 100h

.DATA
    vetor DB 2, 4, 1, 7, 0, 8, 6, 3, 9, 5
    n EQU 10
    msg_desordenado DB 'Vetor desordenado: $'
    msg_ordenado DB 'Vetor ordenado: $'
    buffer DB 3 DUP(?)

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

    ; Começa o bubble sort
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
    ADD AL, '0'
    MOV [buffer+BX], AL
    INC BX
    INC SI
    DEC CX
    JNZ print_loop

    MOV BYTE PTR [buffer+BX], '$'  ; Termina a string com $
    MOV AH, 09h
    LEA DX, buffer
    INT 21h
    RET
print_vetor ENDP

END START  ; Define o ponto de entrada aqui
