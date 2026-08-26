#include <stdio.h>
#include "stdlib.h"
#include "time.h"

void selection(int *, int);

int main( ) {
  int n;
  scanf("%d", &n);
  int v[n];
  for(int i = 0; i < n; i++){
   v[i] = rand() % 100;
  }
  selection(v, n);
  for(int i = 0; i < n; i++){
    printf("%d\t", v[i]);
  }
  return 0;
}

void selection(int *r, int m){
  int min, aux;
  for(int i = 0; i < m - 1; i++){
    min = i;
    for(int j = i + 1; j < m; j++){
       if(r[j] < r[min])
         min = j;
    }
    aux = r[i];
    r[i] = r[min];
    r[min] = aux;        
  }
}
