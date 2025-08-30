#ifndef PERFIS_H
#define PERFIS_H

#include "series.h"

typedef struct profile { // perfis;
    char name[20];
    int age;
} Profile;

typedef struct Prof_Node{ // descritor dos de séries;
    Profile info;
    TVS_Node *start; // acessa a lista de séries;
    TVS_Node *end;

    struct Prof_Node *next;
    struct Prof_Node *before;
    int quantTVShows;
} Prof_Node;

typedef struct { // nó descritor dos perfis;
    Prof_Node *start;
    Prof_Node *end;
    int quantProfiles;
    //int quantSeries; // calcular quantas séries diferentes tem?
} D_profiles;

void createList(D_profiles *li);
int addProfile(D_profiles *li, Profile p);
int addTVShow(Prof_Node *liP, TVShow s);

/* FUNÇÕES
 * criar listas;
 * adicionar perfil ao final da lista;
 * adicionar série ao final do perfil;
 * remover série do perfil;
 * remover perfil;
 * imprimir lista de perfis; // quantidade de perfis também;
 * imprimir séries do perfil;
 * imprimir tudo? pfv não;
 * liberar lista inteira;
 *
 * favoritar item;
 * procurar série em determinado perfil;
 * procurar perfil;
 * alterar informações do perfil;
*/

#endif //PERFIS_H
