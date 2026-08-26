#include "stdio.h"
#include "stdlib.h"

int main(){
    int n, k, j, i;;
    scanf("%d %d",&n, &k);
    double v[n], aux;

    for(i = 0; i < n; i++){
      scanf("%lf", &v[i]);
    }

    for(i = 1; i <= k; i++){
      aux = v[i];
      j = i;
      while(j > 0 && v[j - 1] > aux){
        v[j] = v[j - 1];
        j--;
      }
    v[j] = aux;
    }

    for(i = k + 1; i < n; i++){
      aux = v[i];
       j = i;
      while(j > 0 && v[j - 1] < aux){
        v[j] = v[j - 1];
        j--;
      }
    v[j] = aux;
    }

    for(int i = 0; i < n; i++){
        printf("%.3lf ", v[i]);
    }

    return 0;
}
