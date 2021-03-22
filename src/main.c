#include <stdio.h>
#include <stdlib.h>

#include "..\lib\commun.h"

#include "..\lib\town.h"
#include "..\lib\tower.h"
#include "..\lib\character.h"
#include "..\lib\menu_accueil.h"
#include "..\lib\game.h"


/*!
 *
 * \file main.c
 * \brief Ficher principale du jeu.
 * \author Enzo BRENNUS
 * \date 16/03/21
 *
 */


/*!
 *
 * \fn int main(int argc, char ** argv)
 * \brief Fonction principale du jeu.
 *
 * \param argc est le nombre de parametres.
 * \param argv est un tableau contenant les parametres.
 *
 * \retval int Un entier.
 *
 */

int main(int argc, char ** argv)
{

    /*--- Print SDL & TTF Version ------------------------------------------------*/

    printf("/*--- Startup SDL -------*/\n");

    SDL_version SDL;
    SDL_VERSION(&SDL);

    SDL_version SDL_TTF;
    SDL_TTF_VERSION(&SDL_TTF);

    printf("SDL Version: %d.%d.%d\n", SDL.major, SDL.minor, SDL.patch);

    printf("SDL TTF Version: %d.%d.%d\n", SDL_TTF.major, SDL_TTF.minor, SDL_TTF.patch);

    /*--- End Print SDL & TTF Version --------------------------------------------*/


    /*--- Initialization game ------------------------------------------------*/

    game_t* game = NULL;
    game = game_create();
    if (game == NULL)
    {
        exit_with_error("Cannot create a game_t object > main.c Line 64");
    }

    /*--- End Initialization game --------------------------------------------*/


    /*--- Initialization Variable ------------------------------------------------*/

    character_t * character_save = NULL;

    char actual_save[20] = "\0";


    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch)
    {

        menu_accueil(game, actual_save);

        if (strcmp(actual_save, "\0"))
        {
            character_save = character_create(game->render, actual_save);
            town(game, character_save);
            //tower(game, actual_save);
        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free game --------------------------------------------------------------*/

    game->free(&game);
    printf("game_t * game: freed\n\n");

    /*--- End Free game ----------------------------------------------------------*/


    SDL_Quit();

    printf("Program exited with succes");
    return EXIT_SUCCESS;
}
