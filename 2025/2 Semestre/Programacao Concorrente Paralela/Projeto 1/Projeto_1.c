#include "lib.h"
#define n 10

int main(){
    // Defino as variáveis necessárias para o método sequencial
    FILE *arq = le_arq("C:\\Users\\felip\\Desktop\\Facul\\2025\\2 Semestre\\Programacao Concorrente Paralela\\Projeto 1\\teste.dat");
    double *vetor_resposta = malloc(n * sizeof(double));

    // Verificação para ver se o arquivo foi aberto corretamente
    if(arq == NULL){
        return(0);
    }

    // Chamo a função sequencial para resolver o sistema linear (Jacobi)
    vetor_resposta = jacobi(arq);
    
    // Escrevo as respostas no arquivo final (resultado_sequencial.dat)
    escreve_arq(vetor_resposta);
    return(0);
}