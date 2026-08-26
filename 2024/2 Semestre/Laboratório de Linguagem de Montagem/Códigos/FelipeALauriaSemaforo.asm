STATUS  equ 03h
TRISA   equ 85h
TRISB   equ 86h
PORTA   equ 05h
PORTB   equ 06h
INTCON  equ 0Bh
OPTION_REG equ 81h

GIE     equ 7
INTE    equ 4
INTF    equ 1

VERMELHO equ 8
AMARELO  equ 2
VERDE    equ 8
DELAY_PED equ 4
DELAY_TRAV equ 5

org 0x00
    goto start

org 0x04
    goto interrupcao

start:
    bsf STATUS, RP0
    movlw 0x00
    movwf TRISA
    movwf TRISB
    bcf STATUS, RP0

    bsf INTCON, GIE
    bsf INTCON, INTE

main_loop:
    call semaforo_normal
    goto main_loop

interrupcao:
    btfss INTCON, INTF
    retfie
    bcf INTCON, INTF
    call estado_seguranca
    retfie

semaforo_normal:
    call verde_A_vermelho_B
    call delay_verde

    call amarelo_A_vermelho_B
    call delay_amarelo

    call vermelho_A_verde_B
    call delay_verde

    call vermelho_A_amarelo_B
    call delay_amarelo

    return

estado_seguranca:
    call piscar_amarelo_AB
    goto estado_seguranca

verde_A_vermelho_B:
    return

amarelo_A_vermelho_B:
    return

vermelho_A_verde_B:
    return

vermelho_A_amarelo_B:
    return

piscar_amarelo_AB:
    return

delay_verde:
    return

delay_amarelo:
    return

end
