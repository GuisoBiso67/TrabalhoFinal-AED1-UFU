#include <stdio.h>
#include <stdlib.h>
#include "perfis.h"
#include "series.h"

int main() {
    D_profiles *profiles = createList();
    //load_profiles(profiles, "archives/profiles.txt");
    //printProfiles(profiles);

    Profile p;
    char nameAux[20]; // string auxiliar para nomes na chamada das funções;
    char arquiveNameAux[20]; // string auxiliar para nome de arquivos;
    Prof_Node* pnAux; // nó de perfis auxiliar;
    char nameTVAux[50];

    int op, op2;

    do {
        printf("\n----- MENU PERFIS -----\n");
        printf("1- Adicionar Perfil\n");
        printf("2- Carregar Perfis\n");
        printf("3- Remover Perfil\n");
        printf("4- Modificar Perfil\n"); // opção para adicionar as séries;
        printf("5- Imprimir Perfis\n");
        printf("0- Sair\n");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1:
                printf("Nome: ");
                scanf("%[^\n]", p.name);
                getchar();
                printf("Idade: ");
                scanf("%[^\n]", p.age);
                addProfile(profiles, p);
                break;
            case 2:
                const int ver1 = load_profiles(profiles, "archives/profiles.txt");
                if (ver1 == 1) {
                    printf("Perfis carregados com sucesso!\n");
                }else {
                    printf("Nao foi possivel carregar os perfis.\n");
                }
                break;
            case 3:
                printf("Nome do Perfil: ");
                scanf("%[^\n]", nameAux);
                const int ver2 = removeProfile(profiles, nameAux);
                if (ver2 == 1) {
                    printf("Perfil removido com sucesso!\n");
                }else if (ver2 == -1) {
                    printf("Perfil nao encontrado.\n");
                }else {
                    printf("Lista Vazia!");
                }
                break;
            case 4:
                printf("Perfil a ser modificado: ");
                scanf("%[^\n]", nameAux); // função para encontrar perfil
                pnAux = searchProfile(profiles, nameAux);
                if (pnAux == NULL) {
                    printf("Perfil nao cadastrado.\n");
                    break;
                }
                do {
                    printf("\n----- Perfil de %s -----\n", nameAux);
                    printf("1- Adicionar Serie\n");
                    printf("2- Carregar Series\n");
                    printf("3- Remover Serie\n");
                    printf("4- Imprimir Lista de Series\n");
                    printf("5- Imprimir Favoritos\n");
                    printf("0- Sair do Perfil\n");
                    scanf("%d", &op2);
                    getchar();
                    switch (op2) {
                        case 1:
                            break;
                        case 2:
                            printf("Selecione um arquivo (s1.txt, s_.txt, ...): ");
                            scanf("%[^\n]", arquiveNameAux);
                            const int ver3 = loadTVShows(pnAux, arquiveNameAux); // fazer função para encontrar perfil;
                            if (ver3 == 1) {
                                printf("Series adicionadas com sucesso!");
                            }else {
                                printf("Erro ao ler o arquivo. Tente Novamente.");
                            }
                            break;
                        case 3:
                            printf("Nome da Serie: ");
                            scanf("%[^\n]", nameTVAux);
                            const int ver4 = removeTVShow(pnAux, nameTVAux);
                            if (ver4 == 1) {
                                printf("Serie foi removida do perfil!\n");
                            }else if (ver4 == -1) {
                                printf("Serie nao encontrada.\n");
                            }else {
                                printf("Perfil Vazia!");
                            }
                            break;
                        case 4:
                            printTVShows(pnAux);
                            break;
                        case 5:
                            printf("Funcao nao foi feita. Aguarde");
                            break;
                        case 6:
                            break;
                        case 0:
                            printf("Saindo do perfil...\n");
                            break;
                        default:
                            printf("Opcao invalida.\n");
                            break;
                    }
                }while (op2!=0);
                break;
            case 5:
                printProfiles(profiles);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }while (op!=0);
}