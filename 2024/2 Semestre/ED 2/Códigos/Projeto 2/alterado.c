// Import das bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definições de variavéis globais
#define P 20
#define ORDEM 80
#define TAMANHO_PLACA 8
#define TAMANHO_MODELO 20
#define TAMANHO_MARCA 20
#define TAMANHO_CATEGORIA 15
#define TAMANHO_STATUS 16
#define TAMANHO_REGISTRO 88
#define VETOR_REMOCAO 1000

// Structs utilizadas
typedef struct {
    char placa[TAMANHO_PLACA];
    char modelo[TAMANHO_MODELO];
    char marca[TAMANHO_MARCA];
    int ano;
    char categoria[TAMANHO_CATEGORIA];
    int quilometragem;
    char status[TAMANHO_STATUS];
} dados_veiculo;

typedef struct ArvoreBMais{
    int numero_de_placas;
    char* vetor_placas[ORDEM-1];
    int vetor_rnn[ORDEM-1];
    struct ArvoreBMais *filhos[ORDEM+1];
    bool e_folha;
    int posicao_no;
}arvore;

typedef struct fila_de_no{
    struct fila_de_no *dir;
    int posicao;
    arvore* usada;
}fila;

fila *inicio = NULL;
fila *fim = NULL;

void inserebarvore(arvore**,char*,int);
void inserebarvore_nao_cheia(arvore*,char*,int);
void divide_no(arvore*, int, arvore*);
dados_veiculo* busca_veiculo(char*, int);
void remove_no(arvore *raiz, char* placa);
void redistribuicao(arvore *raiz);
void insere_fila(arvore*);
dados_veiculo* busca_fila(char*);
void escreve_dat(dados_veiculo*);
void escreve_bin(arvore*);
void leitura_arquivodat(arvore**);
arvore* le_bin(int);


int main() {
    arvore *raiz = NULL;
    dados_veiculo *veiculo = malloc(sizeof(dados_veiculo));
    dados_veiculo *veiculo_busca = NULL;

    leitura_arquivodat(&raiz);

    int aux = 1, opcoes, busca;
    while (aux != 0) {
        printf("Bem Vindo a concessionária Ribas!"
               "\nQual Operação deseja realizar:"
               "\n1- Inserir um novo veículo;"
               "\n2- Remover um veículo"
               "\n3- Buscar um veículo"
               "\n4- Sair.\n");
        scanf("%d", &opcoes);
        if (opcoes == 1) {
            printf("Passe os dados do veículo que deseja inserir (Placa, Modelo, Marca, Ano, Categoria, Quilometragem e Status): ");
            scanf("%s %s %s %d %s %d %s", veiculo->placa, veiculo->modelo, veiculo->marca, &veiculo->ano, veiculo->categoria, &veiculo->quilometragem, veiculo->status);
            inserebarvore(&raiz, veiculo->placa, 0);
            escreve_dat(veiculo);
            printf("\nVeículo inserido com sucesso!\n");
        } else if (opcoes == 2) {
            printf("\nDigite a placa do veículo a ser removido: ");
            scanf("%s", veiculo->placa);
            remove_no(raiz, veiculo->placa);
            printf("\nVeículo removido com sucesso!\n");
        } else if (opcoes == 3) {
            printf("O que deseja buscar:"
                   "\n1- Todos os dados do veículo;"
                   "\n2- Modelo do veículo"
                   "\n3- Marca do veículo;"
                   "\n4- Ano do veículo"
                   "\n5- Categoria do veículo"
                   "\n6- Quilometragem do veículo"
                   "\n7- Situação do veículo;"
                   "\n8- Sair.\n");
            scanf("%d", &busca);
            if (busca >= 1 && busca <= 7) {
                printf("\nDigite a placa do veículo que deseja buscar:\n");
                char placa[TAMANHO_PLACA];
                scanf("%s", placa);
                veiculo_busca = busca_veiculo(placa, 0);
                if (veiculo_busca != NULL) {
                    if (busca == 1) {
                        printf("\nDados do veículo são:\nPlaca:%s\nModelo:%s\nMarca:%s\nAno:%d\nCategoria:%s\nQuilometragem:%d\nSituação do veículo:%s\n", veiculo_busca->placa, veiculo_busca->modelo, veiculo_busca->marca, veiculo_busca->ano, veiculo_busca->categoria, veiculo_busca->quilometragem, veiculo_busca->status);
                    } else if (busca == 2) {
                        printf("Modelo:%s\n", veiculo_busca->modelo);
                    } else if (busca == 3) {
                        printf("Marca:%s\n", veiculo_busca->marca);
                    } else if (busca == 4) {
                        printf("Ano:%d\n", veiculo_busca->ano);
                    } else if (busca == 5) {
                        printf("Categoria:%s\n", veiculo_busca->categoria);
                    } else if (busca == 6) {
                        printf("Quilometragem:%d\n", veiculo_busca->quilometragem);
                    } else if (busca == 7) {
                        printf("Situação:%s\n", veiculo_busca->status);
                    }
                } else {
                    printf("Veículo não encontrado.\n");
                }
            } else if (busca == 8) {
                printf("\nSaindo...\n\n\n\n\n\n");
            } else {
                printf("\nOpção inválida\n");
            }
        } else if (opcoes == 4) {
            aux = 0;
            break;
        } else {
            printf("\nOpção inválida\n");
        }
    }

    free(veiculo);
    free(veiculo_busca);
    return 0;
}

