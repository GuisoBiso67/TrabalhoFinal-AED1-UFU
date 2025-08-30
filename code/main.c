#include <stdio.h>
#include <stdlib.h>
#include "perfis.h"
#include "series.h"

int main() {
    D_profiles *profiles = malloc(sizeof(D_profiles));
    //profiles = malloc(sizeof(D_profiles));
    createList(profiles);
}