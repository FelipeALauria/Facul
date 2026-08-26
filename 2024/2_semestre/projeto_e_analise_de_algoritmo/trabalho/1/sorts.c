#include "sorts.h"

int* cria_vetor_desordenado(int n){
    srand(time(NULL));
    int* vetor = (int*) malloc(n*sizeof(int));
    for (int i = 0; i < n; i++){
        vetor[i] = rand() % n;
    }

    return vetor;
}

int* cria_vetor_ordenado(int n){
    int* vetor = (int*) malloc(n*sizeof(int));
    for(int i = 0; i< n; i++){
        vetor[i] = i;
    }

    return vetor;
}

int* cria_vetor_inversamente_ordenado(int n){
    int* vetor = (int*) malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        vetor[i] = n-i-1;
    }

    return vetor;
}

int* copia_vetor(int* vetor, int n){
    int* novo_vetor = (int*) malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        novo_vetor[i] = vetor[i];
    }
    return novo_vetor;
}

void imprime_vetor(int* vetor, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void bubble_sort(int* vetor, int n) {
    printf("Estou no Bubble Sort\n");
    fflush(stdout);
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(vetor[j] > vetor[j + 1]) {
                int aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void insertion_sort(int* vetor, int n){
    printf("Estou no Insertion Sort\n");
    fflush(stdout);
    for(int i = 1; i< n; i++){
        int j = i - 1;
        int aux = vetor[i];

        while(j>=0 && vetor[j] > aux){
            vetor[j+1] = vetor[j];
            j = j - 1;
        }
        vetor[j+1] = aux;
    }
    
}

void merge(int* vetor, int esq, int meio, int dir) {
    int i, j, k;
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = vetor[esq + i];
    for (j = 0; j < n2; j++)
        R[j] = vetor[meio + 1 + j];

    i = 0;
    j = 0;
    k = esq;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        } else {
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(int* vetor, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;

        merge_sort(vetor, esq, meio);
        merge_sort(vetor, meio + 1, dir);

        merge(vetor, esq, meio, dir);
    }
}

void shell_sort(int* vetor, int n) {
    printf("Estou no Shell Sort\n");
    fflush(stdout);
    for (int intervalo = n / 2; intervalo > 0; intervalo /= 2) {
        for (int i = intervalo; i < n; i++) {
            int temp = vetor[i];
            int j;

            for (j = i; j >= intervalo && vetor[j - intervalo] > temp; j -= intervalo) {
                vetor[j] = vetor[j - intervalo];
            }

            vetor[j] = temp;
        }
    }
}

void selection_sort(int* vetor, int n) {
    printf("Estou no Selection Sort\n");
    fflush(stdout);
    for (int i = 0; i < n; i++) {
        int menor_posicao = i;

        for (int j = i + 1; j < n; j++) {
            if (vetor[menor_posicao] > vetor[j]) {
                menor_posicao = j;
            }
        }

        int aux = vetor[i];
        vetor[i] = vetor[menor_posicao];
        vetor[menor_posicao] = aux;
    }
}

void quick_sort(int* vetor, int esq, int dir) {
    while (esq < dir) {
        int i = esq;
        int j = dir;
        int meio = esq + (dir - esq) / 2;
        int pivo = vetor[meio];

        if (vetor[esq] > vetor[meio]) {
            int aux = vetor[esq];
            vetor[esq] = vetor[meio];
            vetor[meio] = aux;
        }
        if (vetor[esq] > vetor[dir]) {
            int aux = vetor[esq];
            vetor[esq] = vetor[dir];
            vetor[dir] = aux;
        }
        if (vetor[meio] > vetor[dir]) {
            int aux = vetor[meio];
            vetor[meio] = vetor[dir];
            vetor[dir] = aux;
        }

        pivo = vetor[meio];

        while (i <= j) {
            while (vetor[i] < pivo) i++;
            while (vetor[j] > pivo) j--;

            if (i <= j) {
                int aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
                i++;
                j--;
            }
        }

        if ((j - esq) < (dir - i)) {
            quick_sort(vetor, esq, j);
            esq = i;
        } else {
            quick_sort(vetor, i, dir);
            dir = j;
        }
    }
}

void counting_sort(int* vetor, int n){
    printf("Estou no Counting Sort\n");
    fflush(stdout);
    int M = 0;
    for (int i = 0; i < n; i++)
        if (vetor[i] > M)
            M = vetor[i];

    int* vetor_contagem = (int*)calloc(M + 1, sizeof(int));

    for (int i = 0; i < n; i++)
        vetor_contagem[vetor[i]]++;

    for (int i = 1; i <= M; i++)
        vetor_contagem[i] += vetor_contagem[i - 1];

    int* vetor_de_saida = (int*)malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--) {
        vetor_de_saida[vetor_contagem[vetor[i]] - 1] = vetor[i];
        vetor_contagem[vetor[i]]--;
    }

    for (int i = 0; i < n; i++)
        vetor[i] = vetor_de_saida[i];

    free(vetor_contagem);
    free(vetor_de_saida);
}

void heap_sort(int* vetor, int n){
    printf("Estou no Heap Sort\n");
    fflush(stdout);
     for (int i = n / 2 - 1; i >= 0; i--) {
        cria_heap(vetor, n, i);
    }

    for (int i = n - 1; i > 0; i--) {

        int temp = vetor[0]; 
        vetor[0] = vetor[i];
        vetor[i] = temp;

        cria_heap(vetor, i, 0);
    }
}

void radix_sort(int* vetor, int n){
    printf("Estou no Radix Sort\n");
    fflush(stdout);
    int maior = maximo(vetor, n);

    for(int expoente = 1; maior/expoente > 0; expoente *= 10){
        counting_sort(vetor, n);
    }
}    

void bucket_sort(int *vetor, int tamanho) {
    printf("Estou no Bucket Sort\n");
    fflush(stdout);

    int max = maximo(vetor, tamanho);

    int *balde = (int *)calloc(max + 1, sizeof(int));
    if (balde == NULL) {
        printf("Erro ao alocar memória para o balde.\n");
        exit(1);
    }

    for (int i = 0; i < tamanho; i++) {
        balde[vetor[i]]++;
    }

    for (int i = 0, j = 0; i <= max; i++) {
        while (balde[i] > 0) {
            vetor[j++] = i;
            balde[i]--;
        }
    }

    free(balde);
}

int maximo(int* vetor, int n){
    int maximo = vetor[0];
    for(int i = 1; i < n; i++){
        if(maximo < vetor[i])
            maximo = vetor[i];
    }

    return maximo;
}

void cria_heap(int* vetor, int n, int i){
    int maior = i; 

    int esq = 2 * i + 1; 

    int dir = 2 * i + 2;

    if (esq < n && vetor[esq] > vetor[maior]) {
        maior = esq;
    }

    if (dir < n && vetor[dir] > vetor[maior]) {
        maior = dir;
    }

    if (maior != i) {
        int temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;

        cria_heap(vetor, n, maior);
    }
}
