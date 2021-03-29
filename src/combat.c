#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "..\lib\town.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\character.h"
#include "..\lib\menu_in_game.h"
#include "..\lib\enemie.h"


/*!
 *
 * \file combat.c
 * \brief A FINIR.
 * \author Enzo BRENNUS
 *
 */


/*!
 *
 * \fn combat(game_t * game, character_t * character, map_t * map)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * \param map A FINIR.
 *
 */

extern
void combat(game_t * game, character_t * character, map_t * map){

    srand(time(NULL));

    /*--- Initialization Variable ------------------------------------------------*/

    enemie_t * enemie_1 = NULL;
    enemie_t * enemie_2 = NULL;
    enemie_t * enemie_3 = NULL;
    enemie_t * enemie_4 = NULL;

    int nb_enemie;

    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    SDL_bool combat_bool = SDL_TRUE;
    
    SDL_Event event;

    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_character.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_character.x = (*game->WINDOWWIDTH) / 1.5;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2;

    SDL_Rect pos_Wind_enemie_1_1;
    pos_Wind_enemie_1_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_enemie_1_1.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_enemie_1_1.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_1_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2;

    SDL_Rect pos_Wind_enemie_2_1;
    pos_Wind_enemie_2_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_enemie_2_1.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_enemie_2_1.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_2_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 3;

    SDL_Rect pos_Wind_enemie_2_2;
    pos_Wind_enemie_2_2.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_enemie_2_2.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_enemie_2_2.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_2_2.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 1.5;

    SDL_Rect pos_Wind_enemie_4_1;
    pos_Wind_enemie_4_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_enemie_4_1.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_enemie_4_1.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_4_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2;

    SDL_Rect pos_Wind_enemie_4_4;
    pos_Wind_enemie_4_4.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_enemie_4_4.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_enemie_4_4.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_4_4.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2;

    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Initialization Enemeis ------------------------------------------------*/

    nb_enemie = rand() % 4 + 1;
    printf("nb_enemie : %i\n", nb_enemie);
    switch (nb_enemie)
    {
    case 1:
        enemie_1 = enemie_create(game->render, "src\\tileset\\Enemies\\Enemies.txt");
        break;

    case 2:
        enemie_1 = enemie_create(game->render, "src\\tileset\\Enemies\\Enemies.txt");
        enemie_2 = enemie_create(game->render, "src\\tileset\\Enemies\\Enemies.txt");
        break;

    case 3:
        enemie_1 = enemie_create(game->render, "src\\tileset\\Enemies\\Enemies.txt");
        enemie_2 = enemie_create(game->render, "src\\tileset\\Enemies\\Enemies.txt");
        enemie_3 = enemie_create(game->render, "src\\tileset\\Enemies\\Enemies.txt");
        break;

    case 4:
        enemie_1 = enemie_create(game->render, "src\\tileset\\Enemies\\Enemies.txt");
        enemie_2 = enemie_create(game->render, "src\\tileset\\Enemies\\Enemies.txt");
        enemie_3 = enemie_create(game->render, "src\\tileset\\Enemies\\Enemies.txt");
        enemie_4 = enemie_create(game->render, "src\\tileset\\Enemies\\Enemies.txt");
        break;
    }

    /*--- End Initialization enemeis --------------------------------------------*/


    SDL_RenderClear(game->render);

    //SDL_RenderCopy(game->render, map->texture, &map->tile_set, &pos_Wind_town);
    switch (nb_enemie)
    {
    case 1:
        SDL_RenderCopy(game->render, enemie_1->texture, NULL, &pos_Wind_enemie_1_1);
        break;

    case 2:
        SDL_RenderCopy(game->render, enemie_1->texture, NULL, &pos_Wind_enemie_2_1);
        SDL_RenderCopy(game->render, enemie_2->texture, NULL, &pos_Wind_enemie_2_2);
        break;

    case 3:
        //SDL_RenderCopy(game->render, enemie_1->texture, NULL, &pos_Wind_enemie_3_1);
        SDL_RenderCopy(game->render, enemie_2->texture, NULL, &pos_Wind_enemie_1_1);
        //SDL_RenderCopy(game->render, enemie_3->texture, NULL, &pos_Wind_enemie_3_3);
        break;

    case 4:
        SDL_RenderCopy(game->render, enemie_1->texture, NULL, &pos_Wind_enemie_4_1);
        SDL_RenderCopy(game->render, enemie_2->texture, NULL, &pos_Wind_enemie_2_1);
        SDL_RenderCopy(game->render, enemie_3->texture, NULL, &pos_Wind_enemie_2_2);
        SDL_RenderCopy(game->render, enemie_4->texture, NULL, &pos_Wind_enemie_4_4);
        break;
    }
    
    SDL_RenderCopy(game->render, character->texture, &character->West_Walk.rect, &pos_Wind_character);
    
    SDL_RenderPresent(game->render);
    

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && combat_bool)
    {

        while (SDL_PollEvent(&event))
        {

            if (event.type == SDL_QUIT)
            {
                (*game->program_launch) = SDL_FALSE;
            }

            if (!keyState[SDL_SCANCODE_ESCAPE])
            {
                combat_bool = SDL_FALSE;
            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/
    
    if (enemie_exist(enemie_1) == SDL_TRUE)
    {
        printf("free 1\n");
        enemie_1->free(&enemie_1);
    }
    if (enemie_exist(enemie_2) == SDL_TRUE)
    {
        printf("free 2\n");
        enemie_2->free(&enemie_2);
    }
    if (enemie_exist(enemie_3) == SDL_TRUE)
    {
        printf("free 3\n");
        enemie_3->free(&enemie_3);
    }
    if (enemie_exist(enemie_4) == SDL_TRUE)
    {
        printf("free 4\n");
        enemie_4->free(&enemie_4);
    }    

    /*--- End Free Memory --------------------------------------------------------*/

}