#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
#include "perfis.h"
#include "series.h"

// a lógica é a mesma do addProfile;
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
    // adiciona sempre ao final da lista;
    newNode->next = NULL;
    newNode->before = pn->end;
    pn->end->next = newNode;
    pn->end = newNode;
    pn->quantTVShows++;
    return 1;
}

int loadTVShows(Prof_Node *pn, const char *filename) { // carrega a lista de séries a partir de um arquivo;
    if (pn == NULL) return 0;

    char str1[11];
    strcpy(str1, "archives/"); // melhorar isso depois
    strcat(str1,filename); // tem que concatenar isso porque os arquivos com as listas de séries ficam numa outra pasta;

    FILE* file = fopen(str1, "r");
    if (file == NULL) {
        //printf("Erro ao abrir o arquivo"); // essa mensagem já é impressa na main;
        return 0;
    }

    TVShow t;
    char linha[200];
    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = '\0';

        // mesma logica do loadProfiles
        strcpy(t.name, strtok(linha, "|"));
        strcpy(t.broadcaster, strtok(NULL, "|"));
        strcpy(t.creator, strtok(NULL, "|"));
        strcpy(t.genre, strtok(NULL, "|"));
        t.seasons = strtol(strtok(NULL, "|"),NULL,10);
        t.episodes = strtol(strtok(NULL, "|"),NULL,10);
        t.year = strtol(strtok(NULL, "|"),NULL,10);
        strcpy(t.ratingIMDB, strtok(NULL, "|"));
        t.personalRating = strtol(strtok(NULL, "|"),NULL,10);

        char *temp = strtok(NULL, ";");
        trim(temp);
        t.favorite = temp[0]; // pega apenas o primeiro caractere

        trim(t.name);
        trim(t.broadcaster);
        trim(t.creator);
        trim(t.genre);
        trim(t.ratingIMDB);

        addTVShow(pn, t);
    }
    fclose(file);
    return 1;
}

void printTVShows(Prof_Node *pn, TVS_Node *item) {
    if (pn == NULL) {
        printf("Lista vazia!");
        return;
    }
    if (pn->quantTVShows == 0) {
        printf("Nenhuma serie foi adicionada ainda.\n");
        return;
    }

    TVS_Node *aux = (item != NULL) ? item : pn->start; // se é true, imprime só um item (para a função search), se não, imprime lista completa
    if (item == NULL) { // imprime titulo só se for lista completa;
        printf("\nSeries de %s:\n",pn->info.name);
    }
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
        printf("------------------------------------\n");
        if (item != NULL) break;  // só um item
        aux = aux->next;
    }
    if (item == NULL) printf("\nSeries Assistidas: %d\n", pn->quantTVShows);
}

void printFavorites(Prof_Node *pn) { // imprime apenas séries favoritas;
    if (pn == NULL) return;
    int cont = 0;
    TVS_Node *aux = pn->start;
    printf("--- Series Favoritas de %s---\n",pn->info.name);
    while (aux != NULL) {
        if (aux->info.favorite == 'Y' || aux->info.favorite == 'y') {
            printTVShows(pn, aux);
            cont++;
        }
        aux = aux->next;
    }
    printf("\nSeries Favoritas: %d\n",cont);
}

int removeTVShow(Prof_Node *pn, const char *name) { // remove uma série (mesma logica do remove perfil);
    if (pn == NULL) return 0;

    TVS_Node *aux = pn->start;
    while (aux != NULL) {
        if (strcmp(aux->info.name, name) == 0) {
            break;
        }
        aux = aux->next;
    }
    if (aux == NULL) return -1; // serie nao esta no perfil;

    if (aux == pn->start) { // série é a primeira na lista
        pn->start = aux->next;
        pn->start->before = NULL;
        pn->quantTVShows--;
        free(aux);
        return 1;
    }
    if (aux == pn->end) { // série é a última na lista
        pn->end = aux->before;
        pn->end->next = NULL;
        pn->quantTVShows--;
        free(aux);
        return 1;
    }
    // série está no meio na lista
    aux->next->before = aux->before;
    aux->before->next = aux->next;
    pn->quantTVShows--;
    free(aux);
    return 1;
}

TVS_Node* searchTVShow(Prof_Node *pn, const char *name) { // procura uma série especifica e retorna o nó;
    if (pn == NULL) return NULL;
    TVS_Node *aux = pn->start;
    while (aux != NULL) {
        if (strcmp(aux->info.name, name) == 0) {
            break;
        }
        aux = aux->next;
    }
    if (aux == NULL) return NULL;
    return aux; // retorna o nó
}

int unfavoriteTVShow(Prof_Node *pn, const char *name) {
    if (pn == NULL) return 0;

    TVS_Node *aux = pn->start;
    while (aux != NULL) {
        if (strcmp(aux->info.name, name) == 0) {
            if (aux->info.favorite == 'Y' || aux->info.favorite == 'y') {
                aux->info.favorite = 'N'; // remove o status de favorito
                return 1;
            }
            else {
                return -1; // já não era favorito;
            }
        }
        aux = aux->next;
    }
    return 0; // não encontrada;
}

int favoriteTVShow(Prof_Node *pn, const char *name) {
    if (pn == NULL) return 0;

    TVS_Node *aux = pn->start;
    while (aux != NULL) {
        if (strcmp(aux->info.name, name) == 0) {
            if (aux->info.favorite == 'N' || aux->info.favorite == 'n') {
                aux->info.favorite = 'Y'; // remove o status de favorito
                return 1;
            }
            else {
                return -1; // ja era favorito;
            }
        }
        aux = aux->next;
    }
    return 0; // não encontrada;
}

void freeShows(TVS_Node *l) { // libera lista de séries
    if (l != NULL) {
        TVS_Node *aux;
        while (l != NULL) {
            aux = l;
            l = l->next;
            free(aux);
        }
    }
}


