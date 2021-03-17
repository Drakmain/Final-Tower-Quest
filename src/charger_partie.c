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

    SDL_Surface *surf_save1 = NULL, *surf_save2 = NULL, *surf_save3 = NULL, *surf_cadre = NULL, *surf_retour = NULL, *surf_fond = NULL, *surf_choisir_empla = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool char_part_bool = SDL_TRUE;

    SDL_Event event;

    int selection = 0;

    /*--- End Initialization variable --------------------------------------------*/


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

    character_save1->free(&character_save1);
    character_save2->free(&character_save2);
    character_save3->free(&character_save3);

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

}
