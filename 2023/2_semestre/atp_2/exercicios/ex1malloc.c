#include "stdio.h"
#include "stdlib.h"

void le(int *m,int l);

int main(){
    int n, *v;
    scanf("%d", &n);
    v =(int *)malloc(n * sizeof(int));
    le(v, n);
    for(int i = 0; i < n; i++){
        printf("%d,", v[i]);
    }
    free(v);
    return 0;
}

void le(int *m, int l){
    for(int i = 0; i < l; i++){
        scanf("%d", &m[i]);
    }
}