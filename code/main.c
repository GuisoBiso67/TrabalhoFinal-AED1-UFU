#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    char nameTVAux[50]; // string auxiliar para nomes de séries;
    TVS_Node* tvsAux; // nó de séries auxiliar
    TVShow tvsAuxStr; // struct auxiliar para dados de séries;

    int opP, opS; // variáveis para seleção;

    do {
        printMainMenu(); // imprime menu principal
        scanf("%d", &opP); // pede opção
        //getchar();
        switch (opP) {
            case 1: // adiciona perfil novo a partir de entradas do usuário;
                printf("Nome: ");
                scanf(" %[^\n]", p.name);
                trim(p.name);
                printf("Idade: ");
                scanf(" %[^\n]", p.age);
                trim(p.age);
                const int ver9 = addProfile(profiles, p);
                if (ver9 == 1) printf("Perfil adicionado!\n");
                else printf("Perfil nao foi adicionado. Tente novamente.\n");
                break;
            case 2: // carrega lista de perfis de um arquivo;
                const int ver1 = load_profiles(profiles, "archives/profiles.txt");
                if (ver1 == 1) {
                    printf("Perfis carregados com sucesso!\n");
                }else {
                    printf("Nao foi possivel carregar os perfis.\n");
                }
                break;
            case 3: // remove um perfil
                printf("Nome do Perfil: ");
                scanf(" %[^\n]", nameAux);
                trim(nameAux);
                const int ver2 = removeProfile(profiles, nameAux);
                if (ver2 == 1) {
                    printf("Perfil removido com sucesso!\n");
                }else if (ver2 == -1) {
                    printf("Perfil nao encontrado.\n");
                }else {
                    printf("Lista Vazia!");
                }
                break;
            case 4: // abre o perfil cadastrado a partir do nome;
                printf("Nome do Perfil: ");
                scanf(" %[^\n]", nameAux); // função para encontrar perfil
                trim(nameAux);
                pnAux = searchProfile(profiles, nameAux); // pnAux recebe o nó com as informações do perfil para ser alterado;
                if (pnAux == NULL) {
                    printf("Perfil nao cadastrado.\n");
                    break;
                }
                do {
                    printMenuProfiles(nameAux); // imprime menu dentro de um perfil;
                    scanf("%d", &opS); // pede opção;
                    //getchar();
                    switch (opS) {
                        case 1: // adiciona uma série a partir de entradas do usuário;
                            printf("Nome: ");
                            scanf(" %[^\n]", tvsAuxStr.name);
                            printf("Emissora/Streaming: ");
                            scanf(" %[^\n]", tvsAuxStr.broadcaster);
                            printf("Nome do Criador: ");
                            scanf(" %[^\n]", tvsAuxStr.creator);
                            printf("Genero (mais de 1, use /): ");
                            scanf(" %[^\n]", tvsAuxStr.genre);
                            printf("No de Temporadas: ");
                            scanf("%d", &tvsAuxStr.seasons);
                            printf("No de Episodios: ");
                            scanf("%d", &tvsAuxStr.episodes);
                            printf("Ano de Inicio: ");
                            scanf("%d", &tvsAuxStr.year);
                            printf("Nota no IMDB: ");
                            scanf(" %[^\n]", tvsAuxStr.ratingIMDB);
                            printf("Nota Pessoal: ");
                            scanf("%d", &tvsAuxStr.personalRating);
                            printf("Eh uma de suas series favoritas?(y/n): ");
                            scanf(" %c", &tvsAuxStr.favorite);
                            const int ver6 = addTVShow(pnAux, tvsAuxStr);
                            if (ver6 == 1) printf("Serie adicionada ao perfil!\n");
                            else printf("Serie nao foi adicionada. Tente novamente.\n");
                            break;
                        case 2: // adiciona uma lista de séries pré-montada a partir de um arquivo;
                            printf("Selecione um arquivo (s1.txt, s_.txt, ...): ");
                            scanf(" %[^\n]", arquiveNameAux);
                            const int ver3 = loadTVShows(pnAux, arquiveNameAux); // fazer função para encontrar perfil;
                            if (ver3 == 1) {
                                printf("Series adicionadas com sucesso!\n");
                            }else {
                                printf("Erro ao ler o arquivo. Tente Novamente.\n");
                            }
                            break;
                        case 3: // remove uma série da lista
                            printf("Nome da Serie: ");
                            scanf(" %[^\n]", nameTVAux);
                            const int ver4 = removeTVShow(pnAux, nameTVAux);
                            if (ver4 == 1) {
                                printf("Serie foi removida do perfil!\n");
                            }else if (ver4 == -1) {
                                printf("Serie nao encontrada.\n");
                            }else {
                                printf("Perfil Vazia!\n");
                            }
                            break;
                        case 4: // imprime lista de séries
                            printTVShows(pnAux, NULL);
                            break;
                        case 5: // imprime apenas séries favoritas
                            printFavorites(pnAux);
                            break;
                        case 6: // procura uma série no perfil
                            printf("Nome da Serie: ");
                            scanf(" %[^\n]", nameTVAux);
                            tvsAux = searchTVShow(pnAux, nameTVAux);
                            if (tvsAux == NULL) printf("Serie nao foi encontrada. Tente Novamente.\n");
                            else {
                                printf("\nSerie encontrada:\n");
                                printTVShows(pnAux, tvsAux);
                            }
                            break;
                        case 7: // adiciona uma série aos favoritos;
                            printf("Nome da Serie: ");
                            scanf(" %[^\n]", nameTVAux);
                            const int ver8 = favoriteTVShow(pnAux, nameTVAux);
                            if (ver8 == 1) printf("Serie adicionada aos favoritos!\n");
                            else if (ver8 == -1) printf("Serie ja estava nos favoritos!\n");
                            else printf("Serie nao foi encontrada.\n");
                            break;
                        case 8: // remove uma série dos favoritos;
                            printf("Nome da Serie: ");
                            scanf(" %[^\n]", nameTVAux);
                            const int ver7 = unfavoriteTVShow(pnAux, nameTVAux);
                            if (ver7 == 1) printf("Serie removida dos favoritos!\n");
                            else if (ver7 == -1) printf("Serie já estava fora dos favoritos!\n");
                            else printf("Serie nao foi encontrada.\n");
                            break;
                        case 0: // sai do perfil;
                            printf("Saindo do perfil...\n");
                            break;
                        default:
                            printf("Opcao invalida.\n");
                            break;
                    }
                }while (opS!=0);
                break;
            case 5: // imprime lista de perfis;
                printProfiles(profiles, NULL);
                break;
            case 6: // procura um perfil
                printf("Nome: ");
                scanf(" %[^\n]", nameAux);
                pnAux = searchProfile(profiles,nameAux);
                if (pnAux == NULL) printf("Perfil nao encontrado.\n");
                else {
                    printf("\nPerfil encontrado:\n");
                    printProfiles(profiles, pnAux);
                }
                break;
            case 7: // altera informações de um perfil já cadstrado;
                printf("Perfil: ");
                scanf(" %[^\n]", nameAux); // função para encontrar perfil
                trim(nameAux);
                pnAux = searchProfile(profiles, nameAux); // pnAux recebe o nó com as informações do perfil para ser alterado;
                if (pnAux == NULL) printf("Perfil nao encontrado.\n");
                else {
                    printf("Nome novo: ");
                    scanf(" %[^\n]", p.name);
                    trim(p.name);
                    printf("Idade nova: ");
                    scanf(" %[^\n]", p.age);
                    trim(p.age);
                    const int ver5 = changeInfo(pnAux, p);
                    if (ver5 == 0) printf("Erro na alteracao. Tente novamente.");
                    else printf("Dados Alterados!\n");
                }
                break;
            case 0: // sai do programa
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }while (opP!=0);

    freeList(profiles); // libera toda a memoria;
}