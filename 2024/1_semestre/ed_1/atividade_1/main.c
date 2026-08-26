//Felipe Lauria e Matheus Thomé

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main(){
  int x = 0;
  int e = 0;
  int control = 0;
  int p = 0;
  int elem = 0;
  lista L;
  tipo_elem Lcontrol;
  printf("Quantos procedimentos deseja fazer?\n");
  scanf("%d", &x);
  for(int i = 0; i< x; i++){
    printf("Digite de 0 a 12 para chamar o procedimento desejado: ");
    scanf("%d", &e);
    switch (e){
      case 1 :
      Definir(&L);
      printf("Lista definida\n");
      break;
      case 2 :
        printf("Digite a chave do elemento: \n");
        scanf("%d",&Lcontrol.chave);
        printf("Digite o nome do elemento: \n");
        scanf("%s",Lcontrol.info.nome);
        printf("Digite a idade do elemento: \n");
        scanf("%d",&Lcontrol.info.idade);
        printf("Digite a media final do elemento: \n");
        scanf("%f",&Lcontrol.info.media_final);
        printf("Digite o lugar que deve ser inserido: \n");
        scanf("%d",&p);
        if(Inserir_posic(Lcontrol, p, &L))
          printf("Elemento adicionado com sucesso\n");
        else
          printf("Procedimento fracassado\n");
        break;
      case 3 :
        printf("Digite a chave do elemento: \n");
        scanf("%d",&Lcontrol.chave);
        printf("Digite o nome do elemento: \n");
        scanf("%s",Lcontrol.info.nome);
        printf("Digite a idade do elemento: \n");
        scanf("%d",&Lcontrol.info.idade);
        printf("Digite a media final do elemento: \n");
        scanf("%f",&Lcontrol.info.media_final);
        if(Inserir_ord( Lcontrol , &L))
          printf("Elemento adicionado com sucesso\n");
        else
          printf("Procedimento fracassado\n");
        break;
      case 4 :
        printf("Digite a chave do elemento a ser buscado: \n");
        scanf("%d",&elem);
        if(Buscar(elem, &L, &p))
          printf("Elemento ocorre na posição %d \n", p);
        else
          printf("Procedimento fracassado \n");
        break;
      case 5 :
        printf("Digite a chave do elemento a ser buscado: \n");
        scanf("%d",&elem);
      if(Buscar_ord(elem, &L, &p))
        printf("Elemento ocorre na posição %d \n", p);
      else
        printf("Procedimento fracassado \n");
      break;
      case 6 :
        printf("Digite o lugar a ser removida: \n");
        scanf("%d",&p);
        Remover_posic(&p,&L);
        printf("Elemento removido com sucesso\n");
        break;
      case 7 :
        printf("Digite a chave do elemento a ser retirado: \n");
        scanf("%d",&elem);
        if(Remover_ch(elem, &L))
          printf("Elemento retirado com sucesso\n");
        else
          printf("Procedimento fracassado\n");
        break;
      case 8 :
        Imprimir(&L);
        break;
      case 9 :
        control = Tamanho(&L);
        printf("A lista tem %d elementos\n", control);
        break;
      case 10 :
        if(Vazia(&L))
          printf("A lista vazia \n");
        else
          printf("A lista tem elementos \n");
        break;
      case 11 :
        if(Cheia(&L))
          printf("Lista cheia \n");
        else
          printf("Lista não preenchida \n");
        break;
      case 12 :
        Apagar(&L);
        printf("Lista apagada\n");
        break;
      }
    }
  system("PAUSE");
  return 0;
}