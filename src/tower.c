#include <stdio.h>
#include <stdlib.h>

#include "..\lib\tower.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\character.h"

/*!
 *
 * \file tower.c
 * \brief Gestion de la map tower.
 * \author Enzo BRENNUS
 * \date 18/02/21
 *
 */


/*!
 *
 * \fn tower(game_t * game, character_t * character)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * 
 */

extern
void tower(game_t * game, character_t * character){

    /*--- Initialization Variable ------------------------------------------------*/

    map_t* tower = NULL;
    tower = map_create(game->render, "src\\tileset\\Maps\\tower.bmp", "src\\tileset\\Maps\\tower.txt");
    if (tower == NULL)
    {
        exit_with_error("Cannot create a map_t object > tower.c Line 36");
    }

    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    SDL_bool tower_bool = SDL_TRUE;

    SDL_Event event;

    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_character.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 2;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2;

    SDL_Rect pos_Wind_tower;
    pos_Wind_tower.x = tower->tile_set.x;
    pos_Wind_tower.y = tower->tile_set.y;
    pos_Wind_tower.h = tower->tile_set.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_tower.w = tower->tile_set.w * (*game->WINDOWWIDTH) * 7.5 / 2560;

    int East_Walk = 0;
    int West_Walk = 0;
    int South_Walk = 0;
    int North_Walk = 0;

    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && tower_bool)
    {

        while (SDL_PollEvent(&event))
        {

            while (*game->program_launch == SDL_TRUE || (event.type == SDL_KEYDOWN && (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_UP])))
            {
                SDL_PollEvent(&event);


                if (event.type == SDL_QUIT || keyState[SDL_SCANCODE_ESCAPE])
                {
                    *game->program_launch = SDL_FALSE;
                }

                while (keyState[SDL_SCANCODE_RIGHT])
                {
                    East_Walk = 1;

                    for (int i = 0; i < 3; i++)
                    {

                        frame_start =  SDL_GetTicks();

                        pos_Wind_tower.x -= 25;

                        tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);

                        character->update(character, game->render, character->East_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > tower.c Line 102");
                        }

                    }

                    SDL_PollEvent(&event);

                }
                if (East_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);
                    character->update(character, game->render, character->East_Walk, pos_Wind_character);
                    render_frame(game->render);
                    East_Walk = 0;
                }




                while (keyState[SDL_SCANCODE_LEFT])
                {

                    for (int i = 0; i < 3; i++)
                    {
                        West_Walk = 1;
                        frame_start =  SDL_GetTicks();

                        pos_Wind_tower.x += 25;

                        tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);

                        character->update(character, game->render, character->West_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > tower.c Line 131");
                        }

                    }

                    SDL_PollEvent(&event);

                }

                if (West_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);
                    character->update(character, game->render, character->West_Walk, pos_Wind_character);
                    render_frame(game->render);
                    West_Walk = 0;
                }


                while (keyState[SDL_SCANCODE_UP])
                {

                    for (int i = 0; i < 3; i++)
                    {
                        South_Walk = 1;
                        frame_start =  SDL_GetTicks();

                        pos_Wind_tower.y += 25;

                        tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);

                        character->update(character, game->render, character->South_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering, tower.c Line 160");
                        }

                    }

                    SDL_PollEvent(&event);

                }

                if (South_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);
                    character->update(character, game->render, character->South_Walk, pos_Wind_character);
                    render_frame(game->render);
                    South_Walk = 0;
                }


                while (keyState[SDL_SCANCODE_DOWN])
                {

                    for (int i = 0; i < 3; i++)
                    {
                        North_Walk = 1;
                        frame_start =  SDL_GetTicks();

                        pos_Wind_tower.y -= 25;

                        tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);

                        character->update(character, game->render, character->North_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > tower.c Line 189");
                        }

                    }

                    SDL_PollEvent(&event);
                }

                if (North_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);
                    character->update(character, game->render, character->North_Walk, pos_Wind_character);
                    render_frame(game->render);
                    North_Walk = 0;
                }

            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    tower->free(&tower);
    character->free(&character);

    /*--- End Free Memory --------------------------------------------------------*/

}