#include <stdio.h>
#include <stdlib.h>

#include "character.h"
#include "map.h"
#include "town.h"
#include "commun.h"

/*!
 * 
 * \file main.c
 * \brief Ficher principale du jeu.
 * \author Robin PAPILLON, Alexis BOUFFARD, Jeremy BOURGOUIN, Enzo BRENNUS
 * \date 12/02/21
 *
 * \section DESCRIPTION
 * Ficher main.c ... A FINIR
 * 
 */


/*!
 *
 * \fn int main(int argc, char ** argv)
 * \brief Fonction principale du jeu.
 *
 * \param argc Nombre de parametres.
 * \param argv Tableau des parametres.
 * 
 * \retval int Un entier.
 * 
 */

int main(int argc, char ** argv)
{

    /*--- Print SDL Version ------------------------------------------------------*/
    printf("/*--- Startup SDL -------*/\n");

    SDL_version nb;
    SDL_VERSION(&nb);

    printf("SDL Version: %d.%d.%d\n", nb.major, nb.minor, nb.patch);

    /*--- End Print SDL Version --------------------------------------------------*/


    /*--- Initialization Variable ------------------------------------------------*/

    SDL_bool program_launch = SDL_TRUE;

    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Initialization SDL Video -----------------------------------------------*/

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("SDL initialization > main.c Line 59");
    }
    else
    {
        printf("SDL Video initialised\n");
    }

    /*--- End Initialization SDL Video -------------------------------------------*/


    /*--- Creation Window --------------------------------------------------------*/

    SDL_Window * window = NULL;

    window = SDL_CreateWindow("Final Tower Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_ExitWithError("Window creation failed > main.c Line 75");
    }
    else
    {
        printf("window created\n");
    }
        
    /*--- End Creation Window ----------------------------------------------------*/


    /*--- Creation Render --------------------------------------------------------*/

    SDL_Renderer * render = NULL;
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (render == NULL)
    {
        SDL_ExitWithError("Render creation failed > main.c Line 92");
    }
    else
    {
        printf("render created\n");
    }

    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);

    SDL_RenderClear(render);
    SDL_RenderPresent(render);

    printf("/*--- End Startup SDL ---*/\n\n");
    /*--- End Creation Render ----------------------------------------------------*/
    

    /*--- Main Loop --------------------------------------------------------------*/

    while (program_launch)
    {

        //start_menu(render, &program_launch);
        //character_selection(render, &program_launch);
        town(render, &program_launch);

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/
    printf("/*--- Free Memory -------*/\n");

    SDL_DestroyRenderer(render);
    printf("render destroyed\n");

    SDL_DestroyWindow(window);
    printf("window destroyed\n");

    printf("/*--- End Free Memory ---*/\n\n");
    /*--- End Free Memory --------------------------------------------------------*/

    SDL_Quit();

    printf("Program exited with succes");
    return EXIT_SUCCESS;
}