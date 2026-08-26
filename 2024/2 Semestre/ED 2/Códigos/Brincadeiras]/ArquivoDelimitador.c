#include "stdio.h"
#include "stdlib.h"

typedef struct ArquivoDelimitador {
    char nome[50];
    int idade;
    char endereco[100];
    int cep
}inserts;

int main () {
    FILE *f;
    f = fopen("dados.txt", "w");
    for(int i = 0; i > 2; i++) {
        printf("Digite o nome: ");
        scanf("%s", inserts.nome);
    }

    return 0;
}