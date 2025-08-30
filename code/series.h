#ifndef SERIES_H
#define SERIES_H

// adicionar mais alguma informação???
typedef struct tvShow { // nó das séries
    char name[40]; // nome;
    char broadcaster[20]; // emissora/streaming;
    char creator[50]; // criador;
    char genre[20]; // gênero da série
    int seasons; // nº de temporadas;
    int episodes; // nº de episódios;
    int year; // ano que começou;
    float ratingIMDB; // nota média no imdb;
    int personalRating; // nota pessoal de 1-10;
    char favorite; // YES or NO;
} TVShow;

typedef struct TVS_Node{
    TVShow info;
    struct TVS_Node *next;
    struct TVS_Node *before;
} TVS_Node;

#endif //SERIES_H
