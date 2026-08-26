#include "ArvoreB.h"

arvore* cria_no(){
    arvore* raiz = malloc(sizeof(arvore));
    if (raiz == NULL) {
        return NULL;
    }
    
    raiz->numero_de_placas = 0;
    raiz->e_folha = 1;
    raiz->posicao_no = proximo_rnn();

    for (int i = 0; i < ORDEM; i++) {
        raiz->filhos[i] = NULL;
    }

    return raiz;
}

// Atuliza o rnn
int proximo_rnn() {
    return ++ultimo_rnn;
}

void insere_nao_cheio(arvore* pai, dados_veiculo* dados){
    int i = pai->numero_de_placas - 1;

    if (pai->e_folha) {
        while (i >= 0 && strcmp(pai->vetor_placas[i], dados->placa) > 0) {
            pai->vetor_placas[i + 1] = pai->vetor_placas[i];
            i--;
        }

        pai->vetor_placas[i + 1] = dados->placa;
        pai->numero_de_placas++;
    } else {
        while (i >= 0 && strcmp(pai->vetor_placas[i], dados->placa) > 0) {
            i--;
        }
        i++;

        if (pai->filhos[i]->numero_de_placas == ORDEM - 1) {
            divide_no(pai, i, pai->filhos[i]);

            if (strcmp(pai->vetor_placas[i], dados->placa) < 0) {
                i++;
            }
        }
        insere_nao_cheio(pai->filhos[i], dados);
    }
}

arvore* insere_no(arvore* pai, dados_veiculo* dados, int rnn) {
    if (pai == NULL) {
        pai = cria_no();
        if (pai == NULL) {
            printf("Erro ao alocar memória para o nó.\n");
            exit(1);
        }
    }

    if (pai->numero_de_placas == ORDEM - 1) {
        arvore* nova_raiz = cria_no();
        nova_raiz->e_folha = 0;
        nova_raiz->filhos[0] = pai;
        divide_no(nova_raiz, 0, pai);
        insere_nao_cheio(nova_raiz, dados);
        escreve_bin(nova_raiz);
        return nova_raiz;
    } else {
        insere_nao_cheio(pai, dados);
        escreve_bin(pai);
        return pai;
    }
}

void divide_no(arvore* pai, int i, arvore* filho) {
    arvore* novo_no = cria_no();
    novo_no->e_folha = filho->e_folha;
    novo_no->numero_de_placas = ORDEM / 2 - 1;

    for (int j = 0; j < ORDEM / 2 - 1; j++) {
        novo_no->vetor_placas[j] = filho->vetor_placas[j + ORDEM / 2];
    }

    if (!filho->e_folha) {
        for (int j = 0; j < ORDEM / 2; j++) {
            novo_no->filhos[j] = filho->filhos[j + ORDEM / 2];
        }
    }

    filho->numero_de_placas = ORDEM / 2 - 1;

    for (int j = pai->numero_de_placas; j >= i + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }

    novo_no->posicao_no = proximo_rnn();
    pai->filhos[i + 1] = novo_no;

    for (int j = pai->numero_de_placas - 1; j >= i; j--) {
        pai->vetor_placas[j + 1] = pai->vetor_placas[j];
    }

    pai->vetor_placas[i] = filho->vetor_placas[ORDEM / 2 - 1];
    pai->numero_de_placas++;

    escreve_bin(filho);
    escreve_bin(novo_no);
    escreve_bin(pai);
}

void remove_no(char placa[TAMANHO_PLACA], int rnn) {
    arvore* no = busca_arvore(placa, rnn);

    if (no == NULL) {
        printf("Placa %s não encontrada na árvore.\n", placa);
        return;
    }

    int i;
    for (i = 0; i < no->numero_de_placas && strcmp(no->vetor_placas[i], placa) < 0; i++);

    if (i < no->numero_de_placas && strcmp(no->vetor_placas[i], placa) == 0) {
        for (int j = i; j < no->numero_de_placas - 1; j++) {
            no->vetor_placas[j] = no->vetor_placas[j + 1];
            no->vetor_rnn[j] = no->vetor_rnn[j + 1];
        }
        no->numero_de_placas--;
        if(no->numero_de_placas <= ORDEM/2 -1){
            arvore* novo_no = cocatena_no(placa, rnn);
            escreve_bin(novo_no);
        }
    }

    escreve_bin(no);
    free(no);
}

arvore* cocatena_no(char placa[TAMANHO_PLACA], int rnn) {
    arvore* no = busca_arvore(placa, rnn);
    
    if (no == NULL) {
        printf("Placa %s não encontrada para concatenação.\n", placa);
        return NULL;
    }

    if (no->numero_de_placas < ORDEM / 2) {
        
        int indice_irmao = rnn - 1;
        arvore* irmao = le_bin(indice_irmao);

        if (irmao && irmao->numero_de_placas < ORDEM - 1) {
            for (int i = 0; i < no->numero_de_placas; i++) {
                irmao->vetor_placas[irmao->numero_de_placas + i] = no->vetor_placas[i];
            }
            irmao->numero_de_placas += no->numero_de_placas;

            escreve_bin(irmao);
            free(no);
            return irmao;
        }
    }
    
    free(no);
    return NULL;
}

