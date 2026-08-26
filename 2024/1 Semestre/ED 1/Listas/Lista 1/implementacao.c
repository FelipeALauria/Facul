#include "stdio.h"
#include "stdlib.h"

typedef struct no {
    int info;
    struct no *esq;
    struct no *dir;
} no;


no* definir ();
int insere_dir (no *pai, int elemento);
int vazia (no *raiz);
no *cria_no (int i, no *esq, no *dir);
no *libera_no (no *t);
int insere_esq (no *pai, int elemento);
void imprime_arvore (no *raiz);

int main ()  {
    int valor;
    int controle;

    no *t = NULL;

    printf("Digite quantos nós deseja adicionar: ");
    scanf("%d", &controle);

    for (int i = 0; i < controle; i++) {
        printf("Digite o valor: ");
        scanf("%i", &valor);

        if(t == NULL)
          t = definir();

        definir(t);

        int aux;

        if (valor > aux) {
            insere_dir(t, valor);
        }
        else {
            insere_esq(t, valor);
        }

        aux = valor;
    }

  return 0;
}

no* definir (){
    return NULL;
}

int vazia (no *raiz) {
    if (raiz->info)
        return 1;
    else
        return 0;
}

no *cria_no (int i, no *esq, no *dir) {
    no *aux = malloc(sizeof(no));

    aux->info = i;
    aux->esq = esq;
    aux->dir = dir;

    return aux;
}

no *libera_no (no *t) {
    no *aux = malloc(sizeof(no));

    aux->info = t->dir->info;
    aux->dir = t->dir->dir;
    aux->esq = t->esq;

    t = NULL;

    return aux;
}

int insere_esq (no *pai, int elemento) {
    if (pai->esq != NULL)
        return 0;

    no *aux = malloc(sizeof(no));

    aux->info = elemento;
    pai->esq = aux;
    aux->esq = NULL;
    aux->dir = NULL;

    return 1;
}

int insere_dir (no *pai, int elemento) {
    if (pai->esq != NULL)
        return 0;

    no *aux = malloc(sizeof(no));

    aux->info = elemento;
    pai->dir = aux;
    aux->esq = NULL;
    aux->dir = NULL;

    return 1;
}

void imprime_arvore (no *raiz) {
    if (raiz == NULL)
        return;
    printf("%i ", raiz->info);
    imprime_arvore (raiz->esq);
    imprime_arvore (raiz->dir);
}