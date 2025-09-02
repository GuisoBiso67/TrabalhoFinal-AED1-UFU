#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
#include "perfis.h"
#include "series.h"

int addTVShow(Prof_Node *pn, TVShow tvs) {
    if (pn == NULL) return 0;
    TVS_Node *newNode = malloc(sizeof(TVS_Node));
    if (newNode == NULL) return 0; // erro de alocação

    newNode->info = tvs;
    if (pn->start == NULL && pn->end == NULL) { // primeira série da lista
        newNode->next = NULL;
        newNode->before = NULL;
        pn->start = newNode;
        pn->end = newNode;
        pn->quantTVShows++;
        return 1;
    }
    newNode->next = NULL;
    newNode->before = pn->end;
    pn->end->next = newNode;
    pn->end = newNode;
    pn->quantTVShows++;
    return 1;
}

int loadTVShows(Prof_Node *pn, const char *filename) {
    if (pn == NULL) return 0;

    char str1[11];
    strcpy(str1, "archives/"); // melhorar isso depois
    strcat(str1,filename);

    FILE* file = fopen(str1, "r");
    if (file == NULL) {
        //printf("Erro ao abrir o arquivo");
        return 0;
    }

    TVShow t;
    char linha[200];
    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = '\0';

        strcpy(t.name, strtok(linha, "|"));
        strcpy(t.broadcaster, strtok(NULL, "|"));
        strcpy(t.creator, strtok(NULL, "|"));
        strcpy(t.genre, strtok(NULL, "|"));
        t.seasons = strtol(strtok(NULL, "|"),NULL,10); // tentativa que ficava dando warning
        t.episodes = strtol(strtok(NULL, "|"),NULL,10);
        t.year = strtol(strtok(NULL, "|"),NULL,10);
        strcpy(t.ratingIMDB, strtok(NULL, "|"));
        t.personalRating = strtol(strtok(NULL, "|"),NULL,10);

        char *temp = strtok(NULL, ";");
        trim(temp);
        t.favorite = temp[0];
        //t.favorite = trim(strtok(NULL, ";"));
        //strcpy(t.favorite, strtok(NULL, ";"));

        trim(t.name);
        trim(t.broadcaster);
        trim(t.creator);
        trim(t.genre);
        trim(t.ratingIMDB);
        //trim(t.favorite);

        addTVShow(pn, t);
    }
    fclose(file);
    return 1;
}

void printTVShows(Prof_Node *pn) {
    if (pn == NULL) {
        printf("Lista vazia!");
        return;
    }
    if (pn->quantTVShows == 0) {
        printf("Nenhuma serie foi adicionada ainda.\n");
        return;
    }

    printf("Series de %s:\n",pn->info.name);
    TVS_Node *aux = pn->start;
    while (aux != NULL) {
        //if (aux->info.favorite == 'Y')
        if (aux->info.favorite == 'Y' || aux->info.favorite == 'y') {
            printf("\nS2 %s (%d)\n",aux->info.name,aux->info.year);
        }else {
            printf("\n%s (%d)\n",aux->info.name,aux->info.year);
        }
        printf("Emissora: %s | Criador(es): %s\n",aux->info.broadcaster,aux->info.creator);
        printf("No de Temporadas: %d | No de Episodios: %d\n",aux->info.seasons, aux->info.episodes);
        printf("Categoria: %s\n",aux->info.genre);
        printf("Nota IMDB: %s | Nota Pessoal: %d\n",aux->info.ratingIMDB, aux->info.personalRating);
        printf("------------------------------------\n\n");
        aux = aux->next;
    }
}

int removeTVShow(Prof_Node *pn, const char *name) {
    if (pn == NULL) return 0;

    TVS_Node *aux = pn->start;
    while (aux != NULL) {
        if (strcmp(aux->info.name, name) == 0) {
            break;
        }
    }
    if (aux == NULL) return -1; // serie nao esta no perfil;

    if (aux == pn->start) { // série é a primeira na lista
        pn->start = aux->next;
        pn->start->before = NULL;
        pn->quantTVShows--;
        free(aux);
        return 1;
    }
    if (aux == pn->end) { // série é a ultima na lista
        pn->end = aux->before;
        pn->end->next = NULL;
        pn->quantTVShows--;
        free(aux);
        return 1;
    }
    // série é esta no meio na lista
    aux->next->before = aux->before;
    aux->before->next = aux->next;
    pn->quantTVShows--;
    free(aux);
    return 1;
}