arvore* busca_arvore(char placa[TAMANHO_PLACA], int posicao){
    printf("Comçando a busca no binario(le_bin)\n");
    fflush(stdout);
    arvore* buscada = le_bin(posicao);
    printf("Terminei a busca!\n");
    fflush(stdout);

    printf("%s", buscada->vetor_placas[0]);
    fflush(stdout);
    
    if(buscada != NULL){
        for(int i = 0; i < ORDEM-1; i++){
            printf("Vou comecar as comparações!\n");
            fflush(stdout);
            if(strcmp(buscada->vetor_placas[i], placa) == 0){
                printf("Achei!\n");
                fflush(stdout);
                return buscada;
            } 
        }
        posicao++;
        return busca_arvore(placa, posicao);
    }

    printf("Não achei a pagina!\n");
    fflush(stdout);
    return NULL;
}

// Busca para localizar em qual página deverá ser inserido um novo veículo
arvore* busca_insercao(char placa[TAMANHO_PLACA]) {
    int rrn_atual = 0;  
    arvore* no_atual = le_bin(rrn_atual);

    while (no_atual != NULL) {
        int i;
        
        for (i = 0; i < no_atual->numero_de_placas; i++) {
            if (strcmp(placa, no_atual->vetor_placas[i]) < 0) {
                break;
            }
        }

        if (no_atual->filhos[0] == NULL) {
            return no_atual;
        }

        rrn_atual = no_atual->filhos[i]->posicao_no;  
        free(no_atual); 

        no_atual = le_bin(rrn_atual);
    }

    printf("Erro: não foi possível localizar o nó de inserção.\n");
    return NULL;
}

bool insere_veiculo(dados_veiculo* veiculo) {
    arvore* buscada = busca_insercao(veiculo->placa);

    int rnn = escreve_dat(veiculo);
    if (rnn == -1) {
        printf("Erro ao escrever os dados do veículo no arquivo.\n");
        return false;
    }

    arvore* no_atualizado = insere_no(buscada, veiculo, rnn);

    escreve_bin(no_atualizado);
    insere_no(buscada, veiculo, rnn);

    return true;
}

bool remove_veiculo(char placa[TAMANHO_PLACA]){
    printf("Removido! ;)");
    return true;
}

dados_veiculo* busca_veiculo(char placa[TAMANHO_PLACA], int rnn){
    printf("Iniciando busca do veículo com placa: %s e RNN: %d\n", placa, rnn);
    arvore* buscada = busca_arvore(placa, rnn);
    if(buscada == NULL){
        printf("Dados do veículo não localizados!\n");
        return NULL;
    }

    for(int i = 0; i < ORDEM-1; i++){
        printf("Comparando placa: %s com %s\n", buscada->vetor_placas[i], placa);
        if(strcmp(buscada->vetor_placas[i], placa) == 0){
            dados_veiculo* veiculo = busca_veiculo_dat(rnn);
            if (veiculo == NULL) {
                printf("Erro ao buscar dados do veículo no arquivo.\n");
            }
            return veiculo;
        }
    }

    printf("Placa não encontrada na árvore.\n");
    return NULL;
}

fila* cria_fila(fila* novo_elem, arvore* ultima_pai){
    novo_elem = malloc(sizeof(fila));
    novo_elem->usada = ultima_pai;
    novo_elem->dir = NULL;
    novo_elem->posicao = 0;
    return novo_elem;   
}

void insere_fila(fila* cabeca, arvore* pai) {
    fila* copia_cabeca = cabeca;
    
    if (cabeca->posicao == P) {
        remove_fila(cabeca);
    }
    
    while (copia_cabeca->dir != NULL) {
        copia_cabeca->posicao++;
        copia_cabeca = copia_cabeca->dir;
    }

    fila* novo_elem = cria_fila(novo_elem, pai);
    copia_cabeca->dir = novo_elem;
    copia_cabeca->posicao++;
}

void remove_fila(fila* cabeca){
    if (cabeca == NULL || cabeca->dir == NULL) {
        return;
    }

    fila* temp = cabeca;
    cabeca = cabeca->dir;
    free(temp);
    temp = NULL;

    fila* atual = cabeca;
    while (atual != NULL) {
        atual->posicao--;
        atual = atual->dir;
    }
}

arvore* busca_fila(fila* cabeca, char placa[TAMANHO_PLACA]){
    fila* atual = cabeca;
    while (atual != NULL) {
        for (int i = 0; i < atual->usada->numero_de_placas; i++) {
            if (strcmp(atual->usada->vetor_placas[i], placa) == 0) {
                return atual->usada;
            }
        }
        atual = atual->dir;
    }
    return NULL;
}

