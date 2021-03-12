#include <stdio.h>
#include <stdlib.h>

#include "options.h"

/*!
 *
 * \file options.c
 * \brief affichage et gestion des options.
 * \author Jeremy BOURGOUIN
 * \date 12/03/21
 *
 */


/*!
 *
 * \fn options_f(SDL_Window *window, SDL_Renderer *render, int windowwidth, int windowheight, SDL_bool* program_launch)
 * \brief A FINIR
 *
 * \param window A FINIR
 * \param render render est un pointeur sur le rendu SDL.
 * \param windowwidth A FINIR
 * \param windowheight A FINIR
 * \param program_launch program_launch est un pointeur booléen.
 *
 */

extern
void options_f(SDL_Window *window, SDL_Renderer *render, int windowwidth, int windowheight, SDL_bool* program_launch){

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    TTF_Font *police = NULL;
    police = TTF_OpenFont("src\\font\\dragon-quest-ix.ttf",50);
    if(police == NULL){
        SDL_ExitWithError("probleme chargement police");
    }


    SDL_Surface* surf_options = NULL, *surf_retour = NULL, *surf_fond = NULL, *surf_cadre = NULL;

    /*---texture "options"--------------------------------------------------------*/
    surf_options = TTF_RenderText_Blended(police, "OPTIONS", blanc);
    if(surf_options == NULL){
        SDL_ExitWithError("probleme surface options");
    }
    SDL_Texture* options = SDL_CreateTextureFromSurface(render, surf_options);
    if(options == NULL){
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_options;
    pos_options.x = windowwidth/2 - windowwidth*107/1200;
    pos_options.y = windowheight/30;
    pos_options.w = windowwidth*214/1200;
    pos_options.h = windowheight/13.5;
    /*------------------------------------------------------------------------------------*/

    /*---texture "retour"--------------------------------------------------------*/
    surf_retour = TTF_RenderText_Blended(police, "Retour", rouge);
    if(surf_retour == NULL){
        SDL_ExitWithError("probleme surface options");
    }
    SDL_Texture* retour = SDL_CreateTextureFromSurface(render, surf_retour);
    if(retour == NULL){
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_retour;
    pos_retour.x = windowwidth/20;
    pos_retour.y = windowheight - windowheight/8;
    pos_retour.w = windowwidth/(1200/129);
    pos_retour.h = windowheight/13.5;
    /*------------------------------------------------------------------------------------*/

    /*---texture fond--------------------------------------------------------*/

    surf_fond = SDL_LoadBMP("src\\image\\fond_menu_accueil.bmp");
    if(surf_fond == NULL){
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture* fond = SDL_CreateTextureFromSurface(render, surf_fond);
    if(fond == NULL){
        SDL_ExitWithError("probleme texture fond menu d'accueil");
    }

    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;
    pos_fond.w = windowwidth;
    pos_fond.h = windowheight;
    /*------------------------------------------------------------------------------------*/

    /*---texture "cadre"--------------------------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_options.bmp");
    if(surf_cadre == NULL){
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture* cadre = SDL_CreateTextureFromSurface(render, surf_cadre);
    if(cadre == NULL){
        SDL_ExitWithError("probleme texture nouvelle partie menu d'accueil");
    }

    SDL_Rect pos_cadre;
    pos_cadre.x = windowwidth/6;
    pos_cadre.y = windowheight/6.75;
    pos_cadre.w = windowwidth*820/1200;
    pos_cadre.h = windowheight*460/675;

    /*------------------------------------------------------------------------------------*/

    /*---texture "fond cadre"--------------------------------------------------------*/
    SDL_Texture* fond_cadre = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowwidth*820/1200, windowheight*460/675);
    if(fond_cadre == NULL){
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_fond_cadre;
    pos_fond_cadre.x = pos_cadre.x;
    pos_fond_cadre.y = pos_cadre.y;
    pos_fond_cadre.w = pos_cadre.w;
    pos_fond_cadre.h = pos_cadre.h;

    SDL_Rect rect_fond_cadre;
    rect_fond_cadre.x = windowwidth*12/1200;
    rect_fond_cadre.y = windowheight*12/675;
    rect_fond_cadre.w = pos_fond_cadre.w - 2*rect_fond_cadre.x;
    rect_fond_cadre.h = pos_fond_cadre.h - 2*rect_fond_cadre.y;

    SDL_SetRenderDrawColor(render,0,0,0, 200);
    SDL_SetRenderTarget(render,fond_cadre);
    SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(render, &rect_fond_cadre);
    SDL_SetRenderTarget(render,NULL);

    /*------------------------------------------------------------------------------------*/

    SDL_RenderClear(render);
    SDL_RenderCopy(render, fond, NULL, &pos_fond);
    SDL_RenderCopy(render, options, NULL, &pos_options);
    SDL_RenderCopy(render, retour, NULL, &pos_retour);
    SDL_RenderCopy(render, fond_cadre, NULL, &pos_fond_cadre);
    SDL_RenderCopy(render, cadre, NULL, &pos_cadre);
    SDL_RenderPresent(render);

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool continu = SDL_TRUE;
    SDL_Event event;

    int selection = 1;

    while (continu && *program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT){
                *program_launch = SDL_FALSE;
                continu = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
                continu = SDL_FALSE;
            /*--- End Event to Exit Program --------------------------------------*/
            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN){
                if(selection == 1){
                    continu = SDL_FALSE;
                }
            }
        }
    }




    SDL_FreeSurface(surf_options);
    SDL_FreeSurface(surf_retour);
    SDL_FreeSurface(surf_fond);

    SDL_DestroyTexture(options);
    SDL_DestroyTexture(retour);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(cadre);

    TTF_CloseFont(police);
}
