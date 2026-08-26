#include "stdio.h"

int hanoi(int a, char ori, char dest, char aux);

int main (){
    int n;  
    char A, B, C;
        scanf("%d", &n);
    hanoi(n, 'A', 'C', 'B');

}

int hanoi(int a, char ori, char dest, char aux) {
        int b, c, d, count;
        count = 1;
        if(a == 1){
            return count;
        } 
        else {
        while (a != 0){
            hanoi(a - 1, ori, aux, dest);
            hanoi(a- 1, ori, aux, dest);
            count ++;
            }
        return count;
        }
    }