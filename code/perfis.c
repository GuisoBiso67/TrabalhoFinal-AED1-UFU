#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "perfis.h"
#include "series.h"

D_profiles* createList() {
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

    Profile p;
    char linha[200];
    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = '\0';

        strcpy(p.name, strtok(linha, "|"));
        //p.age = atoi(strtok(NULL, ";")); // tentativa que ficava dando warning
        strcpy(p.age, strtok(NULL, ";"));
        trim(p.name);
        trim(p.age);
        addProfile(li, p);
    }
    fclose(file);
    return 1;
}

void printProfiles(D_profiles *li) {
    if (li == NULL) {
        printf("Lista Vazia!\n");
        return;
    }
    printf("\n----- PERFIS ------\n\n");
    Prof_Node *aux = li->start;
    while (aux != NULL) {
        printf("%s | Idade: %s | Series Assistidas: %d\n", aux->info.name, aux->info.age, aux->quantTVShows);
        aux = aux->next;
    }
    printf("\n>> Perfis Cadastrados: %d\n", li->quantProfiles);
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

