#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *nome;
    int nro_unesp;
} aluno;

int main() {
    int size = 0;
    FILE *fp, *fp2;

    fp = fopen("arquivo de dados.txt", "r");
    fp2 = fopen("arquivo indice.txt", "w");
    
    if (fp == NULL || fp2 == NULL)
        return 0;

    if (fscanf(fp, "%d", &size) != 1) {
        fclose(fp);
        fclose(fp2);
        return 0;
    }

    printf("%d\n", size);
    fprintf(fp2, "%d\n", size);

    fclose(fp);
    fclose(fp2);

    return 0;
}
