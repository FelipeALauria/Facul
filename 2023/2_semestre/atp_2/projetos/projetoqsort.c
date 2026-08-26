#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

// Declarações das funções utilizadas.
int locatepivot(char **, int, int);
void quicks(char **, int, int);

// Função main.
int main(int argc, char *argv[]) {
    int i = 1, count = -1;
    char words[40], **word;
    long seconds, nanoseconds;
    double elapsed;
    struct timespec begin, end;
    FILE *fp;

    // Abre o arquivo especificado na linha de comando para leitura.
    fp = fopen(argv[1], "r");

    // Verifica se o arquivo foi aberto corretamente.
    if(fp == NULL)
        return 0;

    // Conta o número de palavras no arquivo.
    fscanf(fp, "%s", words);
    while(!feof(fp)){
        count++;
        fscanf(fp, "%s", words);
    }

    // Reposiciona o ponteiro do arquivo para o início.
    fseek(fp, 0, SEEK_SET);

    // Aloca memória para armazenar as palavras.
    word = malloc(count * sizeof(char *));
    word[0] = malloc(40 * sizeof(char));

    fscanf(fp, "%s", word[0]);
    while(!feof(fp) && i <= count){
        word[i] = malloc(40 * sizeof(char));
        fscanf(fp, "%s", word[i]);
        i++;
    }
    fclose(fp);

    // Inicia a contagem do tempo.
    clock_gettime(CLOCK_REALTIME, &begin);
    // Chama a função de ordenação rápida (quicksort).
    quicks(word, 0, count);
    // Finaliza a contagem do tempo.
    clock_gettime(CLOCK_REALTIME, &end);

    // Calcula o tempo decorrido.
    seconds = end.tv_sec - begin.tv_sec;
    nanoseconds = end.tv_nsec - begin.tv_nsec;
    elapsed = seconds + nanoseconds * 1e-9;

    // Gera o nome do arquivo de saída.
    strcpy(words, argv[1]);
    sprintf(strstr(words, "."), "%s", ".output");
    // Abre o arquivo de saída para escrita.
    fp = fopen(words, "w");

    // Escreve as palavras ordenadas no arquivo de saída.
    for(i = 0; i <= count; i++)
        fprintf(fp, "%s\n", word[i]);

    fclose(fp);

    // Exibe o tempo decorrido.
    printf("Time measured: %.3f seconds.\n", elapsed);

    return 0;
}

// Função de ordenação rápida (quicksort).
void quicks(char **strp, int head, int tail) {
    int pivot;

    // Verifica se há elementos para ordenar.
    if(head < tail) {
        // Encontra o pivô para a partição.
        pivot = locatepivot(strp, head, tail);
        // Chama a função recursivamente para as partições à esquerda e à direita do pivô.
        quicks(strp, head, pivot - 1);
        quicks(strp, pivot + 1, tail);
    }
}

// Função auxiliar para encontrar o pivô.
int locatepivot(char **strp, int begin, int end) {
    char aux[40], pivot[40];
    int i, j;

    i = j = begin;
    // Define o último elemento como pivô.
    strcpy(pivot, strp[end]);

    // Percorre os elementos até o penúltimo.
    for(j = 0; j < end; j++) {
        // Compara as palavras e troca se necessário.
        if(strcasecmp(strp[j], pivot) < 0) {
            strcpy(aux, strp[j]);
            strcpy(strp[j], strp[i]);
            strcpy(strp[i], aux);
            i++;
        }
    }

    // Coloca o pivô na posição correta.
    strcpy(strp[end], strp[i]);
    strcpy(strp[i], pivot);

    return i;
}
