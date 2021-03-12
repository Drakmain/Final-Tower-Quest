#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "error.h"

int main(int argc, char** argv)
{
    
    printf("Test de l'objet map: \n");

    map_t* map = NULL;

    printf("Test d'existance sur un map_t inexistant\n");

    (map_exist(map) ? printf("-->KO\n") : printf("-->OK\n"));


    printf("Creation de l'objet map...\n");

    map = map_create(NULL, "src\\tileset\\FF6_World_of_Balance_Maps-Narshe_(Exterior).bmp", "src\\tileset\\FF6_World_of_Balance_Maps-Narshe_(Exterior).txt");


    printf("Affichage des donnees de l'objet map: \n");

    printf("%n, %n, %n, %n;\n", &map->tile_set.x, &map->tile_set.y, &map->tile_set.w, &map->tile_set.h);


    printf("Destruction de l'objet map...");

    map->free(&map);

    return EXIT_SUCCESS;
}