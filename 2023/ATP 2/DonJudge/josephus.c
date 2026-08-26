#include <stdio.h>
#include <stdlib.h>

typedef struct No{
   int id; //identificador
   int k; //quantos vai andar
   int op; //remover=0; inserir=1
  struct No *prox;
}No;

typedef struct Lista{
   No *inicio;
   No *fim;
   int tam;
}Lista; 

No *cria_lista(Lista *, int, int, int);
int roda(Lista *, No *, int);
void remover(Lista *, int);
void insere(Lista *, No *);

int main(void) {
  int N, i, K, O, res;
  Lista lista;
  No *h;
  //inicializando a lista (no começo está vazia)
  lista.inicio = NULL;
  lista.fim = NULL;
  lista.tam = 0;
  
  scanf("%d", &N); //número de pessoas na lista
  
  for(i=0; i<N; i++){ //laço para inserir na lista
    scanf("%d %d", &K, &O);
    h = cria_lista(&lista, i+1, K, O);
  }
 
  res = roda(&lista, h, h->k);
  printf("%d", res); 
  
  return 0;
}

//função que insere os elementos na lista circular
No *cria_lista(Lista *lista, int I, int K, int O){
  No *aux, *novo = malloc(sizeof(No));

  novo->id = I;
  novo->k = K;
  novo->op = O;
  
  if(lista->inicio == NULL){ //se a lista está vazia, insiro o primeiro elem
    lista->inicio = novo;
    lista->fim = novo;
    lista->fim->prox = lista->inicio;
  }else{ //se a lista não estiver vazia, insiro elem e faço o fim apontar para o inicio
    lista->fim->prox = novo;
    lista->fim = novo;
    novo->prox = lista->inicio;
  }
  lista->tam++; //inseri um elemento na lista
  return lista->inicio; //retorno a cabeça 
}

//função que vai realizar as operações desejadas
int roda(Lista *lista, No *comeco, int k){
  No *aux = comeco, *atual = comeco;
  No *ult_rem; //vai apontar para o ultimo removido
  int id, op, i;

  while(lista->tam > 1){ //quando só tiver 1 elem, retorno ele
    for(i=0; i < (k-1); i++){ //laço para achar o elemento que será retirado
      atual = atual->prox;
    }
    k = atual->k; //quanto vai andar
    op = atual->op; //qual opção
  
    if(op == 0){ //removo o elem da posição atual
      //armazeno o elem que vai ser retirado 
      ult_rem = malloc(sizeof(No));
      ult_rem->id = atual->id;
      ult_rem->k = atual->k;
      ult_rem->op = 0;
    
      id = atual->id; //armazeno o identificador que quero retirar
      atual = atual->prox; //vou pro próximo elem
      if(aux->id == id) //se o elem que vou tirar é a cabeça, então a cabeça será o próximo
        aux = aux->prox;
      remover(lista, id);
      lista->tam--; //diminuo o tamanho da lista
    }
    if(op == 1){ 
      insere(lista, ult_rem); //insiro o último elem removido
      ult_rem = malloc(sizeof(No)); //armazeno o elem que será retirado 
      ult_rem->id = atual->id;
      ult_rem->k = atual->k;
      ult_rem->op = 0;

      id = atual->id;
      atual = atual->prox;
      if(aux->id == id)
        aux = aux->prox;
      remover(lista, id);
    }
  }
  return (aux->id);
}

void remover(Lista *lista, int id){
  No *aux = lista->inicio, *antes = lista->inicio;
  
  if(lista->inicio == NULL) //lista vazia
    return;
  
  while(aux->prox != lista->inicio && id > aux->id){ //laço para achar o elem que quero retirar
    antes = aux;
    aux = aux->prox;
  }
  if(id == aux->id){ //achei o elem que quero retirar
    if(aux == lista->inicio){ //retirar a cabeça
      antes = aux->prox;
      while(antes->prox != lista->inicio)
        antes = antes->prox;
      antes->prox = aux->prox;
      lista->inicio = aux->prox;
      free(aux);
      return;
    }else{ //retirar do meio ou do fim
      antes->prox = aux->prox;
      free(aux);
      return;
    }
  }
    else //não encontrei o elem
        return;
}

//função que reinsere o último elem removido
void insere(Lista *lista, No *elem){
  No *aux = lista->inicio, *anterior = lista->inicio;

  while(anterior->prox != lista->inicio && aux->id < elem->id){ //laço para encontrar a posição que será reinserida
    anterior = aux;
    aux = aux->prox;
  }
  if(aux == lista->inicio && elem->id < aux->id){ //inserir elem antes da cabeça
    anterior = aux->prox; //vou pro prox da cabeça
    while(anterior->prox != aux){ //procuro o último elem e faço a inserção da nova cabeça
      anterior = anterior->prox;
    }
    anterior->prox = elem;
    elem->prox = lista->inicio;
    lista->inicio = elem;
    return;
  }else{ //insere no meio
    anterior->prox = elem;
    elem->prox = aux;
    return;
  }
}