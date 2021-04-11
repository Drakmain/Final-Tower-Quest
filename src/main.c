#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\commun.h"

#include "..\lib\game.h"
#include "..\lib\character.h"
#include "..\lib\menu_accueil.h"
#include "..\lib\town.h"
#include "..\lib\tower.h"
#include "..\lib\floor_1.h"
//#include "..\lib\floor_2.h"
//#include "..\lib\floor_3.h"
//#include "..\lib\floor_4.h"
//#include "..\lib\floor_5.h"

/*!
 *
 * \file main.c
 * \brief Ficher principale du jeu.
 * \author Enzo BRENNUS
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

int main(int argc, char **argv)
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

    /*--- Creation of options.txt ------------------------------------------------*/

    FILE *file;

    if ((file = fopen("options.txt", "r")))
    {
        fclose(file);
    }
    else
    {
        file = fopen("options.txt", "a");
        fprintf(file, "WindowResolution: 0 ;\nFullscreen: 0 ;");
        fclose(file);
    }

    /*----------------------------------------------------------------------------*/

    /*--- Initialization game ----------------------------------------------------*/

    game_t *game = NULL;
    game = game_create();
    if (game == NULL)
    {
        exit_with_error("Cannot create a game_t object > main.c Line 58");
    }

    /*--- End Initialization game ------------------------------------------------*/

    /*--- Initialization Variable ------------------------------------------------*/

    character_t *character_save = NULL;

    char actual_save[20] = "\0";

    /*--- End Initialization Variable --------------------------------------------*/

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch)
    {

        menu_accueil(game, actual_save);

        character_save = character_create(game->render, actual_save);

        if (!strcmp(character_save->position, "Village"))
            town(game, character_save);
        if (!strcmp(character_save->position, "Tour"))
            tower(game, character_save);
        if (!strcmp(character_save->position, "Etage_1"))
            floor_1(game, character_save);
        /*if(!strcmp(character_save->position,"Etage_2"))
            floor_2(game, character_save);
        if(!strcmp(character_save->position,"Etage_3"))
            floor_3(game, character_save);
        if(!strcmp(character_save->position,"Etage_4"))
            floor_4(game, character_save);
        if(!strcmp(character_save->position,"Etage_5"))
            floor_5(game, character_save);*/
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free game --------------------------------------------------------------*/

    game->free(&game);
    if (game_exist(game) == SDL_FALSE)
    {
        printf("game_t * game: freed\n\n");
    }
    else
    {
        exit_with_error("Error while freeing the object character_t * character_save > main.c Line 99");
    }

    if (character_exist(character_save) == SDL_TRUE)
    {
        character_save->free(&character_save);
        if (character_exist(character_save) == SDL_FALSE)
        {
            printf("character_t * character_save: freed\n\n");
        }
        else
        {
            exit_with_error("Error while freeing the object character_t * character_save > main.c Line 100");
        }
    }

    /*--- End Free game ----------------------------------------------------------*/

    SDL_Quit();

    printf("Program exited with succes");
    return EXIT_SUCCESS;
}
