#include <stdio.h>
#include <stdlib.h>
#include "perfis.h"
#include "series.h"

int main() {
    D_profiles *profiles = createList();
    load_profiles(profiles, "profiles.txt");
    printProfiles(profiles);
}