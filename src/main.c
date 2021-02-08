#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "character.h"
#include "map.h"

/*!
 * 
 * \file main.c
 * \brief Ficher principale du jeu.
 * \author Robin PAPILLON, Alexis BOUFFARD, Jeremy BOURGOUIN, Enzo BRENNUS
 * \version 0.1
 * \date 22/01/21
 *
 * \section DESCRIPTION
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 */


#define MULTIPLIER 5

#define WINDOWWIDTH 1600
#define WINDOWHEIGHT 900


/*!
 *
 * \fn int main(int argc, char **argv)
 * \brief Fonction principale du jeu.
 *
 * \param argc Nombre de parametres.
 * \param argv Tableau des parametres.
 * 
 */

int main(int argc, char **argv)
{

    /*--- Print SDL Version ------------------------------------------------------*/

    SDL_version nb;
    SDL_VERSION(&nb);

    printf("SDL Version: %d.%d.%d\n", nb.major, nb.minor, nb.patch);

    /*--- End Print SDL Version --------------------------------------------------*/


    /*--- Initialization Variable ------------------------------------------------*/

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool program_launch = SDL_TRUE;
    SDL_Event event;

    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Initialization SDL Video -----------------------------------------------*/

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("SDL initialization");

    /*--- End Initialization SDL Video -------------------------------------------*/


    /*--- Creation Window --------------------------------------------------------*/

    SDL_Window * window = NULL;

    window = SDL_CreateWindow("Final Tower Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);

    if (!window)
        SDL_ExitWithError("Window creation failed");

    /*--- End Creation Window ----------------------------------------------------*/


    /*--- Creation Render --------------------------------------------------------*/

    SDL_Renderer * render = NULL;
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (!render)
        SDL_ExitWithError("Render creation failed");

    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);

    SDL_RenderClear(render);
    SDL_RenderPresent(render);

    /*--- End Creation Render ----------------------------------------------------*/

    /*--- Main Loop --------------------------------------------------------------*/

    while (program_launch)
    {
        
        while (SDL_PollEvent(&event))
        {

            
            
            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT || keyState[SDL_SCANCODE_ESCAPE])
                program_launch = SDL_FALSE;

            /*--- End Event to Exit Program --------------------------------------*/

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    /*--- End Free Memory --------------------------------------------------------*/

    SDL_Quit();

    printf("Program exit with succes");
    return EXIT_SUCCESS;
}
