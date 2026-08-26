    // Import da biblioteca
    #include "ArvoreB.h"

    // Função main
    int main (){
        arvore *raiz = cria_no(); 
        dados_veiculo *veiculo = malloc(sizeof(dados_veiculo));
        dados_veiculo *veiculo_busca = malloc(sizeof(dados_veiculo));
        
        le_dat(raiz);

        int aux = 1000, opcoes, busca;
        while(aux != 0){
            printf("Bem Vindo a concessionária Ribas!"
            "\nQual Operação deseja realizar:"
            "\n1- Inserir um novo veículo;"
            "\n2- Remover um veículo"
            "\n3- Buscar um veículo"
            "\n4- Sair.\n");
            scanf("%i", &opcoes);
            if(opcoes == 1){
                printf("Passe os dados do veículo que deseja inserir(Placa, Modelo, Marca, Ano, Categoria, Quuilometragem e Status):");
                scanf("%s %s %s %d %s %d %s", veiculo->placa, veiculo->modelo, veiculo->marca, &veiculo->ano, veiculo->categoria, &veiculo->quilometragem, veiculo->status);
                bool checar_insercao = insere_veiculo(veiculo);
                if(checar_insercao == true)
                    printf("\nVeículo inserido com sucesso!");
                else    
                    printf("\nErro ao inserir o veículo!");
            }
            else if(opcoes == 2){
                printf("\nDigite a placa do veículo a ser removido: ");
                scanf("%s", veiculo->placa);
                bool checar_remocao = remove_veiculo(veiculo->placa);
                if(checar_remocao == true)
                    printf("\nVeículo removido com sucesso!");
                else
                    printf("\nErro ao remover o veículo!");
            }
            else if(opcoes == 3){
                printf("O que deseja buscar:"
                "\n1- Todos os dados do veículo;"
                "\n2- Modelo do veículo"
                "\n3- Marca do veículo;"
                "\n4- Ano do veículo"
                "\n5- Categoria do veículo"
                "\n6- Quilometragem do veículo"
                "\n7- Situação do veículo;"
                "\n8- Sair.\n");
                scanf("%i", &busca);

                if(busca == 1){
                    printf("\nDigite a placa do veículo que deseja buscar:\n");
                    scanf("%s", veiculo_busca->placa);
                    veiculo_busca = busca_veiculo(veiculo_busca->placa, 0);
                    if(veiculo_busca != NULL){
                        printf("\nDados do veículo são:\nPlaca:%s\nModelo:%s\nMarca:%s\nAno:%d\nCategoria:%s\nQuilometragem:%d\nSituação do veículo:%s\n", veiculo_busca->placa, veiculo_busca->modelo, veiculo_busca->marca, veiculo_busca->ano, veiculo_busca->categoria, veiculo_busca->quilometragem, veiculo_busca->status);
                    }
                }
                else if(busca == 2){
                    printf("\nDigite a placa do veículo que deseja buscar:\n");
                    scanf("%s", veiculo_busca->placa);
                    veiculo_busca = busca_veiculo(veiculo_busca->placa, 0);
                    if(veiculo_busca != NULL){
                        printf("Modelo:%s\n", veiculo_busca->modelo);
                    }
                }
                else if(busca == 3){
                    printf("\nDigite a placa do veículo que deseja buscar:\n");
                    scanf("%s", veiculo_busca->placa);
                    veiculo_busca = busca_veiculo(veiculo_busca->placa, 0);
                    if(veiculo_busca != NULL){
                        printf("Marca:%s\n", veiculo_busca->marca);
                    }                    
                }
                else if(busca == 4){
                    printf("\nDigite a placa do veículo que deseja buscar:\n");
                    scanf("%s", veiculo_busca->placa);
                    veiculo_busca = busca_veiculo(veiculo_busca->placa, 0);
                    if(veiculo_busca != NULL){
                        printf("Ano:%d\n", veiculo_busca->ano);
                    }
                }
                else if(busca == 5){
                    printf("\nDigite a placa do veículo que deseja buscar:\n");
                    scanf("%s", veiculo_busca->placa);
                    veiculo_busca = busca_veiculo(veiculo_busca->placa, 0);
                    if(veiculo_busca != NULL){
                        printf("Categoria:%s\n", veiculo_busca->categoria);
                    }    
                }
                else if(busca == 6){
                    printf("\nDigite a placa do veículo que deseja buscar:\n");
                    scanf("%s", veiculo_busca->placa);
                    veiculo_busca = busca_veiculo(veiculo_busca->placa, 0);
                    if(veiculo_busca != NULL){
                        printf("Quilometragem:%d", veiculo_busca->quilometragem);
                    }
                }
                else if(busca == 7){
                    printf("\nDigite a placa do veículo que deseja buscar:\n");
                    scanf("%s", veiculo_busca->placa);
                    veiculo_busca = busca_veiculo(veiculo_busca->placa, 0);
                    if(veiculo_busca != NULL){
                        printf("Situação:%s", veiculo_busca->status);
                    }
                }
                else if(busca == 8){
                    printf("\nSaindo...\n\n\n\n\n\n");
                }
                else{
                    printf("\nOpção inválida\n");
                }
            }
            else if(opcoes == 4){
                aux = 0;
                break;
            }
            else{
                printf("\nOpção inválida\n");
            }
        }
        
        return 0;
    }
