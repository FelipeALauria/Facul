#include "stdio.h"

// Declaração da função.
int mmcz(int m, int l, int *b, int o, int p, int q);

// Função principal.
int main(){
    int n, k, i, j;
    scanf("%d %d", &n, &k);
    int a[n * n];
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            scanf("%d", &a[i * n + j]);
        }
    }
    printf("%d", mmcz(n, k, a, 0, 0, n));
    return 0;
}

// Função recursiva que localiza a maior submatriz contendo um número k de 0.
int mmcz(int m, int l, int *b, int o, int p, int q){
    int count = 0;
    // Faz a contagem dos 0 da matriz.
    while(count < l){
        for(int i = 0 ; i < m; i++){
            for(int j = 0; j < m; j++){
                if(b[(o + i) * q + (p + j)] == 0){
                    count++;
                }
            }
        }
    }
    // Faz a verifação para saber se o números de 0 é igual ao número pretendido de 0.
    if(count <= l){
        return m;    
    }
    // Faz a verificação se a coluna mais o tamanho da submatriz é menor que o tamanho da matriz, caso seja ele chama a função encrementando o valor da coluna.
    if (p + m < q){
        return(mmcz(m, l, b, o, p + 1, q));
    }
    // Faz a verificação se a linha mais o tamanho da submatriz é menor que o tamanho da matriz, caso seja ele chama a função encrementando o valor da linha e reiniciando a coluna.
    if(o + m < q){
        return(mmcz(m, l, b, o + 1, 0, q));
    }
    // Diminui o tamanho da submatriz e reinicia as linhas e colunas. 
    return(mmcz(m - 1, l , b, 0, 0, q));
}     