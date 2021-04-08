#include <stdio.h>
#include <stdlib.h>

#include "..\lib\affichage_message.h"

/*!
 *
 * \file affichage_message.c
 * \brief A FINIR.
 * \author Jeremy BOURGOUIN
 *
 */

/*!
 *
 * \fn affichage_message(game_t * game, char * message)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param message A FINIR.
 *
 */

extern void affichage_message(game_t *game, char *message, int nombre)
{
    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Color blanc = {255, 255, 255};

    SDL_Surface *surf_cadre = NULL, *surf_message = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    SDL_bool affichage_message_bool = SDL_TRUE;

    char tab [100];
    strcpy(tab, message);
    /*--- End Initialization Variable --------------------------------------------*/

    /*---texture "cadre"--------------------------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_affichage_message.bmp");
    if (surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre affichage_message");
    }

    SDL_Texture *cadre = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if (cadre == NULL)
    {
        SDL_ExitWithError("probleme texture cadre affichage_message");
    }

    SDL_Rect pos_cadre;
    pos_cadre.w = (*game->WINDOWWIDTH) * 900 / 1280;
    pos_cadre.h = (*game->WINDOWHEIGHT) * 100 / 720;
    pos_cadre.x = (*game->WINDOWWIDTH) / 2 - pos_cadre.w / 2;
    pos_cadre.y = (*game->WINDOWHEIGHT) / 2 - pos_cadre.h / 2;

    /*------------------------------------------------------------------------------------*/

    /*---texture fond--------------------------------------------------------*/

    SDL_Texture *fond_cadre = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre.w, pos_cadre.h);
    if (fond_cadre == NULL)
    {
        SDL_ExitWithError("probleme texture fond cadre affichage_message");
    }

    SDL_Rect pos_fond_cadre;
    pos_fond_cadre.x = pos_cadre.x;
    pos_fond_cadre.y = pos_cadre.y;
    pos_fond_cadre.w = pos_cadre.w;
    pos_fond_cadre.h = pos_cadre.h;

    SDL_Rect rect_fond_cadre;
    rect_fond_cadre.x = (*game->WINDOWWIDTH)*12/1280;
    rect_fond_cadre.y = (*game->WINDOWHEIGHT)*12/720;
    rect_fond_cadre.w = pos_fond_cadre.w - 2*rect_fond_cadre.x + 1;
    rect_fond_cadre.h = pos_fond_cadre.h - 2*rect_fond_cadre.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
    SDL_SetRenderTarget(game->render, fond_cadre);
    SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    if(nombre != -1)
    {
        int i = 0 ;
        int y = 0 ;
        char memoire, memoire2;
        char nombre_char[10];
        itoa(nombre, nombre_char, 10);

        while((tab[i] != '%' && tab[i + 1] != 'd') && tab[i] != '\0')i++;

        if(tab[i] == '\0')SDL_ExitWithError("position du nombre dans le message non indique");

        for( ;  nombre_char[y] != '\0' && y < 2; y++ ,i++)
        {
            tab[i] = nombre_char[y];
        }

        for(; nombre_char[y] != '\0' ; y++ ,i++)
        {
            memoire = tab[i];
            tab[i] = nombre_char[y];
            for(int k = i + 1 ; k < strlen(tab) + 1 ; k++)
            {
                memoire2 = memoire;
                memoire = tab[k];
                tab[k] = memoire2;
            }
        }

        if(y == 1)
        {
            for (int k = i + 1; k < strlen(tab) + 1; k++) {
                memoire = tab[k];
                tab[k - 1] = memoire;
            }
        }

    }

    /*--- Creation text "texte de confirmation" ----------------------------------------*/

    surf_message = TTF_RenderText_Blended(game->police, tab, blanc);
    if (surf_message == NULL)
    {
        SDL_ExitWithError("probleme surface message d'affichage_message");
    }

    SDL_Texture *t_message = SDL_CreateTextureFromSurface(game->render, surf_message);
    if (t_message == NULL)
    {
        SDL_ExitWithError("probleme texture message d'affichage_message");
    }

    SDL_Rect pos_message;
    pos_message.w = strlen(tab)*(*game->WINDOWWIDTH)*850/1280/59;
    pos_message.h = (*game->WINDOWHEIGHT)*50/720;
    pos_message.x = (*game->WINDOWWIDTH)/2 - pos_message.w/2;
    pos_message.y = pos_cadre.y + (*game->WINDOWHEIGHT)*22/720;

    /*----------------------------------------------------------------------------*/


    SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
    SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
    SDL_RenderCopy(game->render, t_message, NULL, &pos_message);

    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    while ((*game->program_launch) && affichage_message_bool)
    {

        while (SDL_PollEvent(&event))
        {

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {
                affichage_message_bool = SDL_FALSE;
                SDL_RenderClear(game->render);
            }


            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                (*game->program_launch) = SDL_FALSE;
            }

            /*--- End Event to Exit Program --------------------------------------*/

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_cadre);
    SDL_FreeSurface(surf_message);

    SDL_DestroyTexture(t_message);
    SDL_DestroyTexture(cadre);
    SDL_DestroyTexture(fond_cadre);


    /*--- End Free Memory --------------------------------------------------------*/
}
