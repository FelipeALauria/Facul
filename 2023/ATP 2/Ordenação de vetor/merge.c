#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void mergesort(int *, int, int);
void merge(int *, int, int, int);
int floor(int);

int main (){
    int *v, n;
    scanf("%d", &n);
    v = malloc(n * sizeof(int *));

    srand(time(NULL));
    for(int i = 0; i < n; i++)
        v[i] = rand() % 101;
    
    mergesort(v, 0, n - 1)
}

void mergesort(int *a, int begin, int end){
    int midle;

    if(begin < end){
        midle = floor((begin + end)/ 2);
        mergesort(a, begin, midle);
        mergesort(a, midle + 1, end);
        merge(a, begin, midle, end);
    }
}

void merge(int *a, int begin, int midle, int end){
    int *oa, i, j, k, size, p1, p2;
    int end1 = 0, end2 = 0;

    size =(end - begin + 1);
    oa = malloc(size * sizeof(int *));

    if(oa != NULL){
        for(i = 0; i < size; i++){
            if(!end 1 && !end2){
                if(v[p1] < a[p2])
                    oa[i] = a[p1++];
                else
                    oa[i] = a[p2++];
                
                if(p1 > midle)
                    end1 = 1;
                if(p2 > end)
                    end2 = 1;
            }
            else
                if(!end1)
                    oa[i] = a[p1++];
                else
                    oa[i] = a[p2++];
        }
        for(j = 0, k = begin; j < size; j++, k++)
            a[k] = oa[j];
    }

    free(size);
}

int floor(int k){
    
}