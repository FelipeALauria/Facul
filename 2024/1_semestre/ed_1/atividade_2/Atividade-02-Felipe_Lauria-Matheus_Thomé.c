//Felipe Lauria e Matheus Thomé

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  int valor;
  struct no *esq;
  struct no *dir;
  int altura;
} no;

int altura(no *pai);
int balancear(no *pai);
void pre_ordem(no *pai);
no *rotacao_esq(no *pai);
no *rotacao_dir(no *pai);
int max(int a, int b);
no *min(no *pai);
no *apagar_no(no *pai, int info);
no *inserir_no(no *pai, int info);
no *novo_no(int info);

int main() {
  no *AVL = NULL;
  AVL = inserir_no(AVL, 9);
  AVL = inserir_no(AVL, 10);
  AVL = inserir_no(AVL, 12);
  
  printf("Preordem da AVL: \n");
  pre_ordem(AVL);

  AVL = inserir_no(AVL, 5);

  printf("\nPreordem da AVL: \n");
  pre_ordem(AVL);

  AVL = apagar_no(AVL, 10);

  printf("\nPreordem da AVL depois de apagar o valor 10 \n");
  pre_ordem(AVL);

  return 0;
}

int altura(no *pai) {
  if (pai == NULL)
    return 0;
  else
    return pai->altura;
}

int balancear(no *pai) {
  if (pai == NULL)
    return 0;
  return altura(pai->esq) - altura(pai->dir);
}

void pre_ordem(no *pai) {
  if (pai != NULL) {
    printf("%d ", pai->valor);
    pre_ordem(pai->esq);
    pre_ordem(pai->dir);
  }
}

no *rotacao_esq(no *pai) {
  no *aux = pai->dir;
  no *aux2 = aux->esq;

  aux->esq = pai;
  pai->dir = aux2;

  pai->altura = max(altura(pai->esq), altura(pai->dir)) + 1;
  aux->altura = max(altura(aux->esq), altura(aux->dir)) + 1;

  return aux;
}

no *rotacao_dir(no *pai) {
  no *aux = pai->esq;
  no *aux2 = aux->dir;

  aux->dir = pai;
  pai->esq = aux2;

  pai->altura = max(altura(pai->esq), altura(pai->dir)) + 1;
  aux->altura = max(altura(aux->esq), altura(aux->dir)) + 1;

  return aux;
}

int max(int a, int b) { return (a > b) ? a : b; }

no *min(no *node) {
  no *aux = node;
  while (aux->esq != NULL)
    aux = aux->esq;

  return aux;
}

no *apagar_no(no *pai, int info) {
  if (pai == NULL)
    return pai;

  if (info < pai->valor)
    pai->esq = apagar_no(pai->esq, info);
  else if (info > pai->valor)
    pai->dir = apagar_no(pai->dir, info);

  else {
    if ((pai->esq == NULL) || (pai->dir == NULL)) {
      no *aux = pai->esq ? pai->esq : pai->dir;

      if (aux == NULL) {
        aux = pai;
        pai = NULL;
      } else {
        *pai = *aux;
        free(aux);
      }
    } else {
      no *aux = min(pai->dir);

      pai->valor = aux->valor;

      pai->dir = apagar_no(pai->dir, aux->valor);
    }
  }

  if (pai == NULL)
    return pai;

  pai->altura = 1 + max(altura(pai->esq), altura(pai->dir));

  int FB = balancear(pai);

  if (FB > 1 && balancear(pai->esq) >= 0)
    return rotacao_dir(pai);

  if (FB > 1 && balancear(pai->esq) < 0) {
    pai->esq = rotacao_esq(pai->esq);
    return rotacao_dir(pai);
  }

  if (FB < -1 && balancear(pai->dir) <= 0)
    return rotacao_esq(pai);

  if (FB < -1 && balancear(pai->dir) > 0) {
    pai->dir = rotacao_dir(pai->dir);
    return rotacao_esq(pai);
  }

  return pai;
}

no *inserir_no(no *pai, int info) {
  if (pai == NULL)
    return (novo_no(info));

  if (info < pai->valor)
    pai->esq = inserir_no(pai->esq, info);
  else if (info > pai->valor)
    pai->dir = inserir_no(pai->dir, info);
  else
    return pai;

  pai->altura = 1 + max(altura(pai->esq), altura(pai->dir));

  int FB = balancear(pai);

  if (FB > 1 && info < pai->esq->valor)
    return rotacao_dir(pai);

  if (FB < -1 && info > pai->dir->valor)
    return rotacao_esq(pai);

  if (FB > 1 && info > pai->esq->valor) {
    pai->esq = rotacao_esq(pai->esq);
    return rotacao_dir(pai);
  }

  if (FB < -1 && info < pai->dir->valor) {
    pai->dir = rotacao_dir(pai->dir);
    return rotacao_esq(pai);
  }

  return pai;
}

no *novo_no(int valor) {
  no *novo = malloc(sizeof(no));
  novo->valor = valor;
  novo->esq = NULL;
  novo->dir = NULL;
  novo->altura = 1;
  return (novo);
}