#include "stdio.h"
#include "stdlib.h"

typedef struct {
    char* chave;
    int valor;
}elem;

elem adicionar_elemento(elem elemento, char* chave, int valor);
elem* buscar (elem* elemento, size_t tamanho ,char* chave);

int main() {
    size_t numero_de_itens = 4;
    int aux = numero_de_itens, valor = 0;
    char chave[100];
    elem elementos[numero_de_itens];    

    while(aux !=0){
        elem elemento;
        printf("\nDigite a chave e o valor: ");
        scanf("%s %d", chave, &valor);
        elementos[4 - aux] = adicionar_elemento(elemento, chave, valor);
        aux--;
    }

    char chave_busca[100];
    printf("\nDigite a chave que deseja buscar: ");
    scanf("%s", chave_busca);

    elem* encontrado = buscar(elementos, numero_de_itens, chave_busca);

    if(encontrado != NULL) {
        printf("Elemento %d encotrado!", encontrado->valor);
        return 0;
    }

    return 0;     
}

elem adicionar_elemento(elem elemento, char* chave, int valor) {
    elem novo_elemento;
    novo_elemento.chave = (char*) malloc(strlen(chave) + 1);
    strcpy(novo_elemento.chave, chave);
    novo_elemento.valor = valor;
    return novo_elemento;
}

elem* buscar (elem* elementos, size_t tamanho,char* chave) {
for (size_t i = 0; i < tamanho; i++) {
        if (strcmp(elementos[i].chave, chave) == 0) {
            return &elementos[i];
        }
    }
    return NULL;
}