#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "..\lib\transition.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\combat.h"

/*!
 *
 * \file transition.c
 * \brief A FINIR.
 * \author Alexis BRENNUS
 *
 */

/*!
 *
 * \fn transition(game_t *game)
 * \brief Permet la gestion de la premier map du jeu (town).
 *
 * \param game A FINIR.
 *
 */

extern void transition(game_t *game)
{
    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Surface *surf_rectangle1 = NULL, *surf_rectangle2 = NULL, *surf_rectangle3 = NULL, *surf_rectangle4 = NULL;

    /*--- End Initialization Variable --------------------------------------------*/

    /*--- Initialization rectangle1 --------------------------------------*/

    surf_rectangle1 = SDL_LoadBMP("src\\image\\rectangle.bmp");
    if (surf_rectangle1 == NULL)
    {
        SDL_ExitWithError("probleme chargement rectangle1");
    }

    SDL_Texture *rectangle1 = SDL_CreateTextureFromSurface(game->render, surf_rectangle1);
    if (rectangle1 == NULL)
    {
        SDL_ExitWithError("probleme texture rectangle1");
    }

    SDL_Rect pos_rectangle1;
    pos_rectangle1.x = -(*game->WINDOWWIDTH);
    pos_rectangle1.y = 0;
    pos_rectangle1.w = (*game->WINDOWWIDTH);
    pos_rectangle1.h = (*game->WINDOWHEIGHT) / 4;

    /*----------------------------------------------------------------------------*/

    /*--- Initialization rectangle2 --------------------------------------*/

    surf_rectangle2 = SDL_LoadBMP("src\\image\\rectangle.bmp");
    if (surf_rectangle2 == NULL)
    {
        SDL_ExitWithError("probleme chargement rectangle2");
    }

    SDL_Texture *rectangle2 = SDL_CreateTextureFromSurface(game->render, surf_rectangle2);
    if (rectangle2 == NULL)
    {
        SDL_ExitWithError("probleme texture rectangle2");
    }

    SDL_Rect pos_rectangle2;
    pos_rectangle2.x = (*game->WINDOWWIDTH);
    pos_rectangle2.y = (*game->WINDOWHEIGHT) / 4;
    pos_rectangle2.w = (*game->WINDOWWIDTH);
    pos_rectangle2.h = (*game->WINDOWHEIGHT) / 4;

    /*----------------------------------------------------------------------------*/

    /*--- Initialization rectangle3 --------------------------------------*/

    surf_rectangle3 = SDL_LoadBMP("src\\image\\rectangle.bmp");
    if (surf_rectangle3 == NULL)
    {
        SDL_ExitWithError("probleme chargement rectangle3");
    }

    SDL_Texture *rectangle3 = SDL_CreateTextureFromSurface(game->render, surf_rectangle3);
    if (rectangle3 == NULL)
    {
        SDL_ExitWithError("probleme texture rectangle3");
    }

    SDL_Rect pos_rectangle3;
    pos_rectangle3.x = -(*game->WINDOWWIDTH);
    pos_rectangle3.y = (*game->WINDOWHEIGHT) * 270 * 2 / 1080;
    pos_rectangle3.w = (*game->WINDOWWIDTH);
    pos_rectangle3.h = (*game->WINDOWHEIGHT) / 4;

    /*----------------------------------------------------------------------------*/

    /*--- Initialization rectangle4 --------------------------------------*/

    surf_rectangle4 = SDL_LoadBMP("src\\image\\rectangle.bmp");
    if (surf_rectangle4 == NULL)
    {
        SDL_ExitWithError("probleme chargement rectangle4");
    }

    SDL_Texture *rectangle4 = SDL_CreateTextureFromSurface(game->render, surf_rectangle4);
    if (rectangle4 == NULL)
    {
        SDL_ExitWithError("probleme texture rectangle4");
    }

    SDL_Rect pos_rectangle4;
    pos_rectangle4.x = (*game->WINDOWWIDTH);
    pos_rectangle4.y = (*game->WINDOWHEIGHT) * 270 * 3 / 1080;
    pos_rectangle4.w = (*game->WINDOWWIDTH);
    pos_rectangle4.h = (*game->WINDOWHEIGHT) / 4;

    /*----------------------------------------------------------------------------*/

    for (int i = 0; i < 42; i++)
    {
        pos_rectangle1.x += (*game->WINDOWHEIGHT) * 50 / 1080;
        pos_rectangle2.x -= (*game->WINDOWHEIGHT) * 50 / 1080;
        pos_rectangle3.x += (*game->WINDOWHEIGHT) * 50 / 1080;
        pos_rectangle4.x -= (*game->WINDOWHEIGHT) * 50 / 1080;

        SDL_RenderCopy(game->render, rectangle1, NULL, &pos_rectangle1);
        SDL_RenderCopy(game->render, rectangle2, NULL, &pos_rectangle2);
        SDL_RenderCopy(game->render, rectangle3, NULL, &pos_rectangle3);
        SDL_RenderCopy(game->render, rectangle4, NULL, &pos_rectangle4);

        SDL_RenderPresent(game->render);
        SDL_Delay(40);
    }

    pos_rectangle1.x = -(*game->WINDOWWIDTH);
    pos_rectangle2.x = (*game->WINDOWWIDTH);
    pos_rectangle3.x = -(*game->WINDOWWIDTH);
    pos_rectangle4.x = (*game->WINDOWWIDTH);

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_rectangle1);
    SDL_FreeSurface(surf_rectangle2);
    SDL_FreeSurface(surf_rectangle3);
    SDL_FreeSurface(surf_rectangle4);

    SDL_DestroyTexture(rectangle1);
    SDL_DestroyTexture(rectangle2);
    SDL_DestroyTexture(rectangle3);
    SDL_DestroyTexture(rectangle4);

    /*--- End Free Memory --------------------------------------------------------*/
}
