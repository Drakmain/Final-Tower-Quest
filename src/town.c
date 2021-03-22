#include <stdio.h>
#include <stdlib.h>

#include "..\lib\town.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\character.h"
#include "..\lib\menu_in_game.h"
/*!
 *
 * \file town.c
 * \brief Gestion de la map town.
 * \author Enzo BRENNUS
 * \date 18/02/21
 *
 */

Uint8 * pixel(SDL_Surface * surface, int x, int y)
{
    Uint8 * pixels = (Uint8*)surface->pixels;
    Uint8 * pixel = pixels+y*surface->pitch+x;
    return pixel;
}


/*!
 *
 * \fn town(game_t * game)
 * \brief Permet la gestion de la premier map du jeu (town).
 *
 * \param game A FINIR.
 *
 */

extern
void town(game_t * game, character_t * character){

    /*--- Initialization Variable ------------------------------------------------*/

    map_t* town = NULL;
    town = map_create(game->render, "src\\tileset\\Maps\\town.bmp", "src\\tileset\\Maps\\town.txt");
    if (town == NULL)
    {
        exit_with_error("Cannot create a map_t object > town.c Line 35");
    }

    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    SDL_bool town_bool = SDL_TRUE;

    SDL_Event event;

    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->North_Walk.rect.h * MULTIPLIER;
    pos_Wind_character.w = character->North_Walk.rect.w * MULTIPLIER;
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 2;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2;

    SDL_Rect pos_Wind_town;
    pos_Wind_town.x = town->tile_set.x;
    pos_Wind_town.y = town->tile_set.y;
    pos_Wind_town.h = town->tile_set.h * MULTIPLIER;
    pos_Wind_town.w = town->tile_set.w * MULTIPLIER;

    int East_Walk = 0;
    int West_Walk = 0;
    int South_Walk = 0;
    int North_Walk = 0;
<<<<<<< HEAD

    int x = town->tile_set.w - ((*game->WINDOWHEIGHT) / 2);
    int y = town->tile_set.h - ((*game->WINDOWWIDTH) / 2);
=======

    int x = 128; //A FINIR.
    int y = 88; //A FINIR.
>>>>>>> main

    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && town_bool)
    {

        while (SDL_PollEvent(&event))
        {

            while (*game->program_launch == SDL_TRUE || (event.type == SDL_KEYDOWN && (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_ESCAPE])))
            {
                SDL_PollEvent(&event);

                if (event.type == SDL_QUIT)
                {
                    (*game->program_launch) = SDL_FALSE;
                }
                if (keyState[SDL_SCANCODE_ESCAPE])
                {
                    menu_in_game(game);
                    SDL_RenderPresent(game->render);
                    while(keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)SDL_PollEvent(&event);
                }

                while (keyState[SDL_SCANCODE_RIGHT])
                {
                    East_Walk = 1;

                    for (int i = 0; i < 3; i++)
                    {

                        frame_start =  SDL_GetTicks();

                        pos_Wind_town.x -= 25;
                        x -= 25;

                        printf("x : %i\n",x);
                        printf("y : %i\n\n",y);

                        town->update(town, game->render, town->tile_set, pos_Wind_town);

                        character->update(character, game->render, character->East_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > town.c Line 102");
                        }

                    }

                    SDL_PollEvent(&event);

                }
                if (East_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    town->update(town, game->render, town->tile_set, pos_Wind_town);
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

                        pos_Wind_town.x += 25;
                        x += 25;

                        printf("x : %i\n",x);
                        printf("y : %i\n\n",y);

                        town->update(town, game->render, town->tile_set, pos_Wind_town);

                        character->update(character, game->render, character->West_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > town.c Line 131");
                        }

                    }

                    SDL_PollEvent(&event);

                }

                if (West_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    town->update(town, game->render, town->tile_set, pos_Wind_town);
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

                        pos_Wind_town.y += 25;
                        y += 25;

                        printf("x : %i\n",x);
                        printf("y : %i\n\n",y);

                        town->update(town, game->render, town->tile_set, pos_Wind_town);

                        character->update(character, game->render, character->South_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering, town.c Line 160");
                        }

                    }

                    SDL_PollEvent(&event);

                }

                if (South_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    town->update(town, game->render, town->tile_set, pos_Wind_town);
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

                        pos_Wind_town.y -= 25;
                        y -= 25;

                        printf("x : %i\n",x);
                        printf("y : %i\n\n",y);

                        town->update(town, game->render, town->tile_set, pos_Wind_town);

                        character->update(character, game->render, character->North_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > town.c Line 189");
                        }

                    }

                    SDL_PollEvent(&event);
                }

                if (North_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    town->update(town, game->render, town->tile_set, pos_Wind_town);
                    character->update(character, game->render, character->North_Walk, pos_Wind_character);
                    render_frame(game->render);
                    North_Walk = 0;
                }

                /*
                Uint8 * pixel_surf = pixel(surface, pos_Wind_town.x, pos_Wind_town.y);

                SDL_GetRGB(*pixel_surf, surface->format, &r, &g, &b);

                printf("Couleur : rouge = %i, vert = %i, bleu = %i", r, g, b);
                */

            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    town->free(&town);
    character->free(&character);

    /*--- End Free Memory --------------------------------------------------------*/

}