void inserebarvore(arvore **raiz, char* placa, int rnn) {
    arvore *novo_no = malloc(sizeof(arvore));
    novo_no->numero_de_placas = 1;
    novo_no->vetor_placas[0] = strdup(placa);
    novo_no->vetor_rnn[0] = rnn;
    novo_no->e_folha = true;
    novo_no->filhos[0] = *raiz;
    novo_no->filhos[1] = NULL;
    *raiz = novo_no;
}

void inserebarvore_nao_cheia(arvore *raiz, char* placa, int rnn) {
    arvore *novo_no = malloc(sizeof(arvore));
    novo_no->numero_de_placas = 1;
    novo_no->vetor_placas[0] = strdup(placa);
    novo_no->vetor_rnn[0] = rnn;
    novo_no->e_folha = true;
    novo_no->filhos[0] = raiz->filhos[0];
    novo_no->filhos[1] = NULL;
    raiz->filhos[0] = novo_no;
}

void divide_no(arvore *raiz, int i, arvore *filho) {
    arvore *novo_no = malloc(sizeof(arvore));
    novo_no->numero_de_placas = 1;
    novo_no->vetor_placas[0] = strdup(filho->vetor_placas[ORDEM / 2]);
    novo_no->vetor_rnn[0] = filho->vetor_rnn[ORDEM / 2];
    novo_no->e_folha = true;
    novo_no->filhos[0] = filho->filhos[ORDEM / 2];
    novo_no->filhos[1] = NULL;
    filho->filhos[ORDEM / 2] = novo_no;
}

dados_veiculo* busca_fila(char* placa) {
    fila *temp = inicio;
    while (temp != NULL) {
        arvore *pagina = temp->usada;
        for (int i = 0; i < pagina->numero_de_placas; i++) {
            if (strcmp(pagina->vetor_placas[i], placa) == 0) {
                FILE *file = fopen("arquivo.dat", "rb");
                if (file == NULL) {
                    perror("Erro ao abrir o arquivo");
                    return NULL;
                }
                dados_veiculo *veiculo = malloc(sizeof(dados_veiculo));
                fseek(file, pagina->vetor_rnn[i] * sizeof(dados_veiculo), SEEK_SET);
                fread(veiculo, sizeof(dados_veiculo), 1, file);
                fclose(file);
                return veiculo;
            }
        }
        temp = temp->dir;
    }
    return NULL;
}

