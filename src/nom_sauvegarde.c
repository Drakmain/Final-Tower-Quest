#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\nom_sauvegarde.h"


/*!
 *
 * \file nom_sauvegarde.c
 * \brief A FINIR.
 * \author Alexis BOUFFARD
 *
 */


/*!
 *
 * \fn nom_sauvegarde(game_t * game, char * actual_save)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param actual_save A FINIR.
 *
 */

extern
void nom_sauvegarde(game_t * game, char * actual_save){

    /*--- Initialization variable ----------------------------------------------------*/

    SDL_Color blanc = {255,255,255};

    SDL_Surface *surf_fond = NULL, *surf_demande = NULL, *surf_cadre = NULL;

    SDL_bool nom_sauvegarde_bool = SDL_TRUE;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    /*--- End Initialization variable --------------------------------------------*/


    /*--- Initialization background image ----------------------------------------*/

    surf_fond = SDL_LoadBMP("src\\image\\ciel_sans_lune.bmp");
    if(surf_fond == NULL){
        SDL_ExitWithError("probleme chargement image fond menu de creation de personnage");
    }

    SDL_Texture* fond = SDL_CreateTextureFromSurface(game->render, surf_fond);
    if(fond == NULL){
        SDL_ExitWithError("probleme texture fond menu de creation de personnage");
    }

    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;
    pos_fond.w = (*game->WINDOWWIDTH);
    pos_fond.h = (*game->WINDOWHEIGHT);

    /*----------------------------------------------------------------------------*/

    /*--- Initialization texture "cadre" -----------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_nom_save.bmp");
    if(surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre");
    }

    SDL_Texture* cadre_nom_save = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if(cadre_nom_save == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_nom_save");
    }

    SDL_Rect pos_cadre_nom_save;
    pos_cadre_nom_save.x = (*game->WINDOWHEIGHT) * 271 /720;
    pos_cadre_nom_save.y = (*game->WINDOWHEIGHT) * 325 /720;
    pos_cadre_nom_save.w = (*game->WINDOWWIDTH) * 720 /1280;
    pos_cadre_nom_save.h = (*game->WINDOWHEIGHT) * 110 /720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation texture background "cadre" ------------------------------------*/

    SDL_Texture* fond_cadre_nom_save = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre_nom_save.w, pos_cadre_nom_save.h);
    if(fond_cadre_nom_save == NULL)
    {
        SDL_ExitWithError("probleme texture fond_cadre_nom_save");
    }

    SDL_Rect pos_fond_cadre_nom_save;
    pos_fond_cadre_nom_save.x = pos_cadre_nom_save.x;
    pos_fond_cadre_nom_save.y = pos_cadre_nom_save.y;
    pos_fond_cadre_nom_save.w = pos_cadre_nom_save.w;
    pos_fond_cadre_nom_save.h = pos_cadre_nom_save.h;

    SDL_Rect rect_fond_cadre_nom_save;
    rect_fond_cadre_nom_save.x = pos_fond_cadre_nom_save.w*12/1600 ;
    rect_fond_cadre_nom_save.y = pos_fond_cadre_nom_save.h*12/900;
    rect_fond_cadre_nom_save.w = pos_fond_cadre_nom_save.w - 2*pos_fond_cadre_nom_save.w*12/1600;
    rect_fond_cadre_nom_save.h = pos_fond_cadre_nom_save.h - 2*pos_fond_cadre_nom_save.h*12/900;

    SDL_SetRenderDrawColor(game->render,0,0,0, 200);
    SDL_SetRenderTarget(game->render, fond_cadre_nom_save);
    SDL_SetTextureBlendMode(fond_cadre_nom_save, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre_nom_save);
    SDL_SetRenderTarget(game->render,NULL);

    /*----------------------------------------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
    SDL_RenderCopy(game->render, fond_cadre_nom_save, NULL, &pos_fond_cadre_nom_save);
    SDL_RenderCopy(game->render, cadre_nom_save, NULL, &pos_cadre_nom_save);


    SDL_RenderPresent(game->render);

    /*--- Initialization text "Demande" -----------------------------------------*/

    surf_demande = TTF_RenderText_Blended(game->police, "Votre nom de sauvegarde doit etre compris entre 1 et 10 caracteres :", blanc);
    if(surf_demande == NULL){
        SDL_ExitWithError("Probleme surface demande");
    }

    SDL_Texture * demande = SDL_CreateTextureFromSurface(game ->render, surf_demande);
    if(demande == NULL){
        SDL_ExitWithError("Probleme texture demande");
    }

    SDL_Rect pos_demande;
    pos_demande.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/2.11;
    pos_demande.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5;
    pos_demande.w = (*game->WINDOWWIDTH)/1.05;
    pos_demande.h = (*game->WINDOWHEIGHT)/13.5;

    /*----------------------------------------------------------------------------*/


    /*---Save de caractères-----------------------------------------------------*/

    /*---End Save de caractères-----------------------------------------------------*/


    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
    SDL_RenderCopy(game->render, demande, NULL, &pos_demande);
    SDL_RenderCopy(game->render, fond_cadre_nom_save, NULL, &pos_fond_cadre_nom_save);
    SDL_RenderCopy(game->render, cadre_nom_save, NULL, &pos_cadre_nom_save);
    
    SDL_RenderPresent(game->render);


    /*--- Main Loop --------------------------------------------------------------*/

    while (nom_sauvegarde_bool && *game->program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program -----------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                *game->program_launch = SDL_FALSE;
                nom_sauvegarde_bool = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                nom_sauvegarde_bool = SDL_FALSE;
            }

            /*--- End Event to Exit Program -------------------------------------------*/

            SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
            SDL_RenderCopy(game->render, demande, NULL, &pos_demande);
            SDL_RenderCopy(game->render, fond_cadre_nom_save, NULL, &pos_fond_cadre_nom_save);
            SDL_RenderCopy(game->render, cadre_nom_save, NULL, &pos_cadre_nom_save);

            demande = SDL_CreateTextureFromSurface(game->render, surf_demande);

            SDL_RenderPresent(game->render);
        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_fond);

    SDL_DestroyTexture(fond);

    /*--- End Free Memory --------------------------------------------------------*/

}
