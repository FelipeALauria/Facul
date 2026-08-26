// jacobi.c — Método de Jacobi sequencial
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

// Acessa A como 1D: A[i*N + j]
#define AIDX(i,j) ((size_t)(i)*(size_t)N + (size_t)(j))

static void parse_args(int argc, char **argv, const char **path){
    *path = NULL;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i], "--in")==0 && i+1<argc) { *path = argv[++i]; }
        else {
            fprintf(stderr, "Uso: %s --in <arquivo>\n", argv[0]);
            exit(1);
        }
    }
    if(!*path){
        fprintf(stderr, "Faltou --in <arquivo>\n"); exit(1);
    }
}

static int count_doubles_in_line(const char *line){
    int cnt = 0;
    const char *p = line;
    char *end;
    while(1){
        // pular espaços
        while(*p==' ' || *p=='\t') p++;
        if(*p=='\0' || *p=='\n' || *p=='\r') break;
        (void)strtod(p, &end);
        if(end == p) break;
        cnt++;
        p = end;
    }
    return cnt;
}

int main(int argc, char **argv){
    const char *path;
    parse_args(argc, argv, &path);

    FILE *f = fopen(path, "r");
    if(!f){ perror("fopen"); return 1; }

    // 1) Lê a primeira linha, descobre N, e guarda os N valores (primeira linha de A)
    const size_t LBUFSZ = 1<<20; // 1MB de linha (sobrado)
    char *line = (char*)malloc(LBUFSZ);
    if(!line){ fprintf(stderr,"Falha malloc linha\n"); return 1; }

    if(!fgets(line, (int)LBUFSZ, f)){
        fprintf(stderr,"Arquivo vazio\n");
        free(line); fclose(f); return 1;
    }
    int N = count_doubles_in_line(line);
    if(N <= 0){
        fprintf(stderr,"Não consegui inferir N a partir da 1a linha\n");
        free(line); fclose(f); return 1;
    }

    // 2) Aloca estruturas
    double *A = (double*)malloc((size_t)N*(size_t)N * sizeof(double));
    double *b = (double*)malloc((size_t)N * sizeof(double));
    double *x = (double*)calloc((size_t)N, sizeof(double));   // chute inicial 0
    double *x_new = (double*)malloc((size_t)N * sizeof(double));
    if(!A || !b || !x || !x_new){
        fprintf(stderr,"Falha malloc\n");
        free(line); if(A) free(A); if(b) free(b); if(x) free(x); if(x_new) free(x_new);
        fclose(f); return 1;
    }

    // 3) Preenche A[0,*] com a primeira linha
    {
        const char *p = line; char *end;
        for(int j=0;j<N;j++){
            A[AIDX(0,j)] = strtod(p, &end);
            p = end;
        }
    }

    // 4) Lê as próximas N-1 linhas de A
    for(int i=1;i<N;i++){
        if(!fgets(line, (int)LBUFSZ, f)){
            fprintf(stderr,"Faltaram linhas de A (i=%d)\n", i);
            free(line); free(A); free(b); free(x); free(x_new); fclose(f); return 1;
        }
        // valida: a linha deve ter N doubles
        if(count_doubles_in_line(line) < N){
            fprintf(stderr,"Linha %d tem menos que %d valores\n", i+1, N);
            free(line); free(A); free(b); free(x); free(x_new); fclose(f); return 1;
        }
        const char *p = line; char *end;
        for(int j=0;j<N;j++){
            A[AIDX(i,j)] = strtod(p, &end);
            p = end;
        }
    }

    // 5) Lê a última linha (vetor b) — 1 linha com N valores
    if(!fgets(line, (int)LBUFSZ, f)){
        fprintf(stderr,"Faltou linha de b\n");
        free(line); free(A); free(b); free(x); free(x_new); fclose(f); return 1;
    }
    if(count_doubles_in_line(line) < N){
        fprintf(stderr,"Linha de b tem menos que %d valores\n", N);
        free(line); free(A); free(b); free(x); free(x_new); fclose(f); return 1;
    }
    {
        const char *p = line; char *end;
        for(int j=0;j<N;j++){
            b[j] = strtod(p, &end);
            p = end;
        }
    }
    free(line);
    fclose(f);

    // 6) Validações
    // 6.1) Diagonal != 0
    for(int i=0;i<N;i++){
        if(fabs(A[AIDX(i,i)]) < 1e-14){
            fprintf(stderr,"Erro: A[%d][%d] (diagonal) = 0 (ou ~0). Jacobi indefinido.\n", i, i);
            free(A); free(b); free(x); free(x_new); return 2;
        }
    }
    // 6.2) Aviso de dominância diagonal estrita (não é obrigatório, só aviso)
    {
        int ok = 1;
        for(int i=0;i<N;i++){
            double sum = 0.0, diag = fabs(A[AIDX(i,i)]);
            for(int j=0;j<N;j++) if(j!=i) sum += fabs(A[AIDX(i,j)]);
            if(diag <= sum){ ok = 0; break; }
        }
        if(!ok){
            fprintf(stderr,"Aviso: matriz não é estritamente diagonalmente dominante; Jacobi pode não convergir.\n");
        }
    }

    // 7) Jacobi
    const double tol = 1e-5;
    const int maxit = 200000;

    clock_t t0 = clock();
    int k = 0;

    for(; k<maxit; k++){
        int divergiu = 0;
        double maxdiff = 0.0;
        for(int i=0;i<N;i++){
            double soma = 0.0, diag = A[AIDX(i,i)];
            for(int j=0;j<N;j++) if(j!=i) soma += A[AIDX(i,j)] * x[j];
            double val = (b[i] - soma)/diag;
            if(!isfinite(val)) divergiu = 1;
            x_new[i] = val;
        }
        if(divergiu){
            fprintf(stderr,"Abortei na iteração %d: NaN/Inf detectado (provável divergência do Jacobi).\n", k);
            for(int i=0;i<N;i++) printf("0.0000%s", (i==N-1) ? "\n" : " ");
            clock_t t1 = clock();
            double tempo = (double)(t1-t0)/CLOCKS_PER_SEC;
            fprintf(stderr,"[seq] iter=%d tempo=%.6f s\n", k, tempo);
            free(A); free(b); free(x); free(x_new);
            return 3;
        }
        for(int i=0;i<N;i++){
            double diff = fabs(x_new[i]-x[i]);
            if(diff > maxdiff) maxdiff = diff;
            x[i] = x_new[i];
        }
        if(maxdiff < tol) break;
    }

    clock_t t1 = clock();
    double tempo = (double)(t1-t0)/CLOCKS_PER_SEC;

    // Saída: uma linha com N valores (4 casas decimais)
    for(int i=0;i<N;i++){
        printf("%.4f%s", x[i], (i==N-1) ? "\n" : " ");
    }
    fprintf(stderr,"Iterações: %d Tempo: %.6f s\n", k, tempo);

    free(A); free(b); free(x); free(x_new);
    return 0;
}
