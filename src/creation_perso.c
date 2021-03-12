#include <stdio.h>
#include <stdlib.h>

#include "creation_perso.h"


/*!
 *
 * \file creation_perso.c
 * \brief Creation d'un perosnnage.
 * \author Alexis BOUFFARD
 * \date 12/03/21
 *
 */


/*!
 *
 * \fn creation_perso(SDL_Renderer * render, int windowwidth, int windowheight, SDL_bool * program_launch)
 * \brief A FINIR
 *
 * \param render render est un pointeur sur le rendu SDL.s
 * \param windowwidth A FINIR
 * \param windowheight A FINIR
 * \param program_launch est un pointeur booléen.
 * 
 */

extern
void creation_perso(SDL_Renderer * render, int windowwidth, int windowheight, SDL_bool * program_launch){

    TTF_Font *police = NULL;
    police = TTF_OpenFont("src\\font\\dragon-quest-ix.ttf",50);
    if(police == NULL){
        SDL_ExitWithError("probleme chargement police fonction menu de creation de personnage");
    }


    /*--- Initialization variable ----------------------------------------------------*/

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    SDL_Surface * surf_guerrier = NULL, * surf_mage = NULL, * surf_assassin = NULL, * surf_fond = NULL, * surf_spriteGuerrier = NULL, * surf_spriteMage = NULL, * surf_spriteAssassin = NULL, * surf_cadre = NULL;

    SDL_bool crea_perso_bool = SDL_TRUE;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    int selection = 0;

    /*--- End Initialization variable --------------------------------------------*/


    /*--- Initialization text "Guerrier" -----------------------------------------*/

    surf_guerrier = TTF_RenderText_Blended(police, "Guerrier", rouge);
    if(surf_guerrier == NULL){
        SDL_ExitWithError("Probleme surface guerrier");
    }

    SDL_Texture * guerrier = SDL_CreateTextureFromSurface(render, surf_guerrier);
    if(guerrier == NULL){
        SDL_ExitWithError("Probleme texture guerrier");
    }

    SDL_Rect pos_guerrier;
    pos_guerrier.x = windowwidth/2 - windowwidth/2.2;
    pos_guerrier.y = windowheight/2 - windowwidth/5;
    pos_guerrier.w = windowwidth/7;
    pos_guerrier.h = windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization text "Mage" ---------------------------------------------*/
    
    surf_mage = TTF_RenderText_Blended(police, "Mage", blanc);
    if(surf_mage == NULL){
        SDL_ExitWithError("probleme surface mage");
    }
    SDL_Texture* mage = SDL_CreateTextureFromSurface(render, surf_mage);
    if(mage == NULL){
        SDL_ExitWithError("probleme texture mage");
    }

    SDL_Rect pos_mage;
    pos_mage.x = windowwidth/2 - windowwidth/2.2;
    pos_mage.y = windowheight/2 - windowwidth/29;
    pos_mage.w = windowwidth/11;
    pos_mage.h = windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization text "Assassin" ----------------------------------------*/

    surf_assassin = TTF_RenderText_Blended(police, "Assassin", blanc);
    if(surf_assassin == NULL){
        SDL_ExitWithError("probleme surface assassin");
    }

    SDL_Texture* assassin = SDL_CreateTextureFromSurface(render, surf_assassin);
    if(assassin == NULL){
        SDL_ExitWithError("probleme texture assassin");
    }

    SDL_Rect pos_assassin;
    pos_assassin.x = windowwidth/2 - windowwidth/2.2;
    pos_assassin.y = windowheight/2 + windowwidth/7.5;
    pos_assassin.w = windowwidth/7;
    pos_assassin.h = windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "Guerrier" --------------------------------------*/

    surf_spriteGuerrier = SDL_LoadBMP("src\\tileset\\PJ\\guerrier_frame.bmp");
    SDL_SetColorKey(surf_spriteGuerrier, SDL_TRUE, SDL_MapRGB(surf_spriteGuerrier->format, 255,255,255));
    if(surf_spriteGuerrier == NULL){
        SDL_ExitWithError("probleme chargement sprite du guerrier");
    }

    SDL_Texture* spriteGuerrier = SDL_CreateTextureFromSurface(render, surf_spriteGuerrier);
    if(spriteGuerrier == NULL){
        SDL_ExitWithError("probleme texture sprite du guerrier");
    }

    SDL_Rect pos_spriteGuerrier;
    pos_spriteGuerrier.x = windowwidth/2 + windowwidth/15;
    pos_spriteGuerrier.y = windowheight/2 - windowwidth/5;
    pos_spriteGuerrier.w = windowwidth * 144 /1200;
    pos_spriteGuerrier.h = windowheight * 144 /675;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "Mage" ------------------------------------------*/

    surf_spriteMage = SDL_LoadBMP("src\\tileset\\PJ\\mage_frame.bmp");
    SDL_SetColorKey(surf_spriteMage, SDL_TRUE, SDL_MapRGB(surf_spriteMage->format, 255,255,255));
    if(surf_spriteMage == NULL){
        SDL_ExitWithError("probleme chargement sprite du mage");
    }

    SDL_Texture* spriteMage = SDL_CreateTextureFromSurface(render, surf_spriteMage);
    if(spriteMage == NULL){
        SDL_ExitWithError("probleme texture sprite du mage");
    }

    SDL_Rect pos_spriteMage;
    pos_spriteMage.x = windowwidth/2 + windowwidth/15;
    pos_spriteMage.y = windowheight/2 - windowwidth/5;
    pos_spriteMage.w = windowwidth * 144 /1200;
    pos_spriteMage.h = windowheight * 144 /675;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "Assassin" --------------------------------------*/

    surf_spriteAssassin = SDL_LoadBMP("src\\tileset\\PJ\\assassin_frame.bmp");
    SDL_SetColorKey(surf_spriteAssassin, SDL_TRUE, SDL_MapRGB(surf_spriteAssassin->format, 255,255,255));
    if(surf_spriteAssassin == NULL){
        SDL_ExitWithError("probleme chargement sprite du assassin");
    }

    SDL_Texture* spriteAssassin = SDL_CreateTextureFromSurface(render, surf_spriteAssassin);
    if(spriteAssassin == NULL){
        SDL_ExitWithError("probleme texture sprite du assassin");
    }

    SDL_Rect pos_spriteAssassin;
    pos_spriteAssassin.x = windowwidth/2 + windowwidth/15;
    pos_spriteAssassin.y = windowheight/2 - windowwidth/5;
    pos_spriteAssassin.w = windowwidth * 108 /1200;
    pos_spriteAssassin.h = windowheight * 180 /675;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization background image ----------------------------------------*/
    
    surf_fond = SDL_LoadBMP("src\\image\\ciel_sans_lune.bmp");
    if(surf_fond == NULL){
        SDL_ExitWithError("probleme chargement image fond menu de creation de personnage");
    }

    SDL_Texture* fond = SDL_CreateTextureFromSurface(render, surf_fond);
    if(fond == NULL){
        SDL_ExitWithError("probleme texture fond menu de creation de personnage");
    }

    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;
    pos_fond.w = windowwidth;
    pos_fond.h = windowheight;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "cadre" -----------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_desc.bmp");
    if(surf_cadre == NULL){
        SDL_ExitWithError("probleme chargement image cadre");
    }

    SDL_Texture* cadre_desc = SDL_CreateTextureFromSurface(render, surf_cadre);
    if(cadre_desc == NULL){
        SDL_ExitWithError("probleme texture cadre_desc");
    }

    SDL_Rect pos_cadre_desc;
    pos_cadre_desc.x = windowheight * 478 /675;
    pos_cadre_desc.y = windowheight * 325 /675;
    pos_cadre_desc.w = windowwidth * 550 /1200;
    pos_cadre_desc.h = windowheight * 290 /675;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture background "cadre" ------------------------------------*/

    SDL_Texture* fond_cadre_desc = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre_desc.w, pos_cadre_desc.h);
    if(fond_cadre_desc == NULL){
        SDL_ExitWithError("probleme texture fond_cadre_desc");
    }

    SDL_Rect pos_fond_cadre_desc;
    pos_fond_cadre_desc.x = pos_cadre_desc.x;
    pos_fond_cadre_desc.y = pos_cadre_desc.y;
    pos_fond_cadre_desc.w = pos_cadre_desc.w;
    pos_fond_cadre_desc.h = pos_cadre_desc.h;

    SDL_Rect rect_fond_cadre_desc;
    rect_fond_cadre_desc.x = pos_fond_cadre_desc.w*12/1600 ;
    rect_fond_cadre_desc.y = pos_fond_cadre_desc.h*12/900;
    rect_fond_cadre_desc.w = pos_fond_cadre_desc.w - 2*pos_fond_cadre_desc.w*12/1600;
    rect_fond_cadre_desc.h = pos_fond_cadre_desc.h - 2*pos_fond_cadre_desc.h*12/900;

    SDL_SetRenderDrawColor(render,0,0,0, 200);
    SDL_SetRenderTarget(render, fond_cadre_desc);
    SDL_SetTextureBlendMode(fond_cadre_desc, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(render, &rect_fond_cadre_desc);
    SDL_SetRenderTarget(render,NULL);

    /*------------------------------------------------------------------------------------*/


    SDL_RenderClear(render);

    SDL_RenderCopy(render, fond, NULL, &pos_fond);
    SDL_RenderCopy(render, guerrier, NULL, &pos_guerrier);
    SDL_RenderCopy(render, mage, NULL, &pos_mage);
    SDL_RenderCopy(render, assassin, NULL, &pos_assassin);
    SDL_RenderCopy(render, spriteGuerrier, NULL, &pos_spriteGuerrier);
    SDL_RenderCopy(render, fond_cadre_desc, NULL, &pos_fond_cadre_desc);
    SDL_RenderCopy(render, cadre_desc, NULL, &pos_cadre_desc);

    SDL_RenderPresent(render);


    /*--- Main Loop --------------------------------------------------------------*/

    while (crea_perso_bool && *program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program -----------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                *program_launch = SDL_FALSE;
                crea_perso_bool = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                crea_perso_bool = SDL_FALSE;
            }

            /*--- End Event to Exit Program -------------------------------------------*/


            /*--- Event pour selectionner ---------------------------------------------*/

            if (keyState[SDL_SCANCODE_DOWN] && event.type == SDL_KEYDOWN)
            {
                selection++;
            }

            if (keyState[SDL_SCANCODE_UP] && event.type == SDL_KEYDOWN)
            {
                selection--;
            }

            /*--- End Event pour selectionner -----------------------------------------*/


            SDL_RenderCopy(render, fond, NULL, &pos_fond);
            SDL_RenderCopy(render, guerrier, NULL, &pos_guerrier);
            SDL_RenderCopy(render, mage, NULL, &pos_mage);
            SDL_RenderCopy(render, assassin, NULL, &pos_assassin);
            SDL_RenderCopy(render, fond_cadre_desc, NULL, &pos_fond_cadre_desc);
            SDL_RenderCopy(render, cadre_desc, NULL, &pos_cadre_desc);

            if(selection < 0)selection = 2;
            selection %=3;

            if(selection == 0)
            {
                surf_guerrier = TTF_RenderText_Blended(police, "Guerrier", rouge);
                surf_mage = TTF_RenderText_Blended(police, "Mage", blanc);
                surf_assassin = TTF_RenderText_Blended(police, "Assassin", blanc);

                SDL_RenderCopy(render, spriteGuerrier, NULL, &pos_spriteGuerrier);
            }

            if(selection == 1)
            {
                surf_guerrier = TTF_RenderText_Blended(police, "Guerrier", blanc);
                surf_mage = TTF_RenderText_Blended(police, "Mage", rouge);
                surf_assassin = TTF_RenderText_Blended(police, "Assassin", blanc);

                SDL_RenderCopy(render, spriteMage, NULL, &pos_spriteMage);
            }

            if(selection == 2)
            {
                surf_guerrier = TTF_RenderText_Blended(police, "Guerrier", blanc);
                surf_mage = TTF_RenderText_Blended(police, "Mage", blanc);
                surf_assassin = TTF_RenderText_Blended(police, "Assassin", rouge);

                SDL_RenderCopy(render, spriteAssassin, NULL, &pos_spriteAssassin);

            }
            guerrier = SDL_CreateTextureFromSurface(render, surf_guerrier);
            mage = SDL_CreateTextureFromSurface(render, surf_mage);
            assassin = SDL_CreateTextureFromSurface(render, surf_assassin);


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

            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_guerrier);
    SDL_FreeSurface(surf_mage);
    SDL_FreeSurface(surf_assassin);
    SDL_FreeSurface(surf_fond);
    SDL_FreeSurface(surf_spriteGuerrier);
    SDL_FreeSurface(surf_spriteMage);
    SDL_FreeSurface(surf_spriteAssassin);


    SDL_DestroyTexture(guerrier);
    SDL_DestroyTexture(mage);
    SDL_DestroyTexture(assassin);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(spriteGuerrier);
    SDL_DestroyTexture(spriteMage);
    SDL_DestroyTexture(spriteAssassin);

    /*--- End Free Memory --------------------------------------------------------*/


    TTF_CloseFont(police);

}