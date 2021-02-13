#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "character.h"
#include "frame.h"

/*!
 *
 * \file town.c
 * \brief Gestion de la map town.
 * \author Robin PAPILLON, Alexis BOUFFARD, Jeremy BOURGOUIN, Enzo BRENNUS
 * \date 12/02/21
 *
 * \section DESCRIPTION
 * Ficher town.c ... A FINIR
 *
 */

 /*!
  *
  * \fn void town(SDL_Renderer * render,SDL_bool * program_launch)
  * \brief Permet la gestion de la premier map du jeu (town).
  *
  * \param render Pointeur sur le rendu SDL.
  * \param program_launch A FINIR
  *
  */

extern
void town(SDL_Renderer* render, SDL_bool* program_launch) {

    /*--- Initialization Variable ------------------------------------------------*/

    map_t* FF6_World_of_Balance_Maps_Narshe_Exterior = NULL;
    FF6_World_of_Balance_Maps_Narshe_Exterior = map_create(render, "src\\tileset\\FF6_World_of_Balance_Maps-Narshe_(Exterior).bmp", "src\\tileset\\FF6_World_of_Balance_Maps-Narshe_(Exterior).txt");
    if (FF6_World_of_Balance_Maps_Narshe_Exterior == NULL)
    {
        exit_with_error("Cannot create a map_t object > town.c Line 36");
    }

    character_t* FF6_Terra_Branford = NULL;
    FF6_Terra_Branford = character_create(render, "src\\tileset\\FF6_Terra_Branford.bmp", "src\\tileset\\FF6_Terra_Branford.txt");
    if (FF6_Terra_Branford == NULL)
    {
        exit_with_error("Cannot create a character_t object > town.c Line 43");
    }

    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    SDL_Texture* texture = NULL;

    SDL_Surface* surface = NULL;

    surface = SDL_LoadBMP("src\\tileset\\ff7.bmp");
    if (!surface)
    {
        SDL_ExitWithError("Loading of ff7.bmp failed > town.c Line 59");
    }

    texture = SDL_CreateTextureFromSurface(render, surface);
    if (!texture)
    {
        SDL_ExitWithError("Cannot create a texture from a surface > town.c Line 65");
    }

    SDL_Rect pos_Wind_FF6_Terra;
    pos_Wind_FF6_Terra.h = FF6_Terra_Branford->North_Walk.rect.h * MULTIPLIER;
    pos_Wind_FF6_Terra.w = FF6_Terra_Branford->North_Walk.rect.w * MULTIPLIER;
    pos_Wind_FF6_Terra.x = (WINDOWWIDTH - FF6_Terra_Branford->North_Walk.rect.w) / 2;
    pos_Wind_FF6_Terra.y = (WINDOWHEIGHT - FF6_Terra_Branford->North_Walk.rect.h) / 2;

    SDL_Rect pos_Wind_FF6_Narshe_Exterior;
    pos_Wind_FF6_Narshe_Exterior.x = 0;
    pos_Wind_FF6_Narshe_Exterior.y = 0;
    pos_Wind_FF6_Narshe_Exterior.h = FF6_World_of_Balance_Maps_Narshe_Exterior->tile_set.h * MULTIPLIER;
    pos_Wind_FF6_Narshe_Exterior.w = FF6_World_of_Balance_Maps_Narshe_Exterior->tile_set.w * MULTIPLIER;

    SDL_RenderPresent(render);

    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Main Loop --------------------------------------------------------------*/

    while (*program_launch == SDL_TRUE)
    {

        while (SDL_PollEvent(&event))
        {

            while (*program_launch == SDL_TRUE || (event.type == SDL_KEYDOWN && (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_UP])))
            {
                SDL_PollEvent(&event);

                if (event.type == SDL_QUIT || keyState[SDL_SCANCODE_ESCAPE])
                {
                    *program_launch = SDL_FALSE;
                }

                while (keyState[SDL_SCANCODE_RIGHT])
                {
                    frame_start =  SDL_GetTicks();

                    FF6_World_of_Balance_Maps_Narshe_Exterior->tile_set.x += 5;
                    FF6_World_of_Balance_Maps_Narshe_Exterior->update(FF6_World_of_Balance_Maps_Narshe_Exterior, render, FF6_World_of_Balance_Maps_Narshe_Exterior->tile_set, pos_Wind_FF6_Narshe_Exterior);

                    FF6_Terra_Branford->update(FF6_Terra_Branford, render, FF6_Terra_Branford->East_Walk, pos_Wind_FF6_Terra);

                    render_frame(render);

                    if (SDL_RenderClear(render) != 0)
                    {
                        SDL_ExitWithError("Unable to clear rendering > town.c Line 138");
                    }

                    SDL_PollEvent(&event);
                }
                FF6_Terra_Branford->mov.x = 0;
                FF6_Terra_Branford->mov.y = 0;

                while (keyState[SDL_SCANCODE_LEFT])
                {
                    frame_start =  SDL_GetTicks();

                    FF6_World_of_Balance_Maps_Narshe_Exterior->tile_set.x -= 5;
                    FF6_World_of_Balance_Maps_Narshe_Exterior->update(FF6_World_of_Balance_Maps_Narshe_Exterior, render, FF6_World_of_Balance_Maps_Narshe_Exterior->tile_set, pos_Wind_FF6_Narshe_Exterior);

                    FF6_Terra_Branford->update(FF6_Terra_Branford, render, FF6_Terra_Branford->West_Walk, pos_Wind_FF6_Terra);

                    render_frame(render);

                    if (SDL_RenderClear(render) != 0)
                    {
                        SDL_ExitWithError("Unable to clear rendering > town.c Line 164");
                    }

                    SDL_PollEvent(&event);
                }
                FF6_Terra_Branford->mov.x = 0;
                FF6_Terra_Branford->mov.y = 0;

                while (keyState[SDL_SCANCODE_UP])
                {
                    frame_start =  SDL_GetTicks();

                    FF6_World_of_Balance_Maps_Narshe_Exterior->tile_set.y -= 5;
                    FF6_World_of_Balance_Maps_Narshe_Exterior->update(FF6_World_of_Balance_Maps_Narshe_Exterior, render, FF6_World_of_Balance_Maps_Narshe_Exterior->tile_set, pos_Wind_FF6_Narshe_Exterior);

                    FF6_Terra_Branford->update(FF6_Terra_Branford, render, FF6_Terra_Branford->North_Walk, pos_Wind_FF6_Terra);

                    render_frame(render);

                    if (SDL_RenderClear(render) != 0)
                    {
                        SDL_ExitWithError("Unable to clear rendering, town.c Line 190");
                    }

                    SDL_PollEvent(&event);
                }
                FF6_Terra_Branford->mov.x = 0;
                FF6_Terra_Branford->mov.y = 0;

                while (keyState[SDL_SCANCODE_DOWN])
                {
                    frame_start =  SDL_GetTicks();

                    FF6_World_of_Balance_Maps_Narshe_Exterior->tile_set.y += 5;
                    FF6_World_of_Balance_Maps_Narshe_Exterior->update(FF6_World_of_Balance_Maps_Narshe_Exterior, render, FF6_World_of_Balance_Maps_Narshe_Exterior->tile_set, pos_Wind_FF6_Narshe_Exterior);

                    FF6_Terra_Branford->update(FF6_Terra_Branford, render, FF6_Terra_Branford->South_Walk, pos_Wind_FF6_Terra);

                    render_frame(render);

                    if (SDL_RenderClear(render) != 0)
                    {
                        SDL_ExitWithError("Unable to clear rendering > town.c Line 216");
                    }

                    SDL_PollEvent(&event);
                }
                FF6_Terra_Branford->mov.x = 0;
                FF6_Terra_Branford->mov.y = 0;

            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    FF6_World_of_Balance_Maps_Narshe_Exterior->free(&FF6_World_of_Balance_Maps_Narshe_Exterior);
    FF6_Terra_Branford->free(&FF6_Terra_Branford);

    /*--- End Free Memory --------------------------------------------------------*/
}