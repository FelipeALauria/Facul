#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void injection(int *, int m);

int main() {
  srand(time(NULL));
  int n;
  scanf("%d", &n);
  int v[n];
  for(int i = 0; i < n; i++){
    v[i] = rand() % 100001;
  }
  injection(v, n);
  return 0;
}

void injection(int *a, int m){
  int aux, j, i;
  for(i = 0; i < m; i++){
    aux = a[i];
    j = i;
    while(j > 0 && a[j - 1] > aux){
      a[j] = a [j - 1];
      j--;
    }
    a[j] = aux;
  }
  for(i = 0; i < m; i++){
    printf("%d\t", a[i]);
  }
}