void le_dat(arvore* pai) {
    FILE* fpdat = fopen("veiculos.dat", "rb");
    if (fpdat == NULL) {
        perror("Falha ao abrir o arquivo veiculos.dat\n");
        return;
    }
    
    size_t registros = sizeof(dados_veiculo);
    dados_veiculo* dados_no = malloc(registros);
    if (dados_no == NULL) {
        perror("Falha ao alocar memória para dados_veiculo\n");
        fclose(fpdat);
        return;
    }

    int i = 0;

    while (fread(dados_no, registros, 1, fpdat) == 1) {
        i++;
        insere_no(pai, dados_no, i * registros);
    }

    if (ferror(fpdat)) {
        printf("Erro ao tentar ler os registros de veículos para criar a árvore!\n");
    }

    fclose(fpdat);
    free(dados_no);
}

int escreve_dat(dados_veiculo* veiculo) {
    int aux = 101;
    
    for(int i = 0; i < VETOR_REMOCAO; i++) {
        if(vetor_removidos[i]) {
            aux = vetor_removidos[i];
            vetor_removidos[i] = 0; // Mark the slot as used
            break;
        }
    }

    size_t registros = sizeof(dados_veiculo);
    FILE* fpdat;
    int rnn;

    if(aux == 101) {
        fpdat = fopen("veiculos.dat", "ab");
        if (!fpdat) {
            perror("Erro ao abrir o arquivo veiculos.dat para escrita");
            return -1;
        }
        fseek(fpdat, 0, SEEK_END);
        rnn = ftell(fpdat) / registros;
    } else {    
        fpdat = fopen("veiculos.dat", "rb+");
        if (!fpdat) {
            perror("Erro ao abrir o arquivo veiculos.dat para atualização");
            return -1;
        }
        fseek(fpdat, aux * registros, SEEK_SET);
        rnn = aux;
    }

    size_t escrito = fwrite(veiculo, registros, 1, fpdat);
    
    if(escrito != 1) {
        printf("Erro ao escrever no arquivo veiculos.dat!\n");
        fclose(fpdat);
        return -1;
    }

    fclose(fpdat);
    return rnn;
}

void remove_dat(int rnn) {
    FILE* fpdat = fopen("veiculos.dat", "rb+");
    if (fpdat == NULL) {
        printf("Erro ao abrir o arquivo de dados.\n");
        return;
    }

    vetor_removidos[rnn] = rnn;

    dados_veiculo veiculo_removido = { .placa = "REMOVIDO" };
    fseek(fpdat, rnn * sizeof(dados_veiculo), SEEK_SET);
    fwrite(&veiculo_removido, sizeof(dados_veiculo), 1, fpdat);

    fclose(fpdat);
}

dados_veiculo* busca_veiculo_dat(int rnn){
    FILE* fpdat = fopen("veiculos.dat", "rb");
    if (fpdat == NULL) {
        printf("Erro ao abrir o arquivo veiculos.dat\n");
        return NULL;
    }

    dados_veiculo* veiculo = malloc(sizeof(dados_veiculo));
    if (veiculo == NULL) {
        printf("Erro ao alocar memória para dados_veiculo\n");
        fclose(fpdat);
        return NULL;
    }

    fseek(fpdat, rnn * sizeof(dados_veiculo), SEEK_SET);
    size_t lidos = fread(veiculo, sizeof(dados_veiculo), 1, fpdat);
    if(lidos != 1){
        printf("Erro ao tentar localizar e ler o veículo!\n");
        free(veiculo);
        fclose(fpdat);
        return NULL;
    }

    fclose(fpdat);
    return veiculo;
}

arvore* le_bin(int rrn) {
    FILE* fpbin = fopen("binario.bin", "rb");
    if (fpbin == NULL) {
        printf("Erro ao abrir o arquivo binário para leitura!\n");
        return NULL;
    }

    arvore* buscada = malloc(sizeof(*buscada));
    size_t tamanho_registro = sizeof(*buscada);
    fseek(fpbin, rrn * tamanho_registro, SEEK_SET);

    size_t lido = fread(buscada, tamanho_registro, 1, fpbin);
    if (lido != 1) {
        printf("Erro ao tentar ler o arquivo binário na posição %d\n", rrn);
        free(buscada);
        fclose(fpbin);
        return NULL;
    }

    fclose(fpbin);
    return buscada;
}

void escreve_bin(arvore* pai) {
    FILE* fpbin = fopen("binario.bin", "rb+");

    if (fpbin == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    size_t tamanho_registro = sizeof(*pai);
    fseek(fpbin, pai->posicao_no * tamanho_registro, SEEK_SET);

    size_t elementos_escritos = fwrite(pai, tamanho_registro, 1, fpbin);
    if (elementos_escritos != 1) {
        printf("Erro ao escrever os dados no arquivo binário.\n");
        fclose(fpbin);
        return;
    }

    fclose(fpbin);
}