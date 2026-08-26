#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char word[30];
}w;

void shell(w *, int);

int main(){
    int N;
    scanf(" %d", &N);

    w *vet = malloc(sizeof(w)*N);
    for(int i = 0; i < N; i++){
        scanf(" %s", vet[i].word);
    }


    shell(vet, N);

    return 0;

}

void shell(w *vet, int n){
    int i, j, k, l, m;
    char aux[30];
    k = 1;

    while(k <= n/8)
        k *= 2;
    while(k > 0){
        for(m = k; m < 2*k; m++){
            for(i = m; i < n; i = i + k){
                strcpy(aux, vet[i].word);
                j = i;

                while(j >= k && strcmp(aux, vet[j - k].word) < 0){
                    strcpy(vet[j].word, vet[j - k].word);
                    j = j - k;
                }
                strcpy(vet[j].word, aux);
            }
        }
        printf("%s", vet[0].word);
            for(l = 1; l < n; l++)
                printf(" %s", vet[l].word);
            printf("\n");
            k = k/2;
    } 
}
