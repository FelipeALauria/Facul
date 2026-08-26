#include <stdio.h>

int minMovimentos = 0;

void hanoi(int n, int origem, int auxiliar, int destino, int k[3], int torre[3][20]);

int main() {
    int totalDiscos;
    scanf("%d", &totalDiscos);

    int k[3];
    int torre[3][20] = {0};

    for (int i = 0; i < 3; i++) {
        scanf("%d", &k[i]);
        for (int j = 0; j < k[i]; j++) {
            scanf("%d", &torre[i][j]);
        }
    }

    hanoi(totalDiscos, 0, 1, 2, k, torre);
    printf("%d\n", minMovimentos);

    return 0;
}

void hanoi(int n, int origem, int auxiliar, int destino, int k[3], int torre[3][20]) {
    if (n == 0) {
        return;
    }
    hanoi(n - 1, origem, destino, auxiliar, k, torre);
    int disco = torre[origem][k[origem] - 1];
    k[origem]--;
    torre[destino][k[destino]] = disco;
    k[destino]++;
    minMovimentos++;
    hanoi(n - 1, auxiliar, origem, destino, k, torre);
}
