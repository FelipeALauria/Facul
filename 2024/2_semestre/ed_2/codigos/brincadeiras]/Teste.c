#include "stdio.h"
#include "stdlib.h"

typedef struct node{
    int key;
    struct node *esq;
    struct node *dir;
}no;

void inserir_no_folha(no **a, int chave);
int printar(no *a);

int main() {
    int a = 10;
    no *b;
    b = malloc(sizeof(no));
    inserir_no_folha(&b,a);
    printf("O número é: %d", printar(b));
}

void inserir_no_folha(no **a,int chave) {
    *a = malloc(sizeof(no));
    (*a)->key = chave;
    (*a)->esq = NULL;
    (*a)->dir = NULL;
}

int printar(no *a) {
    return(a->key);
}