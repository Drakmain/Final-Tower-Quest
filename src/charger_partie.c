#include <stdio.h>
#include <stdlib.h>

#include "charger_partie.h"


/*!
 *
 * \file charger_partie.c
 * \brief charger partie.
 * \author Jeremy BOURGOUIN
 * \date 12/03/21
 *
 */


/*!
 *
 * \fn void charger_partie_f(SDL_Renderer *render, int windowwidth, int windowheight,SDL_bool* program_launch)
 * \brief A FINIR
 *
 * \param render render est un pointeur sur le rendu SDL.s
 * \param windowwidth A FINIR
 * \param windowheight A FINIR
 * \param program_launch est un pointeur booléen.
 * 
 */

extern
void charger_partie_f(SDL_Renderer * render, int windowwidth, int windowheight, SDL_bool * program_launch){

    TTF_Font *police = NULL;
    police = TTF_OpenFont("src\\font\\dragon-quest-ix.ttf",50);
    if(police == NULL)
    {
        SDL_ExitWithError("probleme chargement police");
    }


    /*--- Initialization variable ------------------------------------------------*/

    SDL_Surface *surf_save1 = NULL, *surf_save2 = NULL, *surf_save3 = NULL, *surf_cadre = NULL, *surf_retour = NULL, *surf_fond = NULL, *surf_choisir_empla = NULL;

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool continu = SDL_TRUE;

    SDL_Event event;

    int selection = 0;

    /*--- End Initialization variable --------------------------------------------*/


    /*--- Creation text "choisissez emplacement a charger" -----------------------*/

    surf_choisir_empla = TTF_RenderText_Blended(police, "CHOISISSEZ EMPLACEMENT A CHARGER", blanc);
    if(surf_choisir_empla == NULL)
    {
        SDL_ExitWithError("probleme surface choisir emplacement a charger");
    }

    SDL_Texture* choisir_empla = SDL_CreateTextureFromSurface(render, surf_choisir_empla);
    if(choisir_empla == NULL)
    {
        SDL_ExitWithError("probleme texture choisir emplacement a charger");
    }

    SDL_Rect pos_choisir_empla;
    pos_choisir_empla.x = windowwidth/2 - windowwidth*337/1200;
    pos_choisir_empla.y = windowheight/30;
    pos_choisir_empla.w = windowwidth*673/1200;
    pos_choisir_empla.h = windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation text "retour"--------------------------------------------------*/

    surf_retour = TTF_RenderText_Blended(police, "Retour", blanc);
    if(surf_retour == NULL)
    {
        SDL_ExitWithError("probleme surface Retour");
    }
    SDL_Texture* retour = SDL_CreateTextureFromSurface(render, surf_retour);
    if(retour == NULL)
    {
        SDL_ExitWithError("probleme texture Retour");
    }

    SDL_Rect pos_retour;
    pos_retour.x = windowwidth/20;
    pos_retour.y = windowheight - windowheight/8;
    pos_retour.w = windowwidth/(1200/129);
    pos_retour.h = windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture background --------------------------------------------*/

    surf_fond = SDL_LoadBMP("src\\image\\fond_menu_accueil.bmp");
    if(surf_fond == NULL)
    {
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture* fond = SDL_CreateTextureFromSurface(render, surf_fond);
    if(fond == NULL)
    {
        SDL_ExitWithError("probleme texture fond menu d'accueil");
    }

    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;
    pos_fond.w = windowwidth;
    pos_fond.h = windowheight;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture "save 1" ----------------------------------------------*/

    surf_save1 = TTF_RenderText_Blended(police, "options", blanc);
    if(surf_save1 == NULL)
    {
        SDL_ExitWithError("probleme surface options");
    }
    SDL_Texture* save1 = SDL_CreateTextureFromSurface(render, surf_save1);
    if(save1 == NULL)
    {
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_save1;
    pos_save1.x = windowwidth/2 - 107;
    pos_save1.y = windowheight/13.5;
    pos_save1.w = windowwidth/(1200/214);
    pos_save1.h = windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture "save 2" ----------------------------------------------*/

    surf_save2 = TTF_RenderText_Blended(police, "options", blanc);
    if(surf_save2 == NULL)
    {
        SDL_ExitWithError("probleme surface options");
    }
    SDL_Texture* save2 = SDL_CreateTextureFromSurface(render, surf_save2);
    if(save2 == NULL)
    {
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_save2;
    pos_save2.x = windowwidth/2 - 107;
    pos_save2.y = windowheight/13.5;
    pos_save2.w = windowwidth/(1200/214);
    pos_save2.h = windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture "save 3" ----------------------------------------------*/

    surf_save3 = TTF_RenderText_Blended(police, "options", blanc);
    if(surf_save3 == NULL)
    {
        SDL_ExitWithError("probleme surface options");
    }
    SDL_Texture* save3 = SDL_CreateTextureFromSurface(render, surf_save3);
    if(save3 == NULL)
    {
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_save3;
    pos_save3.x = windowwidth/2 - 107;
    pos_save3.y = windowheight/13.5;
    pos_save3.w = windowwidth/(1200/214);
    pos_save3.h = windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Loading texture "cadre choix emplacement" ------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_choix_emplacement.bmp");
    if(surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre");
    }

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "cadre save 1" ----------------------------------*/

    SDL_Texture* cadre_save1 = SDL_CreateTextureFromSurface(render, surf_cadre);
    if(cadre_save1 == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_save1");
    }

    SDL_Rect pos_cadre_save1;
    pos_cadre_save1.x = windowwidth/2 - windowwidth/6 - windowwidth/15;
    pos_cadre_save1.y = windowheight/6.75;
    pos_cadre_save1.w = windowwidth/2 - windowwidth/30;
    pos_cadre_save1.h = windowheight/5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture background "cadre save 1" -----------------------------*/

    SDL_Texture* fond_cadre_save1 = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowwidth/2 - windowwidth/30, windowheight/5);
    if(fond_cadre_save1 == NULL)
    {
        SDL_ExitWithError("probleme texture fond_cadre_save1");
    }

    SDL_Rect pos_fond_cadre_save1;
    pos_fond_cadre_save1.x = pos_cadre_save1.x;
    pos_fond_cadre_save1.y = pos_cadre_save1.y;
    pos_fond_cadre_save1.w = pos_cadre_save1.w;
    pos_fond_cadre_save1.h = pos_cadre_save1.h;

    SDL_Rect rect_fond_cadre_save1;
    rect_fond_cadre_save1.x = windowwidth*12/1200;
    rect_fond_cadre_save1.y = windowheight*12/675;
    rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2*rect_fond_cadre_save1.x;
    rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2*rect_fond_cadre_save1.y;

    SDL_SetRenderDrawColor(render,0,0,0, 200);
    SDL_SetRenderTarget(render, fond_cadre_save1);
    SDL_SetTextureBlendMode(fond_cadre_save1, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(render, &rect_fond_cadre_save1);
    SDL_SetRenderTarget(render,NULL);

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "cadre save 2" ----------------------------------*/

    SDL_Texture* cadre_save2 = SDL_CreateTextureFromSurface(render, surf_cadre);
    if(cadre_save2 == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_save2");
    }

    SDL_Rect pos_cadre_save2;
    pos_cadre_save2.x = windowwidth/2 - windowwidth/6 - windowwidth/15;
    pos_cadre_save2.y = windowheight/2.5;
    pos_cadre_save2.w = windowwidth/2 - windowwidth/30;
    pos_cadre_save2.h = windowheight/5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture background "cadre save 2" -----------------------------*/

    SDL_Texture* fond_cadre_save2 = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowwidth/2 - windowwidth/30, windowheight/5);
    if(fond_cadre_save2 == NULL)
    {
        SDL_ExitWithError("probleme texture fond_cadre_save2");
    }

    SDL_Rect pos_fond_cadre_save2;
    pos_fond_cadre_save2.x = pos_cadre_save2.x;
    pos_fond_cadre_save2.y = pos_cadre_save2.y;
    pos_fond_cadre_save2.w = pos_cadre_save2.w;
    pos_fond_cadre_save2.h = pos_cadre_save2.h;

    SDL_Rect rect_fond_cadre_save2;
    rect_fond_cadre_save2.x = windowwidth*12/1200;
    rect_fond_cadre_save2.y = windowheight*12/675;
    rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2*rect_fond_cadre_save2.x;
    rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2*rect_fond_cadre_save2.y;

    SDL_SetRenderDrawColor(render,0,0,0, 200);
    SDL_SetRenderTarget(render,fond_cadre_save2);
    SDL_SetTextureBlendMode(fond_cadre_save2, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(render, &rect_fond_cadre_save2);
    SDL_SetRenderTarget(render,NULL);

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "cadre save 3" ----------------------------------*/

    SDL_Texture* cadre_save3 = SDL_CreateTextureFromSurface(render, surf_cadre);
    if(cadre_save3 == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_save3");
    }

    SDL_Rect pos_cadre_save3;
    pos_cadre_save3.x = windowwidth/2 - windowwidth/6 - windowwidth/15;
    pos_cadre_save3.y = windowheight*440/675;
    pos_cadre_save3.w = windowwidth/2 - windowwidth/30;
    pos_cadre_save3.h = windowheight/5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture background "cadre save 3" -----------------------------*/

    SDL_Texture* fond_cadre_save3 = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowwidth/2 - windowwidth/30, windowheight/5);
    if(fond_cadre_save3 == NULL)
    {
        SDL_ExitWithError("probleme texture fond_cadre_save3");
    }

    SDL_Rect pos_fond_cadre_save3;
    pos_fond_cadre_save3.x = pos_cadre_save3.x;
    pos_fond_cadre_save3.y = pos_cadre_save3.y;
    pos_fond_cadre_save3.w = pos_cadre_save3.w;
    pos_fond_cadre_save3.h = pos_cadre_save3.h;

    SDL_Rect rect_fond_cadre_save3;
    rect_fond_cadre_save3.x = windowwidth*12/1200;
    rect_fond_cadre_save3.y = windowheight*12/675;
    rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2*rect_fond_cadre_save3.x;
    rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2*rect_fond_cadre_save3.y;

    SDL_SetRenderDrawColor(render,0,0,0, 200);
    SDL_SetRenderTarget(render,fond_cadre_save3);
    SDL_SetTextureBlendMode(fond_cadre_save3, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(render, &rect_fond_cadre_save3);
    SDL_SetRenderTarget(render,NULL);
    
    /*----------------------------------------------------------------------------*/


    SDL_RenderClear(render);

    SDL_RenderCopy(render, fond, NULL, &pos_fond);
    SDL_RenderCopy(render, choisir_empla, NULL, &pos_choisir_empla);
    SDL_RenderCopy(render, retour, NULL, &pos_retour);
    SDL_RenderCopy(render, fond_cadre_save1, NULL, &pos_fond_cadre_save1);
    SDL_RenderCopy(render, fond_cadre_save1, NULL, &pos_fond_cadre_save2);
    SDL_RenderCopy(render, fond_cadre_save1, NULL, &pos_fond_cadre_save3);
    SDL_RenderCopy(render, cadre_save1, NULL, &pos_cadre_save1);
    SDL_RenderCopy(render, cadre_save1, NULL, &pos_cadre_save2);
    SDL_RenderCopy(render, cadre_save1, NULL, &pos_cadre_save3);

    SDL_RenderPresent(render);


    /*--- Main Loop --------------------------------------------------------------*/

    while (continu && *program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                *program_launch = SDL_FALSE;
                continu = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                continu = SDL_FALSE;
            }

            /*--- End Event to Exit Program --------------------------------------*/


            /*--- Event pour selectionner ------------------------------------------*/
            if (keyState[SDL_SCANCODE_DOWN] && event.type == SDL_KEYDOWN){
                if(selection < 3)selection++;
            }

            if (keyState[SDL_SCANCODE_UP] && event.type == SDL_KEYDOWN){
                if(selection > 0)selection--;
            }

            /*--- End Event pour selectionner --------------------------------------*/


            if(selection < 0)selection = windowwidth*12/1200;


            if(selection == 0) {
                pos_cadre_save2.x = windowwidth/2 - windowwidth/6 - windowwidth/15;
                pos_cadre_save2.y = windowheight/2.5;
                pos_cadre_save2.w = windowwidth/2 - windowwidth/30;
                pos_cadre_save2.h = windowheight/5;
                pos_fond_cadre_save2.x = pos_cadre_save2.x;
                pos_fond_cadre_save2.y = pos_cadre_save2.y;
                pos_fond_cadre_save2.w = pos_cadre_save2.w;
                pos_fond_cadre_save2.h = pos_cadre_save2.h;
                rect_fond_cadre_save2.x = windowwidth*12/1200;
                rect_fond_cadre_save2.y = windowheight*12/675;
                rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2*rect_fond_cadre_save2.x;
                rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2*rect_fond_cadre_save2.y;

                pos_cadre_save1.x = windowwidth/2 - windowwidth/6 - windowwidth/15 - windowwidth/120;
                pos_cadre_save1.y = windowheight/6.75 - windowheight/67.5;
                pos_cadre_save1.w = windowwidth/2 - windowwidth/30 + windowwidth/60;
                pos_cadre_save1.h = windowheight/5 + windowheight/33.75;
                pos_fond_cadre_save1.x = pos_cadre_save1.x;
                pos_fond_cadre_save1.y = pos_cadre_save1.y;
                pos_fond_cadre_save1.w = pos_cadre_save1.w;
                pos_fond_cadre_save1.h = pos_cadre_save1.h;
                rect_fond_cadre_save1.x = windowwidth*12/1200;
                rect_fond_cadre_save1.y = windowheight*12/675;
                rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2*rect_fond_cadre_save1.x;
                rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2*rect_fond_cadre_save1.y;
            }
            if(selection == 1){
                pos_cadre_save3.x = windowwidth/2 - windowwidth/6 - windowwidth/15;
                pos_cadre_save3.y = windowheight*440/675;
                pos_cadre_save3.w = windowwidth/2 - windowwidth/30;
                pos_cadre_save3.h = windowheight/5;
                pos_fond_cadre_save3.x = pos_cadre_save3.x;
                pos_fond_cadre_save3.y = pos_cadre_save3.y;
                pos_fond_cadre_save3.w = pos_cadre_save3.w;
                pos_fond_cadre_save3.h = pos_cadre_save3.h;
                rect_fond_cadre_save3.x = windowwidth*12/1200;
                rect_fond_cadre_save3.y = windowheight*12/675;
                rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2*rect_fond_cadre_save3.x;
                rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2*rect_fond_cadre_save3.y;

                pos_cadre_save1.x = windowwidth/2 - windowwidth/6 - windowwidth/15;
                pos_cadre_save1.y = windowheight/6.75;
                pos_cadre_save1.w = windowwidth/2 - windowwidth/30;
                pos_cadre_save1.h = windowheight/5;
                pos_fond_cadre_save1.x = pos_cadre_save1.x;
                pos_fond_cadre_save1.y = pos_cadre_save1.y;
                pos_fond_cadre_save1.w = pos_cadre_save1.w;
                pos_fond_cadre_save1.h = pos_cadre_save1.h;
                rect_fond_cadre_save1.x = windowwidth*12/1200;
                rect_fond_cadre_save1.y = windowheight*12/675;
                rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2*rect_fond_cadre_save1.x;
                rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2*rect_fond_cadre_save1.y;

                pos_cadre_save2.x = windowwidth/2 - windowwidth/6 - windowwidth/15 - windowwidth/120;
                pos_cadre_save2.y = windowheight/2.5 - windowheight/67.5;
                pos_cadre_save2.w = windowwidth/2 - windowwidth/30 + windowwidth/60;
                pos_cadre_save2.h = windowheight/5 + windowheight/33.75;
                pos_fond_cadre_save2.x = pos_cadre_save2.x;
                pos_fond_cadre_save2.y = pos_cadre_save2.y;
                pos_fond_cadre_save2.w = pos_cadre_save2.w;
                pos_fond_cadre_save2.h = pos_cadre_save2.h;
                rect_fond_cadre_save2.x = windowwidth*12/1200;
                rect_fond_cadre_save2.y = windowheight*12/675;
                rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2*rect_fond_cadre_save2.x;
                rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2*rect_fond_cadre_save2.y;
            }
            if(selection == 2){
                pos_cadre_save2.x = windowwidth/2 - windowwidth/6 - windowwidth/15;
                pos_cadre_save2.y = windowheight/2.5;
                pos_cadre_save2.w = windowwidth/2 - windowwidth/30;
                pos_cadre_save2.h = windowheight/5;
                pos_fond_cadre_save2.x = pos_cadre_save2.x;
                pos_fond_cadre_save2.y = pos_cadre_save2.y;
                pos_fond_cadre_save2.w = pos_cadre_save2.w;
                pos_fond_cadre_save2.h = pos_cadre_save2.h;
                rect_fond_cadre_save2.x = windowwidth*12/1200;
                rect_fond_cadre_save2.y = windowheight*12/675;
                rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2*rect_fond_cadre_save2.x;
                rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2*rect_fond_cadre_save2.y;

                pos_cadre_save3.x = windowwidth/2 - windowwidth/6 - windowwidth/15 - windowwidth/120;
                pos_cadre_save3.y = windowheight*440/675 - windowheight/67.5;
                pos_cadre_save3.w = windowwidth/2 - windowwidth/30 + windowwidth/60;
                pos_cadre_save3.h = windowheight/5 + windowheight/33.75;
                pos_fond_cadre_save3.x = pos_cadre_save3.x;
                pos_fond_cadre_save3.y = pos_cadre_save3.y;
                pos_fond_cadre_save3.w = pos_cadre_save3.w;
                pos_fond_cadre_save3.h = pos_cadre_save3.h;
                rect_fond_cadre_save3.x = windowwidth*12/1200;
                rect_fond_cadre_save3.y = windowheight*12/675;
                rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2*rect_fond_cadre_save3.x;
                rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2*rect_fond_cadre_save3.y;

                surf_retour = TTF_RenderText_Blended(police, "Retour", blanc);
                retour = SDL_CreateTextureFromSurface(render, surf_retour);
            }
            if(selection == 3){
                pos_cadre_save3.x = windowwidth/2 - windowwidth/6 - windowwidth/15;
                pos_cadre_save3.y = windowheight*440/675;
                pos_cadre_save3.w = windowwidth/2 - windowwidth/30;
                pos_cadre_save3.h = windowheight/5;
                pos_fond_cadre_save3.x = pos_cadre_save3.x;
                pos_fond_cadre_save3.y = pos_cadre_save3.y;
                pos_fond_cadre_save3.w = pos_cadre_save3.w;
                pos_fond_cadre_save3.h = pos_cadre_save3.h;
                rect_fond_cadre_save3.x = windowwidth*12/1200;
                rect_fond_cadre_save3.y = windowheight*12/675;
                rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2*rect_fond_cadre_save3.x;
                rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2*rect_fond_cadre_save3.y;

                surf_retour = TTF_RenderText_Blended(police, "Retour", rouge);
                retour = SDL_CreateTextureFromSurface(render, surf_retour);
            }

            SDL_RenderClear(render);
            SDL_RenderCopy(render, fond, NULL, &pos_fond);
            SDL_RenderCopy(render, choisir_empla, NULL, &pos_choisir_empla);
            SDL_RenderCopy(render, retour, NULL, &pos_retour);
            SDL_RenderCopy(render, fond_cadre_save1, NULL, &pos_fond_cadre_save1);
            SDL_RenderCopy(render, fond_cadre_save1, NULL, &pos_fond_cadre_save2);
            SDL_RenderCopy(render, fond_cadre_save1, NULL, &pos_fond_cadre_save3);
            SDL_RenderCopy(render, cadre_save1, NULL, &pos_cadre_save1);
            SDL_RenderCopy(render, cadre_save1, NULL, &pos_cadre_save2);
            SDL_RenderCopy(render, cadre_save1, NULL, &pos_cadre_save3);
            SDL_RenderPresent(render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {

                if(selection == 0)
                {

                }
                if(selection == 1)
                {

                }
                if(selection == 2)
                {

                }
                if(selection == 3)
                {
                    continu = SDL_FALSE;
                }

            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_choisir_empla);
    SDL_FreeSurface(surf_retour);
    SDL_FreeSurface(surf_fond);
    SDL_FreeSurface(surf_cadre);
    SDL_FreeSurface(surf_save1);
    SDL_FreeSurface(surf_save2);
    SDL_FreeSurface(surf_save3);

    SDL_DestroyTexture(choisir_empla);
    SDL_DestroyTexture(retour);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(cadre_save1);
    SDL_DestroyTexture(cadre_save2);
    SDL_DestroyTexture(cadre_save3);
    SDL_DestroyTexture(save1);
    SDL_DestroyTexture(save2);
    SDL_DestroyTexture(save3);
    SDL_DestroyTexture(fond_cadre_save1);
    SDL_DestroyTexture(fond_cadre_save2);
    SDL_DestroyTexture(fond_cadre_save3);

    /*--- End Free Memory --------------------------------------------------------*/


    TTF_CloseFont(police);

}