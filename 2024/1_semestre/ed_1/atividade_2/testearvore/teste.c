#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "teste.h"

int main() {
    tree t;
    define(t);

    srand(time(NULL));

    int x = rand() %11;
    data knot;

    knot.num = x;

    createRoot(t, knot);

    knot.num = x;
    insertleft(t, knot);
    knot.num = x;
    insertright(t, knot);

    knot.num = x;
    insertleft(t->left, knot);
    knot.num = x;
    insertright(t->right, knot);

    knot.num = x;
    insertleft(t->right, knot);
    knot.num = x;
    insertright(t->right, knot);

    int control;
    scanf("%d", &control);

    if(control == 0) {
        return empty(t);
    }

    else if(control == 1) {
        printf("Altura é: %d", height(t));
    }

    else if(control == 2) {
        printf("Número de nós é: %d", numberknots(t));
    }

    else {
        printf("Opção invalida");
    }

  return 0;
}