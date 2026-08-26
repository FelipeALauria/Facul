#include <stdio.h>
#include <stdlib.h>

typedef struct pessoa{
  int idade;
  int tempo;
  struct pessoa *prox;
}Fila;

void insere_fila(Fila **, Fila **, int, int);
void prioridade(Fila **, Fila **, int, int);
void remover(Fila **, Fila **);
void imprime(Fila *);

int main(void) {
  int i, N, I, T, atend=3, idade, t_tot, inseriu=1;
  Fila *cabecaux = NULL, *caudaux = NULL, *head = NULL, *tail = NULL;

  scanf("%d", &N);

  for(i=0; i<N; i++){
    scanf("%d %d", &I, &T);
    insere_fila(&cabecaux, &caudaux, I, T);
  }

  idade = cabecaux->idade;
  t_tot = cabecaux->tempo;

  prioridade(&head, &tail, cabecaux->idade, cabecaux->tempo);
  remover(&cabecaux, &caudaux);

  while(!(cabecaux == NULL && head == NULL)){
    if(atend >= 3){
      atend = 0;
      if(head == NULL){
        prioridade(&head, &tail, cabecaux->idade, cabecaux->tempo);
        t_tot = cabecaux->tempo;
        remover(&cabecaux, &caudaux);
        inseriu = 1;
      }
      idade = head->idade;
      remover(&head, &tail);
    }
    while(cabecaux != NULL && t_tot >= cabecaux->tempo){
      prioridade(&head, &tail, cabecaux->idade, cabecaux->tempo);
      remover(&cabecaux, &caudaux);
      inseriu=1;
    }
    if(inseriu){
      printf("%d ", idade);
      imprime(head);
    }
    inseriu=0;
    t_tot++;
    atend++;
  }
  return 0;
}

void insere_fila(Fila **inicio, Fila **fim, int id, int t){
  Fila *novo = malloc(sizeof(Fila)), *aux, *antes;
  novo->idade = id;
  novo->tempo = t;

  if(*inicio == NULL){
    *inicio = novo;
    *fim = novo;
    (*inicio)->prox  = NULL;
    return;
  }
  if(novo->tempo < (*inicio)->tempo || (novo->tempo == (*inicio)->tempo && novo->idade > 59 && novo->idade > (*inicio)->idade)){
    novo->prox = *inicio;
    *inicio = novo;
    return;
  }
  if(novo->tempo > (*fim)->tempo){
    novo->prox = NULL;
    (*fim)->prox = novo;
    *fim = novo;
    return;
  }
  
  aux = (*inicio)->prox;
  antes = *inicio;
  
  while(aux != NULL){
    if(novo->tempo < aux->tempo || (novo->tempo == aux->tempo && novo->idade > 59 && novo->idade > aux->idade)){
      antes->prox = novo;
      novo->prox = aux;
      return;
    }
    antes = aux;
    aux = aux->prox;
  }
   if(novo->tempo == (*inicio)->tempo && ((*inicio)->prox == NULL || (*inicio)->prox->tempo != novo->tempo)){
    novo->prox = (*inicio)->prox;
    (*inicio)->prox = novo;
    return;
  }

  aux = (*inicio)->prox;
  
  while(aux != NULL){
    if(novo->tempo == aux->tempo && (aux->prox == NULL || aux->prox->tempo != novo->tempo)){
      novo->prox = aux->prox;
      aux->prox = novo;
      if(novo->prox == NULL) 
        *fim = novo;
      return;
    }
    aux = aux->prox;
  }
}

void prioridade(Fila **inicio, Fila **fim, int id, int t){
  Fila *novo = malloc(sizeof(Fila)), *aux, *antes;
  novo->idade = id;
  novo->tempo = t;

   if(*inicio == NULL){
    *inicio = novo;
    *fim = novo;
    novo->prox = NULL;
    return;
  }
  if(novo->idade > 59){
    if(novo->idade > (*inicio)->idade){
      novo->prox = *inicio;
      *inicio = novo;
      return;
    }
    aux = (*inicio)->prox;
    antes = (*inicio);
    while(aux != NULL){
      if(novo->idade > aux->idade){
        antes->prox = novo;
        novo->prox = aux;
        return;
      }
      antes = aux;
      aux = aux->prox;
    }
  }
  (*fim)->prox = novo;
  novo->prox = NULL;
  *fim = novo;
}

void remover(Fila **inicio, Fila **fim){
  if(*inicio == NULL) 
    return;
  if((*inicio)->prox == NULL){
    free(*inicio);
    *fim = NULL;
    *inicio = NULL;
    return;
  }
  if((*inicio)->prox == *fim){
    free(*inicio);
    *inicio = *fim;
    return;
  }
  Fila *aux = *inicio;
  *inicio = (*inicio)->prox;
  free(aux);
}

void imprime(Fila *cabeca){
  while(cabeca != NULL){
    printf("%d ", cabeca->idade);
    cabeca = cabeca->prox;
  }
  printf("\n");
}