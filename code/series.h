#ifndef SERIES_H
#define SERIES_H

//#include "perfis.h" // nao entendi muito bem porque esse include nao funciona
typedef struct Prof_Node Prof_Node;

// adicionar mais alguma informação???
typedef struct tvShow { // nó das séries
    char name[50]; // nome;
    char broadcaster[20]; // emissora/streaming;
    char creator[50]; // criador;
    char genre[30]; // gênero da série
    int seasons; // nº de temporadas;
    int episodes; // nº de episódios;
    int year; // ano que começou;
    char ratingIMDB[5]; // nota média no imdb;
    int personalRating; // nota pessoal de 1-10;
    char favorite; // Y or N; y = S2 coração ao lado do nome e N = nada;
} TVShow;

typedef struct TVS_Node{
    TVShow info;
    struct TVS_Node *next;
    struct TVS_Node *before;
} TVS_Node;

int loadTVShows(Prof_Node *pn, const char *filename);
int addTVShow(Prof_Node *pn, TVShow tvs);
void printTVShows(Prof_Node *pn, TVS_Node *item);
int removeTVShow(Prof_Node *pn, const char *name);
TVS_Node* searchTVShow(Prof_Node *pn, const char *name);
void printFavorites(Prof_Node *pn);

/* FUNÇÕES
 * adicionar série ao final do perfil; OK
 * remover série do perfil; OK
 * imprimir séries do perfil; OK
 * liberar lista inteira;
 *
 * favoritar item;
 * remover um favorito;
 * procurar série em determinado perfil; OK
 * imprimir favoritos; OK
*/

#endif //SERIES_H
