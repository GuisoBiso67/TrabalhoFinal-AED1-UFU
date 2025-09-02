#ifndef PERFIS_H
#define PERFIS_H

#include "series.h"

typedef struct profile { // perfis;
    char name[20];
    char age[3];
} Profile;

typedef struct Prof_Node{ // descritor dos de séries;
    Profile info;
    TVS_Node *start; // acessa a lista de séries;
    TVS_Node *end;

    Prof_Node *next;
    Prof_Node *before;
    int quantTVShows;
} Prof_Node;

typedef struct { // nó descritor dos perfis;
    Prof_Node *start;
    Prof_Node *end;
    int quantProfiles;
    //int quantSeries; // calcular quantas séries diferentes tem?
} D_profiles;

D_profiles* createList();
int addProfile(D_profiles *li, Profile p);
int load_profiles(D_profiles *li, const char *filename);
//int addTVShow(Prof_Node *liP, TVShow s);
void printProfiles(D_profiles *li);
int removeProfile(D_profiles *li, const char *name);
Prof_Node* searchProfile(D_profiles *li, const char *name);


void trim(char *str);

/* FUNÇÕES
 * criar listas; OK
 * adicionar perfil ao final da lista; OK
 * remover perfil; OK
 * imprimir lista de perfis; // quantidade de perfis também; OK
 * liberar lista inteira;
 *
 * procurar série em determinado perfil OK;
 * procurar perfil;
 * alterar informações do perfil;
*/

#endif //PERFIS_H
