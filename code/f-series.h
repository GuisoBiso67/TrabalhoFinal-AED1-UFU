#ifndef F_SERIES_H
#define F_SERIES_H

// adicionar mais alguma informação???
typedef struct tvShow { // nó das séries
    char name[40]; // nome;
    char broadcaster[20]; // emissora/streaming;
    char creator[50]; // criador;
    char genre[20]; // gênero da série
    int seasons; // nº de temporadas;
    int episodes; // nº de episódios;
    int yearB, yearF; // ano que começou e ano que terminou;
    int runtime; // tempo médio dos episódios;
    float ratingIMDB; // nota média no imdb;
    char favorite; // yes / no

    struct tvShow *next;
    struct tvShow *before;
} TVShow;

typedef struct profile { // nó dos perfis, que será o descritor dos de séries;
    char name[20];
    int age;

    struct tvShow *s_list; // acessa a lista de séries;

    struct profile *next;
    struct profile *before;
} Profile;

typedef struct { // nó descritor dos perfis;
    Profile *start;
    Profile *end;
    int quantProfiles;
    int quantSeries; // calcular quantas séries diferentes tem?
} D_profiles;

/* FUNÇÕES
 * criar lista;
 * adicionar perfil ao final da lista;
 * adicionar série ao final do perfil;
 * remover série do perfil;
 * remover perfil;
 * favoritar item;
 * procurar série em determinado perfil;
 * procurar perfil;
 * alterar informações do perfil;
 * liberar lista inteira;
*/

#endif //F_SERIES_H
