.SECTION .data
    array: .word 5, 3, 8, 4, 2
    length: .word 5

.SECTION .text
    .globl bubble_sort
bubble_sort:
    mov length, %cx
    dec %cx

outer_loop:
    mov %cx, %dx
    mov $0, %si

inner_loop:
    mov array(%si), %ax
    mov array+2(%si), %bx
    cmp %bx, %ax
    jge no_swap

    mov %bx, array(%si)
    mov %ax, array+2(%si)

no_swap:
    add $2, %si
    dec %dx
    jnz inner_loop

    dec %cx
    jnz outer_loop

    ret
