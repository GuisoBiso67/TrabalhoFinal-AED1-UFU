#include <stdio.h>
#include <stdlib.h>
#include "perfis.h"
#include "series.h"

int main() {
    D_profiles *profiles = createList();
    load_profiles(profiles, "archives/profiles.txt");
    printProfiles(profiles);

    Profile p;
    char nameAux[20]; // string auxiliar para nomes na chamada das funções;
    char arquiveNameAux[20]; // string auxiliar para nome de arquivos;

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
                printf("Idade: ");
                scanf("%d", &p.age);
                addProfile(profiles, p);
                break;
            case 2:
                int ver1 = load_profiles(profiles, "archives/profiles.txt");
                if (ver1 == 1) {
                    printf("Perfis carregados com sucesso!\n");
                }else {
                    printf("Nao foi possivel carregar os perfis.\n");
                }
                break;
            case 3:
                printf("Nome do Perfil: ");
                scanf("%[^\n]", nameAux);
                int ver2 = removeProfile(profiles, nameAux);
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
                do {
                    printf("\n----- MENU PERFIS -----\n");
                    printf("1- Adicionar Serie\n");
                    printf("2- Carregar Series\n");
                    printf("3- Remover Serie\n"); // fazer função ainda;
                    printf("4- Imprimir Series\n");
                    printf("5- ?\n");
                    printf("0- Sair do Perfil\n");
                    scanf("%d", &op2);
                    getchar();
                    switch (op2) {
                        case 1:
                        case 2:
                            printf("Selecione um arquivo (s1.txt, sn.txt, ...): ");
                            scanf("%[^\n]", arquiveNameAux);
                            loadTVShows(profiles, arquiveNameAux); // fazer função para encontrar perfil;
                        case 3:
                        case 4:
                        case 5:
                        case 6:
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


    /*
    removeProfile(profiles, "Guilherme");
    printProfiles(profiles);
    removeProfile(profiles, "Cleisson");
    printProfiles(profiles);
    removeProfile(profiles, "Bolsonaro");
    printProfiles(profiles);
    */

    loadTVShows(profiles->start, "archives/s1.txt");
    printTVShows(profiles->start);

}