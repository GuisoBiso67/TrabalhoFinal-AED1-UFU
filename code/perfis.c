#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "perfis.h"
#include "series.h"

D_profiles* createList() {
    // aloca memória e inicializa ponteiros e variáveis
    D_profiles *li = malloc(sizeof(D_profiles));
    li->start = NULL;
    li->end = NULL;
    li->quantProfiles = 0;
    return li;
}

int addProfile(D_profiles *li, Profile p){
    if (li == NULL) return 0;
    Prof_Node *newProfile = malloc(sizeof(Prof_Node));
    if (newProfile == NULL) return 0; // erro de alocação;

    newProfile->info = p;
    newProfile->start = NULL; // null para lista de séries (que não foi criada ainda)
    newProfile->end = NULL; // null para lista de séries (que não foi criada ainda)
    newProfile->quantTVShows = 0;
    if (li->quantProfiles == 0) { // adicionar primeiro perfil
        newProfile->next = NULL;
        newProfile->before = NULL;

        li->start = newProfile;
        li->end = newProfile;
        li->quantProfiles++;
        return 1;
    }
    // adiciona um novo perfil sempre ao final da lista;
    newProfile->before = li->end; // before do novo nó é o fim
    newProfile->next = NULL; // next do novo nó é nul
    li->end->next = newProfile; // next do fim é o novo nó
    li->end = newProfile; // novo fim é o novo nó
    li->quantProfiles++; // incrementa quantidade de perfis
    return 1;
}

int load_profiles(D_profiles *li, const char *filename) {
    if (li == NULL) return 0;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo");
        return 0;
    }

    // Lá no loadTVShows eu preciso concatenar "archives/", mas aqui não, já que eu tenho apenas uma lista de perfis;
    // Aí eu chamo direto já com "arquives/profiles.txt" na main

    Profile p;
    char linha[200];
    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = '\0';

        // cada linha do arquivo é assim: "NOME | IDADE;" Ex: Guilherme | 19;

        strcpy(p.name, strtok(linha, "|")); // separa o nome
        strcpy(p.age, strtok(NULL, ";")); // separa idade
        trim(p.name); // retira espaços
        trim(p.age);
        addProfile(li, p);
    }
    fclose(file);
    return 1;
}

void printProfiles(D_profiles *li, Prof_Node *item) {
    if (li == NULL) {
        printf("Lista Vazia!\n");
        return;
    }
    Prof_Node *aux = (item != NULL) ? item : li->start; // se item não for NULL, ele imprime apenas 1 perfil específico
    if (item == NULL) printf("\n----- PERFIS ------\n\n");
    while (aux != NULL) {
        printf("%s | Idade: %s | Series Assistidas: %d\n", aux->info.name, aux->info.age, aux->quantTVShows);
        if (item != NULL) break;
        aux = aux->next;
    }
    if (item == NULL) printf("\n>> Perfis Cadastrados: %d\n", li->quantProfiles); // imprime quantidade de perfis apenas se item for NULL (nao imprimir apenas 1 perfil);
    printf("\n-----------------------\n");
}

int removeProfile(D_profiles *li, const char *name) {
    if (li == NULL) return 0;
    Prof_Node *aux = li->start;
    while (aux != NULL) {
        if (strcmp(aux->info.name, name) == 0) {
            break;
        }
        aux = aux->next;
    }
    if (aux == NULL) return -1; // perfil não existe;
    if (aux == li->start) { // perfil a ser removido é o primeiro
        li->start = aux->next;
        li->start->before = NULL;
        li->quantProfiles--;
        free(aux);
        return 1;
    }
    if (aux == li->end) { // perfil a ser removido é o último
        li->end = aux->before;
        li->end->next = NULL;
        li->quantProfiles--;
        free(aux);
        return 1;
    }
    // perfil a ser removido é algum do meio
    aux->next->before = aux->before;
    aux->before->next = aux->next;
    li->quantProfiles--;
    free(aux);
    return 1;
}

Prof_Node* searchProfile(D_profiles *li, const char *name) {
    if (li == NULL) return NULL;
    Prof_Node *aux = li->start;
    while (aux != NULL) {
        if (strcmp(aux->info.name, name) == 0) {
            break; // se achar perfil ele para
        }
        aux = aux->next;
    }
    if (aux == NULL) return NULL; // não achou perfil retorna um nó nulo;
    return aux; // se achou ele retorna o nó do perfil;
}

void freeProfiles(Prof_Node* pn) { // libera lista de perfis
    if (pn != NULL) {
        Prof_Node *aux;
        while (pn != NULL) {
            aux = pn;
            pn = pn->next;
            freeShows(aux->start); // libera a lista de séries do perfil;
            free(aux); // libera perfil
        }
        //free(pn);
    }
}

int changeInfo(Prof_Node *pn, Profile p) { // altera informações de um perfil já cadastrado;
    if (pn == NULL) return 0;
    strcpy(pn->info.name, p.name);
    strcpy(pn->info.age, p.age);
    return 1;
}

void freeList(D_profiles* dp) { // libera todas as listas (usa quando finaliza o programa);
    if (dp != NULL) {
        freeProfiles(dp->start);
    }
    free(dp);
}

void printMainMenu() { // opções explicadas na main
    printf("\n----- MENU PERFIS -----\n");
    printf("1- Adicionar Perfil\n");
    printf("2- Carregar Perfis\n");
    printf("3- Remover Perfil\n");
    printf("4- Abrir Perfil\n");
    printf("5- Imprimir Perfis\n");
    printf("6- Procurar Perfil\n");
    printf("7- Alterar Perfil\n");
    printf("0- Sair\n");
}

void printMenuProfiles(const char *name) { // opções explicadas na main
    printf("\n----- Perfil de %s -----\n", name);
    printf("1- Adicionar Serie\n");
    printf("2- Carregar Series\n");
    printf("3- Remover Serie\n");
    printf("4- Imprimir Lista de Series\n");
    printf("5- Imprimir Favoritos\n");
    printf("6- Procurar Serie\n");
    printf("7- Adicionar Favorito\n");
    printf("8- Remover Favorito\n");
    printf("0- Sair do Perfil\n");
}

// FUNÇÃO QUE NAO TEM QUE MEXER
void trim(char *str) {
    char *start, *end;
    // Encontrar o primeiro caractere que não é espaço em branco
    start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    // Se a string estiver vazia, retorna
    if (*start == 0) {
        *str = '\0';
        return;
    }
    // Encontrar o último caractere que não é espaço
    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    // Adiciona o caractere nulo após o último caractere que não é espaço
    *(end + 1) = '\0';
    // Mover a string para o início da posição de memória original
    if (start != str) {
        memmove(str, start, end - start + 2);
    }
}

