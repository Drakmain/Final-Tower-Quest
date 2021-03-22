#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "..\lib\game.h"

#include "..\lib\error.h"

int main(int argc, char** argv)
{
    
    printf("Test de l'objet game: \n");

    game_t* game = NULL;

    printf("Test d'existance sur un game_t inexistant\n");

    (game_exist(game) ? printf("-->KO\n") : printf("-->OK\n"));


    printf("Creation de l'objet game...\n\n");
    printf("/*--- Startup SDL -------*/\n");
    game = game_create();
        
    
    printf("Affichage des donnees de l'objet game: \n");

    printf("WINDOWHEIGHT: %i\n", *game->WINDOWHEIGHT);
    printf("WINDOWWIDTH: %i\n", *game->WINDOWWIDTH);

    switch (*game->etat_fullscreen)
    {
    case SDL_TRUE:
        printf("etat_fullscreen: Vrai (%i)\n", *game->etat_fullscreen);
        break;
    
    case SDL_FALSE:
        printf("etat_fullscreen: Faux (%i)\n", *game->etat_fullscreen);
        break;
    
    default:
        printf("etat_fullscreen: Erreur mauvais chiffre (%i)\n", *game->etat_fullscreen);
        break;
    }

    switch (*game->program_launch)
    {
    case SDL_TRUE:
        printf("program_launch: Vrai (%i)\n", *game->program_launch);
        break;
    
    case SDL_FALSE:
        printf("program_launch: Faux (%i)\n", *game->program_launch);
        break;
    
    default:
        printf("program_launch: Erreur mauvais chiffre (%i)\n", *game->program_launch);
        break;
    }
    

    printf("Destruction de l'objet game...\n\n");

    game->free(&game);

    return EXIT_SUCCESS;
}