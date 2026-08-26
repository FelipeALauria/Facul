#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void buble(int *, int m);

int main() {
  srand(time(NULL));
  int n;
  scanf("%d", &n);
  int v[n];
  for(int i = 0; i < n; i++){
    v[i] = rand() % 10;
  }
  buble(v, n);
  for(int i = 0; i < n; i++){
    printf("%d\t", v[i]);
  }
  return 0;
}

void buble(int *a, int m){
  int aux, i, j, sw;
  for (i = 0; i < m - 1; i++){
    sw = 0;
    for (j = 0; j < m - 1 - i; j++){
      if (a[j] > a[j + 1]) {
        aux = a[j];
        a[j] = a[j + 1];
        a[j + 1] = aux;
        sw = 1;
      }
    }
    if (sw == 0) {
      break;
    }
  }
}
