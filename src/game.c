#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\game.h"

/*!
 *
 * \file game.c
 * \brief Gestion de l'objet game.
 * \author Enzo BRENNUS
 * \date 16/03/21
 *
 */


/*!
 *
 * \struct game_t game.h "game.h"
 * \brief Structure de l'objet game_t.
 *
 */


/*!
 *
 * \fn void game_free(game_t ** game)
 * \brief Permet la liberation d'un objet game.
 *
 * \param game est un objet game_t qui doit etre libéré.
 *
 */

static
void game_free(game_t ** game)
{
    /*--- Free Memory ------------------------------------------------------------*/

    printf("/*--- Free Memory -------*/\n");

    SDL_DestroyRenderer((*game)->render);
    printf("SDL_Renderer * render: destroyed\n");

    SDL_DestroyWindow((*game)->window);
    printf("SDL_Window * window: destroyed\n");

    TTF_CloseFont((*game)->police);
    printf("TTF_Font * police: closed\n");

    free((*game)->WINDOWWIDTH);
    printf("int * WINDOWWIDTH: freed\n");
    free((*game)->WINDOWHEIGHT);
    printf("int * WINDOWHEIGHT: freed\n");

    free((*game)->etat_fullscreen);
    printf("SDL_bool * etat_fullscreen: freed\n");

    free((*game)->program_launch);
    printf("SDL_bool * program_launch: freed\n");

    printf("/*--- End Free Memory ---*/\n\n");

    /*--- End Free Memory --------------------------------------------------------*/

    SDL_Quit();

    free(*game);

}


/*!
 *
 * \fn game_create()
 * \brief Permet la creation du l'objet game.
 *
 * \return game Un objet game créé dans cette fonction.
 * \retval game_t * Un pointeur sur l'objet game.
 *
 */

extern
game_t * game_create()
{

    /*--- Initialization variable ------------------------------------------------*/

    game_t * game = NULL;
    game = malloc(sizeof(game_t));

    /*--- End Initialization variable --------------------------------------------*/


    /*--- Open options file ------------------------------------------------------*/

    FILE * opts = fopen("options.txt", "r");

    fclose(opts);

    /*----------------------------------------------------------------------------*/


    /*--- Initialization Variable ------------------------------------------------*/

    game->program_launch = malloc(sizeof(SDL_bool));
    (*game->program_launch) = SDL_TRUE;

    game->etat_fullscreen = malloc(sizeof(SDL_bool));
    (*game->etat_fullscreen) = SDL_FALSE;

    game->WINDOWWIDTH = malloc(sizeof(int));
    (*game->WINDOWWIDTH) = WINDOWWIDTH_720P;
    game->WINDOWHEIGHT = malloc(sizeof(int));
    (*game->WINDOWHEIGHT) = WINDOWHEIGHT_720P;

    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Initialization SDL Video -----------------------------------------------*/

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("SDL Video initialization > game.c Line 133");
    }
    else
    {
        printf("SDL Video initialised\n");
    }

    /*--- End Initialization SDL Video -------------------------------------------*/


    /*--- Initialization SDL TTF -------------------------------------------------*/

    if (TTF_Init() == -1)
    {
        SDL_ExitWithError("SDL TTF initialization > game.c Line 147");
    }
    else
    {
        printf("SDL TTF initialised\n");
    }

    /*--- End Initialization SDL TTF ---------------------------------------------*/


    /*--- Creation Window --------------------------------------------------------*/

    game->window = NULL;
    game->window = SDL_CreateWindow("Final Tower Quest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT), SDL_WINDOW_SHOWN);
    if (game->window == NULL)
    {
        SDL_ExitWithError("Window creation failed > game.c Line 163");
    }
    else
    {
        printf("window created\n");
    }

    /*--- End Creation Window ----------------------------------------------------*/


    /*--- Creation Render --------------------------------------------------------*/

    game->render = NULL;
    game->render = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_SOFTWARE);
    if (game->render == NULL)
    {
        SDL_ExitWithError("Render creation failed > game.c Line 179");
    }
    else
    {
        printf("render created\n");
    }

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 0);

    SDL_RenderClear(game->render);
    SDL_RenderPresent(game->render);

    printf("/*--- End Startup SDL ---*/\n\n");

    /*--- End Creation Render ----------------------------------------------------*/


    /*--- Creation Police --------------------------------------------------------*/

    game->police = NULL;
    game->police = TTF_OpenFont("src\\font\\dragon-quest-ix.ttf",50);
    if(game->police == NULL)
    {
        SDL_ExitWithError("probleme chargement police > game.c Line 179");
    }

    /*--- End Creation Police ----------------------------------------------------*/


    /*--- Initialization method --------------------------------------------------*/

    game->free = game_free;

    /*----------------------------------------------------------------------------*/

    return(game);
}


/*!
 *
 * \fn SDL_bool game_exist(game_t * const game)
 * \brief Permet de verifier l'existence du l'objet game_t.
 *
 * \param game est un pointeur sur un objet game_t.
 *
 * \retval SDL_bool Une variable booléenne SDL.
 *
 */

extern
SDL_bool game_exist(game_t * const game)
{

    if(game == NULL)
    {
        return(SDL_FALSE);
    }
    else
    {
        return(SDL_TRUE);
    }

}
