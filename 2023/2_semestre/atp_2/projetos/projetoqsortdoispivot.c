#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

// Declaração da função utilizada.
void quicks(char **, int, int);

// Função principal.
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
    if (fp == NULL)
        return 0;

    // Conta o número de palavras no arquivo.
    fscanf(fp, "%s", words);
    while (!feof(fp)) {
        count++;
        fscanf(fp, "%s", words);
    }

    // Reposiciona o ponteiro do arquivo para o início.
    fseek(fp, 0, SEEK_SET);
    
    // Aloca memória para armazenar as palavras.
    word = malloc(count * sizeof(char *));
    word[0] = malloc(40 * sizeof(char));
    fscanf(fp, "%s", word[0]);
    while (!feof(fp) && i <= count) {
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
    for (i = 0; i <= count; i++)
        fprintf(fp, "%s\n", word[i]);
 
    fclose(fp);

    // Exibe o tempo decorrido.
    printf("Time measured: %.3f seconds.\n", elapsed);

    return 0;
}

// Função de ordenação rápida (quicksort).
void quicks(char **strp, int begin, int end) {
    if (begin < end) {
        int l = begin + 1;
        int r = end - 1;
        int i = begin + 1;
        char aux[40], pivot_left[40], pivot_right[40];

        // Ordena os extremos (esquerdo e direito) em relação ao pivô.
        if (strcasecmp(strp[begin], strp[end]) > 0) {
            strcpy(aux, strp[begin]);
            strcpy(strp[begin], strp[end]);
            strcpy(strp[end], aux);
        }

        // Define os pivôs.
        strcpy(pivot_left, strp[begin]);
        strcpy(pivot_right, strp[end]);

        // Particiona os elementos em relação aos pivôs.
        while (i <= r) {
            if (strcasecmp(strp[i], pivot_left) < 0) {
                strcpy(aux, strp[i]);
                strcpy(strp[i], strp[l]);
                strcpy(strp[l], aux);
                l++;
                i++;
            }
            else if (strcasecmp(strp[i], pivot_right) > 0) {
                strcpy(aux, strp[i]);
                strcpy(strp[i], strp[r]);
                strcpy(strp[r], aux);
                r--;
            }
            else {
                i++;
            }
        }

        // Coloca os pivôs nas posições corretas.
        strcpy(strp[begin], strp[l - 1]);
        strcpy(strp[l - 1], pivot_left);
        strcpy(strp[end], strp[r + 1]);
        strcpy(strp[r + 1], pivot_right);

        // Chama recursivamente para as partições à esquerda e à direita dos pivôs.
        quicks(strp, begin, l - 2);
        quicks(strp, l, r);
        quicks(strp, r + 2, end);
    }
}
