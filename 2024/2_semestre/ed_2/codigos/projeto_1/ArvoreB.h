// Import das bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definições de variavéis globais
#define P 6
#define ORDEM 15
#define TAMANHO_PLACA 8
#define TAMANHO_MODELO 20
#define TAMANHO_MARCA 20
#define TAMANHO_CATEGORIA 15
#define TAMANHO_STATUS 16
#define TAMANHO_REGISTRO 88
#define VETOR_REMOCAO 1000

// Structs utilizadas
typedef struct {
    char placa[TAMANHO_PLACA];
    char modelo[TAMANHO_MODELO];
    char marca[TAMANHO_MARCA];
    int ano;
    char categoria[TAMANHO_CATEGORIA];
    int quilometragem;
    char status[TAMANHO_STATUS];
} dados_veiculo;

typedef struct arvoreb{
    int numero_de_placas;
    char* vetor_placas[ORDEM-1];
    int vetor_rnn[ORDEM-1];
    struct arvoreb *filhos[ORDEM+1];
    bool e_folha;
    int posicao_no;
}arvore;

typedef struct fila_de_no{
    struct fila_de_no *dir;
    int posicao;
    arvore* usada;
}fila;

// Utilizado para marcar as posições vazias no arquivo dat, para realizar novas inserções e para controlar o rnn
int vetor_removidos[VETOR_REMOCAO];
static int ultimo_rnn = 0;


// Definições das funções utilizadas 
arvore* cria_no();
int proximo_rnn();
arvore* insere_no(arvore*, dados_veiculo*, int);
void insere_nao_cheio(arvore*, dados_veiculo*);
void divide_no(arvore*, int, arvore*);
void remove_no();
arvore* cocatena_no();
arvore* busca_arvore(char [TAMANHO_PLACA], int);
arvore* busca_insercao(char [TAMANHO_PLACA]);
fila* cria_fila(fila*, arvore*);
void insere_fila(fila*, arvore*);
void remove_fila(fila*);
arvore* busca_fila(fila*, char [TAMANHO_PLACA]);
bool insere_veiculo(dados_veiculo*);
bool remove_veiculo(char [TAMANHO_PLACA]);
dados_veiculo* busca_veiculo(char [TAMANHO_PLACA], int);
void le_dat(arvore*);
dados_veiculo* busca_veiculo_dat(int);
arvore* le_bin(int);
int escreve_dat(dados_veiculo*);
void escreve_bin(arvore*);
void remove_dat();
void remove_bin(arvore*);