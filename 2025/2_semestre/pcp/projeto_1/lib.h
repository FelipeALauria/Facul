//  Declaracao das bibliotecas e constantes
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#define n 10
#define MAX_ITER 1000
#define CRT_PARADA 1e-5

// Declaração das funções
FILE* le_arq(char *);
FILE *cria_arq(char *);
void escreve_arq(double *);
double *jacobi(FILE *);

// Função para ler o arquivo
FILE* le_arq(char *arquivo){
    FILE *arq = fopen(arquivo, "r");
    
    if(arq == NULL){
        fclose(arq);
        printf("Erro ao abir %s\n", arquivo);
        return(NULL);
    }

    printf("Arquivo %s aberto com sucesso!\n", arquivo);
    return(arq);
}

// Função para criar o arquivo final
FILE *cria_arq(char *arquivo){
    FILE *arq = fopen(arquivo, "w");
    
    if(arq == NULL){
        fclose(arq);
        printf("Erro ao criar %s\n", arquivo);
        return(NULL);
    }

    printf("Arquivo %s criado com sucesso!\n", arquivo);
    return(arq);
}

// Escrita da resposta no arquivo final
void escreve_arq(double *vetor){
    FILE *arq = cria_arq("C:\\Users\\felip\\Desktop\\Facul\\2025\\2 Semestre\\Programacao Concorrente Paralela\\Projeto 1\\resultado_sequencial.dat");
    if(arq == NULL) {
        printf("Erro ao abrir arquivo de escrita\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        fprintf(arq, "%lf", vetor[i]);
        if(i < n - 1)
            fprintf(arq, " ");
    }
    fprintf(arq, "\n");
 
    printf("Arquivo escrito com sucesso!\n");
    fclose(arq);
}

// Função do método de Jacobi
double *jacobi(FILE *arq){
    // Declaração das variáveis necessárias
    double **matrizA = malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrizA[i] = malloc(n * sizeof(double));
    }
    double *vetorB = malloc(n * sizeof(double));
    double *vetorX = malloc(n * sizeof(double));
    double *aux = malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(arq, "%lf", &matrizA[i][j]) != 1) {
                printf("Erro ao ler matrizA[%d][%d]\n", i, j);
                exit(1);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(arq, "%lf", &vetorB[i]) != 1) {
            printf("Erro ao ler vetorB[%d]\n", i);
            exit(1);
        }
    }

    for (int i = 0; i < n; i++) {
        vetorX[i] = 0.0;
    }

    for (int iter = 0; iter < MAX_ITER; iter++) {
        for (int i = 0; i < n; i++) {
            double soma = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    soma += matrizA[i][j] * vetorX[j];
                }
            }
            aux[i] = (vetorB[i] - soma) / matrizA[i][i];
        }

        // Verificação da diferença máxima
        double erro = fabs(aux[0] - vetorX[0]);
        for (int i = 1; i < n; i++) {
            double dif = fabs(aux[i] - vetorX[i]);
            if (dif > erro) erro = dif;
        }

        // Atualiza X
        for (int i = 0; i < n; i++) {
            vetorX[i] = aux[i];
        }

        if (erro < CRT_PARADA) {
            printf("Convergência atingida na iteração %d\n", iter + 1);
            break;
        }
    }

    free(aux);
    for (int i = 0; i < n; i++) free(matrizA[i]);
    free(matrizA);
    free(vetorB);

    return vetorX;
}