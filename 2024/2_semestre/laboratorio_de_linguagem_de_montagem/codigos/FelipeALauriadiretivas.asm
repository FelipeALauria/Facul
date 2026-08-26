.SECTION .data
    contador: .word 0
    .space 2

.SECTION .text
    .globl incrementa_contador
incrementa_contador:
    mov $0, %ax
loop_incrementa:
    inc %ax
    mov %ax, contador
    cmp $6, %ax
    jne loop_incrementa
    ret

    .globl ADD
ADD:
    mov $0, %ax
loop_add:
    inc %ax
    cmp $6, %ax
    jne loop_add
    ret