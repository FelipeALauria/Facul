#include "stdio.h"
#include "sorts.h"
#include "stdlib.h"
#include "time.h"

#define n 1000000
int main() {
    FILE *fp = fopen("Tempos.txt", "w");
    if(fp == NULL)
        return 1;

    clock_t inicio, fim;
    double tempo_gasto;
    int *vetor, *vetor_desordenado;
    vetor_desordenado = cria_vetor_desordenado(n);

    for(int i = 0; i < 30; i++) {
        if(i < 3) {
            if(i == 0) {
                vetor = cria_vetor_ordenado(n);
                inicio = clock();
                bubble_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Bubble Sort (Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else if(i == 1) {
                vetor = copia_vetor(vetor_desordenado, n);
                inicio = clock();
                bubble_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Bubble Sort (Desordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else if(i == 2){
                vetor = cria_vetor_inversamente_ordenado(n);
                inicio = clock();
                bubble_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Bubble Sort (Inversamente Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
        }else if(i < 6) {
            if(i == 3) {
                vetor = cria_vetor_ordenado(n);
                inicio = clock();
                insertion_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Insertion Sort (Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else if(i == 4) {
                vetor = copia_vetor(vetor_desordenado, n);
                inicio = clock();
                insertion_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Insertion Sort (Desordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else{
                vetor = cria_vetor_inversamente_ordenado(n);
                inicio = clock();
                insertion_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Insertion Sort (Inversamente Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
        } else if(i < 9) {
            if(i == 6) {
                vetor = cria_vetor_ordenado(n);
                inicio = clock();
                selection_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Selection Sort (Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else if(i == 7) {
                vetor = copia_vetor(vetor_desordenado, n);
                inicio = clock();
                selection_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Selection Sort (Desordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else{
                vetor = cria_vetor_inversamente_ordenado(n);
                inicio = clock();
                selection_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Selection Sort (Inversamente Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
        } else if(i < 12) {
            if(i == 9) {
                vetor = cria_vetor_ordenado(n);
                inicio = clock();
                merge_sort(vetor, 0, n-1);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Merge Sort (Ordenado): %.5f segundos\n", tempo_gasto);
                fflush(fp);
                free(vetor);
            } else if(i == 10) {
                vetor = copia_vetor(vetor_desordenado, n);
                inicio = clock();
                merge_sort(vetor, 0, n-1);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Merge Sort (Desordenado): %.5f segundos\n", tempo_gasto);
                fflush(fp);
                free(vetor);
            } else {
                vetor = cria_vetor_inversamente_ordenado(n);
                inicio = clock();
                merge_sort(vetor, 0, n-1);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Merge Sort (Inversamente Ordenado): %.5f segundos\n", tempo_gasto);
                fflush(fp);
                free(vetor);
            }
        } else if(i < 15) {
            if(i == 12) {
                vetor = cria_vetor_ordenado(n);
                inicio = clock();
                shell_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Shell Sort (Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else if(i == 13) {
                vetor = copia_vetor(vetor_desordenado, n);
                inicio = clock();
                shell_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Shell Sort (Desordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else {
                vetor = cria_vetor_inversamente_ordenado(n);
                inicio = clock();
                shell_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Shell Sort (Inversamente Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
        } else if(i < 18) {
            if(i == 15) {
                vetor = cria_vetor_ordenado(n);
                inicio = clock();
                quick_sort(vetor, 0, n-1);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Quick Sort (Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else if(i == 16) {
                vetor = copia_vetor(vetor_desordenado, n);
                inicio = clock();
                quick_sort(vetor, 0, n-1);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Quick Sort (Desordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else {
                vetor = cria_vetor_inversamente_ordenado(n);
                inicio = clock();
                quick_sort(vetor, 0, n-1);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Quick Sort (Inversamente Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
        } else if(i < 21) {
            if(i == 18) {
                vetor = cria_vetor_ordenado(n);
                inicio = clock();
                radix_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Radix Sort (Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else if(i == 19) {
                vetor = copia_vetor(vetor_desordenado, n);
                inicio = clock();
                radix_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Radix Sort (Desordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else {
                vetor = cria_vetor_inversamente_ordenado(n);
                inicio = clock();
                radix_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Radix Sort (Inversamente Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
        } else if(i < 24) {
            if(i == 21) {
                vetor = cria_vetor_ordenado(n);
                inicio = clock();
                counting_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Counting Sort (Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else if(i == 22) {
                vetor = copia_vetor(vetor_desordenado, n);
                inicio = clock();
                counting_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Counting Sort (Desordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            } else {
                vetor = cria_vetor_inversamente_ordenado(n);
                inicio = clock();
                counting_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Counting Sort (Inversamente Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
        }
        else if(i < 27){
            if(i == 24){
                vetor = cria_vetor_ordenado(n);
                inicio = clock();
                heap_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Heap Sort (Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
            else if(i == 25){
                vetor = copia_vetor(vetor_desordenado, n);
                inicio = clock();
                heap_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Heap Sort (Desordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
            else{
                vetor = cria_vetor_inversamente_ordenado(n);
                inicio = clock();
                heap_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Heap Sort (Inversamente Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
        }
        else{
            if(i == 27){
                vetor = cria_vetor_ordenado(n);
                inicio = clock();
                bucket_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Bucket Sort (Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
            else if(i == 28){
                vetor = copia_vetor(vetor_desordenado, n);
                inicio = clock();
                bucket_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Bucket Sort (Desordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
            else{
                vetor = cria_vetor_inversamente_ordenado(n);
                inicio = clock();
                bucket_sort(vetor, n);
                fim = clock();
                tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                fprintf(fp, "Bucket Sort (Inversamente Ordenado): %.5f segundos\n", tempo_gasto);
                free(vetor);
            }
        }
    } 

    fclose(fp);
    return 0;
}
