#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\nouvelle_partie.h"

#include "..\lib\texte_confirmation.h"
#include "..\lib\creation_perso.h"
#include "..\lib\character.h"
#include "..\lib\character_attacks.h"

/*!
 *
 * \file nouvelle_partie.c
 * \brief Gestion des nouvelles partie.
 * \author Jeremy BOURGOUIN, Alexis BOUFFARD.
 *
 */

/*!
 *
 * \fn nouvelle_partie_f(game_t *game, char *actual_save)
 * \brief Fonction qui permet la création d'une nouvelle partie.
 *
 * \param game est un pointeur sur l'objet game_t du jeu.
 * \param actual_save représente le fichier initialisé lorsque le joueur sélectionne le personnage.
 */

extern void nouvelle_partie_f(game_t *game, char *actual_save)
{
    /*--- Initialization variable ----------------------------------------------------*/

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};

    SDL_Surface *surf_save1_vide = NULL, *surf_save2_vide = NULL, *surf_save3_vide = NULL, *surf_save1 = NULL, *surf_save2 = NULL, *surf_save3 = NULL, *surf_spriteGuerrier = NULL, *surf_spriteMage = NULL, *surf_spriteAssassin = NULL, *surf_nom_save1 = NULL, *surf_nom_save2 = NULL, *surf_nom_save3 = NULL, *surf_cadre = NULL, *surf_retour = NULL, *surf_fond = NULL, *surf_choisir_empla = NULL, *surf_position = NULL, *surf_position_save1 = NULL, *surf_position_save2 = NULL, *surf_position_save3 = NULL, *surf_lvl = NULL, *surf_lvl_save1 = NULL, *surf_lvl_save2 = NULL, *surf_lvl_save3 = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool nouv_part_bool = SDL_TRUE;

    SDL_Event event;

    int selection = 0;

    char *temp = malloc(sizeof(char) * 20);

    /*--- End Initialization variable --------------------------------------------*/

    /*--- Open save file ---------------------------------------------------------*/

    character_t *character_save1 = NULL;
    character_save1 = character_create(game->render, "save//save1.txt");
    if (character_save1 == NULL)
    {
        exit_with_error("Cannot create a character_t object > nouvelle_partie.c Line 341");
    }

    character_t *character_save2 = NULL;
    character_save2 = character_create(game->render, "save//save2.txt");
    if (character_save2 == NULL)
    {
        exit_with_error("Cannot create a character_t object > nouvelle_partie.c Line 337");
    }

    character_t *character_save3 = NULL;
    character_save3 = character_create(game->render, "save//save3.txt");
    if (character_save3 == NULL)
    {
        exit_with_error("Cannot create a character_t object > nouvelle_partie.c Line 374");
    }

    /*----------------------------------------------------------------------------*/

    /*--- Affichage save1 vide -----------------------------*/

    surf_save1_vide = TTF_RenderText_Blended(game->police, "Sauvegarde vide", blanc);
    if (surf_save1_vide == NULL)
    {
        SDL_ExitWithError("Probleme surface save1_vide");
    }

    SDL_Texture *save1_vide = SDL_CreateTextureFromSurface(game->render, surf_save1_vide);
    if (save1_vide == NULL)
    {
        SDL_ExitWithError("Probleme texture save1_vide");
    }

    SDL_Rect pos_save1_vide;
    pos_save1_vide.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 8 - (*game->WINDOWWIDTH) / 22;
    pos_save1_vide.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 5.95;
    pos_save1_vide.w = (*game->WINDOWWIDTH) / (500 / 129);
    pos_save1_vide.h = (*game->WINDOWHEIGHT) / 13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Affichage nom save1 ----------------------------------------------------*/

    SDL_Texture *nom_save1 = NULL;

    if (character_save1->empty == SDL_FALSE)
    {
        surf_nom_save1 = TTF_RenderText_Blended(game->police, character_save1->save_name, blanc);
        if (surf_nom_save1 == NULL)
        {
            SDL_ExitWithError("Probleme surface nom save 1");
        }

        nom_save1 = SDL_CreateTextureFromSurface(game->render, surf_nom_save1);
        if (nom_save1 == NULL)
        {
            SDL_ExitWithError("Probleme texture nom save 1");
        }
    }

    /*--- End Affichage nom save1 ---------------------------------------------------*/

    /*--- Affichage position save1 --------------------------------------------------*/

    SDL_Texture *position_save1 = NULL;

    strcpy(temp, character_save1->position);

    _toEspace(temp);

    if (character_save1->empty == SDL_FALSE)
    {
        surf_position_save1 = TTF_RenderText_Blended(game->police, temp, blanc);
        if (surf_position_save1 == NULL)
        {
            SDL_ExitWithError("probleme surface position save 1");
        }

        position_save1 = SDL_CreateTextureFromSurface(game->render, surf_position_save1);
        if (position_save1 == NULL)
        {
            SDL_ExitWithError("probleme texture position save 1");
        }
    }

    SDL_Rect pos_position_save1;
    pos_position_save1.x = (*game->WINDOWWIDTH) / 1.64 - (*game->WINDOWWIDTH) / 13 - (*game->WINDOWWIDTH) / 14;
    pos_position_save1.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 7;
    pos_position_save1.w = strlen(character_save1->position) * (*game->WINDOWWIDTH) / (9 * 11);
    pos_position_save1.h = (*game->WINDOWHEIGHT) / 14;

    /*--- End Affichage position save1 ----------------------------------------------*/

    /*--- Affichage lvl save1 -------------------------------------------------------*/

    char char_lvl_save1[10];
    SDL_Texture *lvl_save1 = NULL;

    if (character_save1->empty == SDL_FALSE)
    {
        itoa(character_save1->lvl, char_lvl_save1, 10);

        surf_lvl_save1 = TTF_RenderText_Blended(game->police, char_lvl_save1, blanc);
        if (surf_lvl_save1 == NULL)
        {
            SDL_ExitWithError("probleme surface niveau save 1");
        }

        lvl_save1 = SDL_CreateTextureFromSurface(game->render, surf_lvl_save1);
        if (lvl_save1 == NULL)
        {
            SDL_ExitWithError("probleme texture niveau save 1");
        }
    }

    SDL_Rect pos_lvl_save1;
    pos_lvl_save1.x = (*game->WINDOWWIDTH) / 1.43 - (*game->WINDOWWIDTH) / 50;
    pos_lvl_save1.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 7.19;
    pos_lvl_save1.w = strlen(char_lvl_save1) * (*game->WINDOWWIDTH) / 14 / 5;
    pos_lvl_save1.h = (*game->WINDOWHEIGHT) / 16;

    /*--- End Affichage lvl save1 ---------------------------------------------------*/

    /*--- Affichage save2 vide -----------------------------*/

    surf_save2_vide = TTF_RenderText_Blended(game->police, "Sauvegarde vide", blanc);
    if (surf_save2_vide == NULL)
    {
        SDL_ExitWithError("Probleme surface save2_vide");
    }

    SDL_Texture *save2_vide = SDL_CreateTextureFromSurface(game->render, surf_save2_vide);
    if (save2_vide == NULL)
    {
        SDL_ExitWithError("Probleme texture save2_vide");
    }

    SDL_Rect pos_save2_vide;
    pos_save2_vide.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 8 - (*game->WINDOWWIDTH) / 22;
    pos_save2_vide.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 33;
    pos_save2_vide.w = (*game->WINDOWWIDTH) / (500 / 129);
    pos_save2_vide.h = (*game->WINDOWHEIGHT) / 13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Affichage nom save2 -------------------------------------------------------*/

    SDL_Texture *nom_save2 = NULL;

    if (character_save2->empty == SDL_FALSE)
    {
        surf_nom_save2 = TTF_RenderText_Blended(game->police, character_save2->save_name, blanc);
        if (surf_nom_save2 == NULL)
        {
            SDL_ExitWithError("Probleme surface nom save 2");
        }

        nom_save2 = SDL_CreateTextureFromSurface(game->render, surf_nom_save2);
        if (nom_save2 == NULL)
        {
            SDL_ExitWithError("Probleme texture nom save 2");
        }
    }

    /*--- End Affichage nom save2 ---------------------------------------------------*/

    /*--- Affichage position save2 --------------------------------------------------*/

    SDL_Texture *position_save2 = NULL;

    strcpy(temp, character_save2->position);

    _toEspace(temp);

    if (character_save2->empty == SDL_FALSE)
    {
        surf_position_save2 = TTF_RenderText_Blended(game->police, temp, blanc);
        if (surf_position_save2 == NULL)
        {
            SDL_ExitWithError("probleme surface position save 2");
        }

        position_save2 = SDL_CreateTextureFromSurface(game->render, surf_position_save2);
        if (position_save2 == NULL)
        {
            SDL_ExitWithError("probleme texture position save 2");
        }
    }

    SDL_Rect pos_position_save2;
    pos_position_save2.x = (*game->WINDOWWIDTH) / 1.64 - (*game->WINDOWWIDTH) / 13 - (*game->WINDOWWIDTH) / 14;
    pos_position_save2.y = (*game->WINDOWHEIGHT) / 1.87 - (*game->WINDOWWIDTH) / 50;
    pos_position_save2.w = strlen(character_save2->position) * (*game->WINDOWWIDTH) / (9 * 11);
    pos_position_save2.h = (*game->WINDOWHEIGHT) / 14;

    /*--- End Affichage position save2 ----------------------------------------------*/

    /*--- Affichage lvl save2 -------------------------------------------------------*/

    char char_lvl_save2[10];
    SDL_Texture *lvl_save2 = NULL;

    if (character_save2->empty == SDL_FALSE)
    {
        itoa(character_save2->lvl, char_lvl_save2, 10);

        surf_lvl_save2 = TTF_RenderText_Blended(game->police, char_lvl_save2, blanc);
        if (surf_lvl_save2 == NULL)
        {
            SDL_ExitWithError("probleme surface niveau save 2");
        }

        lvl_save2 = SDL_CreateTextureFromSurface(game->render, surf_lvl_save2);
        if (lvl_save2 == NULL)
        {
            SDL_ExitWithError("probleme texture niveau save 2");
        }
    }

    SDL_Rect pos_lvl_save2;
    pos_lvl_save2.x = (*game->WINDOWWIDTH) / 1.43 - (*game->WINDOWWIDTH) / 50;
    pos_lvl_save2.y = (*game->WINDOWHEIGHT) / 1.86 - (*game->WINDOWWIDTH) / 50;
    pos_lvl_save2.w = strlen(char_lvl_save2) * (*game->WINDOWWIDTH) / 14 / 5;
    pos_lvl_save2.h = (*game->WINDOWHEIGHT) / 16;

    /*--- End Affichage lvl save2 ---------------------------------------------------*/

    /*--- Affichage save3 vide -----------------------------*/

    surf_save3_vide = TTF_RenderText_Blended(game->police, "Sauvegarde vide", blanc);
    if (surf_save3_vide == NULL)
    {
        SDL_ExitWithError("Probleme surface save3_vide");
    }

    SDL_Texture *save3_vide = SDL_CreateTextureFromSurface(game->render, surf_save3_vide);
    if (save3_vide == NULL)
    {
        SDL_ExitWithError("Probleme texture save3_vide");
    }

    SDL_Rect pos_save3_vide;
    pos_save3_vide.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 8 - (*game->WINDOWWIDTH) / 22;
    pos_save3_vide.y = (*game->WINDOWHEIGHT) / 1.38 - (*game->WINDOWWIDTH) / 80;
    pos_save3_vide.w = (*game->WINDOWWIDTH) / (500 / 129);
    pos_save3_vide.h = (*game->WINDOWHEIGHT) / 13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Affichage nom save3 -------------------------------------------------------*/

    SDL_Texture *nom_save3 = NULL;

    if (character_save3->empty == SDL_FALSE)
    {
        surf_nom_save3 = TTF_RenderText_Blended(game->police, character_save3->save_name, blanc);
        if (surf_nom_save3 == NULL)
        {
            SDL_ExitWithError("Probleme surface nom save 3");
        }

        nom_save3 = SDL_CreateTextureFromSurface(game->render, surf_nom_save3);
        if (nom_save3 == NULL)
        {
            SDL_ExitWithError("Probleme texture nom save 3");
        }
    }

    /*--- End Affichage nom save3 ---------------------------------------------------*/

    /*--- Affichage position save3 --------------------------------------------------*/

    SDL_Texture *position_save3 = NULL;

    strcpy(temp, character_save3->position);

    _toEspace(temp);

    if (character_save3->empty == SDL_FALSE)
    {
        surf_position_save3 = TTF_RenderText_Blended(game->police, temp, blanc);
        if (surf_position_save3 == NULL)
        {
            SDL_ExitWithError("probleme surface position save 3");
        }

        position_save3 = SDL_CreateTextureFromSurface(game->render, surf_position_save3);
        if (position_save3 == NULL)
        {
            SDL_ExitWithError("probleme texture position save 3");
        }
    }

    SDL_Rect pos_position_save3;
    pos_position_save3.x = (*game->WINDOWWIDTH) / 1.64 - (*game->WINDOWWIDTH) / 13 - (*game->WINDOWWIDTH) / 14;
    pos_position_save3.y = (*game->WINDOWHEIGHT) / 1.28 - (*game->WINDOWWIDTH) / 50;
    pos_position_save3.w = strlen(character_save3->position) * (*game->WINDOWWIDTH) / (9 * 11);
    pos_position_save3.h = (*game->WINDOWHEIGHT) / 14;

    /*---  End Affichage position save3 ----------------------------------------------*/

    /*--- Affichage lvl save3 -------------------------------------------------------*/

    char char_lvl_save3[10];
    SDL_Texture *lvl_save3 = NULL;

    if (character_save3->empty == SDL_FALSE)
    {
        itoa(character_save3->lvl, char_lvl_save3, 10);

        surf_lvl_save3 = TTF_RenderText_Blended(game->police, char_lvl_save3, blanc);
        if (surf_lvl_save3 == NULL)
        {
            SDL_ExitWithError("probleme surface niveau save 3");
        }

        lvl_save3 = SDL_CreateTextureFromSurface(game->render, surf_lvl_save3);
        if (lvl_save3 == NULL)
        {
            SDL_ExitWithError("probleme texture niveau save 3");
        }
    }

    SDL_Rect pos_lvl_save3;
    pos_lvl_save3.x = (*game->WINDOWWIDTH) / 1.43 - (*game->WINDOWWIDTH) / 50;
    pos_lvl_save3.y = (*game->WINDOWHEIGHT) / 1.27 - (*game->WINDOWWIDTH) / 50;
    pos_lvl_save3.w = strlen(char_lvl_save3) * (*game->WINDOWWIDTH) / 14 / 5;
    pos_lvl_save3.h = (*game->WINDOWHEIGHT) / 16;

    /*--- End Affichage lvl save3 ------------------------------------------------*/

    /*--- Affichage position -----------------------------------------------------*/

    surf_position = TTF_RenderText_Blended(game->police, "Position : ", blanc);
    if (surf_position == NULL)
    {
        SDL_ExitWithError("probleme surface position");
    }
    SDL_Texture *position = SDL_CreateTextureFromSurface(game->render, surf_position);
    if (position == NULL)
    {
        SDL_ExitWithError("probleme texture position");
    }

    /*--- End Affichage position -------------------------------------------------*/

    /*--- Affichage lvl ----------------------------------------------------------*/

    surf_lvl = TTF_RenderText_Blended(game->police, "LVL : ", blanc);
    if (surf_lvl == NULL)
    {
        SDL_ExitWithError("probleme surface niveau");
    }
    SDL_Texture *lvl = SDL_CreateTextureFromSurface(game->render, surf_lvl);
    if (lvl == NULL)
    {
        SDL_ExitWithError("probleme texture niveau");
    }

    /*--- End Affichage lvl ------------------------------------------------------*/

    /*--- Creation text "choisissez emplacement" ---------------------------------*/

    surf_choisir_empla = TTF_RenderText_Blended(game->police, "CHOISISSEZ EMPLACEMENT", blanc);
    if (surf_choisir_empla == NULL)
    {
        SDL_ExitWithError("probleme surface choisir emplacement");
    }
    SDL_Texture *choisir_empla = SDL_CreateTextureFromSurface(game->render, surf_choisir_empla);
    if (choisir_empla == NULL)
    {
        SDL_ExitWithError("probleme texture choisir emplacement");
    }

    SDL_Rect pos_choisir_empla;
    pos_choisir_empla.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) * 337 / 1200;
    pos_choisir_empla.y = (*game->WINDOWHEIGHT) / 30;
    pos_choisir_empla.w = (*game->WINDOWWIDTH) * 673 / 1200;
    pos_choisir_empla.h = (*game->WINDOWHEIGHT) / 13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Creation texture "retour"-----------------------------------------------*/

    surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
    if (surf_retour == NULL)
    {
        SDL_ExitWithError("probleme surface Retour");
    }
    SDL_Texture *retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
    if (retour == NULL)
    {
        SDL_ExitWithError("probleme texture Retour");
    }

    SDL_Rect pos_retour;
    pos_retour.x = (*game->WINDOWWIDTH) / 20;
    pos_retour.y = (*game->WINDOWHEIGHT) - (*game->WINDOWHEIGHT) / 8;
    pos_retour.w = (*game->WINDOWWIDTH) / (1200 / 129);
    pos_retour.h = (*game->WINDOWHEIGHT) / 13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Creation texture background --------------------------------------------*/

    surf_fond = SDL_LoadBMP("src\\image\\fond_menu_accueil.bmp");
    if (surf_fond == NULL)
    {
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture *fond = SDL_CreateTextureFromSurface(game->render, surf_fond);
    if (fond == NULL)
    {
        SDL_ExitWithError("probleme texture fond menu d'accueil");
    }

    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;
    pos_fond.w = (*game->WINDOWWIDTH);
    pos_fond.h = (*game->WINDOWHEIGHT);

    /*----------------------------------------------------------------------------*/

    /*--- Loading texture "cadre choix emplacement" ------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_choix_emplacement.bmp");
    if (surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre");
    }

    /*----------------------------------------------------------------------------*/

    /*--- Initialization texture "cadre save 1" ----------------------------------*/

    SDL_Texture *cadre_save1 = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if (cadre_save1 == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_save1");
    }

    SDL_Rect pos_cadre_save1;
    pos_cadre_save1.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15;
    pos_cadre_save1.y = (*game->WINDOWHEIGHT) / 6.75;
    pos_cadre_save1.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30;
    pos_cadre_save1.h = (*game->WINDOWHEIGHT) / 5;

    /*----------------------------------------------------------------------------*/

    /*--- Creation texture background "cadre save 1" -----------------------------*/

    SDL_Texture *fond_cadre_save1 = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30, (*game->WINDOWHEIGHT) / 5);
    if (fond_cadre_save1 == NULL)
    {
        SDL_ExitWithError("probleme texture fond_cadre_save1");
    }

    SDL_Rect pos_fond_cadre_save1;
    pos_fond_cadre_save1.x = pos_cadre_save1.x;
    pos_fond_cadre_save1.y = pos_cadre_save1.y;
    pos_fond_cadre_save1.w = pos_cadre_save1.w;
    pos_fond_cadre_save1.h = pos_cadre_save1.h;

    SDL_Rect rect_fond_cadre_save1;
    rect_fond_cadre_save1.x = (*game->WINDOWWIDTH) * 12 / 1200;
    rect_fond_cadre_save1.y = (*game->WINDOWHEIGHT) * 12 / 675;
    rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2 * rect_fond_cadre_save1.x;
    rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2 * rect_fond_cadre_save1.y;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 200);
    SDL_SetRenderTarget(game->render, fond_cadre_save1);
    SDL_SetTextureBlendMode(fond_cadre_save1, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre_save1);
    SDL_SetRenderTarget(game->render, NULL);

    /*----------------------------------------------------------------------------*/

    /*--- Initialization texture "cadre save 2" ----------------------------------*/

    SDL_Texture *cadre_save2 = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if (cadre_save2 == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_save2");
    }

    SDL_Rect pos_cadre_save2;
    pos_cadre_save2.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15;
    pos_cadre_save2.y = (*game->WINDOWHEIGHT) / 2.5;
    pos_cadre_save2.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30;
    pos_cadre_save2.h = (*game->WINDOWHEIGHT) / 5;

    /*----------------------------------------------------------------------------*/

    /*--- Creation texture background "cadre save 2" -----------------------------*/

    SDL_Texture *fond_cadre_save2 = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30, (*game->WINDOWHEIGHT) / 5);
    if (fond_cadre_save2 == NULL)
    {
        SDL_ExitWithError("probleme texture fond_cadre_save2");
    }

    SDL_Rect pos_fond_cadre_save2;
    pos_fond_cadre_save2.x = pos_cadre_save2.x;
    pos_fond_cadre_save2.y = pos_cadre_save2.y;
    pos_fond_cadre_save2.w = pos_cadre_save2.w;
    pos_fond_cadre_save2.h = pos_cadre_save2.h;

    SDL_Rect rect_fond_cadre_save2;
    rect_fond_cadre_save2.x = (*game->WINDOWWIDTH) * 12 / 1200;
    rect_fond_cadre_save2.y = (*game->WINDOWHEIGHT) * 12 / 675;
    rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2 * rect_fond_cadre_save2.x;
    rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2 * rect_fond_cadre_save2.y;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 200);
    SDL_SetRenderTarget(game->render, fond_cadre_save2);
    SDL_SetTextureBlendMode(fond_cadre_save2, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre_save2);
    SDL_SetRenderTarget(game->render, NULL);

    /*----------------------------------------------------------------------------*/

    /*--- Initialization texture "cadre save 3" ----------------------------------*/

    SDL_Texture *cadre_save3 = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if (cadre_save3 == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_save3");
    }

    SDL_Rect pos_cadre_save3;
    pos_cadre_save3.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15;
    pos_cadre_save3.y = (*game->WINDOWHEIGHT) * 440 / 675;
    pos_cadre_save3.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30;
    pos_cadre_save3.h = (*game->WINDOWHEIGHT) / 5;

    /*----------------------------------------------------------------------------*/

    /*--- Creation texture background "cadre save 3" -----------------------------*/

    SDL_Texture *fond_cadre_save3 = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30, (*game->WINDOWHEIGHT) / 5);
    if (fond_cadre_save3 == NULL)
    {
        SDL_ExitWithError("probleme texture fond_cadre_save3");
    }

    SDL_Rect pos_fond_cadre_save3;
    pos_fond_cadre_save3.x = pos_cadre_save3.x;
    pos_fond_cadre_save3.y = pos_cadre_save3.y;
    pos_fond_cadre_save3.w = pos_cadre_save3.w;
    pos_fond_cadre_save3.h = pos_cadre_save3.h;

    SDL_Rect rect_fond_cadre_save3;
    rect_fond_cadre_save3.x = (*game->WINDOWWIDTH) * 12 / 1200;
    rect_fond_cadre_save3.y = (*game->WINDOWHEIGHT) * 12 / 675;
    rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2 * rect_fond_cadre_save3.x;
    rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2 * rect_fond_cadre_save3.y;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 200);
    SDL_SetRenderTarget(game->render, fond_cadre_save3);
    SDL_SetTextureBlendMode(fond_cadre_save3, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre_save3);
    SDL_SetRenderTarget(game->render, NULL);

    /*----------------------------------------------------------------------------*/

    /*--- Initialization texture "Guerrier" --------------------------------------*/

    surf_spriteGuerrier = SDL_LoadBMP("src\\tileset\\PJ\\Guerrier.bmp");
    SDL_SetColorKey(surf_spriteGuerrier, SDL_TRUE, SDL_MapRGB(surf_spriteGuerrier->format, 255, 255, 255));
    if (surf_spriteGuerrier == NULL)
    {
        SDL_ExitWithError("probleme chargement sprite du guerrier");
    }

    SDL_Texture *spriteGuerrier = SDL_CreateTextureFromSurface(game->render, surf_spriteGuerrier);
    if (spriteGuerrier == NULL)
    {
        SDL_ExitWithError("probleme texture sprite du guerrier");
    }

    SDL_Rect pos_sprite_guerrier;
    pos_sprite_guerrier.x = 3;
    pos_sprite_guerrier.y = 3;
    pos_sprite_guerrier.w = 20;
    pos_sprite_guerrier.h = 30;

    /*----------------------------------------------------------------------------*/

    /*--- Initialization texture "Mage" ------------------------------------------*/

    surf_spriteMage = SDL_LoadBMP("src\\tileset\\PJ\\Mage.bmp");
    SDL_SetColorKey(surf_spriteMage, SDL_TRUE, SDL_MapRGB(surf_spriteMage->format, 255, 255, 255));
    if (surf_spriteMage == NULL)
    {
        SDL_ExitWithError("probleme chargement sprite du mage");
    }

    SDL_Texture *spriteMage = SDL_CreateTextureFromSurface(game->render, surf_spriteMage);
    if (spriteMage == NULL)
    {
        SDL_ExitWithError("probleme texture sprite du mage");
    }

    SDL_Rect pos_sprite_mage;
    pos_sprite_mage.x = 3;
    pos_sprite_mage.y = 3;
    pos_sprite_mage.w = 16;
    pos_sprite_mage.h = 31;

    /*----------------------------------------------------------------------------*/

    /*--- Initialization texture "Assassin" --------------------------------------*/

    surf_spriteAssassin = SDL_LoadBMP("src\\tileset\\PJ\\Assassin.bmp");
    SDL_SetColorKey(surf_spriteAssassin, SDL_TRUE, SDL_MapRGB(surf_spriteAssassin->format, 255, 255, 255));
    if (surf_spriteAssassin == NULL)
    {
        SDL_ExitWithError("probleme chargement sprite du assassin");
    }

    SDL_Texture *spriteAssassin = SDL_CreateTextureFromSurface(game->render, surf_spriteAssassin);
    if (spriteAssassin == NULL)
    {
        SDL_ExitWithError("probleme texture sprite du assassin");
    }

    SDL_Rect pos_sprite_assassin;
    pos_sprite_assassin.x = 3;
    pos_sprite_assassin.y = 3;
    pos_sprite_assassin.w = 18;
    pos_sprite_assassin.h = 30;

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

    while (nouv_part_bool && *game->program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                *game->program_launch = SDL_FALSE;
                nouv_part_bool = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                nouv_part_bool = SDL_FALSE;
                strcpy(actual_save, "\0");
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

            if (selection < 0)
                selection = 3;
            selection %= 4;

            if (selection == 0)
            {
                pos_cadre_save2.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15;
                pos_cadre_save2.y = (*game->WINDOWHEIGHT) / 2.5;
                pos_cadre_save2.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30;
                pos_cadre_save2.h = (*game->WINDOWHEIGHT) / 5;
                pos_fond_cadre_save2.x = pos_cadre_save2.x;
                pos_fond_cadre_save2.y = pos_cadre_save2.y;
                pos_fond_cadre_save2.w = pos_cadre_save2.w;
                pos_fond_cadre_save2.h = pos_cadre_save2.h;
                rect_fond_cadre_save2.x = (*game->WINDOWWIDTH) * 12 / 1200;
                rect_fond_cadre_save2.y = (*game->WINDOWHEIGHT) * 12 / 675;
                rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2 * rect_fond_cadre_save2.x;
                rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2 * rect_fond_cadre_save2.y;

                pos_cadre_save1.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15 - (*game->WINDOWWIDTH) / 120;
                pos_cadre_save1.y = (*game->WINDOWHEIGHT) / 6.75 - (*game->WINDOWHEIGHT) / 67.5;
                pos_cadre_save1.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30 + (*game->WINDOWWIDTH) / 60;
                pos_cadre_save1.h = (*game->WINDOWHEIGHT) / 5 + (*game->WINDOWHEIGHT) / 33.75;
                pos_fond_cadre_save1.x = pos_cadre_save1.x;
                pos_fond_cadre_save1.y = pos_cadre_save1.y;
                pos_fond_cadre_save1.w = pos_cadre_save1.w;
                pos_fond_cadre_save1.h = pos_cadre_save1.h;
                rect_fond_cadre_save1.x = (*game->WINDOWWIDTH) * 12 / 1200;
                rect_fond_cadre_save1.y = (*game->WINDOWHEIGHT) * 12 / 675;
                rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2 * rect_fond_cadre_save1.x;
                rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2 * rect_fond_cadre_save1.y;

                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
                retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
            }

            if (selection == 1)
            {
                pos_cadre_save3.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15;
                pos_cadre_save3.y = (*game->WINDOWHEIGHT) * 440 / 675;
                pos_cadre_save3.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30;
                pos_cadre_save3.h = (*game->WINDOWHEIGHT) / 5;
                pos_fond_cadre_save3.x = pos_cadre_save3.x;
                pos_fond_cadre_save3.y = pos_cadre_save3.y;
                pos_fond_cadre_save3.w = pos_cadre_save3.w;
                pos_fond_cadre_save3.h = pos_cadre_save3.h;
                rect_fond_cadre_save3.x = (*game->WINDOWWIDTH) * 12 / 1200;
                rect_fond_cadre_save3.y = (*game->WINDOWHEIGHT) * 12 / 675;
                rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2 * rect_fond_cadre_save3.x;
                rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2 * rect_fond_cadre_save3.y;

                pos_cadre_save1.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15;
                pos_cadre_save1.y = (*game->WINDOWHEIGHT) / 6.75;
                pos_cadre_save1.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30;
                pos_cadre_save1.h = (*game->WINDOWHEIGHT) / 5;
                pos_fond_cadre_save1.x = pos_cadre_save1.x;
                pos_fond_cadre_save1.y = pos_cadre_save1.y;
                pos_fond_cadre_save1.w = pos_cadre_save1.w;
                pos_fond_cadre_save1.h = pos_cadre_save1.h;
                rect_fond_cadre_save1.x = (*game->WINDOWWIDTH) * 12 / 1200;
                rect_fond_cadre_save1.y = (*game->WINDOWHEIGHT) * 12 / 675;
                rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2 * rect_fond_cadre_save1.x;
                rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2 * rect_fond_cadre_save1.y;

                pos_cadre_save2.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15 - (*game->WINDOWWIDTH) / 120;
                pos_cadre_save2.y = (*game->WINDOWHEIGHT) / 2.5 - (*game->WINDOWHEIGHT) / 67.5;
                pos_cadre_save2.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30 + (*game->WINDOWWIDTH) / 60;
                pos_cadre_save2.h = (*game->WINDOWHEIGHT) / 5 + (*game->WINDOWHEIGHT) / 33.75;
                pos_fond_cadre_save2.x = pos_cadre_save2.x;
                pos_fond_cadre_save2.y = pos_cadre_save2.y;
                pos_fond_cadre_save2.w = pos_cadre_save2.w;
                pos_fond_cadre_save2.h = pos_cadre_save2.h;
                rect_fond_cadre_save2.x = (*game->WINDOWWIDTH) * 12 / 1200;
                rect_fond_cadre_save2.y = (*game->WINDOWHEIGHT) * 12 / 675;
                rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2 * rect_fond_cadre_save2.x;
                rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2 * rect_fond_cadre_save2.y;
            }

            if (selection == 2)
            {
                pos_cadre_save2.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15;
                pos_cadre_save2.y = (*game->WINDOWHEIGHT) / 2.5;
                pos_cadre_save2.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30;
                pos_cadre_save2.h = (*game->WINDOWHEIGHT) / 5;
                pos_fond_cadre_save2.x = pos_cadre_save2.x;
                pos_fond_cadre_save2.y = pos_cadre_save2.y;
                pos_fond_cadre_save2.w = pos_cadre_save2.w;
                pos_fond_cadre_save2.h = pos_cadre_save2.h;
                rect_fond_cadre_save2.x = (*game->WINDOWWIDTH) * 12 / 1200;
                rect_fond_cadre_save2.y = (*game->WINDOWHEIGHT) * 12 / 675;
                rect_fond_cadre_save2.w = pos_fond_cadre_save2.w - 2 * rect_fond_cadre_save2.x;
                rect_fond_cadre_save2.h = pos_fond_cadre_save2.h - 2 * rect_fond_cadre_save2.y;

                pos_cadre_save3.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15 - (*game->WINDOWWIDTH) / 120;
                pos_cadre_save3.y = (*game->WINDOWHEIGHT) * 440 / 675 - (*game->WINDOWHEIGHT) / 67.5;
                pos_cadre_save3.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30 + (*game->WINDOWWIDTH) / 60;
                pos_cadre_save3.h = (*game->WINDOWHEIGHT) / 5 + (*game->WINDOWHEIGHT) / 33.75;
                pos_fond_cadre_save3.x = pos_cadre_save3.x;
                pos_fond_cadre_save3.y = pos_cadre_save3.y;
                pos_fond_cadre_save3.w = pos_cadre_save3.w;
                pos_fond_cadre_save3.h = pos_cadre_save3.h;
                rect_fond_cadre_save3.x = (*game->WINDOWWIDTH) * 12 / 1200;
                rect_fond_cadre_save3.y = (*game->WINDOWHEIGHT) * 12 / 675;
                rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2 * rect_fond_cadre_save3.x;
                rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2 * rect_fond_cadre_save3.y;

                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
                retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
            }

            if (selection == 3)
            {
                pos_cadre_save1.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15;
                pos_cadre_save1.y = (*game->WINDOWHEIGHT) / 6.75;
                pos_cadre_save1.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30;
                pos_cadre_save1.h = (*game->WINDOWHEIGHT) / 5;
                pos_fond_cadre_save1.x = pos_cadre_save1.x;
                pos_fond_cadre_save1.y = pos_cadre_save1.y;
                pos_fond_cadre_save1.w = pos_cadre_save1.w;
                pos_fond_cadre_save1.h = pos_cadre_save1.h;
                rect_fond_cadre_save1.x = (*game->WINDOWWIDTH) * 12 / 1200;
                rect_fond_cadre_save1.y = (*game->WINDOWHEIGHT) * 12 / 675;
                rect_fond_cadre_save1.w = pos_fond_cadre_save1.w - 2 * rect_fond_cadre_save1.x;
                rect_fond_cadre_save1.h = pos_fond_cadre_save1.h - 2 * rect_fond_cadre_save1.y;

                pos_cadre_save3.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 15;
                pos_cadre_save3.y = (*game->WINDOWHEIGHT) * 440 / 675;
                pos_cadre_save3.w = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 30;
                pos_cadre_save3.h = (*game->WINDOWHEIGHT) / 5;
                pos_fond_cadre_save3.x = pos_cadre_save3.x;
                pos_fond_cadre_save3.y = pos_cadre_save3.y;
                pos_fond_cadre_save3.w = pos_cadre_save3.w;
                pos_fond_cadre_save3.h = pos_cadre_save3.h;
                rect_fond_cadre_save3.x = (*game->WINDOWWIDTH) * 12 / 1200;
                rect_fond_cadre_save3.y = (*game->WINDOWHEIGHT) * 12 / 675;
                rect_fond_cadre_save3.w = pos_fond_cadre_save3.w - 2 * rect_fond_cadre_save3.x;
                rect_fond_cadre_save3.h = pos_fond_cadre_save3.h - 2 * rect_fond_cadre_save3.y;

                surf_retour = TTF_RenderText_Blended(game->police, "Retour", rouge);
                retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
            }

            SDL_RenderClear(game->render);

            SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
            SDL_RenderCopy(game->render, choisir_empla, NULL, &pos_choisir_empla);
            SDL_RenderCopy(game->render, retour, NULL, &pos_retour);
            SDL_RenderCopy(game->render, fond_cadre_save1, NULL, &pos_fond_cadre_save1);
            SDL_RenderCopy(game->render, fond_cadre_save2, NULL, &pos_fond_cadre_save2);
            SDL_RenderCopy(game->render, fond_cadre_save3, NULL, &pos_fond_cadre_save3);
            SDL_RenderCopy(game->render, cadre_save1, NULL, &pos_cadre_save1);
            SDL_RenderCopy(game->render, cadre_save2, NULL, &pos_cadre_save2);
            SDL_RenderCopy(game->render, cadre_save3, NULL, &pos_cadre_save3);

            if (character_save1->empty == SDL_TRUE)
            {
                SDL_RenderCopy(game->render, save1_vide, NULL, &pos_save1_vide);
            }
            else
            {
                SDL_Rect pos_position;
                pos_position.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 13 - (*game->WINDOWWIDTH) / 14;
                pos_position.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 7;
                pos_position.w = (*game->WINDOWWIDTH) / 9;
                pos_position.h = (*game->WINDOWHEIGHT) / 14;
                SDL_RenderCopy(game->render, position, NULL, &pos_position);
                SDL_RenderCopy(game->render, position_save1, NULL, &pos_position_save1);

                SDL_Rect pos_lvl;
                pos_lvl.x = (*game->WINDOWWIDTH) / 1.6 - (*game->WINDOWWIDTH) / 50;
                pos_lvl.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 7.19;
                pos_lvl.w = (*game->WINDOWWIDTH) / 14;
                pos_lvl.h = (*game->WINDOWHEIGHT) / 16;
                SDL_RenderCopy(game->render, lvl, NULL, &pos_lvl);
                SDL_RenderCopy(game->render, lvl_save1, NULL, &pos_lvl_save1);

                SDL_Rect pos_nom_save1;
                pos_nom_save1.w = strlen(character_save1->save_name) * (*game->WINDOWWIDTH) / 7 / 10;
                pos_nom_save1.h = (*game->WINDOWHEIGHT) / 13.5;
                pos_nom_save1.x = (*game->WINDOWWIDTH) / 2 - pos_nom_save1.w / 2;
                pos_nom_save1.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 5.3;
                SDL_RenderCopy(game->render, nom_save1, NULL, &pos_nom_save1);

                if (strcmp(character_save1->classe_name, "Guerrier") == 0)
                {
                    SDL_Rect pos_spriteGuerrier;
                    pos_spriteGuerrier.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 18;
                    pos_spriteGuerrier.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 5.4;
                    pos_spriteGuerrier.w = (*game->WINDOWWIDTH) * 66.5 / 1200;
                    pos_spriteGuerrier.h = (*game->WINDOWHEIGHT) * 105 / 675;
                    SDL_RenderCopy(game->render, spriteGuerrier, &pos_sprite_guerrier, &pos_spriteGuerrier);
                }
                else if (strcmp(character_save1->classe_name, "Mage") == 0)
                {
                    SDL_Rect pos_spriteMage;
                    pos_spriteMage.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 18;
                    pos_spriteMage.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 5.4;
                    pos_spriteMage.w = (*game->WINDOWWIDTH) * 49 / 1200;
                    pos_spriteMage.h = (*game->WINDOWHEIGHT) * 108.5 / 675;
                    SDL_RenderCopy(game->render, spriteMage, &pos_sprite_mage, &pos_spriteMage);
                }
                else if (strcmp(character_save1->classe_name, "Assassin") == 0)
                {
                    SDL_Rect pos_spriteAssassin;
                    pos_spriteAssassin.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 18;
                    pos_spriteAssassin.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 5.4;
                    pos_spriteAssassin.w = (*game->WINDOWWIDTH) * 63 / 1200;
                    pos_spriteAssassin.h = (*game->WINDOWHEIGHT) * 105 / 675;
                    SDL_RenderCopy(game->render, spriteAssassin, &pos_sprite_assassin, &pos_spriteAssassin);
                }
            }

            if (character_save2->empty == SDL_TRUE)
            {
                SDL_RenderCopy(game->render, save2_vide, NULL, &pos_save2_vide);
            }
            else
            {
                SDL_Rect pos_position;
                pos_position.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 13 - (*game->WINDOWWIDTH) / 14;
                pos_position.y = (*game->WINDOWHEIGHT) / 1.87 - (*game->WINDOWWIDTH) / 50;
                pos_position.w = (*game->WINDOWWIDTH) / 9;
                pos_position.h = (*game->WINDOWHEIGHT) / 14;
                SDL_RenderCopy(game->render, position, NULL, &pos_position);
                SDL_RenderCopy(game->render, position_save2, NULL, &pos_position_save2);

                SDL_Rect pos_lvl;
                pos_lvl.x = (*game->WINDOWWIDTH) / 1.6 - (*game->WINDOWWIDTH) / 50;
                pos_lvl.y = (*game->WINDOWHEIGHT) / 1.86 - (*game->WINDOWWIDTH) / 50;
                pos_lvl.w = (*game->WINDOWWIDTH) / 14;
                pos_lvl.h = (*game->WINDOWHEIGHT) / 16;
                SDL_RenderCopy(game->render, lvl, NULL, &pos_lvl);
                SDL_RenderCopy(game->render, lvl_save2, NULL, &pos_lvl_save2);

                SDL_Rect pos_nom_save2;
                pos_nom_save2.w = strlen(character_save2->save_name) * (*game->WINDOWWIDTH) / 7 / 10;
                pos_nom_save2.h = (*game->WINDOWHEIGHT) / 13.5;
                pos_nom_save2.x = (*game->WINDOWWIDTH) / 2 - pos_nom_save2.w / 2;
                pos_nom_save2.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 22.7;
                SDL_RenderCopy(game->render, nom_save2, NULL, &pos_nom_save2);

                if (strcmp(character_save2->classe_name, "Guerrier") == 0)
                {
                    SDL_Rect pos_spriteGuerrier;
                    pos_spriteGuerrier.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 18;
                    pos_spriteGuerrier.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 22.7;
                    pos_spriteGuerrier.w = (*game->WINDOWWIDTH) * 66.5 / 1200;
                    pos_spriteGuerrier.h = (*game->WINDOWHEIGHT) * 105 / 675;
                    SDL_RenderCopy(game->render, spriteGuerrier, &pos_sprite_guerrier, &pos_spriteGuerrier);
                }
                else if (strcmp(character_save2->classe_name, "Mage") == 0)
                {
                    SDL_Rect pos_spriteMage;
                    pos_spriteMage.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 18;
                    pos_spriteMage.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 22.7;
                    pos_spriteMage.w = (*game->WINDOWWIDTH) * 49 / 1200;
                    pos_spriteMage.h = (*game->WINDOWHEIGHT) * 108.5 / 675;
                    SDL_RenderCopy(game->render, spriteMage, &pos_sprite_mage, &pos_spriteMage);
                }
                else if (strcmp(character_save2->classe_name, "Assassin") == 0)
                {
                    SDL_Rect pos_spriteAssassin;
                    pos_spriteAssassin.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 18;
                    pos_spriteAssassin.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 22.6;
                    pos_spriteAssassin.w = (*game->WINDOWWIDTH) * 63 / 1200;
                    pos_spriteAssassin.h = (*game->WINDOWHEIGHT) * 105 / 675;
                    SDL_RenderCopy(game->render, spriteAssassin, &pos_sprite_assassin, &pos_spriteAssassin);
                }
            }

            if (character_save3->empty == SDL_TRUE)
            {
                SDL_RenderCopy(game->render, save3_vide, NULL, &pos_save3_vide);
            }
            else
            {
                SDL_Rect pos_position;
                pos_position.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 13 - (*game->WINDOWWIDTH) / 14;
                pos_position.y = (*game->WINDOWHEIGHT) / 1.28 - (*game->WINDOWWIDTH) / 50;
                pos_position.w = (*game->WINDOWWIDTH) / 9;
                pos_position.h = (*game->WINDOWHEIGHT) / 14;
                SDL_RenderCopy(game->render, position, NULL, &pos_position);
                SDL_RenderCopy(game->render, position_save3, NULL, &pos_position_save3);

                SDL_Rect pos_lvl;
                pos_lvl.x = (*game->WINDOWWIDTH) / 1.6 - (*game->WINDOWWIDTH) / 50;
                pos_lvl.y = (*game->WINDOWHEIGHT) / 1.27 - (*game->WINDOWWIDTH) / 50;
                pos_lvl.w = (*game->WINDOWWIDTH) / 14;
                pos_lvl.h = (*game->WINDOWHEIGHT) / 16;
                SDL_RenderCopy(game->render, lvl, NULL, &pos_lvl);
                SDL_RenderCopy(game->render, lvl_save3, NULL, &pos_lvl_save3);

                SDL_Rect pos_nom_save3;
                pos_nom_save3.w = strlen(character_save3->save_name) * (*game->WINDOWWIDTH) / 7 / 10;
                pos_nom_save3.h = (*game->WINDOWHEIGHT) / 13.5;
                pos_nom_save3.x = (*game->WINDOWWIDTH) / 2 - pos_nom_save3.w / 2;
                pos_nom_save3.y = (*game->WINDOWHEIGHT) / 1.33 - (*game->WINDOWWIDTH) / 22.7;
                SDL_RenderCopy(game->render, nom_save3, NULL, &pos_nom_save3);

                if (strcmp(character_save3->classe_name, "Guerrier") == 0)
                {
                    SDL_Rect pos_spriteGuerrier;
                    pos_spriteGuerrier.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 18;
                    pos_spriteGuerrier.y = (*game->WINDOWHEIGHT) / 1.33 - (*game->WINDOWWIDTH) / 22.7;
                    pos_spriteGuerrier.w = (*game->WINDOWWIDTH) * 66.5 / 1200;
                    pos_spriteGuerrier.h = (*game->WINDOWHEIGHT) * 105 / 675;
                    SDL_RenderCopy(game->render, spriteGuerrier, &pos_sprite_guerrier, &pos_spriteGuerrier);
                }
                else if (strcmp(character_save3->classe_name, "Mage") == 0)
                {
                    SDL_Rect pos_spriteMage;
                    pos_spriteMage.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 18;
                    pos_spriteMage.y = (*game->WINDOWHEIGHT) / 1.33 - (*game->WINDOWWIDTH) / 22.7;
                    pos_spriteMage.w = (*game->WINDOWWIDTH) * 49 / 1200;
                    pos_spriteMage.h = (*game->WINDOWHEIGHT) * 108.5 / 675;
                    SDL_RenderCopy(game->render, spriteMage, &pos_sprite_mage, &pos_spriteMage);
                }
                else if (strcmp(character_save3->classe_name, "Assassin") == 0)
                {
                    SDL_Rect pos_spriteAssassin;
                    pos_spriteAssassin.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6 - (*game->WINDOWWIDTH) / 18;
                    pos_spriteAssassin.y = (*game->WINDOWHEIGHT) / 1.33 - (*game->WINDOWWIDTH) / 22.7;
                    pos_spriteAssassin.w = (*game->WINDOWWIDTH) * 63 / 1200;
                    pos_spriteAssassin.h = (*game->WINDOWHEIGHT) * 105 / 675;
                    SDL_RenderCopy(game->render, spriteAssassin, &pos_sprite_assassin, &pos_spriteAssassin);
                }
            }

            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {

                if (selection == 0)
                {

                    if (character_save1->empty == SDL_FALSE)
                    {
                        if (texte_confirmation(game, "Voulez-vous vraiment ecraser la sauvegarde ?"))
                        {
                            strcpy(actual_save, "save//save1.txt");
                            creation_perso(game, actual_save);
                            nouv_part_bool = SDL_FALSE;
                        }
                    }
                    else
                    {
                        strcpy(actual_save, "save//save1.txt");
                        creation_perso(game, actual_save);
                        nouv_part_bool = SDL_FALSE;
                    }
                }

                if (selection == 1)
                {

                    if (character_save2->empty == SDL_FALSE)
                    {
                        if (texte_confirmation(game, "Voulez-vous vraiment ecraser la sauvegarde ?"))
                        {
                            strcpy(actual_save, "save//save2.txt");
                            creation_perso(game, actual_save);
                            nouv_part_bool = SDL_FALSE;
                        }
                    }
                    else
                    {
                        strcpy(actual_save, "save//save2.txt");
                        creation_perso(game, actual_save);
                        nouv_part_bool = SDL_FALSE;
                    }
                }

                if (selection == 2)
                {

                    if (character_save3->empty == SDL_FALSE)
                    {
                        if (texte_confirmation(game, "Voulez-vous vraiment ecraser la sauvegarde ?"))
                        {
                            strcpy(actual_save, "save//save3.txt");
                            creation_perso(game, actual_save);
                            nouv_part_bool = SDL_FALSE;
                        }
                    }
                    else
                    {
                        strcpy(actual_save, "save//save3.txt");
                        creation_perso(game, actual_save);
                        nouv_part_bool = SDL_FALSE;
                    }
                }

                if (selection == 3)
                {
                    nouv_part_bool = SDL_FALSE;
                    strcpy(actual_save, "\0");
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
    SDL_DestroyTexture(fond_cadre_save1);
    SDL_DestroyTexture(fond_cadre_save2);
    SDL_DestroyTexture(fond_cadre_save3);

    /*--- End Free Memory --------------------------------------------------------*/
}
