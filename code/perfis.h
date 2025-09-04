#ifndef PERFIS_H
#define PERFIS_H

#include "series.h"

typedef struct profile { // struct com os dados do perfil;
    char name[20];
    char age[3];
} Profile;

typedef struct Prof_Node{ // descritor dos de séries e nó dos perfis;
    Profile info;
    TVS_Node *start; // acessa o primeiro nó da lista de séries;
    TVS_Node *end; // acessa o último nó da lista de séries;
    int quantTVShows; // quantidade de séries no perfil do usuário;

    Prof_Node *next; // ponteiro para o próximo nó;
    Prof_Node *before; // ponteiro para o nó anterior;
} Prof_Node;

typedef struct { // nó descritor dos perfis;
    Prof_Node *start; // acessa o primeiro nó da lista de perfis;
    Prof_Node *end; // acessa o último nó da lista de perfis;
    int quantProfiles; // quantidade de perfis
} D_profiles;

D_profiles* createList(); // cria nó descritor e o retorna;
int addProfile(D_profiles *li, Profile p); // adiciona perfil a partir de dados que o usuario fornece;
int load_profiles(D_profiles *li, const char *filename); // carrega perfis de um arquivo;
void printProfiles(D_profiles *li, Prof_Node *p); // imprime lista de perfis;
int removeProfile(D_profiles *li, const char *name); // remove um perfil da lista;
Prof_Node* searchProfile(D_profiles *li, const char *name); // procura um perfil e retorna seu nó;
void freeProfiles(Prof_Node* pn); // libera lista de perfis;
void freeList(D_profiles* dp); // libera todas as listas (perfis + series);
int changeInfo(Prof_Node *pn, Profile p); // altera informações de um perfil
void printMainMenu(); // função que imprime menu principal;
void printMenuProfiles(const char *name); // função que imprime menu dentro do perfil;

void trim(char *str);

/* FUNÇÕES
 * criar listas; OK
 * adicionar perfil ao final da lista; OK
 * remover perfil; OK
 * imprimir lista de perfis; // quantidade de perfis também; OK
 * liberar lista inteira; OK
 *
 * procurar série em determinado perfil OK;
 * procurar perfil; OK
 * alterar informações do perfil; OK
*/

#endif //PERFIS_H
