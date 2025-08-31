#include <stdio.h>
#include <stdlib.h>
#include "perfis.h"
#include "series.h"

int main() {
    D_profiles *profiles = createList();
    load_profiles(profiles, "archives/profiles.txt");
    printProfiles(profiles);

    /*
    removeProfile(profiles, "Guilherme");
    printProfiles(profiles);
    removeProfile(profiles, "Cleisson");
    printProfiles(profiles);
    removeProfile(profiles, "Bolsonaro");
    printProfiles(profiles);
    */

    loadTVShows(profiles->start, "archives/s1.txt");
    printTVShows(profiles->start);

}