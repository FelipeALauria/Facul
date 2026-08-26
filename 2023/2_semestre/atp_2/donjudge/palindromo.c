#include <stdio.h>
#include <string.h>

int pali(char* a, int n);
void invstr(char* str);

int main() {
    int n, max;
    char A[2000];
    scanf("%s", A);
    n = strlen(A);
    max = pali(A, n);
    printf("%d", max);
    return 0;
}

void invstr(char* str) {
    int tam = strlen(str);
    for (int i = 0; i < tam / 2; i++) {
        char temp = str[i];
        str[i] = str[tam - i - 1];
        str[tam - i - 1] = temp;
    }
}

int pali(char* a, int n) {
    char B[2000];
    strcpy(B, a);
    invstr(B);

    int m = n;
    int dp[n + 1][m + 1];
    int maxLen = 0;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (a[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    return maxLen;
}