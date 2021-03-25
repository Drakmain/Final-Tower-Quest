#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "charger_partie.h"

#include "character.h"


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
 * \fn void charger_partie_f(game_t * game, char * actual_save)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param actual_save A FINIR.
 *
 */

extern
void charger_partie_f(game_t * game, char * actual_save){


    /*--- Initialization variable ------------------------------------------------*/

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    SDL_Surface *surf_save1 = NULL, *surf_save1_vide = NULL, *surf_save2 = NULL, *surf_save2_vide = NULL, *surf_save3 = NULL, *surf_save3_vide = NULL, *surf_spriteGuerrier = NULL, *surf_spriteMage = NULL, *surf_spriteAssassin = NULL, *surf_nom_save_guerrier = NULL, *surf_nom_save_mage = NULL, *surf_nom_save_assassin = NULL, *surf_cadre = NULL, *surf_retour = NULL, *surf_fond = NULL, *surf_choisir_empla = NULL, *surf_position1 = NULL, *surf_lvl1 = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool char_part_bool = SDL_TRUE;

    SDL_Event event;

    int selection = 0;

    /*--- End Initialization variable --------------------------------------------*/

    /*--- Open save file ---------------------------------------------------------*/

    character_t * character_save1 = NULL;
    character_save1 = character_create(game->render, "save//save1.txt");
    if (character_save1 == NULL)
    {
        exit_with_error("Cannot create a character_t object > charger_partie.c Line 341");
    }
    else if (character_save1->empty == SDL_TRUE)
    {
        //Affichage sauvegarde vide
        printf("Save 1 vide\n");
    }
    else
    {
        printf("%s\n", character_save1->save_name);
    }


    character_t * character_save2 = NULL;
    character_save2 = character_create(game->render, "save//save2.txt");
    if (character_save2 == NULL)
    {
        exit_with_error("Cannot create a character_t object > charger_partie.c Line 337");
    }
    else if (character_save2->empty == SDL_TRUE)
    {
        //Affichage sauvegarde vide
        printf("Save 2 vide\n");
    }
    else
    {
        printf("%s\n", character_save2->save_name);
    }


    character_t * character_save3 = NULL;
    character_save3 = character_create(game->render, "save//save3.txt");
    if (character_save3 == NULL)
    {
        exit_with_error("Cannot create a character_t object > charger_partie.c Line 374");
    }
    else if (character_save3->empty == SDL_TRUE)
    {
        //Affichage sauvegarde vide
        printf("Save 3 vide\n\n");
    }
    else
    {
        printf("%s\n\n", character_save3->save_name);
    }

    /*----------------------------------------------------------------------------*/


    /*--- Creation text "choisissez emplacement a charger" -----------------------*/

    surf_choisir_empla = TTF_RenderText_Blended(game->police, "CHOISISSEZ EMPLACEMENT A CHARGER", blanc);
    if(surf_choisir_empla == NULL)
    {
        SDL_ExitWithError("probleme surface choisir emplacement a charger");
    }

    SDL_Texture* choisir_empla = SDL_CreateTextureFromSurface(game->render, surf_choisir_empla);
    if(choisir_empla == NULL)
    {
        SDL_ExitWithError("probleme texture choisir emplacement a charger");
    }

    SDL_Rect pos_choisir_empla;
    pos_choisir_empla.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)*337/1200;
    pos_choisir_empla.y = (*game->WINDOWHEIGHT)/30;
    pos_choisir_empla.w = (*game->WINDOWWIDTH)*673/1200;
    pos_choisir_empla.h = (*game->WINDOWHEIGHT)/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation text "retour" -------------------------------------------------*/

    surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
    if(surf_retour == NULL)
    {
        SDL_ExitWithError("probleme surface Retour");
    }
    SDL_Texture* retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
    if(retour == NULL)
    {
        SDL_ExitWithError("probleme texture Retour");
    }

    SDL_Rect pos_retour;
    pos_retour.x = (*game->WINDOWWIDTH)/20;
    pos_retour.y = (*game->WINDOWHEIGHT) - (*game->WINDOWHEIGHT)/8;
    pos_retour.w = (*game->WINDOWWIDTH)/(1200/129);
    pos_retour.h = (*game->WINDOWHEIGHT)/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture background --------------------------------------------*/

    surf_fond = SDL_LoadBMP("src\\image\\fond_menu_accueil.bmp");
    if(surf_fond == NULL)
    {
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture* fond = SDL_CreateTextureFromSurface(game->render, surf_fond);
    if(fond == NULL)
    {
        SDL_ExitWithError("probleme texture fond menu d'accueil");
    }

    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;
    pos_fond.w = (*game->WINDOWWIDTH);
    pos_fond.h = (*game->WINDOWHEIGHT);

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture "save 1" ----------------------------------------------*/

    surf_save1 = TTF_RenderText_Blended(game->police, "options", blanc);
    if(surf_save1 == NULL)
    {
        SDL_ExitWithError("probleme surface options");
    }
    SDL_Texture* save1 = SDL_CreateTextureFromSurface(game->render, surf_save1);
    if(save1 == NULL)
    {
        SDL_ExitWithError("probleme texture options");
    }

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture "save 2" ----------------------------------------------*/

    surf_save2 = TTF_RenderText_Blended(game->police, "options", blanc);
    if(surf_save2 == NULL)
    {
        SDL_ExitWithError("probleme surface options");
    }
    SDL_Texture* save2 = SDL_CreateTextureFromSurface(game->render, surf_save2);
    if(save2 == NULL)
    {
        SDL_ExitWithError("probleme texture options");
    }

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture "save 3" ----------------------------------------------*/

    surf_save3 = TTF_RenderText_Blended(game->police, "options", blanc);
    if(surf_save3 == NULL)
    {
        SDL_ExitWithError("probleme surface options");
    }
    SDL_Texture* save3 = SDL_CreateTextureFromSurface(game->render, surf_save3);
    if(save3 == NULL)
    {
        SDL_ExitWithError("probleme texture options");
    }

    /*----------------------------------------------------------------------------*/


    /*--- Loading texture "cadre choix emplacement" ------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_choix_emplacement.bmp");
    if(surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre");
    }

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "cadre save 1" ----------------------------------*/

    SDL_Texture* cadre_save1 = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if(cadre_save1 == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_save1");
    }

    SDL_Rect pos_cadre_save1;
    pos_cadre_save1.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15;
    pos_cadre_save1.y = (*game->WINDOWHEIGHT)/6.75;
    pos_cadre_save1.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30;
    pos_cadre_save1.h = (*game->WINDOWHEIGHT)/5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture background "cadre save 1" -----------------------------*/

    SDL_Texture* fond_cadre_save1 = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30, (*game->WINDOWHEIGHT)/5);
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
    rect_fond_cadre_save1.x = (*game->WINDOWWIDTH)*12/1200;
    rect_fond_cadre_save1.y = (*game->WINDOWHEIGHT)*12/675;
    rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2*rect_fond_cadre_save1.x;
    rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2*rect_fond_cadre_save1.y;

    SDL_SetRenderDrawColor(game->render,0,0,0, 200);
    SDL_SetRenderTarget(game->render, fond_cadre_save1);
    SDL_SetTextureBlendMode(fond_cadre_save1, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre_save1);
    SDL_SetRenderTarget(game->render,NULL);

    /*----------------------------------------------------------------------------*/

    /*--- Affichage save1 vide -----------------------------*/
    surf_save1_vide = TTF_RenderText_Blended(game->police, "Sauvegarde vide", blanc);
    if(surf_save1_vide == NULL){
        SDL_ExitWithError("Probleme surface save1_vide");
    }

    SDL_Texture * save1_vide = SDL_CreateTextureFromSurface(game ->render, surf_save1_vide);
    if(save1_vide == NULL){
        SDL_ExitWithError("Probleme texture save1_vide");
    }

    SDL_Rect pos_save1_vide;
    pos_save1_vide.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/8 - (*game->WINDOWWIDTH)/22;
    pos_save1_vide.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5.95;
    pos_save1_vide.w = (*game->WINDOWWIDTH)/(500/129);
    pos_save1_vide.h = (*game->WINDOWHEIGHT)/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "cadre save 2" ----------------------------------*/

    SDL_Texture* cadre_save2 = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if(cadre_save2 == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_save2");
    }

    SDL_Rect pos_cadre_save2;
    pos_cadre_save2.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15;
    pos_cadre_save2.y = (*game->WINDOWHEIGHT)/2.5;
    pos_cadre_save2.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30;
    pos_cadre_save2.h = (*game->WINDOWHEIGHT)/5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture background "cadre save 2" -----------------------------*/

    SDL_Texture* fond_cadre_save2 = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30, (*game->WINDOWHEIGHT)/5);
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
    rect_fond_cadre_save2.x = (*game->WINDOWWIDTH)*12/1200;
    rect_fond_cadre_save2.y = (*game->WINDOWHEIGHT)*12/675;
    rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2*rect_fond_cadre_save2.x;
    rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2*rect_fond_cadre_save2.y;

    SDL_SetRenderDrawColor(game->render,0,0,0, 200);
    SDL_SetRenderTarget(game->render,fond_cadre_save2);
    SDL_SetTextureBlendMode(fond_cadre_save2, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre_save2);
    SDL_SetRenderTarget(game->render,NULL);

    /*----------------------------------------------------------------------------*/

    /*--- Affichage save2 vide -----------------------------*/
    surf_save2_vide = TTF_RenderText_Blended(game->police, "Sauvegarde vide", blanc);
    if(surf_save2_vide == NULL){
        SDL_ExitWithError("Probleme surface save2_vide");
    }

    SDL_Texture * save2_vide = SDL_CreateTextureFromSurface(game ->render, surf_save2_vide);
    if(save2_vide == NULL){
        SDL_ExitWithError("Probleme texture save2_vide");
    }

    SDL_Rect pos_save2_vide;
    pos_save2_vide.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/8 - (*game->WINDOWWIDTH)/22;
    pos_save2_vide.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/33;
    pos_save2_vide.w = (*game->WINDOWWIDTH)/(500/129);
    pos_save2_vide.h = (*game->WINDOWHEIGHT)/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "cadre save 3" ----------------------------------*/

    SDL_Texture* cadre_save3 = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if(cadre_save3 == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_save3");
    }

    SDL_Rect pos_cadre_save3;
    pos_cadre_save3.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15;
    pos_cadre_save3.y = (*game->WINDOWHEIGHT)*440/675;
    pos_cadre_save3.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30;
    pos_cadre_save3.h = (*game->WINDOWHEIGHT)/5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture background "cadre save 3" -----------------------------*/

    SDL_Texture* fond_cadre_save3 = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30, (*game->WINDOWHEIGHT)/5);
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
    rect_fond_cadre_save3.x = (*game->WINDOWWIDTH)*12/1200;
    rect_fond_cadre_save3.y = (*game->WINDOWHEIGHT)*12/675;
    rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2*rect_fond_cadre_save3.x;
    rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2*rect_fond_cadre_save3.y;

    SDL_SetRenderDrawColor(game->render,0,0,0, 200);
    SDL_SetRenderTarget(game->render,fond_cadre_save3);
    SDL_SetTextureBlendMode(fond_cadre_save3, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre_save3);
    SDL_SetRenderTarget(game->render,NULL);

    /*----------------------------------------------------------------------------*/

    /*--- Affichage save3 vide -----------------------------*/
    surf_save3_vide = TTF_RenderText_Blended(game->police, "Sauvegarde vide", blanc);
    if(surf_save3_vide == NULL){
        SDL_ExitWithError("Probleme surface save3_vide");
    }

    SDL_Texture * save3_vide = SDL_CreateTextureFromSurface(game ->render, surf_save3_vide);
    if(save3_vide == NULL){
        SDL_ExitWithError("Probleme texture save3_vide");
    }

    SDL_Rect pos_save3_vide;
    pos_save3_vide.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/8 - (*game->WINDOWWIDTH)/22;
    pos_save3_vide.y = (*game->WINDOWHEIGHT)/1.38 - (*game->WINDOWWIDTH)/80;
    pos_save3_vide.w = (*game->WINDOWWIDTH)/(500/129);
    pos_save3_vide.h = (*game->WINDOWHEIGHT)/13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Initialization texture "Guerrier" --------------------------------------*/

    surf_spriteGuerrier = SDL_LoadBMP("src\\tileset\\PJ\\guerrier_frame.bmp");
    SDL_SetColorKey(surf_spriteGuerrier, SDL_TRUE, SDL_MapRGB(surf_spriteGuerrier->format, 255,255,255));
    if(surf_spriteGuerrier == NULL)
    {
        SDL_ExitWithError("probleme chargement sprite du guerrier");
    }

    SDL_Texture* spriteGuerrier = SDL_CreateTextureFromSurface(game->render, surf_spriteGuerrier);
    if(spriteGuerrier == NULL)
    {
        SDL_ExitWithError("probleme texture sprite du guerrier");
    }

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "Mage" ------------------------------------------*/

    surf_spriteMage = SDL_LoadBMP("src\\tileset\\PJ\\mage_frame.bmp");
    SDL_SetColorKey(surf_spriteMage, SDL_TRUE, SDL_MapRGB(surf_spriteMage->format, 255,255,255));
    if(surf_spriteMage == NULL)
    {
        SDL_ExitWithError("probleme chargement sprite du mage");
    }

    SDL_Texture* spriteMage = SDL_CreateTextureFromSurface(game->render, surf_spriteMage);
    if(spriteMage == NULL)
    {
        SDL_ExitWithError("probleme texture sprite du mage");
    }

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "Assassin" --------------------------------------*/

    surf_spriteAssassin = SDL_LoadBMP("src\\tileset\\PJ\\assassin_frame.bmp");
    SDL_SetColorKey(surf_spriteAssassin, SDL_TRUE, SDL_MapRGB(surf_spriteAssassin->format, 255,255,255));
    if(surf_spriteAssassin == NULL)
    {
        SDL_ExitWithError("probleme chargement sprite du assassin");
    }

    SDL_Texture* spriteAssassin = SDL_CreateTextureFromSurface(game->render, surf_spriteAssassin);
    if(spriteAssassin == NULL)
    {
        SDL_ExitWithError("probleme texture sprite du assassin");
    }

    /*----------------------------------------------------------------------------*/

    /*---Affichage nom save guerrier-------------------------------------------------------*/
    surf_nom_save_guerrier = TTF_RenderText_Blended(game->police, "Guerrier", blanc);
    if(surf_nom_save_guerrier == NULL){
        SDL_ExitWithError("Probleme surface nom save_guerrier");
    }

    SDL_Texture * nom_save_guerrier = SDL_CreateTextureFromSurface(game->render, surf_nom_save_guerrier);
    if(nom_save_guerrier == NULL){
        SDL_ExitWithError("Probleme texture nom save_guerrier");
    }
    /*---End Affichage nom save guerrier---------------------------------------------------*/

    /*---Affichage nom save mage-------------------------------------------------------*/
    surf_nom_save_mage = TTF_RenderText_Blended(game->police, "Mage", blanc);
    if(surf_nom_save_mage == NULL){
        SDL_ExitWithError("Probleme surface nom save mage");
    }

    SDL_Texture * nom_save_mage = SDL_CreateTextureFromSurface(game->render, surf_nom_save_mage);
    if(nom_save_mage == NULL){
        SDL_ExitWithError("Probleme texture nom save mage");
    }

    /*---End Affichage nom save mage---------------------------------------------------*/

    /*---Affichage nom save assassin-------------------------------------------------------*/
    surf_nom_save_assassin = TTF_RenderText_Blended(game->police, "Assassin", blanc);
    if(surf_nom_save_assassin == NULL){
        SDL_ExitWithError("Probleme surface nom save assassin");
    }

    SDL_Texture * nom_save_assassin = SDL_CreateTextureFromSurface(game->render, surf_nom_save_assassin);
    if(nom_save_assassin == NULL){
        SDL_ExitWithError("Probleme texture nom save assassin");
    }


    /*---End Affichage nom save assassin---------------------------------------------------*/


    /*---Affichage position save--------------------------------------------------*/
    surf_position1 = TTF_RenderText_Blended(game->police, "Position : ", blanc);
    if(surf_position1 == NULL)
    {
        SDL_ExitWithError("probleme surface position");
    }
    SDL_Texture* position1 = SDL_CreateTextureFromSurface(game->render, surf_position1);
    if(retour == NULL)
    {
        SDL_ExitWithError("probleme texture position");
    }




    /*---End Affichage position save----------------------------------------------*/


    /*---Affichage lvl save-------------------------------------------------------*/

    surf_lvl1 = TTF_RenderText_Blended(game->police, "LVL : ", blanc);
    if(surf_lvl1 == NULL)
    {
        SDL_ExitWithError("probleme surface niveau");
    }
    SDL_Texture* lvl1 = SDL_CreateTextureFromSurface(game->render, surf_lvl1);
    if(retour == NULL)
    {
        SDL_ExitWithError("probleme texture niveau");
    }



    /*---End Affichage lvl save---------------------------------------------------*/





    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
    SDL_RenderCopy(game->render, choisir_empla, NULL, &pos_choisir_empla);
    SDL_RenderCopy(game->render, retour, NULL, &pos_retour);
    SDL_RenderCopy(game->render, fond_cadre_save1, NULL, &pos_fond_cadre_save1);
    SDL_RenderCopy(game->render, fond_cadre_save1, NULL, &pos_fond_cadre_save2);
    SDL_RenderCopy(game->render, fond_cadre_save1, NULL, &pos_fond_cadre_save3);
    SDL_RenderCopy(game->render, cadre_save1, NULL, &pos_cadre_save1);
    SDL_RenderCopy(game->render, cadre_save1, NULL, &pos_cadre_save2);
    SDL_RenderCopy(game->render, cadre_save1, NULL, &pos_cadre_save3);

    SDL_RenderPresent(game->render);


    /*--- Main Loop --------------------------------------------------------------*/

    while (char_part_bool && *game->program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                *game->program_launch = SDL_FALSE;
                char_part_bool = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                char_part_bool = SDL_FALSE;
            }

            /*--- End Event to Exit Program --------------------------------------*/


            /*--- Event pour selectionner ------------------------------------------*/

            if (keyState[SDL_SCANCODE_DOWN] && event.type == SDL_KEYDOWN)
            {
                selection++;
            }

            if (keyState[SDL_SCANCODE_UP] && event.type == SDL_KEYDOWN)
            {
                selection--;
            }

            /*--- End Event pour selectionner --------------------------------------*/


            if(selection < 0)selection = 3;
            selection %= 4;

            if(selection == 0)
            {
                pos_cadre_save2.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15;
                pos_cadre_save2.y = (*game->WINDOWHEIGHT)/2.5;
                pos_cadre_save2.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30;
                pos_cadre_save2.h = (*game->WINDOWHEIGHT)/5;
                pos_fond_cadre_save2.x = pos_cadre_save2.x;
                pos_fond_cadre_save2.y = pos_cadre_save2.y;
                pos_fond_cadre_save2.w = pos_cadre_save2.w;
                pos_fond_cadre_save2.h = pos_cadre_save2.h;
                rect_fond_cadre_save2.x = (*game->WINDOWWIDTH)*12/1200;
                rect_fond_cadre_save2.y = (*game->WINDOWHEIGHT)*12/675;
                rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2*rect_fond_cadre_save2.x;
                rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2*rect_fond_cadre_save2.y;

                pos_cadre_save1.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15 - (*game->WINDOWWIDTH)/120;
                pos_cadre_save1.y = (*game->WINDOWHEIGHT)/6.75 - (*game->WINDOWHEIGHT)/67.5;
                pos_cadre_save1.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30 + (*game->WINDOWWIDTH)/60;
                pos_cadre_save1.h = (*game->WINDOWHEIGHT)/5 + (*game->WINDOWHEIGHT)/33.75;
                pos_fond_cadre_save1.x = pos_cadre_save1.x;
                pos_fond_cadre_save1.y = pos_cadre_save1.y;
                pos_fond_cadre_save1.w = pos_cadre_save1.w;
                pos_fond_cadre_save1.h = pos_cadre_save1.h;
                rect_fond_cadre_save1.x = (*game->WINDOWWIDTH)*12/1200;
                rect_fond_cadre_save1.y = (*game->WINDOWHEIGHT)*12/675;
                rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2*rect_fond_cadre_save1.x;
                rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2*rect_fond_cadre_save1.y;

                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
                retour = SDL_CreateTextureFromSurface(game->render, surf_retour);

            }

            if(selection == 1)
            {
                pos_cadre_save3.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15;
                pos_cadre_save3.y = (*game->WINDOWHEIGHT)*440/675;
                pos_cadre_save3.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30;
                pos_cadre_save3.h = (*game->WINDOWHEIGHT)/5;
                pos_fond_cadre_save3.x = pos_cadre_save3.x;
                pos_fond_cadre_save3.y = pos_cadre_save3.y;
                pos_fond_cadre_save3.w = pos_cadre_save3.w;
                pos_fond_cadre_save3.h = pos_cadre_save3.h;
                rect_fond_cadre_save3.x = (*game->WINDOWWIDTH)*12/1200;
                rect_fond_cadre_save3.y = (*game->WINDOWHEIGHT)*12/675;
                rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2*rect_fond_cadre_save3.x;
                rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2*rect_fond_cadre_save3.y;

                pos_cadre_save1.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15;
                pos_cadre_save1.y = (*game->WINDOWHEIGHT)/6.75;
                pos_cadre_save1.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30;
                pos_cadre_save1.h = (*game->WINDOWHEIGHT)/5;
                pos_fond_cadre_save1.x = pos_cadre_save1.x;
                pos_fond_cadre_save1.y = pos_cadre_save1.y;
                pos_fond_cadre_save1.w = pos_cadre_save1.w;
                pos_fond_cadre_save1.h = pos_cadre_save1.h;
                rect_fond_cadre_save1.x = (*game->WINDOWWIDTH)*12/1200;
                rect_fond_cadre_save1.y = (*game->WINDOWHEIGHT)*12/675;
                rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2*rect_fond_cadre_save1.x;
                rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2*rect_fond_cadre_save1.y;

                pos_cadre_save2.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15 - (*game->WINDOWWIDTH)/120;
                pos_cadre_save2.y = (*game->WINDOWHEIGHT)/2.5 - (*game->WINDOWHEIGHT)/67.5;
                pos_cadre_save2.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30 + (*game->WINDOWWIDTH)/60;
                pos_cadre_save2.h = (*game->WINDOWHEIGHT)/5 + (*game->WINDOWHEIGHT)/33.75;
                pos_fond_cadre_save2.x = pos_cadre_save2.x;
                pos_fond_cadre_save2.y = pos_cadre_save2.y;
                pos_fond_cadre_save2.w = pos_cadre_save2.w;
                pos_fond_cadre_save2.h = pos_cadre_save2.h;
                rect_fond_cadre_save2.x = (*game->WINDOWWIDTH)*12/1200;
                rect_fond_cadre_save2.y = (*game->WINDOWHEIGHT)*12/675;
                rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2*rect_fond_cadre_save2.x;
                rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2*rect_fond_cadre_save2.y;

            }

            if(selection == 2)
            {
                pos_cadre_save2.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15;
                pos_cadre_save2.y = (*game->WINDOWHEIGHT)/2.5;
                pos_cadre_save2.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30;
                pos_cadre_save2.h = (*game->WINDOWHEIGHT)/5;
                pos_fond_cadre_save2.x = pos_cadre_save2.x;
                pos_fond_cadre_save2.y = pos_cadre_save2.y;
                pos_fond_cadre_save2.w = pos_cadre_save2.w;
                pos_fond_cadre_save2.h = pos_cadre_save2.h;
                rect_fond_cadre_save2.x = (*game->WINDOWWIDTH)*12/1200;
                rect_fond_cadre_save2.y = (*game->WINDOWHEIGHT)*12/675;
                rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2*rect_fond_cadre_save2.x;
                rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2*rect_fond_cadre_save2.y;

                pos_cadre_save3.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15 - (*game->WINDOWWIDTH)/120;
                pos_cadre_save3.y = (*game->WINDOWHEIGHT)*440/675 - (*game->WINDOWHEIGHT)/67.5;
                pos_cadre_save3.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30 + (*game->WINDOWWIDTH)/60;
                pos_cadre_save3.h = (*game->WINDOWHEIGHT)/5 + (*game->WINDOWHEIGHT)/33.75;
                pos_fond_cadre_save3.x = pos_cadre_save3.x;
                pos_fond_cadre_save3.y = pos_cadre_save3.y;
                pos_fond_cadre_save3.w = pos_cadre_save3.w;
                pos_fond_cadre_save3.h = pos_cadre_save3.h;
                rect_fond_cadre_save3.x = (*game->WINDOWWIDTH)*12/1200;
                rect_fond_cadre_save3.y = (*game->WINDOWHEIGHT)*12/675;
                rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2*rect_fond_cadre_save3.x;
                rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2*rect_fond_cadre_save3.y;

                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
                retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
            }

            if(selection == 3)
            {
                pos_cadre_save1.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15;
                pos_cadre_save1.y = (*game->WINDOWHEIGHT)/6.75;
                pos_cadre_save1.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30;
                pos_cadre_save1.h = (*game->WINDOWHEIGHT)/5;
                pos_fond_cadre_save1.x = pos_cadre_save1.x;
                pos_fond_cadre_save1.y = pos_cadre_save1.y;
                pos_fond_cadre_save1.w = pos_cadre_save1.w;
                pos_fond_cadre_save1.h = pos_cadre_save1.h;
                rect_fond_cadre_save1.x = (*game->WINDOWWIDTH)*12/1200;
                rect_fond_cadre_save1.y = (*game->WINDOWHEIGHT)*12/675;
                rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2*rect_fond_cadre_save1.x;
                rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2*rect_fond_cadre_save1.y;

                pos_cadre_save3.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/15;
                pos_cadre_save3.y = (*game->WINDOWHEIGHT)*440/675;
                pos_cadre_save3.w = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/30;
                pos_cadre_save3.h = (*game->WINDOWHEIGHT)/5;
                pos_fond_cadre_save3.x = pos_cadre_save3.x;
                pos_fond_cadre_save3.y = pos_cadre_save3.y;
                pos_fond_cadre_save3.w = pos_cadre_save3.w;
                pos_fond_cadre_save3.h = pos_cadre_save3.h;
                rect_fond_cadre_save3.x = (*game->WINDOWWIDTH)*12/1200;
                rect_fond_cadre_save3.y = (*game->WINDOWHEIGHT)*12/675;
                rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2*rect_fond_cadre_save3.x;
                rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2*rect_fond_cadre_save3.y;

                surf_retour = TTF_RenderText_Blended(game->police, "Retour", rouge);
                retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
            }

            SDL_RenderClear(game->render);

            SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
            SDL_RenderCopy(game->render, choisir_empla, NULL, &pos_choisir_empla);
            SDL_RenderCopy(game->render, retour, NULL, &pos_retour);
            SDL_RenderCopy(game->render, fond_cadre_save1, NULL, &pos_fond_cadre_save1);
            SDL_RenderCopy(game->render, fond_cadre_save1, NULL, &pos_fond_cadre_save2);
            SDL_RenderCopy(game->render, fond_cadre_save1, NULL, &pos_fond_cadre_save3);
            SDL_RenderCopy(game->render, cadre_save1, NULL, &pos_cadre_save1);
            SDL_RenderCopy(game->render, cadre_save1, NULL, &pos_cadre_save2);
            SDL_RenderCopy(game->render, cadre_save1, NULL, &pos_cadre_save3);

            if (character_save1->empty == SDL_TRUE)
            {
                //Affichage sauvegarde vide
                printf("Save 1 vide\n");
                SDL_RenderCopy(game->render, save1_vide, NULL, &pos_save1_vide);
            }

            else
            {

                SDL_Rect pos_position1;
                pos_position1.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/13 - (*game->WINDOWWIDTH)/14;
                pos_position1.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/7;
                pos_position1.w = (*game->WINDOWWIDTH)/9;
                pos_position1.h = (*game->WINDOWHEIGHT)/14;
                SDL_RenderCopy(game->render, position1, NULL, &pos_position1);

                SDL_Rect pos_lvl1;
                pos_lvl1.x = (*game->WINDOWWIDTH)/1.6 - (*game->WINDOWWIDTH)/50;
                pos_lvl1.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/7.19;
                pos_lvl1.w = (*game->WINDOWWIDTH)/14;
                pos_lvl1.h = (*game->WINDOWHEIGHT)/16;
                SDL_RenderCopy(game->render, lvl1, NULL, &pos_lvl1);

                if(strcmp(character_save1->charactere_name, "Guerrier") == 0) {
                    SDL_Rect pos_spriteGuerrier;
                    pos_spriteGuerrier.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/18;
                    pos_spriteGuerrier.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5.4;
                    pos_spriteGuerrier.w = (*game->WINDOWWIDTH) * 66.5 /1200;
                    pos_spriteGuerrier.h = (*game->WINDOWHEIGHT) * 105 /675;
                    SDL_RenderCopy(game->render, spriteGuerrier, NULL, &pos_spriteGuerrier);

                    SDL_Rect pos_nom_save_guerrier;
                    pos_nom_save_guerrier.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/29 - (*game->WINDOWWIDTH)/29;
                    pos_nom_save_guerrier.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5.3;
                    pos_nom_save_guerrier.w = (*game->WINDOWWIDTH)/7;
                    pos_nom_save_guerrier.h = (*game->WINDOWHEIGHT)/13.5;
                    SDL_RenderCopy(game->render, nom_save_guerrier, NULL, &pos_nom_save_guerrier);

                }
                else if(strcmp(character_save1->charactere_name, "Mage") == 0) {
                    SDL_Rect pos_spriteMage;
                    pos_spriteMage.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/18;
                    pos_spriteMage.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5.4;
                    pos_spriteMage.w = (*game->WINDOWWIDTH) * 49 /1200;
                    pos_spriteMage.h = (*game->WINDOWHEIGHT) * 108.5 /675;
                    SDL_RenderCopy(game->render, spriteMage, NULL, &pos_spriteMage);

                    SDL_Rect pos_nom_save_mage;
                    pos_nom_save_mage.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/22;
                    pos_nom_save_mage.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5.3;
                    pos_nom_save_mage.w = (*game->WINDOWWIDTH)/11;
                    pos_nom_save_mage.h = (*game->WINDOWHEIGHT)/13.5;
                    SDL_RenderCopy(game->render, nom_save_mage, NULL, &pos_nom_save_mage);

                }
                else if(strcmp(character_save1->charactere_name, "Assassin") == 0) {
                    SDL_Rect pos_spriteAssassin;
                    pos_spriteAssassin.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/18;
                    pos_spriteAssassin.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5.4;
                    pos_spriteAssassin.w = (*game->WINDOWWIDTH) * 63 /1200;
                    pos_spriteAssassin.h = (*game->WINDOWHEIGHT) * 105 /675;
                    SDL_RenderCopy(game->render, spriteAssassin, NULL, &pos_spriteAssassin);

                    SDL_Rect pos_nom_save_assassin;
                    pos_nom_save_assassin.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/29 - (*game->WINDOWWIDTH)/29;
                    pos_nom_save_assassin.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5.3;
                    pos_nom_save_assassin.w = (*game->WINDOWWIDTH)/7;
                    pos_nom_save_assassin.h = (*game->WINDOWHEIGHT)/13.5;
                    SDL_RenderCopy(game->render, nom_save_assassin, NULL, &pos_nom_save_assassin);
                }
            }

            if (character_save2->empty == SDL_TRUE)
            {
                //Affichage sauvegarde vide
                printf("Save 2 vide\n");
                SDL_RenderCopy(game->render, save2_vide, NULL, &pos_save2_vide);
            }

            else
            {

                SDL_Rect pos_position1;
                pos_position1.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/13 - (*game->WINDOWWIDTH)/14;
                pos_position1.y = (*game->WINDOWHEIGHT)/1.87 - (*game->WINDOWWIDTH)/50;
                pos_position1.w = (*game->WINDOWWIDTH)/9;
                pos_position1.h = (*game->WINDOWHEIGHT)/14;
                SDL_RenderCopy(game->render, position1, NULL, &pos_position1);

                SDL_Rect pos_lvl1;
                pos_lvl1.x = (*game->WINDOWWIDTH)/1.6 - (*game->WINDOWWIDTH)/50;
                pos_lvl1.y = (*game->WINDOWHEIGHT)/1.86 - (*game->WINDOWWIDTH)/50;
                pos_lvl1.w = (*game->WINDOWWIDTH)/14;
                pos_lvl1.h = (*game->WINDOWHEIGHT)/16;
                SDL_RenderCopy(game->render, lvl1, NULL, &pos_lvl1);

                if(strcmp(character_save2->charactere_name, "Guerrier") == 0) {
                    SDL_Rect pos_spriteGuerrier;
                    pos_spriteGuerrier.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/18;
                    pos_spriteGuerrier.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/22.7;
                    pos_spriteGuerrier.w = (*game->WINDOWWIDTH) * 66.5 /1200;
                    pos_spriteGuerrier.h = (*game->WINDOWHEIGHT) * 105 /675;
                    SDL_RenderCopy(game->render, spriteGuerrier, NULL, &pos_spriteGuerrier);

                    SDL_Rect pos_nom_save_guerrier;
                    pos_nom_save_guerrier.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/29 - (*game->WINDOWWIDTH)/29;
                    pos_nom_save_guerrier.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/22.7;
                    pos_nom_save_guerrier.w = (*game->WINDOWWIDTH)/7;
                    pos_nom_save_guerrier.h = (*game->WINDOWHEIGHT)/13.5;
                    SDL_RenderCopy(game->render, nom_save_guerrier, NULL, &pos_nom_save_guerrier);
                }
                else if(strcmp(character_save2->charactere_name, "Mage") == 0) {
                    SDL_Rect pos_spriteMage;
                    pos_spriteMage.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/18;
                    pos_spriteMage.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/22.7;
                    pos_spriteMage.w = (*game->WINDOWWIDTH) * 49 /1200;
                    pos_spriteMage.h = (*game->WINDOWHEIGHT) * 108.5 /675;
                    SDL_RenderCopy(game->render, spriteMage, NULL, &pos_spriteMage);

                    SDL_Rect pos_nom_save_mage;
                    pos_nom_save_mage.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/22;
                    pos_nom_save_mage.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/22.7;
                    pos_nom_save_mage.w = (*game->WINDOWWIDTH)/11;
                    pos_nom_save_mage.h = (*game->WINDOWHEIGHT)/13.5;
                    SDL_RenderCopy(game->render, nom_save_mage, NULL, &pos_nom_save_mage);
                }
                else if(strcmp(character_save2->charactere_name, "Assassin") == 0) {
                    SDL_Rect pos_spriteAssassin;
                    pos_spriteAssassin.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/18;
                    pos_spriteAssassin.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/22.6;
                    pos_spriteAssassin.w = (*game->WINDOWWIDTH) * 63 /1200;
                    pos_spriteAssassin.h = (*game->WINDOWHEIGHT) * 105 /675;
                    SDL_RenderCopy(game->render, spriteAssassin, NULL, &pos_spriteAssassin);

                    SDL_Rect pos_nom_save_assassin;
                    pos_nom_save_assassin.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/29 - (*game->WINDOWWIDTH)/29;
                    pos_nom_save_assassin.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/22.7;
                    pos_nom_save_assassin.w = (*game->WINDOWWIDTH)/7;
                    pos_nom_save_assassin.h = (*game->WINDOWHEIGHT)/13.5;
                    SDL_RenderCopy(game->render, nom_save_assassin, NULL, &pos_nom_save_assassin);

                }
            }

            if (character_save3->empty == SDL_TRUE)
            {
                //Affichage sauvegarde vide
                printf("Save 3 vide\n");
                SDL_RenderCopy(game->render, save3_vide, NULL, &pos_save3_vide);
            }

            else
            {

                SDL_Rect pos_position1;
                pos_position1.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/13 - (*game->WINDOWWIDTH)/14;
                pos_position1.y = (*game->WINDOWHEIGHT)/1.28 - (*game->WINDOWWIDTH)/50;
                pos_position1.w = (*game->WINDOWWIDTH)/9;
                pos_position1.h = (*game->WINDOWHEIGHT)/14;
                SDL_RenderCopy(game->render, position1, NULL, &pos_position1);

                SDL_Rect pos_lvl1;
                pos_lvl1.x = (*game->WINDOWWIDTH)/1.6 - (*game->WINDOWWIDTH)/50;
                pos_lvl1.y = (*game->WINDOWHEIGHT)/1.27 - (*game->WINDOWWIDTH)/50;
                pos_lvl1.w = (*game->WINDOWWIDTH)/14;
                pos_lvl1.h = (*game->WINDOWHEIGHT)/16;
                SDL_RenderCopy(game->render, lvl1, NULL, &pos_lvl1);

                if(strcmp(character_save3->charactere_name, "Guerrier") == 0) {
                    SDL_Rect pos_spriteGuerrier;
                    pos_spriteGuerrier.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/18;
                    pos_spriteGuerrier.y = (*game->WINDOWHEIGHT)/1.33 - (*game->WINDOWWIDTH)/22.7;
                    pos_spriteGuerrier.w = (*game->WINDOWWIDTH) * 66.5 /1200;
                    pos_spriteGuerrier.h = (*game->WINDOWHEIGHT) * 105 /675;
                    SDL_RenderCopy(game->render, spriteGuerrier, NULL, &pos_spriteGuerrier);

                    SDL_Rect pos_nom_save_guerrier;
                    pos_nom_save_guerrier.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/29 - (*game->WINDOWWIDTH)/29;
                    pos_nom_save_guerrier.y = (*game->WINDOWHEIGHT)/1.33 - (*game->WINDOWWIDTH)/22.7;
                    pos_nom_save_guerrier.w = (*game->WINDOWWIDTH)/7;
                    pos_nom_save_guerrier.h = (*game->WINDOWHEIGHT)/13.5;
                    SDL_RenderCopy(game->render, nom_save_guerrier, NULL, &pos_nom_save_guerrier);

                }
                else if(strcmp(character_save3->charactere_name, "Mage") == 0) {
                    SDL_Rect pos_spriteMage;
                    pos_spriteMage.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/18;
                    pos_spriteMage.y = (*game->WINDOWHEIGHT)/1.33 - (*game->WINDOWWIDTH)/22.7;
                    pos_spriteMage.w = (*game->WINDOWWIDTH) * 49 /1200;
                    pos_spriteMage.h = (*game->WINDOWHEIGHT) * 108.5 /675;
                    SDL_RenderCopy(game->render, spriteMage, NULL, &pos_spriteMage);

                    SDL_Rect pos_nom_save_mage;
                    pos_nom_save_mage.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/22;
                    pos_nom_save_mage.y = (*game->WINDOWHEIGHT)/1.33 - (*game->WINDOWWIDTH)/22.7;
                    pos_nom_save_mage.w = (*game->WINDOWWIDTH)/11;
                    pos_nom_save_mage.h = (*game->WINDOWHEIGHT)/13.5;
                    SDL_RenderCopy(game->render, nom_save_mage, NULL, &pos_nom_save_mage);

                }
                else if(strcmp(character_save3->charactere_name, "Assassin") == 0) {
                    SDL_Rect pos_spriteAssassin;
                    pos_spriteAssassin.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/6 - (*game->WINDOWWIDTH)/18;
                    pos_spriteAssassin.y = (*game->WINDOWHEIGHT)/1.33 - (*game->WINDOWWIDTH)/22.7;
                    pos_spriteAssassin.w = (*game->WINDOWWIDTH) * 63 /1200;
                    pos_spriteAssassin.h = (*game->WINDOWHEIGHT) * 105 /675;
                    SDL_RenderCopy(game->render, spriteAssassin, NULL, &pos_spriteAssassin);

                    SDL_Rect pos_nom_save_assassin;
                    pos_nom_save_assassin.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/29 - (*game->WINDOWWIDTH)/29;
                    pos_nom_save_assassin.y = (*game->WINDOWHEIGHT)/1.33 - (*game->WINDOWWIDTH)/22.7;
                    pos_nom_save_assassin.w = (*game->WINDOWWIDTH)/7;
                    pos_nom_save_assassin.h = (*game->WINDOWHEIGHT)/13.5;
                    SDL_RenderCopy(game->render, nom_save_assassin, NULL, &pos_nom_save_assassin);

                }
            }

            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {

                if(selection == 0)
                {
                    strcpy(actual_save, "save//save1.txt");
                    char_part_bool = SDL_FALSE;
                }

                if(selection == 1)
                {
                    strcpy(actual_save, "save//save2.txt");
                    char_part_bool = SDL_FALSE;
                }

                if(selection == 2)
                {
                    strcpy(actual_save, "save//save3.txt");
                    char_part_bool = SDL_FALSE;
                }

                if(selection == 3)
                {
                    strcpy(actual_save, "\0");
                    char_part_bool = SDL_FALSE;
                }

            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/
/*
    character_save1->free(&character_save1);
    character_save2->free(&character_save2);
    character_save3->free(&character_save3);
*/
    SDL_FreeSurface(surf_choisir_empla);
    SDL_FreeSurface(surf_retour);
    SDL_FreeSurface(surf_fond);
    SDL_FreeSurface(surf_cadre);
    SDL_FreeSurface(surf_save1);
    SDL_FreeSurface(surf_save2);
    SDL_FreeSurface(surf_save3);
    SDL_FreeSurface(surf_save1_vide);
    SDL_FreeSurface(surf_save2_vide);
    SDL_FreeSurface(surf_save3_vide);

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

}
