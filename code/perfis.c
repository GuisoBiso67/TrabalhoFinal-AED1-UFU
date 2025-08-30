#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perfis.h"
#include "series.h"

/*
void createList(D_profiles *li) {
    li->start = NULL;
    li->end = NULL;
    li->quantProfiles = 0;
}

int addProfile(D_profiles *li, Profile p){
    if (li == NULL) return 0;
    Prof_Node *newProfile = malloc(sizeof(Prof_Node));
    if (newProfile == NULL) return 0; // erro de alocação;

    newProfile->info = p;
    if (li->quantProfiles == 0) { // adicionar primeiro perfil
        li->start = newProfile;
        li->end = newProfile;
        li->quantProfiles++;
        return 1;
    }
    li->end = newProfile;
    li->quantProfiles++;
    return 1;
}
*/
