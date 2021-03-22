#include <stdio.h>
#include <stdlib.h>

#include "..\lib\menu_in_game.h"
#include "..\lib\map.h"
#include "..\lib\character.h"


/*!
 *
 * \file menu_accueil.c
 * \brief Menu d'accueil.
 * \author Jeremy BOURGOUIN
 * \date 10/02/21
 *
 */


/*!
 *
 * \fn menu_accueil(SDL_Window * window, SDL_Renderer * game->render, int (*game->WINDOWWIDTH), int (*game->WINDOWHEIGHT),SDL_bool * program_launch)
 * \brief A FINIR
 *
 * \param render render est un pointeur sur le rendu SDL.s
 * \param (*game->WINDOWWIDTH) A FINIR
 * \param (*game->WINDOWHEIGHT) A FINIR
 * \param program_launch est un pointeur booléen.
 *
 */

extern
void menu_in_game(game_t * game){

    /*--- Initialization variable ------------------------------------------------*/
    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    SDL_Surface *surf_inventaire = NULL, *surf_caracteristique = NULL, *surf_sauvegarder = NULL, *surf_options = NULL, *surf_retourner_menu = NULL, *surf_cadre = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool menu = SDL_TRUE;

    SDL_Event event;

    int selection = 0;

    /*--- End Initialization variable --------------------------------------------*/


    /*--- Creation text "nouvelle partie" ----------------------------------------*/
    surf_inventaire = TTF_RenderText_Blended(game->police, "Inventaire", rouge);
    if(surf_inventaire == NULL){
        SDL_ExitWithError("probleme surface inventaire menu in game");
    }

    SDL_Texture* inventaire = SDL_CreateTextureFromSurface(game->render, surf_inventaire);
    if(inventaire == NULL){
        SDL_ExitWithError("probleme texture inventaire menu in game");
    }

    SDL_Rect pos_inventaire;
    pos_inventaire.x = (*game->WINDOWWIDTH) - 410;
    pos_inventaire.y = 25;
    pos_inventaire.w = (*game->WINDOWWIDTH)*215/1200;
    pos_inventaire.h = 50;
    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nouvelle partie" ----------------------------------------*/
    surf_caracteristique = TTF_RenderText_Blended(game->police, "Caracteristique", blanc);
    if(surf_caracteristique == NULL){
        SDL_ExitWithError("probleme surface caracteristique menu in game");
    }

    SDL_Texture* caracteristique = SDL_CreateTextureFromSurface(game->render, surf_caracteristique);
    if(caracteristique == NULL){
        SDL_ExitWithError("probleme texture caracteristique menu in game");
    }

    SDL_Rect pos_caracteristique;
    pos_caracteristique.x = (*game->WINDOWWIDTH) - 410;
    pos_caracteristique.y = 100;
    pos_caracteristique.w = (*game->WINDOWWIDTH)*322/1200;
    pos_caracteristique.h = 50;
    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nouvelle partie" ----------------------------------------*/
    surf_sauvegarder = TTF_RenderText_Blended(game->police, "Sauvegarder", blanc);
    if(surf_sauvegarder == NULL){
        SDL_ExitWithError("probleme surface sauvegarder menu in game");
    }

    SDL_Texture* sauvegarder = SDL_CreateTextureFromSurface(game->render, surf_sauvegarder);
    if(sauvegarder == NULL){
        SDL_ExitWithError("probleme texture sauvegarder menu in game");
    }

    SDL_Rect pos_sauvegarder;
    pos_sauvegarder.x = (*game->WINDOWWIDTH) - 410;
    pos_sauvegarder.y = 175;
    pos_sauvegarder.w = (*game->WINDOWWIDTH)*236/1200;
    pos_sauvegarder.h = 50;
    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nouvelle partie" ----------------------------------------*/
    surf_options = TTF_RenderText_Blended(game->police, "Options", blanc);
    if(surf_options == NULL){
        SDL_ExitWithError("probleme surface options menu in game");
    }

    SDL_Texture* options = SDL_CreateTextureFromSurface(game->render, surf_options);
    if(options == NULL){
        SDL_ExitWithError("probleme texture options menu in game");
    }

    SDL_Rect pos_options;
    pos_options.x = (*game->WINDOWWIDTH) - 410;
    pos_options.y = 250;
    pos_options.w = (*game->WINDOWWIDTH)*150/1200;
    pos_options.h = 50;
    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nouvelle partie" ----------------------------------------*/
    surf_retourner_menu = TTF_RenderText_Blended(game->police, "Retourner au menu", blanc);
    if(surf_retourner_menu == NULL){
        SDL_ExitWithError("probleme surface retourner_menu menu in game");
    }

    SDL_Texture* retourner_menu = SDL_CreateTextureFromSurface(game->render, surf_retourner_menu);
    if(retourner_menu == NULL){
        SDL_ExitWithError("probleme texture retourner_menu menu in game");
    }

    SDL_Rect pos_retourner_menu;
    pos_retourner_menu.x = (*game->WINDOWWIDTH) - 410;
    pos_retourner_menu.y = 325;
    pos_retourner_menu.w = (*game->WINDOWWIDTH)*365/1200;
    pos_retourner_menu.h = 50;
    /*----------------------------------------------------------------------------*/

    /*---texture "cadre"--------------------------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_menu_in_game.bmp");
    if(surf_cadre == NULL){
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture* cadre = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if(cadre == NULL){
        SDL_ExitWithError("probleme texture nouvelle partie menu d'accueil");
    }

    SDL_Rect pos_cadre;
    pos_cadre.x = (*game->WINDOWWIDTH) - 435;
    pos_cadre.y = 0;
    pos_cadre.w = 435;
    pos_cadre.h = 400;
    /*------------------------------------------------------------------------------------*/

    /*---texture fond--------------------------------------------------------*/

    SDL_Texture* fond_cadre = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre.w, pos_cadre.h);
    if(fond_cadre == NULL){
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_fond_cadre;
    pos_fond_cadre.x = pos_cadre.x;
    pos_fond_cadre.y = pos_cadre.y;
    pos_fond_cadre.w = pos_cadre.w;
    pos_fond_cadre.h = pos_cadre.h;

    SDL_Rect rect_fond_cadre;
    rect_fond_cadre.x = (*game->WINDOWWIDTH)*12/1200;
    rect_fond_cadre.y = (*game->WINDOWHEIGHT)*12/675;
    rect_fond_cadre.w = pos_fond_cadre.w - 2*rect_fond_cadre.x;
    rect_fond_cadre.h = pos_fond_cadre.h - 2*rect_fond_cadre.y;

    SDL_SetRenderDrawColor(game->render,0,0,0, 200);
    SDL_SetRenderTarget(game->render,fond_cadre);
    SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre);
    SDL_SetRenderTarget(game->render,NULL);
    /*------------------------------------------------------------------------------------*/

    SDL_RenderClear(game->render);
    SDL_RenderCopy(game->render, town->texture, &town->tile_set, &pos_Wind_town);
    SDL_RenderCopy(game->render, character->texture, &character->mov, &pos_Wind_character);
    SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
    SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
    SDL_RenderCopy(game->render, inventaire, NULL, &pos_inventaire);
    SDL_RenderCopy(game->render, caracteristique, NULL, &pos_caracteristique);
    SDL_RenderCopy(game->render, sauvegarder, NULL, &pos_sauvegarder);
    SDL_RenderCopy(game->render, options, NULL, &pos_options);
    SDL_RenderCopy(game->render, retourner_menu, NULL, &pos_retourner_menu);
    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    while (menu && (*game->program_launch))
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                menu = SDL_FALSE;
                (*game->program_launch) = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                menu = SDL_FALSE;
            }

            /*--- End Event to Exit Program --------------------------------------*/


            /*--- Event pour selectionner ------------------------------------------*/

            if (keyState[SDL_SCANCODE_DOWN] && event.type == SDL_KEYDOWN){

            }

            if (keyState[SDL_SCANCODE_UP] && event.type == SDL_KEYDOWN){

            }

            /*--- End Event pour selectionner --------------------------------------*/

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN){

            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/
    SDL_FreeSurface(surf_cadre);
    SDL_FreeSurface(surf_inventaire);
    SDL_FreeSurface(surf_caracteristique);
    SDL_FreeSurface(surf_sauvegarder);
    SDL_FreeSurface(surf_options);
    SDL_FreeSurface(surf_retourner_menu);

    SDL_DestroyTexture(inventaire);
    SDL_DestroyTexture(caracteristique);
    SDL_DestroyTexture(sauvegarder);
    SDL_DestroyTexture(options);
    SDL_DestroyTexture(retourner_menu);
    SDL_DestroyTexture(cadre);
    SDL_DestroyTexture(fond_cadre);

    /*--- End Free Memory --------------------------------------------------------*/

}