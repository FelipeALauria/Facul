#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct k{
    char carac;
    struct k *ant;
};

struct k_bao{
    int num;
    struct k_bao *ant;
};

struct k *bota(struct k *ultimo, char op) {
    struct k *aux;
    if (ultimo == NULL) {
        ultimo = malloc(sizeof(struct k));
        ultimo->carac = op;
        ultimo->ant = NULL;
        return ultimo;
    }

    aux = malloc(sizeof(struct k));
    aux->carac = op;
    aux->ant = ultimo;

    return aux;
}

struct k_bao *bota_num(struct k_bao *ultimo, int op) {
    struct k_bao *aux;
    if (ultimo == NULL) {
        ultimo = malloc(sizeof(struct k_bao));
        ultimo->num = op;
        ultimo->ant = NULL;
        return ultimo;
    }
    aux = malloc(sizeof(struct k_bao));
    aux->num = op;
    aux->ant = ultimo;

    return aux;
}

struct k *tira(struct k **ultimo) {
    struct k *aux;

    if (*ultimo == NULL) {
        return NULL;
    }
    aux = *ultimo;
    *ultimo = (*ultimo)->ant;
    
    return aux;
}

struct k_bao *tira_num(struct k_bao **ultimo) {
    struct k_bao *aux;

    if (*ultimo == NULL) {
        return NULL;
    }

    aux = *ultimo;
    *ultimo = (*ultimo)->ant;
    
    return aux;
}

int operacao(int n1, int n2, char op) {
    return op == '+' ? n1 + n2
        : op == '-' ? n2 - n1
        : op == '*' ? n1 * n2
        : op == '/' ? n2 / n1
        : printf("BIGODOU TOTAL %c\n", op);
}

int main() {
    struct k *ultimo = NULL, *remov = NULL;
    struct k_bao *nums = NULL, *n1, *n2;
    int i = 0, aux = 0, num = 0, arr[200], arr_i = 0, str_len = 1;
    char a, str[1000], antes[50], str_fim[1000] = "|";

    while(1){
        a = getc(stdin);
        str[i++] = a;

        if (a == 10) {
            break;
        }
    }
    i = 0;
    while (str[i] != 10) {
        if (str[i] != 32) {
            antes[aux++] = str[i];
            antes[aux] = '\0';
        } else {
            if (antes[0] >= '0' && antes[0] <= '9') {
                arr[arr_i++] = atoi(antes);
                printf("%d ", arr[arr_i - 1]);
                strcpy(&str_fim[str_len], antes);
                str_len = strlen(str_fim);
                str_fim[str_len++] = '|';
            } else if (antes[0] == '(') {
                ultimo = bota(ultimo, antes[0]);
            } else if (antes[0] == ')') {
                while (ultimo != NULL && ultimo->carac != '(') {
                    remov = tira(&ultimo);
                    printf("%c ", remov->carac);
                    str_fim[str_len++] = remov->carac;
                    str_fim[str_len++] = '|';
                    free(remov);
                }
                free(tira(&ultimo));
            } else {
                if (ultimo == NULL) {
                    ultimo = bota(ultimo, antes[0]);
                } else if (
                    (ultimo->carac == '+' || ultimo->carac == '-')
                    && (antes[0] == '*' || antes[0] == '/')
                ) {
                    ultimo = bota(ultimo, antes[0]);
                } else {
                    if (ultimo->carac == '(' || ultimo->carac == ')') {
                        remov = NULL;
                    } else {
                        remov = tira(&ultimo);
                    }
                    ultimo = bota(ultimo, antes[0]);
                    if (
                        remov != NULL &&
                        remov->carac != ')' && remov->carac != '('
                    ) {
                        printf("%c ", remov->carac);
                        str_fim[str_len++] = remov->carac;
                        str_fim[str_len++] = '|';
                    }
                    free(remov);
                }
            }
            antes[0] = '\0';
            aux = 0;
        }
        i++;

        if (str[i] == 10) {
            if (antes[0] != ')' && antes[0] != '(' && antes[0] != '\0') {
                printf("%s ", antes);
                strcpy(&str_fim[str_len], antes);
                str_len = strlen(str_fim);
                str_fim[str_len++] = '|';
            }
            while (ultimo != NULL) {
                remov = tira(&ultimo);
                if (remov->carac != ')' && remov->carac != '(') {
                    printf("%c ", remov->carac);
                    str_fim[str_len++] = remov->carac;
                    str_fim[str_len++] = '|';
                }
                free(remov);
            }
        }
    }
    
    str_fim[str_len] = '\0';
    str_len = 0;
    aux = 0;
    while (str_fim[str_len] != '\0') {
        if (
            str_fim[str_len] == '+' || str_fim[str_len] == '*' ||
            str_fim[str_len] == '-' || str_fim[str_len] == '/'
        ) {
            n1 = tira_num(&nums);
            n2 = tira_num(&nums);
            nums = bota_num(nums, operacao(n1->num, n2->num, str_fim[str_len]));
            free(n1);
            free(n2);
            antes[0] = '\0';
            aux = 0;
        } else if (str_fim[str_len] != '|') {
            antes[aux++] = str_fim[str_len];
            antes[aux] = '\0';
        } else {
            if (antes[0] >= '0' && antes[0] <= '9') {
                nums = bota_num(nums, atoi(antes));
            }
            antes[0] = '\0';
            aux = 0;
        }
        str_len++;
    }

    printf("\n%d\n", tira_num(&nums)->num);

    return 0;
}