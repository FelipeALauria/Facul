// jacobi_omp.c — Método de Jacobi (OpenMP) com detecção automática de N
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

// Acessa A como 1D: A[i*N + j]
#define AIDX(i,j) ((size_t)(i)*(size_t)N + (size_t)(j))

static void parse_args(int argc, char **argv,
                       const char **path, int *nth,
                       int *has_chunk, int *chunk, int *sched_kind){
    // sched_kind: 0=static, 1=dynamic, 2=guided
    *path = NULL; *nth = 2; *has_chunk = 0; *chunk = 0; *sched_kind = 0;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i], "--in")==0 && i+1<argc) { *path = argv[++i]; }
        else if(strcmp(argv[i], "--threads")==0 && i+1<argc) { *nth = atoi(argv[++i]); }
        else if(strcmp(argv[i], "--schedule")==0 && i+1<argc) {
            const char *s = argv[++i];
            if(!strcmp(s,"static")) *sched_kind = 0;
            else if(!strcmp(s,"dynamic")) *sched_kind = 1;
            else if(!strcmp(s,"guided")) *sched_kind = 2;
            else { fprintf(stderr,"schedule inválido: %s\n", s); exit(1); }
        }
        else if(strcmp(argv[i], "--chunk")==0 && i+1<argc){
            *has_chunk = 1; *chunk = atoi(argv[++i]);
        }
        else {
            fprintf(stderr, "Uso: %s --in <arquivo> [--threads N] [--schedule static|dynamic|guided] [--chunk C]\n", argv[0]);
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
    const char *path; int nth, has_chunk, chunk, sched_kind;
    parse_args(argc, argv, &path, &nth, &has_chunk, &chunk, &sched_kind);

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

    omp_set_num_threads(nth);
    double t0 = omp_get_wtime();
    int k = 0;

    for(; k<maxit; k++){
        int divergiu = 0;      // reduction OR
        double maxdiff = 0.0;  // reduction MAX

        // 7.1) Calcula x_new a partir de x
        if(!has_chunk){
            if(sched_kind==0){
                // static
#pragma omp parallel for schedule(static) reduction(|:divergiu)
                for(int i=0;i<N;i++){
                    double soma = 0.0, diag = A[AIDX(i,i)];
                    for(int j=0;j<N;j++) if(j!=i) soma += A[AIDX(i,j)] * x[j];
                    double val = (b[i] - soma)/diag;
                    if(!isfinite(val)) divergiu |= 1;
                    x_new[i] = val;
                }
            } else if(sched_kind==1){
                // dynamic
#pragma omp parallel for schedule(dynamic) reduction(|:divergiu)
                for(int i=0;i<N;i++){
                    double soma = 0.0, diag = A[AIDX(i,i)];
                    for(int j=0;j<N;j++) if(j!=i) soma += A[AIDX(i,j)] * x[j];
                    double val = (b[i] - soma)/diag;
                    if(!isfinite(val)) divergiu |= 1;
                    x_new[i] = val;
                }
            } else {
                // guided
#pragma omp parallel for schedule(guided) reduction(|:divergiu)
                for(int i=0;i<N;i++){
                    double soma = 0.0, diag = A[AIDX(i,i)];
                    for(int j=0;j<N;j++) if(j!=i) soma += A[AIDX(i,j)] * x[j];
                    double val = (b[i] - soma)/diag;
                    if(!isfinite(val)) divergiu |= 1;
                    x_new[i] = val;
                }
            }
        } else {
            if(sched_kind==0){
#pragma omp parallel for schedule(static,chunk) reduction(|:divergiu)
                for(int i=0;i<N;i++){
                    double soma = 0.0, diag = A[AIDX(i,i)];
                    for(int j=0;j<N;j++) if(j!=i) soma += A[AIDX(i,j)] * x[j];
                    double val = (b[i] - soma)/diag;
                    if(!isfinite(val)) divergiu |= 1;
                    x_new[i] = val;
                }
            } else if(sched_kind==1){
#pragma omp parallel for schedule(dynamic,chunk) reduction(|:divergiu)
                for(int i=0;i<N;i++){
                    double soma = 0.0, diag = A[AIDX(i,i)];
                    for(int j=0;j<N;j++) if(j!=i) soma += A[AIDX(i,j)] * x[j];
                    double val = (b[i] - soma)/diag;
                    if(!isfinite(val)) divergiu |= 1;
                    x_new[i] = val;
                }
            } else {
#pragma omp parallel for schedule(guided,chunk) reduction(|:divergiu)
                for(int i=0;i<N;i++){
                    double soma = 0.0, diag = A[AIDX(i,i)];
                    for(int j=0;j<N;j++) if(j!=i) soma += A[AIDX(i,j)] * x[j];
                    double val = (b[i] - soma)/diag;
                    if(!isfinite(val)) divergiu |= 1;
                    x_new[i] = val;
                }
            }
        }

        if(divergiu){
            fprintf(stderr,"Abortei na iteração %d: NaN/Inf detectado (provável divergência do Jacobi).\n", k);
            // imprime linha de zeros para manter formato (a critério do professor)
            for(int i=0;i<N;i++) printf("0.0000%s", (i==N-1) ? "\n" : " ");
            double t1 = omp_get_wtime();
            fprintf(stderr,"[omp] thr=%d iter=%d tempo=%.6f s\n", nth, k, (t1-t0));
            free(A); free(b); free(x); free(x_new);
            return 3;
        }

        // 7.2) Atualiza x e calcula maxdiff
#pragma omp parallel for reduction(max:maxdiff) schedule(static)
        for(int i=0;i<N;i++){
            double diff = fabs(x_new[i]-x[i]);
            if(diff > maxdiff) maxdiff = diff;
            x[i] = x_new[i];
        }

        if(maxdiff < tol) break;
    }

    double t1 = omp_get_wtime();

    // 8) Saída: uma linha com N valores (4 casas decimais)
    for(int i=0;i<N;i++){
        printf("%.4f%s", x[i], (i==N-1) ? "\n" : " ");
    }
    // Log em stderr (não polui a solução)
    fprintf(stderr,"[omp] thr=%d iter=%d tempo=%.6f s\n", nth, k, (t1-t0));

    free(A); free(b); free(x); free(x_new);
    return 0;
}
