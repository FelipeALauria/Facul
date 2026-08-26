#include "stdio.h"
#include "stdlib.h"

int main() {
int i, n, x, y, soma;
scanf("%d", &n);
for(i = 0; i < n; i++){
   scanf("%d %d", &x, &y);
   soma = x + y;
  if(soma % 2 == 0){
     printf("\nA");
   }
  else{
    printf("\n\tB");
  }
}
  
return 0;
  
}