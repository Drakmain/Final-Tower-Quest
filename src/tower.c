#include <stdio.h>
#include <stdlib.h>

#include "tower.h"
#include "frame.h"
#include "map.h"
#include "character.h"

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
  * \fn tower(SDL_Renderer * render, int * WINDOWWIDTH, int * WINDOWHEIGHT, SDL_bool * program_launch)
  * \brief A FINIR
  *
  * \param render est un pointeur sur le rendu SDL.
  * \param WINDOWWIDTH est la largeur de la fenetre.
  * \param WINDOWHEIGHT est la hauteur de la fenetre.
  * \param program_launch A FINIR.
  *
  */

extern
void tower(SDL_Renderer * render, int * WINDOWWIDTH, int * WINDOWHEIGHT, SDL_bool * program_launch){

    /*--- Initialization Variable ------------------------------------------------*/

    map_t* tower = NULL;
    tower = map_create(render, "src\\tileset\\Maps\\tower.bmp", "src\\tileset\\Maps\\tower.txt");
    if (tower == NULL)
    {
        exit_with_error("Cannot create a map_t object > tower.c Line 35");
    }

    character_t* Assassin = NULL;
    //Assassin = character_create(render, "src\\tileset\\PJ\\Assassin.bmp", "src\\tileset\\PJ\\Assassin.txt");
    if (Assassin == NULL)
    {
        exit_with_error("Cannot create a character_t object > tower.c Line 42");
    }

    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    SDL_bool tower_bool = SDL_TRUE;

    SDL_Event event;

    SDL_Rect pos_Wind_Assassin;
    pos_Wind_Assassin.h = Assassin->North_Walk.rect.h * MULTIPLIER;
    pos_Wind_Assassin.w = Assassin->North_Walk.rect.w * MULTIPLIER;
    pos_Wind_Assassin.x = (*WINDOWWIDTH - pos_Wind_Assassin.w) / 2;
    pos_Wind_Assassin.y = (*WINDOWHEIGHT - pos_Wind_Assassin.h) / 2;

    SDL_Rect pos_Wind_tower;
    pos_Wind_tower.x = 0;
    pos_Wind_tower.y = 0;
    pos_Wind_tower.h = tower->tile_set.h * MULTIPLIER;
    pos_Wind_tower.w = tower->tile_set.w * MULTIPLIER;

    int East_Walk = 0;
    int West_Walk = 0;
    int South_Walk = 0;
    int North_Walk = 0;

    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Main Loop --------------------------------------------------------------*/

    while (*program_launch && tower_bool)
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
                    East_Walk = 1;

                    for (int i = 0; i < 3; i++)
                    {

                        frame_start =  SDL_GetTicks();

                        pos_Wind_tower.x -= 25;

                        tower->update(tower, render, tower->tile_set, pos_Wind_tower);

                        Assassin->update(Assassin, render, Assassin->East_Walk, pos_Wind_Assassin);

                        render_frame(render);

                        if (SDL_RenderClear(render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > tower.c Line 102");
                        }

                    }

                    SDL_PollEvent(&event);

                }
                if (East_Walk == 1)
                {
                    Assassin->mov.x = 0;
                    Assassin->mov.y = 0;
                    tower->update(tower, render, tower->tile_set, pos_Wind_tower);
                    Assassin->update(Assassin, render, Assassin->East_Walk, pos_Wind_Assassin);
                    render_frame(render);
                    East_Walk = 0;
                }
                
                
                

                while (keyState[SDL_SCANCODE_LEFT])
                {

                    for (int i = 0; i < 3; i++)
                    {
                        West_Walk = 1;
                        frame_start =  SDL_GetTicks();

                        pos_Wind_tower.x += 25;

                        tower->update(tower, render, tower->tile_set, pos_Wind_tower);

                        Assassin->update(Assassin, render, Assassin->West_Walk, pos_Wind_Assassin);

                        render_frame(render);

                        if (SDL_RenderClear(render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > tower.c Line 131");
                        }

                    }
                    
                    SDL_PollEvent(&event);
                    
                }

                if (West_Walk == 1)
                {
                    Assassin->mov.x = 0;
                    Assassin->mov.y = 0;
                    tower->update(tower, render, tower->tile_set, pos_Wind_tower);
                    Assassin->update(Assassin, render, Assassin->West_Walk, pos_Wind_Assassin);
                    render_frame(render);
                    West_Walk = 0;
                }
                

                while (keyState[SDL_SCANCODE_UP])
                {

                    for (int i = 0; i < 3; i++)
                    {
                        South_Walk = 1;
                        frame_start =  SDL_GetTicks();

                        pos_Wind_tower.y += 25;

                        tower->update(tower, render, tower->tile_set, pos_Wind_tower);

                        Assassin->update(Assassin, render, Assassin->South_Walk, pos_Wind_Assassin);

                        render_frame(render);

                        if (SDL_RenderClear(render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering, tower.c Line 160");
                        }

                    }
                    
                    SDL_PollEvent(&event);

                }

                if (South_Walk == 1)
                {
                    Assassin->mov.x = 0;
                    Assassin->mov.y = 0;
                    tower->update(tower, render, tower->tile_set, pos_Wind_tower);
                    Assassin->update(Assassin, render, Assassin->South_Walk, pos_Wind_Assassin);
                    render_frame(render);
                    South_Walk = 0;
                }


                while (keyState[SDL_SCANCODE_DOWN])
                {

                    for (int i = 0; i < 3; i++)
                    {
                        North_Walk = 1;
                        frame_start =  SDL_GetTicks();

                        pos_Wind_tower.y -= 25;

                        tower->update(tower, render, tower->tile_set, pos_Wind_tower);

                        Assassin->update(Assassin, render, Assassin->North_Walk, pos_Wind_Assassin);

                        render_frame(render);

                        if (SDL_RenderClear(render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > tower.c Line 189");
                        }

                    }

                    SDL_PollEvent(&event);
                }

                if (North_Walk == 1)
                {
                    Assassin->mov.x = 0;
                    Assassin->mov.y = 0;
                    tower->update(tower, render, tower->tile_set, pos_Wind_tower);
                    Assassin->update(Assassin, render, Assassin->North_Walk, pos_Wind_Assassin);
                    render_frame(render);
                    North_Walk = 0;
                }

            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    tower->free(&tower);
    Assassin->free(&Assassin);

    /*--- End Free Memory --------------------------------------------------------*/
}