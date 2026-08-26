#include "stdio.h"
#include "stdlib.h"

typedef struct no {
  int chave;
  struct no *esq;
  struct no *dir;
} no;

void rotacao_esquerda(no *p);
void rotacao_direita(no *p);
void rotacao_dupla_esquerda(no *p);
void rotacap_dupla_direita(no *p);
no *definir();
void insere_dir(no *pai, int elemento);
int vazia(no *raiz);
no *cria_no(int i, no *esq, no *dir);
void libera_no(no *t);
void insere_esq(no *pai, int elemento);
void imprime_arvore(no *raiz);

int main() {
  int valor;
  int controle;
  int aux = 3;

  no *t = definir();
  
  printf("Digite qual lado deseja inserir(1-esq e 2-dir):\n ");
  scanf("%i", &controle);

  if (controle == 1) {
    while (aux != 0) {
      printf("Digite o valor:\n ");
      scanf("%i", &valor);

      insere_esq(t, valor);
      aux--;
    }
    imprime_arvore(t);
    printf("\n");

    rotacao_esquerda(&t);
    imprime_arvore(t);
  } else {
    while (aux != 0) {
      printf("Digite o valor: ");
      scanf("%i", &valor);

      insere_dir(t, valor);
      aux--;
    }
    imprime_arvore(t);
    printf("\n");

    rotacao_direita(&t);
    imprime_arvore(t);
  }

  return 0;
}

void rotacao_esquerda(no *p) {
  no *aux = p->dir->esq;
  aux->esq = p;
  aux->dir = p->dir;
  p = aux;
}

void rotacao_direita(no *p) {
  no *aux = p->esq->dir;
  aux->esq = p->esq;
  aux->dir = p;
  p = aux;
}

void rotacao_dupla_esquerda(no *p) {
  no *aux = p->dir->esq;
  aux->esq = p;
  aux->dir = p->dir;
}

void rotacap_dupla_direita(no *p) {
  no *aux = p->esq->dir;
  aux->dir = p;
  aux->esq = p->esq;
}

no *definir() {
  return NULL;
}

int vazia(no *raiz) {
  if (raiz->chave)
    return 1;
  else
    return 0;
}

no *cria_no(int i, no *esq, no *dir) {
  no *aux = malloc(sizeof(no));

  aux->chave = i;
  aux->esq = esq;
  aux->dir = dir;

  return aux;
}

void libera_no(no *t) {
  no *aux = malloc(sizeof(no));

  aux->chave = t->dir->chave;
  aux->dir = t->dir->dir;
  aux->esq = t->esq;

  t = NULL;
}

void insere_esq(no *pai, int elemento) {
  if (pai->esq != NULL)
    return;

  no *aux = malloc(sizeof(no));

  aux->chave = elemento;
  pai->esq = aux;
  aux->esq = NULL;
  aux->dir = NULL;

  return;
}

void insere_dir(no *pai, int elemento) {
  if (pai->dir != NULL)
    return;
  
  no *aux = malloc(sizeof(no));

  aux->chave = elemento;
  pai->dir = aux;
  aux->esq = NULL;
  aux->dir = NULL;

  return;
}

void imprime_arvore(no *raiz) {
  if (raiz == NULL)
    return;
  printf("%i ", raiz->chave);
  imprime_arvore(raiz->esq);
  imprime_arvore(raiz->dir);
}