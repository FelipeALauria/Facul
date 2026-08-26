#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct letras{
  char pal[50];
  struct letras *prox;
}palavra;

palavra *alocar(char *novapal){
  palavra *nova = malloc(sizeof(palavra));
  strcpy(nova->pal, novapal);
  nova->prox = NULL;
  return(nova);
}

palavra *insere(palavra *, palavra *);
void retira(palavra **, char *);
void imprimir(palavra *);

int main(void) {
  int N, M, i, op;
  
  scanf("%d %d", &N, &M); //N = nº inicial de palavras / M = nº operações
  char novapalavra[50];
  palavra *aux;
  palavra *head;
  head = NULL;

  for(i=0; i<N; i++){
    scanf(" %s", novapalavra);
    aux = alocar(novapalavra);
    head = insere(head, aux);
    }
  for(i=0; i<M; i++){
    scanf("%d %s", &op, novapalavra);
    if(op==1){ //insere palavra
      aux = alocar(novapalavra);
      head = insere(head, aux); 
    }else if(op==0){ //remove palavra
      retira(&head, novapalavra);
      if(head==NULL)
        printf("NULL\n");
      else
        imprimir(head);
    }
  }
  
  return 0;
}

palavra *insere(palavra *h, palavra *p){
  palavra *antes, *aux;
  if(!h)
    return p;
  aux = antes = h;
  while(aux->prox && strcmp(p->pal, aux->pal) > 0){
    antes = aux;
    aux = aux->prox;
  }
  if(aux == h){
    if(strcmp(p->pal, h->pal) < 0){
      p->prox = h;
      return p;
    } else if(strcmp(p->pal, h->pal) > 0){
      p->prox = h->prox;
      h->prox = p;
      return h;
    }else{
      return h;
    }
  }

  if(strcmp(p->pal, aux->pal) < 0){
    antes->prox = p;
    p->prox = aux;
    return h;
  }else if(strcmp(p->pal, aux->pal) > 0){
    p->prox = aux->prox;
    aux->prox = p;
    return h;
  }else{
    return h;
  }
}

void retira(palavra **h, char *novapalavra){
  palavra *aux, *antes;
  aux = *h;
  if(aux != NULL && strcmp(aux->pal, novapalavra)==0){
    *h = aux->prox;
    free(aux);
    return;
  }
  while(aux != NULL && strcmp(aux->pal, novapalavra)!=0){
    antes = aux;
    aux = aux->prox;
  }
  if(aux==NULL)
    return;
  antes->prox = aux->prox;
  free(aux);
}

void imprimir(palavra *head){
  palavra *aux = head;
  while(aux != NULL){
    printf("%s ", aux->pal);
    aux = aux->prox;
  }
  printf("\n");
}