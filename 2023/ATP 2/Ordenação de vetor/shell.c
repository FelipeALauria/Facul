#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void shellsort(int *, int );

int main(){
    int v[10000];
    srand(time(NULL));
    for(int i = 0; i < 10000; i++){
        v[i] = rand() % 10000;
    }
    shellsort(v, 10000);
    for(int i = 0; i < 10000; i++){
        printf("%d ", v[i]);
    }
    return 0;
}

void shellsort(int *a, int n){
    int i, j, aux, h;
    h = 1;
    while(h < n/3){
        h = 3 * h + 1;
    }

    while(h > 0){
        for(i = 0; i < n; i++){
            aux = a[i];
            j = i;
            while(j >= h && aux < a[j - h]){
                a[j] = a[j - h];
                j = j- h;
            }
            a[j] = aux;
        }
        h = (h - 1)/3;
    }
}