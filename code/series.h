#ifndef SERIES_H
#define SERIES_H

//#include "perfis.h" // nao entendi muito bem porque esse include nao funciona
typedef struct Prof_Node Prof_Node;

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
    TVShow info; // struct com as informações
    struct TVS_Node *next; // ponteiro para o próximo nó
    struct TVS_Node *before; // ponteiro para o nó anterior
} TVS_Node;

int loadTVShows(Prof_Node *pn, const char *filename); // preenche a lista de séries a partir dos arquivos;
int addTVShow(Prof_Node *pn, TVShow tvs); // preenche um nó da lista de séries a partir dos dados que o usuario fornece;
void printTVShows(Prof_Node *pn, TVS_Node *item); // imprime lista de séries;
int removeTVShow(Prof_Node *pn, const char *name); // remove um nó da lista de séries (uma série, no caso);
TVS_Node* searchTVShow(Prof_Node *pn, const char *name); // procura uma série na lista e retorna o nó dessa série
void printFavorites(Prof_Node *pn); // imprime apenas os favoritos da lista
void freeShows(TVS_Node *l); // libera lista de séries

/* FUNÇÕES
 * adicionar série ao final do perfil; OK
 * remover série do perfil; OK
 * imprimir séries do perfil; OK
 * liberar lista inteira; OK
 *
 * favoritar item;
 * remover um favorito;
 * procurar série em determinado perfil; OK
 * imprimir favoritos; OK
*/

#endif //SERIES_H
