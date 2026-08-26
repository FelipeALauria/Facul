#include "stdio.h"
#include "stdlib.h"

int* recebe(int n);
void imprimmi(int *pv,int m);
void limpa(int *pv1);

int main(){
    int m, *b;
    scanf("%d", &m);
    b = recebe(m);
    imprimmi(b, m);
    return 0;
}

int* recebe(int n){
    int *v;
    v = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }
    return v;
}

void imprimmi(int *pv, int n){
    for(int i = 0; i < n; i++){
        printf("%d\t", pv[i]);
    }
}

void limpa(int *pv1){
    free(pv1);
}