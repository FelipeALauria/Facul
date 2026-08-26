#ifndef _main
#define _main
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void bubble_sort(int*, int);
void insertion_sort(int*, int);
void merge_sort(int*, int, int);
void shell_sort(int*, int);
void quick_sort(int*, int, int);
void selection_sort(int*, int);
void counting_sort(int*, int);
void heap_sort(int*, int);
void radix_sort(int*, int);
void bucket_sort(int*, int);
void merge(int*, int, int, int);
int maximo(int*, int);
void cria_heap(int*, int, int);
int* cria_vetor_ordenado(int);
int* cria_vetor_desordenado(int);
int* cria_vetor_inversamente_ordenado(int);
int* copia_vetor(int*, int);
void imprime_vetor(int*, int);

#endif