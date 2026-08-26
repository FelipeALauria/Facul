.model small
.stack 100h
.data           
; Secaoo de dados

adivinheMSG db 'Adivinhe o numero sorteado! O numero sorteado esta entre 0 e 9, incluindo os dois:', 13, 10, '$'
input dw ?       ; Define 2 bytes para armazenar o input do usuário
random dw ? ; Define 2 bytes para o numero gerado
seed dw 0 ; Define 2 bytes                
positiva db 13,10, 'Parabens! O numero sorteado foi igual ao digitado ', 13, 10, '$'
negativa db 13,10, 'Nao foi dessa vez, o numero digitado foi diferente do sorteado ', 13, 10, '$'   
randomMSG db 'O Numero sorteado foi: ', 13, 10, '$'

.start    

    mov ax, @data
    mov ds, ax
    

    ; Escreve a mensagem adivinheMSG
    mov ah, 09h
    lea dx, adivinheMSG
    int 21h   ;Exibe a String

    ; Le um caractere de entrada do usuário
    mov ah, 01h                  ; Funcao 01h para ler um caractere
    int 21h                      ; Interrompe para receber a entrada
    mov [input], ax              ; Armazena o caractere de entrada em 'input'
    call random_number         ;chama a funcao para gerar o numero
    call imprime_resultado  ; imprime o numero
    
                        
 
 
random_number:    
    mov ah, 0          ; Funcao 0 de INT 1Ah - Retorna tempo
    int 1Ah            ; Chama a interrupcao 
    mov [seed], dx     ; Usa o valor de DX (tempo) como semente

    mov ax, [seed]     ; Carrega o valor atual da semente em AX
    mov cx, 1103515245 & 0xFFFF ; Parte baixa do multiplicador (16 bits)
    mul cx             ; AX = AX * CX (multiplicação de 16 bits) // armazena em AX!
    add ax, 12345      ; Adiciona o incremento "c" (12345)

    

    ; Divisao para obter o modulo 10
    mov bx, 10         ; Divisor para obter numeros de 0 a 9
    xor dx, dx         ; Limpa DX para evitar problemas na divisao
    div bx             ; AX / BX -> quociente em AX, resto em DX, usaremos apenas o resto
    mov [random],dx
    
ret

imprime_resultado:
    mov ax, [random] ;Carrega o numero gerado em AX
    mov bx, [input]  ;Carrega o numero digitado em BX
    sub bx, 30h   ;ADiciona 30h (Tabela ASCII)
    xor bh,bh   ;Limpa BX
    cmp ax,bx   ; Compara e pula para "acertou" caso seja o certo
    je acertou
    
    
errou:
    mov ah, 09h        ; Funcao para exibir string
    lea dx, negativa   ; Carrega o endereço de negativa
    int 21h            ; Exibe a string
    jmp fim            ; Pula para o fim do programa

acertou:
    mov ah, 09h        ; Funcao para exibir string
    lea dx, positiva   ; Carrega o endereço de positiva
    int 21h            ; Exibe a string
    jmp fim            ; Pula para o fim do programa         
     
    
fim:
   ; Encerrar o programa    
    call imprime_sorteado_input
    mov ax, 4C00h                ; Funcaoo de saida do DOS
    int 21h  
    
    
imprime_sorteado_input:
    mov ah, 09h       ; Funcaoo 09h para exibir string
    lea dx, randomMSG ; Carrega o endereço de randomMSG
    int 21h           ; Exibe a String
    
    mov ah, 02h       ; Funcao para imprimir o valor do registrador dl
    mov dx, [random]  ; Carrega o numero gerado
    add dl, 30h       ; Soma 30h (Tabela ASCII)
    int 21h           ; Exibe o numero sorteado
    ret