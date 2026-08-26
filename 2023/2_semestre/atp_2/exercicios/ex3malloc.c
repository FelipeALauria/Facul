#include "stdio.h"
#include "stdlib.h"

int* matr(int k, int l);

int main(){
    int *matriz, n, m, *b;
    scanf("%d %d", &n, &m);
    matriz =(int *)malloc((n + 1)* m * sizeof(int));
    b = matr(n, m);
}

int* matr(int k, int l){
    int *ma;
    for(int i = 0; i < k; i++){
        for(int j = 0; j < l; j++){
            scanf("%d", )
        }
    }
}