void leitura_arquivodat(arvore **raiz) {
    FILE *file = fopen("arquivo.dat", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    dados_veiculo veiculo;
    int rnn = 0;
    while (fread(&veiculo, sizeof(dados_veiculo), 1, file) == 1) {
        inserebarvore(raiz, veiculo.placa, rnn);
        rnn++;
        fseek(file, rnn * TAMANHO_REGISTRO, SEEK_SET); // Move para o próximo registro
    }

    fclose(file);
}

dados_veiculo* busca_veiculo(char* placa, int posicao) {
    return busca_fila(placa);
}

void remove_no(arvore *raiz, char* placa) {
    arvore *temp = raiz;
    arvore *anterior = NULL;
    while (temp != NULL) {
        for (int i = 0; i < temp->numero_de_placas; i++) {
            if (strcmp(temp->vetor_placas[i], placa) == 0) {
                if (anterior != NULL) {
                    anterior->filhos[0] = temp->filhos[0];
                } else {
                    raiz = temp->filhos[0];
                }
                free(temp);
                printf("Veículo removido com sucesso.\n");
                return;
            }
        }
        anterior = temp;
        temp = temp->filhos[0];
    }
    printf("Veículo não encontrado.\n");
}

void redistribuicao(arvore *raiz) {
    for (int i = 0; i <= raiz->numero_de_placas; i++) {
        if (raiz->filhos[i]->numero_de_placas < ORDEM / 2) {
            if (i != 0 && raiz->filhos[i - 1]->numero_de_placas > ORDEM / 2) {
                arvore *esquerda = raiz->filhos[i - 1];
                arvore *direita = raiz->filhos[i];

                for (int j = direita->numero_de_placas; j > 0; j--) {
                    strcpy(direita->vetor_placas[j], direita->vetor_placas[j - 1]);
                    direita->vetor_rnn[j] = direita->vetor_rnn[j - 1];
                }

                if (!direita->e_folha) {
                    for (int j = direita->numero_de_placas + 1; j > 0; j--) {
                        direita->filhos[j] = direita->filhos[j - 1];
                    }
                }

                strcpy(direita->vetor_placas[0], raiz->vetor_placas[i - 1]);
                direita->vetor_rnn[0] = raiz->vetor_rnn[i - 1];

                if (!direita->e_folha) {
                    direita->filhos[0] = esquerda->filhos[esquerda->numero_de_placas];
                }

                strcpy(raiz->vetor_placas[i - 1], esquerda->vetor_placas[esquerda->numero_de_placas - 1]);
                raiz->vetor_rnn[i - 1] = esquerda->vetor_rnn[esquerda->numero_de_placas - 1];

                esquerda->numero_de_placas--;
                direita->numero_de_placas++;
            } else if (i != raiz->numero_de_placas && raiz->filhos[i + 1]->numero_de_placas > ORDEM / 2) {
                arvore *esquerda = raiz->filhos[i];
                arvore *direita = raiz->filhos[i + 1];

                strcpy(esquerda->vetor_placas[esquerda->numero_de_placas], raiz->vetor_placas[i]);
                esquerda->vetor_rnn[esquerda->numero_de_placas] = raiz->vetor_rnn[i];

                if (!esquerda->e_folha) {
                    esquerda->filhos[esquerda->numero_de_placas + 1] = direita->filhos[0];
                }

                strcpy(raiz->vetor_placas[i], direita->vetor_placas[0]);
                raiz->vetor_rnn[i] = direita->vetor_rnn[0];

                for (int j = 0; j < direita->numero_de_placas - 1; j++) {
                    strcpy(direita->vetor_placas[j], direita->vetor_placas[j + 1]);
                    direita->vetor_rnn[j] = direita->vetor_rnn[j + 1];
                }

                if (!direita->e_folha) {
                    for (int j = 0; j < direita->numero_de_placas; j++) {
                        direita->filhos[j] = direita->filhos[j + 1];
                    }
                }

                esquerda->numero_de_placas++;
                direita->numero_de_placas--;
            } else {
                if (i != 0) {
                    arvore *esquerda = raiz->filhos[i - 1];
                    arvore *direita = raiz->filhos[i];

                    strcpy(esquerda->vetor_placas[esquerda->numero_de_placas], raiz->vetor_placas[i - 1]);
                    esquerda->vetor_rnn[esquerda->numero_de_placas] = raiz->vetor_rnn[i - 1];

                    for (int j = 0; j < direita->numero_de_placas; j++) {
                        strcpy(esquerda->vetor_placas[esquerda->numero_de_placas + 1 + j], direita->vetor_placas[j]);
                        esquerda->vetor_rnn[esquerda->numero_de_placas + 1 + j] = direita->vetor_rnn[j];
                    }

                    if (!esquerda->e_folha) {
                        for (int j = 0; j <= direita->numero_de_placas; j++) {
                            esquerda->filhos[esquerda->numero_de_placas + 1 + j] = direita->filhos[j];
                        }
                    }

                    esquerda->numero_de_placas += direita->numero_de_placas + 1;

                    for (int j = i - 1; j < raiz->numero_de_placas - 1; j++) {
                        strcpy(raiz->vetor_placas[j], raiz->vetor_placas[j + 1]);
                        raiz->vetor_rnn[j] = raiz->vetor_rnn[j + 1];
                        raiz->filhos[j + 1] = raiz->filhos[j + 2];
                    }

                    raiz->numero_de_placas--;
                    free(direita);
                } else {
                    arvore *esquerda = raiz->filhos[i];
                    arvore *direita = raiz->filhos[i + 1];

                    strcpy(esquerda->vetor_placas[esquerda->numero_de_placas], raiz->vetor_placas[i]);
                    esquerda->vetor_rnn[esquerda->numero_de_placas] = raiz->vetor_rnn[i];

                    for (int j = 0; j < direita->numero_de_placas; j++) {
                        strcpy(esquerda->vetor_placas[esquerda->numero_de_placas + 1 + j], direita->vetor_placas[j]);
                        esquerda->vetor_rnn[esquerda->numero_de_placas + 1 + j] = direita->vetor_rnn[j];
                    }

                    if (!esquerda->e_folha) {
                        for (int j = 0; j <= direita->numero_de_placas; j++) {
                            esquerda->filhos[esquerda->numero_de_placas + 1 + j] = direita->filhos[j];
                        }
                    }

                    esquerda->numero_de_placas += direita->numero_de_placas + 1;

                    for (int j = i; j < raiz->numero_de_placas - 1; j++) {
                        strcpy(raiz->vetor_placas[j], raiz->vetor_placas[j + 1]);
                        raiz->vetor_rnn[j] = raiz->vetor_rnn[j + 1];
                        raiz->filhos[j + 1] = raiz->filhos[j + 2];
                    }

                    raiz->numero_de_placas--;
                    free(direita);
                }
            }
        }
    }
}

void insere_fila(arvore *pagina) {
    fila *novo_no = malloc(sizeof(fila));
    novo_no->usada = pagina;
    novo_no->dir = NULL;
    if (inicio == NULL) {
        inicio = novo_no;
    } else {
        fim->dir = novo_no;
    }
    fim = novo_no;
}

void escreve_dat(dados_veiculo *veiculo) {
    FILE *file = fopen("arquivo.dat", "ab");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fwrite(veiculo, sizeof(dados_veiculo), 1, file);
    fclose(file);
}

void escreve_bin(arvore *raiz) {
    if (raiz == NULL) return;

    FILE *file = fopen("arvore.bin", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fila *queue = NULL;
    fila *tail = NULL;

    fila *novo_no = malloc(sizeof(fila));
    novo_no->usada = raiz;
    novo_no->dir = NULL;
    novo_no->posicao = 0;
    queue = tail = novo_no;

    int posicao = 0;

    while (queue != NULL) {
        arvore *pagina = queue->usada;
        pagina->posicao_no = posicao;

        fseek(file, posicao * sizeof(arvore), SEEK_SET);
        fwrite(pagina, sizeof(arvore), 1, file);

        for (int i = 0; i <= pagina->numero_de_placas; i++) {
            if (pagina->filhos[i] != NULL) {
                fila *novo_no = malloc(sizeof(fila));
                novo_no->usada = pagina->filhos[i];
                novo_no->dir = NULL;
                novo_no->posicao = ++posicao;
                tail->dir = novo_no;
                tail = novo_no;
            }
        }

        fila *temp = queue;
        queue = queue->dir;
        free(temp);
    }

    fclose(file);
}

arvore* le_bin(int posicao) {
    FILE *file = fopen("arvore.bin", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    arvore *pagina = malloc(sizeof(arvore));
    fseek(file, posicao * sizeof(arvore), SEEK_SET);
    fread(pagina, sizeof(arvore), 1, file);
    fclose(file);

    return pagina;
}