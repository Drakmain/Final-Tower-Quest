#include <stdio.h>
#include <stdlib.h>

#include "town.h"
#include "tower.h"
#include "menu_accueil.h"
#include "commun.h"

/*!
 * 
 * \file main.c
 * \brief Ficher principale du jeu.
 * \author Enzo BRENNUS
 * \date 12/03/21
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

    /*--- Print SDL Version ------------------------------------------------------*/
    printf("/*--- Startup SDL -------*/\n");

    SDL_version SDL;
    SDL_VERSION(&SDL);

    SDL_version SDL_TTF;
    SDL_TTF_VERSION(&SDL_TTF);

    printf("SDL Version: %d.%d.%d\n", SDL.major, SDL.minor, SDL.patch);

    printf("SDL TTF Version: %d.%d.%d\n", SDL_TTF.major, SDL_TTF.minor, SDL_TTF.patch);

    /*--- End Print SDL Version --------------------------------------------------*/


    /*--- Initialization Variable ------------------------------------------------*/

    SDL_bool program_launch = SDL_TRUE;

    int WINDOWWIDTH = WINDOWWIDTH_1080P;
    int WINDOWHEIGHT = WINDOWHEIGHT_1080P;

    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Initialization SDL Video -----------------------------------------------*/

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("SDL Video initialization > main.c Line 53");
    }
    else
    {
        printf("SDL Video initialised\n");
    }

    /*--- End Initialization SDL Video -------------------------------------------*/

    /*--- Initialization SDL TTF -------------------------------------------------*/

    if (TTF_Init() == -1)
    {
        SDL_ExitWithError("SDL TTF initialization > main.c Line 74");
    }
    else
    {
        printf("SDL TTF initialised\n");
    }

    /*--- End Initialization SDL TTF ---------------------------------------------*/


    /*--- Creation Window --------------------------------------------------------*/

    SDL_Window * window = NULL;

    window = SDL_CreateWindow("Final Tower Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_ExitWithError("Window creation failed > main.c Line 90");
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
        SDL_ExitWithError("Render creation failed > main.c Line 106");
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

        menu_accueil(window, render, WINDOWWIDTH, WINDOWHEIGHT,&program_launch);
        town(render, &WINDOWWIDTH, &WINDOWHEIGHT, &program_launch);
        tower(render, &WINDOWWIDTH, &WINDOWHEIGHT, &program_launch);

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