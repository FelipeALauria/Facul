#include <stdbool.h> //Tipo booleano

//EDs e tipos
//---------------------------------
typedef struct tipo_dado {
	int valor;
} tipo_dado;

typedef struct no {
	tipo_dado info;
	struct no *dir;
	struct no *esq;
} no;

typedef struct no *tree; //árvore: ponteiro p/ um nó
//---------------------------------

//Protótipo das funções
//---------------------------------
void Definir (tree t);

bool Vazia (tree t);

tree criaRaiz (tree t, tipo_dado elem);

int Altura (tree t);

bool Balanceada (tree t);

int numeroNos (tree t);

bool perfeitamenteBalanceada (tree t);

bool insereDireita (tree pai, tipo_dado elem);

bool insereEsquerda (tree pai, tipo_dado elem);

void Visita (tree t);

void preOrdem (tree t);

void inOrdem (tree t);

void posOrdem (tree t);
//---------------------------------
