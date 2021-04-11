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
 * \fn affichage_message(game_t *game, char *message, int nombre)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param message A FINIR.
 * \param nombre A FINIR.
 *
 */

extern void affichage_message(game_t *game, SDL_Texture *texture_render, char *message, int nombre)
{
    /*--- Initialization Variable ------------------------------------------------*/
    SDL_Color blanc = {255, 255, 255};

    SDL_Surface *surf_cadre = NULL, *surf_message = NULL, *surf_message2 = NULL;

    SDL_Texture *t_message2;

    SDL_Rect pos_message2;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    SDL_bool affichage_message_bool = SDL_TRUE, part2_bool = SDL_FALSE;

    char tab_part1_message[strlen(message) + 20];
    char tab_part2_message[strlen(message) + 20];
    strcpy(tab_part1_message, message);

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
    rect_fond_cadre.x = (*game->WINDOWWIDTH) * 12 / 1280;
    rect_fond_cadre.y = (*game->WINDOWHEIGHT) * 12 / 720;
    rect_fond_cadre.w = pos_fond_cadre.w - 2 * rect_fond_cadre.x + 1;
    rect_fond_cadre.h = pos_fond_cadre.h - 2 * rect_fond_cadre.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
    SDL_SetRenderTarget(game->render, fond_cadre);
    SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    if (nombre != -1)
    {
        int i = 0;
        int y = 0;
        char memoire, memoire2;
        char nombre_char[10];
        itoa(nombre, nombre_char, 10);

        while ((tab_part1_message[i] != '%' && tab_part1_message[i + 1] != 'd') && tab_part1_message[i] != '\0')
            i++;

        if (tab_part1_message[i] == '\0')
            SDL_ExitWithError("position du nombre dans le message non indique");

        for (; nombre_char[y] != '\0' && y < 2; y++, i++)
        {
            tab_part1_message[i] = nombre_char[y];
        }

        for (; nombre_char[y] != '\0'; y++, i++)
        {
            memoire = tab_part1_message[i];
            tab_part1_message[i] = nombre_char[y];
            for (int k = i + 1; k < strlen(tab_part1_message) + 1; k++)
            {
                memoire2 = memoire;
                memoire = tab_part1_message[k];
                tab_part1_message[k] = memoire2;
            }
        }

        if (y == 1)
        {
            for (int k = i + 1; k < strlen(tab_part1_message) + 1; k++)
            {
                memoire = tab_part1_message[k];
                tab_part1_message[k - 1] = memoire;
            }
        }
    }

    int i = 0;
    int fin_part1;
    while ((tab_part1_message[i] != '%' && tab_part1_message[i + 1] != 'n') && tab_part1_message[i] != '\0')
        i++;

    if (tab_part1_message[i] == '%')
    {
        part2_bool = SDL_TRUE;
        fin_part1 = i;
        i += 3;

        for (int y = 0; i < strlen(tab_part1_message) + 1; i++, y++)
        {
            tab_part2_message[y] = tab_part1_message[i];
        }
        tab_part1_message[fin_part1] = '\0';

        /*---texture "cadre"--------------------------------------------------------*/

        surf_cadre = SDL_LoadBMP("src\\image\\cadre_affichage_message_2lignes.bmp");
        if (surf_cadre == NULL)
        {
            SDL_ExitWithError("probleme chargement image cadre affichage_message");
        }

        cadre = SDL_CreateTextureFromSurface(game->render, surf_cadre);
        if (cadre == NULL)
        {
            SDL_ExitWithError("probleme texture cadre affichage_message");
        }

        pos_cadre.h = (*game->WINDOWHEIGHT) * 175 / 720;
        pos_cadre.y = (*game->WINDOWHEIGHT) / 2 - pos_cadre.h / 2;

        /*------------------------------------------------------------------------------------*/

        /*---texture fond--------------------------------------------------------*/

        fond_cadre = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre.w, pos_cadre.h);
        if (fond_cadre == NULL)
        {
            SDL_ExitWithError("probleme texture fond cadre affichage_message");
        }

        pos_fond_cadre.y = pos_cadre.y;
        pos_fond_cadre.h = pos_cadre.h;

        rect_fond_cadre.h = pos_fond_cadre.h - 2 * rect_fond_cadre.y + 1;

        SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
        SDL_SetRenderTarget(game->render, fond_cadre);
        SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(game->render, &rect_fond_cadre);
        SDL_SetRenderTarget(game->render, NULL);

        /*------------------------------------------------------------------------------------*/

        /*--- Creation text "partie 2 message" ----------------------------------------*/

        surf_message2 = TTF_RenderText_Blended(game->police, tab_part2_message, blanc);
        if (surf_message2 == NULL)
        {
            SDL_ExitWithError("probleme surface message d'affichage_message");
        }

        t_message2 = SDL_CreateTextureFromSurface(game->render, surf_message2);
        if (t_message2 == NULL)
        {
            SDL_ExitWithError("probleme texture message d'affichage_message");
        }

        pos_message2.w = strlen(tab_part2_message) * (*game->WINDOWWIDTH) * 850 / 1280 / 59;
        pos_message2.h = (*game->WINDOWHEIGHT) * 50 / 720;
        pos_message2.x = pos_cadre.x + rect_fond_cadre.x + (*game->WINDOWWIDTH) * 15 / 1280;
        pos_message2.y = pos_cadre.y + rect_fond_cadre.y + (*game->WINDOWHEIGHT) * 85 / 720;

        /*----------------------------------------------------------------------------*/
    }

    /*--- Creation text "partie 1 message" ----------------------------------------*/

    surf_message = TTF_RenderText_Blended(game->police, tab_part1_message, blanc);
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
    pos_message.w = strlen(tab_part1_message) * (*game->WINDOWWIDTH) * 850 / 1280 / 59;
    pos_message.h = (*game->WINDOWHEIGHT) * 50 / 720;
    pos_message.x = pos_cadre.x + rect_fond_cadre.x + (*game->WINDOWWIDTH) * 15 / 1280;
    pos_message.y = pos_cadre.y + rect_fond_cadre.y + (*game->WINDOWHEIGHT) * 15 / 720;

    /*----------------------------------------------------------------------------*/

    SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
    SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
    SDL_RenderCopy(game->render, t_message, NULL, &pos_message);
    if (part2_bool)
        SDL_RenderCopy(game->render, t_message2, NULL, &pos_message2);
    SDL_RenderPresent(game->render);

    SDL_Rect pos_texture_render;
    pos_texture_render.x = 0;
    pos_texture_render.y = 0;
    pos_texture_render.w = (*game->WINDOWWIDTH);
    pos_texture_render.h = (*game->WINDOWHEIGHT);
    /*--- Main Loop --------------------------------------------------------------*/
    while ((*game->program_launch) && affichage_message_bool)
    {

        while (SDL_PollEvent(&event))
        {

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {
                affichage_message_bool = SDL_FALSE;
                SDL_RenderClear(game->render);
                SDL_RenderCopy(game->render, texture_render, NULL, &pos_texture_render);
                SDL_RenderPresent(game->render);
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
    SDL_FreeSurface(surf_message2);

    SDL_DestroyTexture(t_message);
    if (part2_bool)
        SDL_DestroyTexture(t_message2);
    SDL_DestroyTexture(cadre);
    SDL_DestroyTexture(fond_cadre);

    /*--- End Free Memory --------------------------------------------------------*/
}
