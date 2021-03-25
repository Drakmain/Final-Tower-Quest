#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "..\lib\map.h"

#include "..\lib\game.h"
#include "..\lib\error.h"

int main(int argc, char** argv)
{

    game_t * game = NULL;
    printf("/*--- Startup SDL -------*/\n");
    game = game_create();
    if (game == NULL)
    {
        exit_with_error("Cannot create a game_t object > test_map.c Line 15");
    }

    
    printf("Test de l'objet map: \n");

    map_t* map = NULL;

    printf("Test d'existance sur un map_t inexistant\n");

    (map_exist(map) ? printf("-->KO\n") : printf("-->OK\n"));


    printf("Creation de l'objet map...\n");

    map = map_create(game->render, "src\\tileset\\Maps\\town.bmp", "src\\tileset\\Maps\\town.txt");


    printf("Affichage des donnees de l'objet map: \n");

    printf("%n, %n, %n, %n;\n", &map->tile_set.x, &map->tile_set.y, &map->tile_set.w, &map->tile_set.h);


    printf("Destruction de l'objet map...\n\n");

    map->free(&map);


    game->free(&game);

    return EXIT_SUCCESS;
}