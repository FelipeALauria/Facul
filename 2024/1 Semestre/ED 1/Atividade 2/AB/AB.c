//Arquivo de implementação

#include <stdlib.h>
#include <stdio.h>
#include "AB.h"

//EDs e tipos
//-------------------------------------------
//Tipo nó
struct no {
	char info;
	struct no *esq;
	struct no *dir;
};
//-------------------------------------------

//Operações
//-------------------------------------------
No *criavazia () {
	return NULL;
}

No *cria (char c, No *esq, No *dir) {
	
	No *aux = malloc(sizeof(No));
	aux->info = c;
	aux->esq = esq;
	aux->dir = dir;
	
	return (aux);
}

int vazia (No *t) {
	return t == NULL;
}

void imprime (No *t) {
	
	if (!vazia(t)) {
		printf("%c ", t->info); //Imp. raíz
		imprime (t->esq); //Imp. esq. (funcao recursiva)
		imprime (t->dir); //Imp. dir. (funcao recursiva)
	}
		
}
	
No *libera (No *t) {
	
	if (vazia(t)){
		libera (t->esq);
		libera (t->dir);
		free (t);
	}
	
	return NULL;
}

int pertence (No *t, char c){
	
	if (vazia(t))
		return 0; //árvore vazia
	else
		return t->info == c || pertence (t->esq,c) || pertence (t->dir,c);
}
