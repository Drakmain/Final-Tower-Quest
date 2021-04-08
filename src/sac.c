#include <stdio.h>
#include <stdlib.h>

#include "..\lib\commun.h"

#include "..\lib\character.h"
#include "..\lib\texte_confirmation.h"
#include "..\lib\affichage_message.h"

/*!
 *
 * \file sac.c
 * \brief A FINIR.
 * \author Jeremy BOURGOUIN
 *
 */

/*!
 *
 * \fn ouverture_sac(game_t *game, character_t *character, SDL_Texture *texture_render_menu_ig, SDL_bool *echap_relache, SDL_bool combat)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * \param texture_render_menu_ig A FINIR.
 * \param echap_relache A FINIR.
 * \param combat A FINIR.
 *
 */

void ouverture_sac(game_t *game, character_t *character, SDL_Texture *texture_render_menu_ig, SDL_bool *echap_relache, SDL_bool combat)
{
    /*--- Initialization variable ------------------------------------------------*/

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};

    SDL_Surface *surf_sac = NULL, *surf_retour = NULL, *surf_cadre_sac = NULL, *surf_cadre_potions = NULL, *surf_potions = NULL, *surf_cadre_rouge_potions = NULL, *surf_effet_petite_popo_soin = NULL, *surf_effet_moyenne_popo_soin = NULL, *surf_effet_petite_popo_mana = NULL, *surf_effet_moyenne_popo_mana = NULL, *surf_effet_popo_puissance = NULL, *surf_effet_popo_agi = NULL, *surf_possede = NULL;
    SDL_Surface *surf_nb_petite_popo_soin = NULL, *surf_nb_moyenne_popo_soin = NULL, *surf_nb_petite_popo_mana = NULL, *surf_nb_moyenne_popo_mana = NULL, *surf_nb_popo_puissance = NULL, *surf_nb_popo_agi = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool sac_bool = SDL_TRUE;
    SDL_bool potion_utilise_bool = SDL_FALSE;
    SDL_Event event;

    int selection_vertical = 0, selection_horizontal = 0;

    SDL_Texture *texture_render_sac = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

    /*--- End Initialization variable --------------------------------------------*/

    /*---texture "cadre sac"--------------------------------------------------------*/

    surf_cadre_sac = SDL_LoadBMP("src\\image\\cadre_caracteristiques.bmp");
    if (surf_cadre_sac == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre_sac menu in game");
    }

    SDL_Texture *cadre_sac = SDL_CreateTextureFromSurface(game->render, surf_cadre_sac);
    if (cadre_sac == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_sac menu in gam");
    }

    SDL_Rect pos_cadre_sac;
    pos_cadre_sac.w = (*game->WINDOWWIDTH) * 950 / 1280;
    pos_cadre_sac.h = (*game->WINDOWHEIGHT) * 600 / 720;
    pos_cadre_sac.x = (*game->WINDOWWIDTH) / 2 - pos_cadre_sac.w / 2;
    pos_cadre_sac.y = (*game->WINDOWHEIGHT) / 2 - pos_cadre_sac.h / 2;

    /*------------------------------------------------------------------------------------*/

    /*---texture fond cadre sac--------------------------------------------------------*/

    SDL_Texture *fond_cadre_sac = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre_sac.w, pos_cadre_sac.h);
    if (fond_cadre_sac == NULL)
    {
        SDL_ExitWithError("probleme texture fond cadre");
    }

    SDL_Rect pos_fond_cadre_sac;
    pos_fond_cadre_sac.x = pos_cadre_sac.x;
    pos_fond_cadre_sac.y = pos_cadre_sac.y;
    pos_fond_cadre_sac.w = pos_cadre_sac.w;
    pos_fond_cadre_sac.h = pos_cadre_sac.h;

    SDL_Rect rect_fond_cadre_sac;
    rect_fond_cadre_sac.x = (*game->WINDOWWIDTH) * 12 / 1280;
    rect_fond_cadre_sac.y = (*game->WINDOWHEIGHT) * 12 / 720;
    rect_fond_cadre_sac.w = pos_fond_cadre_sac.w - 2 * rect_fond_cadre_sac.x + 1;
    rect_fond_cadre_sac.h = pos_fond_cadre_sac.h - 2 * rect_fond_cadre_sac.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 240);
    SDL_SetRenderTarget(game->render, fond_cadre_sac);
    SDL_SetTextureBlendMode(fond_cadre_sac, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre_sac);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    /*--- Initialization text "commandes" ------------------------------------------*/

    surf_sac = TTF_RenderText_Blended(game->police, "SAC", blanc);
    if (surf_sac == NULL)
    {
        SDL_ExitWithError("probleme surface sac");
    }
    SDL_Texture *sac = SDL_CreateTextureFromSurface(game->render, surf_sac);
    if (sac == NULL)
    {
        SDL_ExitWithError("probleme texture sac");
    }

    SDL_Rect pos_sac;
    pos_sac.w = (*game->WINDOWWIDTH) * 65 / 1200;
    pos_sac.h = (*game->WINDOWHEIGHT) / 13.5;
    pos_sac.x = (*game->WINDOWWIDTH) / 2 - pos_sac.w / 2;
    pos_sac.y = pos_cadre_sac.y + rect_fond_cadre_sac.y + (*game->WINDOWHEIGHT) * 15 / 720;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "Retour" ----------------------------------------*/

    surf_retour = TTF_RenderText_Blended(game->police, "Retour", rouge);
    if (surf_retour == NULL)
    {
        SDL_ExitWithError("probleme surface retour");
    }
    SDL_Texture *retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
    if (retour == NULL)
    {
        SDL_ExitWithError("probleme texture retour");
    }

    SDL_Rect pos_retour;
    pos_retour.w = (*game->WINDOWWIDTH) * 129 / 1200;
    pos_retour.h = (*game->WINDOWHEIGHT) / 13.5;
    pos_retour.x = pos_cadre_sac.x + rect_fond_cadre_sac.x + (*game->WINDOWWIDTH) * 15 / 1280;
    pos_retour.y = pos_cadre_sac.y + pos_cadre_sac.h - rect_fond_cadre_sac.y - pos_retour.h - (*game->WINDOWHEIGHT) * 20 / 720;
    /*-------------------------------------------------------------------------*/

    /*---texture "cadre potions"--------------------------------------------------------*/

    surf_cadre_potions = SDL_LoadBMP("src\\image\\cadre_potions.bmp");
    if (surf_cadre_potions == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre potions menu in game");
    }

    SDL_Texture *cadre_potions = SDL_CreateTextureFromSurface(game->render, surf_cadre_potions);
    if (cadre_potions == NULL)
    {
        SDL_ExitWithError("probleme texture cadre potions menu in game");
    }
    /*------------------------------------------------------------------------------------*/

    /*---texture petite popo soin--------------------------------------------------------*/

    SDL_Rect pos_cadre_petite_popo_soin;
    pos_cadre_petite_popo_soin.w = (*game->WINDOWWIDTH) * 200 / 1280;
    pos_cadre_petite_popo_soin.h = (*game->WINDOWHEIGHT) * 120 / 720;
    pos_cadre_petite_popo_soin.x = (*game->WINDOWWIDTH) / 2 - pos_cadre_petite_popo_soin.w - (*game->WINDOWWIDTH) * 25 / 1280;
    pos_cadre_petite_popo_soin.y = pos_sac.y + pos_sac.h + (*game->WINDOWHEIGHT) * 25 / 720;

    SDL_Texture *fond_petite_popo_soin = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) * 200 / 1280, (*game->WINDOWHEIGHT) * 120 / 720);
    if (fond_petite_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme texture fond petite popo soin");
    }

    SDL_Rect pos_fond_petite_popo_soin;
    pos_fond_petite_popo_soin.w = pos_cadre_petite_popo_soin.w;
    pos_fond_petite_popo_soin.h = pos_cadre_petite_popo_soin.h;
    pos_fond_petite_popo_soin.x = pos_cadre_petite_popo_soin.x;
    pos_fond_petite_popo_soin.y = pos_cadre_petite_popo_soin.y;

    SDL_Rect rect_fond_petite_popo_soin;
    rect_fond_petite_popo_soin.x = (*game->WINDOWWIDTH) * 12 / 1280;
    rect_fond_petite_popo_soin.y = (*game->WINDOWHEIGHT) * 12 / 720;
    rect_fond_petite_popo_soin.w = pos_fond_petite_popo_soin.w - 2 * rect_fond_petite_popo_soin.x + 1;
    rect_fond_petite_popo_soin.h = pos_fond_petite_popo_soin.h - 2 * rect_fond_petite_popo_soin.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
    SDL_SetRenderTarget(game->render, fond_petite_popo_soin);
    SDL_SetTextureBlendMode(fond_petite_popo_soin, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_petite_popo_soin);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    /*---texture moyenne popo soin--------------------------------------------------------*/

    SDL_Rect pos_cadre_moyenne_popo_soin;
    pos_cadre_moyenne_popo_soin.w = (*game->WINDOWWIDTH) * 200 / 1280;
    pos_cadre_moyenne_popo_soin.h = (*game->WINDOWHEIGHT) * 120 / 720;
    pos_cadre_moyenne_popo_soin.x = pos_fond_petite_popo_soin.x + pos_fond_petite_popo_soin.w + (*game->WINDOWWIDTH) * 50 / 1280;
    pos_cadre_moyenne_popo_soin.y = pos_fond_petite_popo_soin.y;

    SDL_Texture *fond_moyenne_popo_soin = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) * 200 / 1280, (*game->WINDOWHEIGHT) * 120 / 720);
    if (fond_moyenne_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme texture fond moyenne popo soin");
    }

    SDL_Rect pos_fond_moyenne_popo_soin;
    pos_fond_moyenne_popo_soin.w = pos_cadre_moyenne_popo_soin.w;
    pos_fond_moyenne_popo_soin.h = pos_cadre_moyenne_popo_soin.h;
    pos_fond_moyenne_popo_soin.x = pos_cadre_moyenne_popo_soin.x;
    pos_fond_moyenne_popo_soin.y = pos_cadre_moyenne_popo_soin.y;

    SDL_Rect rect_fond_moyenne_popo_soin;
    rect_fond_moyenne_popo_soin.x = (*game->WINDOWWIDTH) * 12 / 1280;
    rect_fond_moyenne_popo_soin.y = (*game->WINDOWHEIGHT) * 12 / 720;
    rect_fond_moyenne_popo_soin.w = pos_fond_moyenne_popo_soin.w - 2 * rect_fond_moyenne_popo_soin.x + 1;
    rect_fond_moyenne_popo_soin.h = pos_fond_moyenne_popo_soin.h - 2 * rect_fond_moyenne_popo_soin.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
    SDL_SetRenderTarget(game->render, fond_moyenne_popo_soin);
    SDL_SetTextureBlendMode(fond_moyenne_popo_soin, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_moyenne_popo_soin);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    /*---texture petite popo mana--------------------------------------------------------*/

    SDL_Rect pos_cadre_petite_popo_mana;
    pos_cadre_petite_popo_mana.w = (*game->WINDOWWIDTH) * 200 / 1280;
    pos_cadre_petite_popo_mana.h = (*game->WINDOWHEIGHT) * 120 / 720;
    pos_cadre_petite_popo_mana.x = (*game->WINDOWWIDTH) / 2 - pos_cadre_petite_popo_mana.w - (*game->WINDOWWIDTH) * 25 / 1280;
    pos_cadre_petite_popo_mana.y = pos_fond_moyenne_popo_soin.y + pos_fond_moyenne_popo_soin.h + (*game->WINDOWHEIGHT) * 20 / 720;

    SDL_Texture *fond_petite_popo_mana = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) * 200 / 1280, (*game->WINDOWHEIGHT) * 120 / 720);
    if (fond_petite_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme texture petite popo mana");
    }

    SDL_Rect pos_fond_petite_popo_mana;
    pos_fond_petite_popo_mana.w = pos_cadre_petite_popo_mana.w;
    pos_fond_petite_popo_mana.h = pos_cadre_petite_popo_mana.h;
    pos_fond_petite_popo_mana.x = pos_cadre_petite_popo_mana.x;
    pos_fond_petite_popo_mana.y = pos_cadre_petite_popo_mana.y;

    SDL_Rect rect_fond_petite_popo_mana;
    rect_fond_petite_popo_mana.x = (*game->WINDOWWIDTH) * 12 / 1280;
    rect_fond_petite_popo_mana.y = (*game->WINDOWHEIGHT) * 12 / 720;
    rect_fond_petite_popo_mana.w = pos_fond_petite_popo_mana.w - 2 * rect_fond_petite_popo_mana.x + 1;
    rect_fond_petite_popo_mana.h = pos_fond_petite_popo_mana.h - 2 * rect_fond_petite_popo_mana.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
    SDL_SetRenderTarget(game->render, fond_petite_popo_mana);
    SDL_SetTextureBlendMode(fond_petite_popo_mana, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_petite_popo_mana);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    /*---texture moyenne popo mana--------------------------------------------------------*/

    SDL_Rect pos_cadre_moyenne_popo_mana;
    pos_cadre_moyenne_popo_mana.w = (*game->WINDOWWIDTH) * 200 / 1280;
    pos_cadre_moyenne_popo_mana.h = (*game->WINDOWHEIGHT) * 120 / 720;
    pos_cadre_moyenne_popo_mana.x = pos_fond_petite_popo_mana.x + pos_fond_petite_popo_mana.w + (*game->WINDOWWIDTH) * 50 / 1280;
    pos_cadre_moyenne_popo_mana.y = pos_fond_petite_popo_mana.y;

    SDL_Texture *fond_moyenne_popo_mana = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) * 200 / 1280, (*game->WINDOWHEIGHT) * 120 / 720);
    if (fond_moyenne_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme texture fond moyenne popo mana");
    }

    SDL_Rect pos_fond_moyenne_popo_mana;
    pos_fond_moyenne_popo_mana.w = pos_cadre_moyenne_popo_mana.w;
    pos_fond_moyenne_popo_mana.h = pos_cadre_moyenne_popo_mana.h;
    pos_fond_moyenne_popo_mana.x = pos_cadre_moyenne_popo_mana.x;
    pos_fond_moyenne_popo_mana.y = pos_cadre_moyenne_popo_mana.y;

    SDL_Rect rect_fond_moyenne_popo_mana;
    rect_fond_moyenne_popo_mana.x = (*game->WINDOWWIDTH) * 12 / 1280;
    rect_fond_moyenne_popo_mana.y = (*game->WINDOWHEIGHT) * 12 / 720;
    rect_fond_moyenne_popo_mana.w = pos_fond_moyenne_popo_mana.w - 2 * rect_fond_moyenne_popo_mana.x + 1;
    rect_fond_moyenne_popo_mana.h = pos_fond_moyenne_popo_mana.h - 2 * rect_fond_moyenne_popo_mana.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
    SDL_SetRenderTarget(game->render, fond_moyenne_popo_mana);
    SDL_SetTextureBlendMode(fond_moyenne_popo_mana, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_moyenne_popo_mana);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    /*---texture popo puissance--------------------------------------------------------*/

    SDL_Rect pos_cadre_popo_puissance;
    pos_cadre_popo_puissance.w = (*game->WINDOWWIDTH) * 200 / 1280;
    pos_cadre_popo_puissance.h = (*game->WINDOWHEIGHT) * 120 / 720;
    pos_cadre_popo_puissance.x = (*game->WINDOWWIDTH) / 2 - pos_cadre_popo_puissance.w - (*game->WINDOWWIDTH) * 25 / 1280;
    pos_cadre_popo_puissance.y = pos_fond_moyenne_popo_mana.y + pos_fond_moyenne_popo_mana.h + (*game->WINDOWHEIGHT) * 20 / 720;

    SDL_Texture *fond_popo_puissance = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) * 200 / 1280, (*game->WINDOWHEIGHT) * 120 / 720);
    if (fond_popo_puissance == NULL)
    {
        SDL_ExitWithError("probleme texture fond popo puissance");
    }

    SDL_Rect pos_fond_popo_puissance;
    pos_fond_popo_puissance.w = pos_cadre_popo_puissance.w;
    pos_fond_popo_puissance.h = pos_cadre_popo_puissance.h;
    pos_fond_popo_puissance.x = pos_cadre_popo_puissance.x;
    pos_fond_popo_puissance.y = pos_cadre_popo_puissance.y;

    SDL_Rect rect_fond_popo_puissance;
    rect_fond_popo_puissance.x = (*game->WINDOWWIDTH) * 12 / 1280;
    rect_fond_popo_puissance.y = (*game->WINDOWHEIGHT) * 12 / 720;
    rect_fond_popo_puissance.w = pos_fond_popo_puissance.w - 2 * rect_fond_popo_puissance.x + 1;
    rect_fond_popo_puissance.h = pos_fond_popo_puissance.h - 2 * rect_fond_popo_puissance.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
    SDL_SetRenderTarget(game->render, fond_popo_puissance);
    SDL_SetTextureBlendMode(fond_popo_puissance, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_popo_puissance);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    /*---texture popo agi--------------------------------------------------------*/

    SDL_Rect pos_cadre_popo_agi;
    pos_cadre_popo_agi.w = (*game->WINDOWWIDTH) * 200 / 1280;
    pos_cadre_popo_agi.h = (*game->WINDOWHEIGHT) * 120 / 720;
    pos_cadre_popo_agi.x = pos_fond_popo_puissance.x + pos_fond_popo_puissance.w + (*game->WINDOWWIDTH) * 50 / 1280;
    pos_cadre_popo_agi.y = pos_fond_popo_puissance.y;

    SDL_Texture *fond_popo_agi = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) * 200 / 1280, (*game->WINDOWHEIGHT) * 120 / 720);
    if (fond_popo_agi == NULL)
    {
        SDL_ExitWithError("probleme texture fond popo agi");
    }

    SDL_Rect pos_fond_popo_agi;
    pos_fond_popo_agi.w = pos_cadre_popo_agi.w;
    pos_fond_popo_agi.h = pos_cadre_popo_agi.h;
    pos_fond_popo_agi.x = pos_cadre_popo_agi.x;
    pos_fond_popo_agi.y = pos_cadre_popo_agi.y;

    SDL_Rect rect_fond_popo_agi;
    rect_fond_popo_agi.x = (*game->WINDOWWIDTH) * 12 / 1280;
    rect_fond_popo_agi.y = (*game->WINDOWHEIGHT) * 12 / 720;
    rect_fond_popo_agi.w = pos_fond_popo_agi.w - 2 * rect_fond_popo_agi.x + 1;
    rect_fond_popo_agi.h = pos_fond_popo_agi.h - 2 * rect_fond_popo_agi.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
    SDL_SetRenderTarget(game->render, fond_popo_agi);
    SDL_SetTextureBlendMode(fond_popo_agi, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_popo_agi);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    /*---surface "image potions"--------------------------------------------------------*/

    surf_potions = SDL_LoadBMP("src\\image\\potions.bmp");
    if (surf_potions == NULL)
    {
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }
    /*------------------------------------------------------------------------------------*/

    /*---texture "petite potion soin"--------------------------------------------------------*/

    SDL_Texture *petite_popo_soin = SDL_CreateTextureFromSurface(game->render, surf_potions);
    if (petite_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme texture petite_popo_soin sac menu in game");
    }

    SDL_Rect pos_petite_popo_soin;
    pos_petite_popo_soin.w = (*game->WINDOWWIDTH) * 40 / 1280;
    pos_petite_popo_soin.h = (*game->WINDOWHEIGHT) * 60 / 720;
    pos_petite_popo_soin.x = pos_cadre_petite_popo_soin.x + rect_fond_petite_popo_soin.x + (*game->WINDOWWIDTH) * 15 / 1280;
    pos_petite_popo_soin.y = pos_cadre_petite_popo_soin.y + rect_fond_petite_popo_soin.y + (*game->WINDOWWIDTH) * 18 / 1280;

    SDL_Rect rect_petite_popo_soin;
    rect_petite_popo_soin.x = 4;
    rect_petite_popo_soin.y = 2;
    rect_petite_popo_soin.w = 8;
    rect_petite_popo_soin.h = 12;

    /*------------------------------------------------------------------------------------*/

    /*---texture "moyenne potion soin"--------------------------------------------------------*/

    SDL_Texture *moyenne_popo_soin = SDL_CreateTextureFromSurface(game->render, surf_potions);
    if (moyenne_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme texture moyenne_popo_soin sac menu in game");
    }

    SDL_Rect pos_moyenne_popo_soin;
    pos_moyenne_popo_soin.w = (*game->WINDOWWIDTH) * 60 / 1280;
    pos_moyenne_popo_soin.h = (*game->WINDOWHEIGHT) * 60 / 720;
    pos_moyenne_popo_soin.x = pos_cadre_moyenne_popo_soin.x + rect_fond_moyenne_popo_soin.x + (*game->WINDOWWIDTH) * 15 / 1280;
    pos_moyenne_popo_soin.y = pos_cadre_moyenne_popo_soin.y + rect_fond_moyenne_popo_soin.y + (*game->WINDOWWIDTH) * 18 / 1280;

    SDL_Rect rect_moyenne_popo_soin;
    rect_moyenne_popo_soin.x = 129;
    rect_moyenne_popo_soin.y = 1;
    rect_moyenne_popo_soin.w = 14;
    rect_moyenne_popo_soin.h = 14;

    /*------------------------------------------------------------------------------------*/

    /*---texture "petite potion mana"--------------------------------------------------------*/

    SDL_Texture *petite_popo_mana = SDL_CreateTextureFromSurface(game->render, surf_potions);
    if (petite_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme texture petite_popo_mana sac menu in game");
    }

    SDL_Rect pos_petite_popo_mana;
    pos_petite_popo_mana.w = (*game->WINDOWWIDTH) * 40 / 1280;
    pos_petite_popo_mana.h = (*game->WINDOWHEIGHT) * 60 / 720;
    pos_petite_popo_mana.x = pos_cadre_petite_popo_mana.x + rect_fond_petite_popo_mana.x + (*game->WINDOWWIDTH) * 15 / 1280;
    pos_petite_popo_mana.y = pos_cadre_petite_popo_mana.y + rect_fond_petite_popo_mana.y + (*game->WINDOWWIDTH) * 18 / 1280;

    SDL_Rect rect_petite_popo_mana;
    rect_petite_popo_mana.x = 4;
    rect_petite_popo_mana.y = 82;
    rect_petite_popo_mana.w = 8;
    rect_petite_popo_mana.h = 12;

    /*------------------------------------------------------------------------------------*/

    /*---texture "moyenne potion mana"--------------------------------------------------------*/

    SDL_Texture *moyenne_popo_mana = SDL_CreateTextureFromSurface(game->render, surf_potions);
    if (moyenne_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme texture moyenne_popo_mana sac menu in game");
    }

    SDL_Rect pos_moyenne_popo_mana;
    pos_moyenne_popo_mana.w = (*game->WINDOWWIDTH) * 60 / 1280;
    pos_moyenne_popo_mana.h = (*game->WINDOWHEIGHT) * 60 / 720;
    pos_moyenne_popo_mana.x = pos_cadre_moyenne_popo_mana.x + rect_fond_moyenne_popo_mana.x + (*game->WINDOWWIDTH) * 15 / 1280;
    pos_moyenne_popo_mana.y = pos_cadre_moyenne_popo_mana.y + rect_fond_moyenne_popo_mana.y + (*game->WINDOWWIDTH) * 18 / 1280;

    SDL_Rect rect_moyenne_popo_mana;
    rect_moyenne_popo_mana.x = 129;
    rect_moyenne_popo_mana.y = 81;
    rect_moyenne_popo_mana.w = 14;
    rect_moyenne_popo_mana.h = 14;

    /*------------------------------------------------------------------------------------*/

    /*---texture "potion puissance"--------------------------------------------------------*/

    SDL_Texture *popo_puissance = SDL_CreateTextureFromSurface(game->render, surf_potions);
    if (popo_puissance == NULL)
    {
        SDL_ExitWithError("probleme texture popo_puissance sac menu in game");
    }

    SDL_Rect pos_popo_puissance;
    pos_popo_puissance.w = (*game->WINDOWWIDTH) * 60 / 1280;
    pos_popo_puissance.h = (*game->WINDOWHEIGHT) * 60 / 720;
    pos_popo_puissance.x = pos_cadre_popo_puissance.x + rect_fond_popo_puissance.x + (*game->WINDOWWIDTH) * 15 / 1280;
    pos_popo_puissance.y = pos_cadre_popo_puissance.y + rect_fond_popo_puissance.y + (*game->WINDOWWIDTH) * 18 / 1280;

    SDL_Rect rect_popo_puissance;
    rect_popo_puissance.x = 129;
    rect_popo_puissance.y = 33;
    rect_popo_puissance.w = 14;
    rect_popo_puissance.h = 14;

    /*------------------------------------------------------------------------------------*/

    /*---texture "potion puissance"--------------------------------------------------------*/

    SDL_Texture *popo_agi = SDL_CreateTextureFromSurface(game->render, surf_potions);
    if (popo_agi == NULL)
    {
        SDL_ExitWithError("probleme texture popo_agi sac menu in game");
    }

    SDL_Rect pos_popo_agi;
    pos_popo_agi.w = (*game->WINDOWWIDTH) * 60 / 1280;
    pos_popo_agi.h = (*game->WINDOWHEIGHT) * 60 / 720;
    pos_popo_agi.x = pos_cadre_popo_agi.x + rect_fond_popo_agi.x + (*game->WINDOWWIDTH) * 15 / 1280;
    pos_popo_agi.y = pos_cadre_popo_agi.y + rect_fond_popo_agi.y + (*game->WINDOWWIDTH) * 18 / 1280;

    SDL_Rect rect_popo_agi;
    rect_popo_agi.x = 129;
    rect_popo_agi.y = 49;
    rect_popo_agi.w = 14;
    rect_popo_agi.h = 14;

    /*------------------------------------------------------------------------------------*/

    /*--- Initialization text "effet petite popo soin" ----------------------------------------*/

    surf_effet_petite_popo_soin = TTF_RenderText_Blended(game->police, "Effet : +20 PV", blanc);
    if (surf_effet_petite_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme surface effet_petite_popo_soin sac menu in game");
    }
    SDL_Texture *effet_petite_popo_soin = SDL_CreateTextureFromSurface(game->render, surf_effet_petite_popo_soin);
    if (effet_petite_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme texture effet_petite_popo_soin sac menu in game");
    }

    SDL_Rect pos_effet_petite_popo_soin;
    pos_effet_petite_popo_soin.w = (*game->WINDOWWIDTH) * 83 / 1280;
    pos_effet_petite_popo_soin.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_effet_petite_popo_soin.x = pos_petite_popo_soin.x + pos_petite_popo_soin.w + (*game->WINDOWWIDTH) * 19 / 1280;
    pos_effet_petite_popo_soin.y = pos_cadre_petite_popo_soin.y + rect_fond_petite_popo_soin.y + (*game->WINDOWHEIGHT) * 18 / 720;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "effet moyenne popo soin" ----------------------------------------*/

    surf_effet_moyenne_popo_soin = TTF_RenderText_Blended(game->police, "Effet : +50 PV", blanc);
    if (surf_effet_moyenne_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme surface effet_moyenne_popo_soin sac menu in game");
    }
    SDL_Texture *effet_moyenne_popo_soin = SDL_CreateTextureFromSurface(game->render, surf_effet_moyenne_popo_soin);
    if (effet_moyenne_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme texture effet_moyenne_popo_soin sac menu in game");
    }

    SDL_Rect pos_effet_moyenne_popo_soin;
    pos_effet_moyenne_popo_soin.w = (*game->WINDOWWIDTH) * 83 / 1280;
    pos_effet_moyenne_popo_soin.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_effet_moyenne_popo_soin.x = pos_moyenne_popo_soin.x + pos_moyenne_popo_soin.w + (*game->WINDOWWIDTH) * 9 / 1280;
    pos_effet_moyenne_popo_soin.y = pos_cadre_moyenne_popo_soin.y + rect_fond_moyenne_popo_soin.y + (*game->WINDOWHEIGHT) * 18 / 720;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "effet petite popo mana" ----------------------------------------*/

    surf_effet_petite_popo_mana = TTF_RenderText_Blended(game->police, "Effet : +20 PM", blanc);
    if (surf_effet_petite_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme surface effet_petite_popo_mana sac menu in game");
    }
    SDL_Texture *effet_petite_popo_mana = SDL_CreateTextureFromSurface(game->render, surf_effet_petite_popo_mana);
    if (effet_petite_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme texture effet_petite_popo_mana sac menu in game");
    }

    SDL_Rect pos_effet_petite_popo_mana;
    pos_effet_petite_popo_mana.w = (*game->WINDOWWIDTH) * 84 / 1280;
    pos_effet_petite_popo_mana.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_effet_petite_popo_mana.x = pos_petite_popo_mana.x + pos_petite_popo_mana.w + (*game->WINDOWWIDTH) * 19 / 1280;
    pos_effet_petite_popo_mana.y = pos_cadre_petite_popo_mana.y + rect_fond_petite_popo_mana.y + (*game->WINDOWHEIGHT) * 18 / 720;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "effet moyenne popo mana" ----------------------------------------*/

    surf_effet_moyenne_popo_mana = TTF_RenderText_Blended(game->police, "Effet : +50 PM", blanc);
    if (surf_effet_moyenne_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme surface effet_moyenne_popo_mana sac menu in game");
    }
    SDL_Texture *effet_moyenne_popo_mana = SDL_CreateTextureFromSurface(game->render, surf_effet_moyenne_popo_mana);
    if (effet_moyenne_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme texture effet_moyenne_popo_mana sac menu in game");
    }

    SDL_Rect pos_effet_moyenne_popo_mana;
    pos_effet_moyenne_popo_mana.w = (*game->WINDOWWIDTH) * 84 / 1280;
    pos_effet_moyenne_popo_mana.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_effet_moyenne_popo_mana.x = pos_moyenne_popo_mana.x + pos_moyenne_popo_mana.w + (*game->WINDOWWIDTH) * 9 / 1280;
    pos_effet_moyenne_popo_mana.y = pos_cadre_moyenne_popo_mana.y + rect_fond_moyenne_popo_mana.y + (*game->WINDOWHEIGHT) * 18 / 720;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "effet popo puissance" ----------------------------------------*/

    surf_effet_popo_puissance = TTF_RenderText_Blended(game->police, "Effet : +10 PUI", blanc);
    if (surf_effet_popo_puissance == NULL)
    {
        SDL_ExitWithError("probleme surface effet_popo_puissance sac menu in game");
    }
    SDL_Texture *effet_popo_puissance = SDL_CreateTextureFromSurface(game->render, surf_effet_popo_puissance);
    if (effet_popo_puissance == NULL)
    {
        SDL_ExitWithError("probleme texture effet_popo_puissance sac menu in game");
    }

    SDL_Rect pos_effet_popo_puissance;
    pos_effet_popo_puissance.w = (*game->WINDOWWIDTH) * 84 / 1280;
    pos_effet_popo_puissance.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_effet_popo_puissance.x = pos_popo_puissance.x + pos_popo_puissance.w + (*game->WINDOWWIDTH) * 9 / 1280;
    pos_effet_popo_puissance.y = pos_cadre_popo_puissance.y + rect_fond_popo_puissance.y + (*game->WINDOWHEIGHT) * 18 / 720;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "effet popo agi" ----------------------------------------*/

    surf_effet_popo_agi = TTF_RenderText_Blended(game->police, "Effet : +10 AGI", blanc);
    if (surf_effet_popo_agi == NULL)
    {
        SDL_ExitWithError("probleme surface effet_popo_agi sac menu in game");
    }
    SDL_Texture *effet_popo_agi = SDL_CreateTextureFromSurface(game->render, surf_effet_popo_agi);
    if (effet_popo_agi == NULL)
    {
        SDL_ExitWithError("probleme texture effet_popo_agi sac menu in game");
    }

    SDL_Rect pos_effet_popo_agi;
    pos_effet_popo_agi.w = (*game->WINDOWWIDTH) * 84 / 1280;
    pos_effet_popo_agi.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_effet_popo_agi.x = pos_popo_agi.x + pos_popo_agi.w + (*game->WINDOWWIDTH) * 9 / 1280;
    pos_effet_popo_agi.y = pos_cadre_popo_agi.y + rect_fond_popo_agi.y + (*game->WINDOWHEIGHT) * 18 / 720;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "effet popo agi" ----------------------------------------*/

    surf_possede = TTF_RenderText_Blended(game->police, "Possede : ", blanc);
    if (surf_possede == NULL)
    {
        SDL_ExitWithError("probleme surface possede sac menu in game");
    }
    SDL_Texture *possede = SDL_CreateTextureFromSurface(game->render, surf_possede);
    if (effet_popo_agi == NULL)
    {
        SDL_ExitWithError("probleme texture possede sac menu in game");
    }

    SDL_Rect pos_possede_petite_popo_soin;
    pos_possede_petite_popo_soin.w = (*game->WINDOWWIDTH) * 60 / 1280;
    pos_possede_petite_popo_soin.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_possede_petite_popo_soin.x = pos_effet_petite_popo_soin.x;
    pos_possede_petite_popo_soin.y = pos_effet_petite_popo_soin.y + pos_effet_petite_popo_soin.h + (*game->WINDOWHEIGHT) * 20 / 720;

    SDL_Rect pos_possede_moyenne_popo_soin;
    pos_possede_moyenne_popo_soin.w = (*game->WINDOWWIDTH) * 60 / 1280;
    pos_possede_moyenne_popo_soin.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_possede_moyenne_popo_soin.x = pos_effet_moyenne_popo_soin.x;
    pos_possede_moyenne_popo_soin.y = pos_effet_moyenne_popo_soin.y + pos_effet_moyenne_popo_soin.h + (*game->WINDOWHEIGHT) * 20 / 720;

    SDL_Rect pos_possede_petite_popo_mana;
    pos_possede_petite_popo_mana.w = (*game->WINDOWWIDTH) * 60 / 1280;
    pos_possede_petite_popo_mana.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_possede_petite_popo_mana.x = pos_effet_petite_popo_mana.x;
    pos_possede_petite_popo_mana.y = pos_effet_petite_popo_mana.y + pos_effet_petite_popo_mana.h + (*game->WINDOWHEIGHT) * 20 / 720;

    SDL_Rect pos_possede_moyenne_popo_mana;
    pos_possede_moyenne_popo_mana.w = (*game->WINDOWWIDTH) * 60 / 1280;
    pos_possede_moyenne_popo_mana.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_possede_moyenne_popo_mana.x = pos_effet_moyenne_popo_mana.x;
    pos_possede_moyenne_popo_mana.y = pos_effet_moyenne_popo_mana.y + pos_effet_moyenne_popo_mana.h + (*game->WINDOWHEIGHT) * 20 / 720;

    SDL_Rect pos_possede_popo_puissance;
    pos_possede_popo_puissance.w = (*game->WINDOWWIDTH) * 60 / 1280;
    pos_possede_popo_puissance.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_possede_popo_puissance.x = pos_effet_popo_puissance.x;
    pos_possede_popo_puissance.y = pos_effet_popo_puissance.y + pos_effet_popo_puissance.h + (*game->WINDOWHEIGHT) * 20 / 720;

    SDL_Rect pos_possede_popo_agi;
    pos_possede_popo_agi.w = (*game->WINDOWWIDTH) * 60 / 1280;
    pos_possede_popo_agi.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_possede_popo_agi.x = pos_effet_popo_agi.x;
    pos_possede_popo_agi.y = pos_effet_popo_agi.y + pos_effet_popo_agi.h + (*game->WINDOWHEIGHT) * 20 / 720;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "nb petite popo soin" ----------------------------------------*/
    char character_nb_petite_popo_soin[10];

    if (character->nb_petite_popo_soin > 999)
    {
        character_nb_petite_popo_soin[0] = '9';
        character_nb_petite_popo_soin[1] = '9';
        character_nb_petite_popo_soin[2] = '9';
        character_nb_petite_popo_soin[3] = '+';
    }
    else
        itoa(character->nb_petite_popo_soin, character_nb_petite_popo_soin, 10);

    surf_nb_petite_popo_soin = TTF_RenderText_Blended(game->police, character_nb_petite_popo_soin, blanc);
    if (surf_nb_petite_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme surface nb_petite_popo_soin sac menu in game");
    }
    SDL_Texture *nb_petite_popo_soin = SDL_CreateTextureFromSurface(game->render, surf_nb_petite_popo_soin);
    if (nb_petite_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme texture nb_petite_popo_soin sac menu in game");
    }

    SDL_Rect pos_nb_petite_popo_soin;
    pos_nb_petite_popo_soin.w = strlen(character_nb_petite_popo_soin) * (*game->WINDOWWIDTH) * 6 / 1280;
    pos_nb_petite_popo_soin.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_nb_petite_popo_soin.x = pos_possede_petite_popo_soin.x + pos_possede_petite_popo_soin.w;

    pos_nb_petite_popo_soin.y = pos_possede_petite_popo_soin.y;
    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "nb moyenne popo soin" ----------------------------------------*/
    char character_nb_moyenne_popo_soin[10];

    if (character->nb_moyenne_popo_soin > 999)
    {
        character_nb_moyenne_popo_soin[0] = '9';
        character_nb_moyenne_popo_soin[1] = '9';
        character_nb_moyenne_popo_soin[2] = '9';
        character_nb_moyenne_popo_soin[3] = '+';
    }
    else
        itoa(character->nb_moyenne_popo_soin, character_nb_moyenne_popo_soin, 10);

    surf_nb_moyenne_popo_soin = TTF_RenderText_Blended(game->police, character_nb_moyenne_popo_soin, blanc);
    if (surf_nb_moyenne_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme surface nb_moyenne_popo_soin sac menu in game");
    }
    SDL_Texture *nb_moyenne_popo_soin = SDL_CreateTextureFromSurface(game->render, surf_nb_moyenne_popo_soin);
    if (nb_moyenne_popo_soin == NULL)
    {
        SDL_ExitWithError("probleme texture nb_moyenne_popo_soin sac menu in game");
    }

    SDL_Rect pos_nb_moyenne_popo_soin;
    pos_nb_moyenne_popo_soin.w = strlen(character_nb_moyenne_popo_soin) * (*game->WINDOWWIDTH) * 6 / 1280;
    pos_nb_moyenne_popo_soin.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_nb_moyenne_popo_soin.x = pos_possede_moyenne_popo_soin.x + pos_possede_moyenne_popo_soin.w;
    pos_nb_moyenne_popo_soin.y = pos_possede_moyenne_popo_soin.y;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "nb petite popo mana" ----------------------------------------*/

    char character_nb_petite_popo_mana[10];

    if (character->nb_petite_popo_mana > 999)
    {
        character_nb_petite_popo_mana[0] = '9';
        character_nb_petite_popo_mana[1] = '9';
        character_nb_petite_popo_mana[2] = '9';
        character_nb_petite_popo_mana[3] = '+';
    }
    else
        itoa(character->nb_petite_popo_mana, character_nb_petite_popo_mana, 10);

    surf_nb_petite_popo_mana = TTF_RenderText_Blended(game->police, character_nb_petite_popo_mana, blanc);
    if (surf_nb_petite_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme surface nb_petite_popo_mana sac menu in game");
    }
    SDL_Texture *nb_petite_popo_mana = SDL_CreateTextureFromSurface(game->render, surf_nb_petite_popo_mana);
    if (nb_petite_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme texture nb_petite_popo_mana sac menu in game");
    }

    SDL_Rect pos_nb_petite_popo_mana;
    pos_nb_petite_popo_mana.w = strlen(character_nb_petite_popo_mana) * (*game->WINDOWWIDTH) * 6 / 1280;
    pos_nb_petite_popo_mana.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_nb_petite_popo_mana.x = pos_possede_petite_popo_mana.x + pos_possede_petite_popo_mana.w;
    pos_nb_petite_popo_mana.y = pos_possede_petite_popo_mana.y;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "nb moyenne popo mana" ----------------------------------------*/

    char character_nb_moyenne_popo_mana[10];

    if (character->nb_moyenne_popo_mana > 999)
    {
        character_nb_moyenne_popo_mana[0] = '9';
        character_nb_moyenne_popo_mana[1] = '9';
        character_nb_moyenne_popo_mana[2] = '9';
        character_nb_moyenne_popo_mana[3] = '+';
    }
    else
        itoa(character->nb_moyenne_popo_mana, character_nb_moyenne_popo_mana, 10);

    surf_nb_moyenne_popo_mana = TTF_RenderText_Blended(game->police, character_nb_moyenne_popo_mana, blanc);
    if (surf_nb_moyenne_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme surface nb_moyenne_popo_mana sac menu in game");
    }
    SDL_Texture *nb_moyenne_popo_mana = SDL_CreateTextureFromSurface(game->render, surf_nb_moyenne_popo_mana);
    if (nb_moyenne_popo_mana == NULL)
    {
        SDL_ExitWithError("probleme texture nb_moyenne_popo_mana sac menu in game");
    }

    SDL_Rect pos_nb_moyenne_popo_mana;
    pos_nb_moyenne_popo_mana.w = strlen(character_nb_moyenne_popo_mana) * (*game->WINDOWWIDTH) * 6 / 1280;
    pos_nb_moyenne_popo_mana.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_nb_moyenne_popo_mana.x = pos_possede_moyenne_popo_mana.x + pos_possede_moyenne_popo_mana.w;
    pos_nb_moyenne_popo_mana.y = pos_possede_moyenne_popo_mana.y;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "nb popo puissance" ----------------------------------------*/

    char character_nb_popo_puissance[10];

    if (character->nb_popo_puissance > 999)
    {
        character_nb_popo_puissance[0] = '9';
        character_nb_popo_puissance[1] = '9';
        character_nb_popo_puissance[2] = '9';
        character_nb_popo_puissance[3] = '+';
    }
    else
        itoa(character->nb_popo_puissance, character_nb_popo_puissance, 10);

    surf_nb_popo_puissance = TTF_RenderText_Blended(game->police, character_nb_popo_puissance, blanc);
    if (surf_nb_popo_puissance == NULL)
    {
        SDL_ExitWithError("probleme surface nb_popo_puissance sac menu in game");
    }
    SDL_Texture *nb_popo_puissance = SDL_CreateTextureFromSurface(game->render, surf_nb_popo_puissance);
    if (nb_popo_puissance == NULL)
    {
        SDL_ExitWithError("probleme texture nb_popo_puissance sac menu in game");
    }

    SDL_Rect pos_nb_popo_puissance;
    pos_nb_popo_puissance.w = strlen(character_nb_popo_puissance) * (*game->WINDOWWIDTH) * 6 / 1280;
    pos_nb_popo_puissance.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_nb_popo_puissance.x = pos_possede_popo_puissance.x + pos_possede_popo_puissance.w;
    pos_nb_popo_puissance.y = pos_possede_popo_puissance.y;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "nb popo agi" ----------------------------------------*/

    char character_nb_popo_agi[10];

    if (character->nb_popo_agi > 999)
    {
        character_nb_popo_agi[0] = '9';
        character_nb_popo_agi[1] = '9';
        character_nb_popo_agi[2] = '9';
        character_nb_popo_agi[3] = '+';
    }
    else
        itoa(character->nb_popo_agi, character_nb_popo_agi, 10);

    surf_nb_popo_agi = TTF_RenderText_Blended(game->police, character_nb_popo_agi, blanc);
    if (surf_nb_popo_agi == NULL)
    {
        SDL_ExitWithError("probleme surface nb_popo_agi sac menu in game");
    }
    SDL_Texture *nb_popo_agi = SDL_CreateTextureFromSurface(game->render, surf_nb_popo_agi);
    if (nb_popo_agi == NULL)
    {
        SDL_ExitWithError("probleme texture nb_popo_agi sac menu in game");
    }

    SDL_Rect pos_nb_popo_agi;
    pos_nb_popo_agi.w = strlen(character_nb_popo_agi) * (*game->WINDOWWIDTH) * 6 / 1280;
    pos_nb_popo_agi.h = (*game->WINDOWHEIGHT) * 20 / 720;
    pos_nb_popo_agi.x = pos_possede_popo_agi.x + pos_possede_popo_agi.w;
    pos_nb_popo_agi.y = pos_possede_popo_agi.y;

    /*-------------------------------------------------------------------------*/

    /*---texture "cadre rouge potions"--------------------------------------------------------*/

    surf_cadre_rouge_potions = SDL_LoadBMP("src\\image\\cadre_rouge_potions.bmp");
    if (surf_cadre_rouge_potions == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre rouge potions menu in game");
    }

    SDL_Texture *cadre_rouge_potions = SDL_CreateTextureFromSurface(game->render, surf_cadre_rouge_potions);
    if (cadre_rouge_potions == NULL)
    {
        SDL_ExitWithError("probleme texture cadre rouge potions menu in game");
    }
    SDL_Rect pos_cadre_rouge_potions;
    pos_cadre_rouge_potions.w = pos_cadre_petite_popo_soin.w;
    pos_cadre_rouge_potions.h = pos_cadre_petite_popo_soin.h;
    pos_cadre_rouge_potions.x = pos_cadre_petite_popo_soin.x;
    pos_cadre_rouge_potions.y = pos_cadre_petite_popo_soin.y;

    /*------------------------------------------------------------------------------------*/

    SDL_Rect pos_texture_render_menu_ig;
    pos_texture_render_menu_ig.x = 0;
    pos_texture_render_menu_ig.y = 0;
    pos_texture_render_menu_ig.w = (*game->WINDOWWIDTH);
    pos_texture_render_menu_ig.h = (*game->WINDOWHEIGHT);

    /*--- Main Loop -----------------------------------------------------------*/

    while (sac_bool && *game->program_launch)
    {
        while (SDL_PollEvent(&event))
        {
            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                *game->program_launch = SDL_FALSE;
                sac_bool = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                if (echap_relache != NULL)
                    *echap_relache = SDL_FALSE;

                sac_bool = SDL_FALSE;
            }

            /*--- End Event to Exit Program --------------------------------------*/

            if (keyState[SDL_SCANCODE_DOWN] && event.type == SDL_KEYDOWN)
            {
                selection_vertical++;
            }

            if (keyState[SDL_SCANCODE_UP] && event.type == SDL_KEYDOWN)
            {
                selection_vertical--;
            }

            if (keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN && selection_horizontal)
            {
                if (combat && selection_vertical != 3)
                    selection_horizontal--;

                if (!combat && selection_vertical != 2)
                    selection_horizontal--;
            }

            if (keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN && !selection_horizontal)
            {
                if (combat && selection_vertical != 3)
                    selection_horizontal++;

                if (!combat && selection_vertical != 2)
                    selection_horizontal++;
            }

            if (combat)
            {
                if (selection_vertical < 0)
                    selection_vertical = 3;
                selection_vertical %= 4;
            }
            else
            {
                if (selection_vertical < 0)
                    selection_vertical = 2;
                selection_vertical %= 3;
            }

            if (selection_vertical == 0)
            {
                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);

                if (selection_horizontal == 0)
                {
                    pos_cadre_rouge_potions.x = pos_cadre_petite_popo_soin.x;
                    pos_cadre_rouge_potions.y = pos_cadre_petite_popo_soin.y;
                }

                else
                {
                    pos_cadre_rouge_potions.x = pos_cadre_moyenne_popo_soin.x;
                    pos_cadre_rouge_potions.y = pos_cadre_moyenne_popo_soin.y;
                }
            }

            if (selection_vertical == 1)
            {
                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);

                if (selection_horizontal == 0)
                {
                    pos_cadre_rouge_potions.x = pos_cadre_petite_popo_mana.x;
                    pos_cadre_rouge_potions.y = pos_cadre_petite_popo_mana.y;
                }

                else
                {
                    pos_cadre_rouge_potions.x = pos_cadre_moyenne_popo_mana.x;
                    pos_cadre_rouge_potions.y = pos_cadre_moyenne_popo_mana.y;
                }
            }

            if (combat && selection_vertical == 2)
            {
                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);

                if (selection_horizontal == 0)
                {
                    pos_cadre_rouge_potions.x = pos_cadre_popo_puissance.x;
                    pos_cadre_rouge_potions.y = pos_cadre_popo_puissance.y;
                }

                else
                {
                    pos_cadre_rouge_potions.x = pos_cadre_popo_agi.x;
                    pos_cadre_rouge_potions.y = pos_cadre_popo_agi.y;
                }
            }

            if (!combat && selection_vertical == 2)
            {
                surf_retour = TTF_RenderText_Blended(game->police, "Retour", rouge);
            }

            if (combat && selection_vertical == 3)
            {
                surf_retour = TTF_RenderText_Blended(game->police, "Retour", rouge);
            }

            retour = SDL_CreateTextureFromSurface(game->render, surf_retour);

            SDL_RenderClear(game->render);
            SDL_SetRenderTarget(game->render, texture_render_sac);

            SDL_RenderCopy(game->render, texture_render_menu_ig, NULL, &pos_texture_render_menu_ig);
            SDL_RenderCopy(game->render, fond_cadre_sac, NULL, &pos_fond_cadre_sac);
            SDL_RenderCopy(game->render, cadre_sac, NULL, &pos_cadre_sac);
            SDL_RenderCopy(game->render, sac, NULL, &pos_sac);
            SDL_RenderCopy(game->render, retour, NULL, &pos_retour);

            SDL_RenderCopy(game->render, cadre_potions, NULL, &pos_cadre_petite_popo_soin);
            SDL_RenderCopy(game->render, cadre_potions, NULL, &pos_cadre_moyenne_popo_soin);
            SDL_RenderCopy(game->render, cadre_potions, NULL, &pos_cadre_petite_popo_mana);
            SDL_RenderCopy(game->render, cadre_potions, NULL, &pos_cadre_moyenne_popo_mana);
            SDL_RenderCopy(game->render, cadre_potions, NULL, &pos_cadre_popo_puissance);
            SDL_RenderCopy(game->render, cadre_potions, NULL, &pos_cadre_popo_agi);

            if (combat && selection_vertical != 3)
                SDL_RenderCopy(game->render, cadre_rouge_potions, NULL, &pos_cadre_rouge_potions);

            if (!combat && selection_vertical != 2)
                SDL_RenderCopy(game->render, cadre_rouge_potions, NULL, &pos_cadre_rouge_potions);

            SDL_RenderCopy(game->render, fond_petite_popo_soin, NULL, &pos_fond_petite_popo_soin);
            SDL_RenderCopy(game->render, fond_moyenne_popo_soin, NULL, &pos_fond_moyenne_popo_soin);
            SDL_RenderCopy(game->render, fond_petite_popo_mana, NULL, &pos_fond_petite_popo_mana);
            SDL_RenderCopy(game->render, fond_moyenne_popo_mana, NULL, &pos_fond_moyenne_popo_mana);
            SDL_RenderCopy(game->render, fond_popo_puissance, NULL, &pos_fond_popo_puissance);
            SDL_RenderCopy(game->render, fond_popo_agi, NULL, &pos_fond_popo_agi);

            SDL_RenderCopy(game->render, petite_popo_soin, &rect_petite_popo_soin, &pos_petite_popo_soin);
            SDL_RenderCopy(game->render, moyenne_popo_soin, &rect_moyenne_popo_soin, &pos_moyenne_popo_soin);
            SDL_RenderCopy(game->render, petite_popo_mana, &rect_petite_popo_mana, &pos_petite_popo_mana);
            SDL_RenderCopy(game->render, moyenne_popo_mana, &rect_moyenne_popo_mana, &pos_moyenne_popo_mana);
            SDL_RenderCopy(game->render, popo_puissance, &rect_popo_puissance, &pos_popo_puissance);
            SDL_RenderCopy(game->render, popo_agi, &rect_popo_agi, &pos_popo_agi);

            SDL_RenderCopy(game->render, effet_petite_popo_soin, NULL, &pos_effet_petite_popo_soin);
            SDL_RenderCopy(game->render, effet_moyenne_popo_soin, NULL, &pos_effet_moyenne_popo_soin);
            SDL_RenderCopy(game->render, effet_petite_popo_mana, NULL, &pos_effet_petite_popo_mana);
            SDL_RenderCopy(game->render, effet_moyenne_popo_mana, NULL, &pos_effet_moyenne_popo_mana);
            SDL_RenderCopy(game->render, effet_popo_puissance, NULL, &pos_effet_popo_puissance);
            SDL_RenderCopy(game->render, effet_popo_agi, NULL, &pos_effet_popo_agi);

            SDL_RenderCopy(game->render, possede, NULL, &pos_possede_petite_popo_soin);
            SDL_RenderCopy(game->render, possede, NULL, &pos_possede_moyenne_popo_soin);
            SDL_RenderCopy(game->render, possede, NULL, &pos_possede_petite_popo_mana);
            SDL_RenderCopy(game->render, possede, NULL, &pos_possede_moyenne_popo_mana);
            SDL_RenderCopy(game->render, possede, NULL, &pos_possede_popo_puissance);
            SDL_RenderCopy(game->render, possede, NULL, &pos_possede_popo_agi);

            SDL_RenderCopy(game->render, nb_petite_popo_soin, NULL, &pos_nb_petite_popo_soin);
            SDL_RenderCopy(game->render, nb_moyenne_popo_soin, NULL, &pos_nb_moyenne_popo_soin);
            SDL_RenderCopy(game->render, nb_petite_popo_mana, NULL, &pos_nb_petite_popo_mana);
            SDL_RenderCopy(game->render, nb_moyenne_popo_mana, NULL, &pos_nb_moyenne_popo_mana);
            SDL_RenderCopy(game->render, nb_popo_puissance, NULL, &pos_nb_popo_puissance);
            SDL_RenderCopy(game->render, nb_popo_agi, NULL, &pos_nb_popo_agi);

            SDL_SetRenderTarget(game->render, NULL);
            SDL_RenderCopy(game->render, texture_render_sac, NULL, &pos_texture_render_menu_ig);
            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {
                if (selection_vertical == 0)
                {
                    if (selection_horizontal == 0)
                    {
                        if (character->nb_petite_popo_soin == 0)
                        {
                            affichage_message(game, "Vous n'en avez aucune dans votre sac.", -1);
                        }
                        else if (texte_confirmation(game, "Voulez-vous utiliser une petite potion de soin ?"))
                        {
                            SDL_RenderClear(game->render);
                            SDL_RenderCopy(game->render, texture_render_sac, NULL, &pos_texture_render_menu_ig);
                            SDL_RenderPresent(game->render);

                            if (character->life == character->max_life)
                            {
                                affichage_message(game, "Cela n'a servit a rien.", -1);
                            }
                            else if (character->max_life - character->life < 20)
                            {
                                affichage_message(game, "Vous avez recupere %d PV.", character->max_life - character->life);
                                character->life = character->max_life;
                            }
                            else
                            {
                                affichage_message(game, "Vous avez recupere %d PV.", 20);
                                character->life += 20;
                            }
                            potion_utilise_bool = SDL_TRUE;
                            character->nb_petite_popo_soin--;

                            if (character->nb_petite_popo_soin > 999)
                            {
                                character_nb_petite_popo_soin[0] = '9';
                                character_nb_petite_popo_soin[1] = '9';
                                character_nb_petite_popo_soin[2] = '9';
                                character_nb_petite_popo_soin[3] = '+';
                            }
                            else
                                itoa(character->nb_petite_popo_soin, character_nb_petite_popo_soin, 10);

                            surf_nb_petite_popo_soin = TTF_RenderText_Blended(game->police, character_nb_petite_popo_soin, blanc);
                            nb_petite_popo_soin = SDL_CreateTextureFromSurface(game->render, surf_nb_petite_popo_soin);
                            pos_nb_petite_popo_soin.w = strlen(character_nb_petite_popo_soin) * (*game->WINDOWWIDTH) * 6 / 1280;
                        }
                    }

                    if (selection_horizontal == 1)
                    {
                        if (character->nb_moyenne_popo_soin == 0)
                        {
                            affichage_message(game, "Vous n'en avez aucune dans votre sac.", -1);
                        }
                        else if (texte_confirmation(game, "Voulez-vous utiliser une moyenne potion de soin ?"))
                        {
                            SDL_RenderClear(game->render);
                            SDL_RenderCopy(game->render, texture_render_sac, NULL, &pos_texture_render_menu_ig);
                            SDL_RenderPresent(game->render);

                            if (character->life == character->max_life)
                            {
                                affichage_message(game, "Cela n'a servit a rien.", -1);
                            }
                            else if (character->max_life - character->life < 50)
                            {
                                affichage_message(game, "Vous avez recupere %d PV.", character->max_life - character->life);
                                character->life = character->max_life;
                            }
                            else
                            {
                                affichage_message(game, "Vous avez recupere %d PV.", 50);
                                character->life += 50;
                            }
                            potion_utilise_bool = SDL_TRUE;
                            character->nb_moyenne_popo_soin--;

                            if (character->nb_moyenne_popo_soin > 999)
                            {
                                character_nb_moyenne_popo_soin[0] = '9';
                                character_nb_moyenne_popo_soin[1] = '9';
                                character_nb_moyenne_popo_soin[2] = '9';
                                character_nb_moyenne_popo_soin[3] = '+';
                            }
                            else
                                itoa(character->nb_moyenne_popo_soin, character_nb_moyenne_popo_soin, 10);

                            surf_nb_moyenne_popo_soin = TTF_RenderText_Blended(game->police, character_nb_moyenne_popo_soin, blanc);
                            nb_moyenne_popo_soin = SDL_CreateTextureFromSurface(game->render, surf_nb_moyenne_popo_soin);
                            pos_nb_moyenne_popo_soin.w = strlen(character_nb_moyenne_popo_soin) * (*game->WINDOWWIDTH) * 6 / 1280;
                        }
                    }
                }

                if (selection_vertical == 1)
                {
                    if (selection_horizontal == 0)
                    {
                        if (character->nb_petite_popo_mana == 0)
                        {
                            affichage_message(game, "Vous n'en avez aucune dans votre sac.", -1);
                        }
                        else if (texte_confirmation(game, "Voulez-vous utiliser une petite potion de mana ?"))
                        {
                            SDL_RenderClear(game->render);
                            SDL_RenderCopy(game->render, texture_render_sac, NULL, &pos_texture_render_menu_ig);
                            SDL_RenderPresent(game->render);

                            if (character->mana == character->max_mana)
                            {
                                affichage_message(game, "Cela n'a servit a rien.", -1);
                            }
                            else if (character->max_mana - character->mana < 20)
                            {
                                affichage_message(game, "Vous avez recupere %d PM.", character->max_mana - character->mana);
                                character->mana = character->max_mana;
                            }
                            else
                            {
                                affichage_message(game, "Vous avez recupere %d PM.", 20);
                                character->mana += 20;
                            }
                            potion_utilise_bool = SDL_TRUE;
                            character->nb_petite_popo_mana--;

                            if (character->nb_petite_popo_mana > 999)
                            {
                                character_nb_petite_popo_mana[0] = '9';
                                character_nb_petite_popo_mana[1] = '9';
                                character_nb_petite_popo_mana[2] = '9';
                                character_nb_petite_popo_mana[3] = '+';
                            }
                            else
                                itoa(character->nb_petite_popo_mana, character_nb_petite_popo_mana, 10);

                            surf_nb_petite_popo_mana = TTF_RenderText_Blended(game->police, character_nb_petite_popo_mana, blanc);
                            nb_petite_popo_mana = SDL_CreateTextureFromSurface(game->render, surf_nb_petite_popo_mana);
                            pos_nb_petite_popo_mana.w = strlen(character_nb_petite_popo_mana) * (*game->WINDOWWIDTH) * 6 / 1280;
                        }
                    }

                    if (selection_horizontal == 1)
                    {
                        if (character->nb_moyenne_popo_mana == 0)
                        {
                            affichage_message(game, "Vous n'en avez aucune dans votre sac.", -1);
                        }
                        else if (texte_confirmation(game, "Voulez-vous utiliser une moyenne potion de soin ?"))
                        {
                            SDL_RenderClear(game->render);
                            SDL_RenderCopy(game->render, texture_render_sac, NULL, &pos_texture_render_menu_ig);
                            SDL_RenderPresent(game->render);

                            if (character->mana == character->max_mana)
                            {
                                affichage_message(game, "Cela n'a servit a rien.", -1);
                            }
                            else if (character->max_mana - character->mana < 50)
                            {
                                affichage_message(game, "Vous avez recupere %d PM.", character->max_mana - character->mana);
                                character->mana = character->max_mana;
                            }
                            else
                            {
                                affichage_message(game, "Vous avez recupere %d PM.", 50);
                                character->mana += 50;
                            }
                            potion_utilise_bool = SDL_TRUE;
                            character->nb_moyenne_popo_mana--;

                            if (character->nb_moyenne_popo_mana > 999)
                            {
                                character_nb_moyenne_popo_mana[0] = '9';
                                character_nb_moyenne_popo_mana[1] = '9';
                                character_nb_moyenne_popo_mana[2] = '9';
                                character_nb_moyenne_popo_mana[3] = '+';
                            }
                            else
                                itoa(character->nb_moyenne_popo_mana, character_nb_moyenne_popo_mana, 10);

                            surf_nb_moyenne_popo_mana = TTF_RenderText_Blended(game->police, character_nb_moyenne_popo_mana, blanc);
                            nb_moyenne_popo_mana = SDL_CreateTextureFromSurface(game->render, surf_nb_moyenne_popo_mana);
                            pos_nb_moyenne_popo_mana.w = strlen(character_nb_moyenne_popo_mana) * (*game->WINDOWWIDTH) * 6 / 1280;
                        }
                    }
                }

                if (!combat && selection_vertical == 2)
                {
                    sac_bool = SDL_FALSE;
                }

                if (combat && selection_vertical == 2)
                {
                    if (selection_horizontal == 0)
                    {
                        if (character->nb_popo_puissance == 0)
                        {
                            affichage_message(game, "Vous n'en avez aucune dans votre sac.", -1);
                        }
                        else if (texte_confirmation(game, "Voulez-vous utiliser une potion de puissance ?"))
                        {
                            SDL_RenderClear(game->render);
                            SDL_RenderCopy(game->render, texture_render_sac, NULL, &pos_texture_render_menu_ig);
                            SDL_RenderPresent(game->render);

                            if (character->nb_tour_restant_puissance > 0)
                                affichage_message(game, "Une potion de puissance fait encore effet.", -1);
                            else if (character->nb_tour_restant_agi > 0)
                                affichage_message(game, "Une potion d'agilite fait encore effet.", -1);
                            else
                            {
                                affichage_message(game, "Vous puissance a ete augmente de 10 pendant 3 tours", -1);
                                character->puissance += 10;
                                character->nb_popo_puissance--;
                                character->nb_tour_restant_puissance = 3;
                                potion_utilise_bool = SDL_TRUE;
                            }

                            if (character->nb_popo_puissance > 999)
                            {
                                character_nb_popo_puissance[0] = '9';
                                character_nb_popo_puissance[1] = '9';
                                character_nb_popo_puissance[2] = '9';
                                character_nb_popo_puissance[3] = '+';
                            }
                            else
                                itoa(character->nb_popo_puissance, character_nb_popo_puissance, 10);

                            surf_nb_popo_puissance = TTF_RenderText_Blended(game->police, character_nb_popo_puissance, blanc);
                            nb_popo_puissance = SDL_CreateTextureFromSurface(game->render, surf_nb_popo_puissance);
                            pos_nb_popo_puissance.w = strlen(character_nb_popo_puissance) * (*game->WINDOWWIDTH) * 6 / 1280;
                        }
                    }

                    if (selection_horizontal == 1)
                    {
                        if (character->nb_popo_agi == 0)
                        {
                            affichage_message(game, "Vous n'en avez aucune dans votre sac.", -1);
                        }
                        else if (texte_confirmation(game, "Voulez-vous utiliser une potion de puissance ?"))
                        {
                            SDL_RenderClear(game->render);
                            SDL_RenderCopy(game->render, texture_render_sac, NULL, &pos_texture_render_menu_ig);
                            SDL_RenderPresent(game->render);

                            if (character->nb_tour_restant_puissance > 0)
                                affichage_message(game, "Une potion de puissance fait encore effet.", -1);
                            else if (character->nb_tour_restant_agi > 0)
                                affichage_message(game, "Une potion d'agilite fait encore effet.", -1);
                            else
                            {
                                affichage_message(game, "Vous puissance a ete augmente de 10 pendant 3 tours", -1);
                                character->agilite += 10;
                                character->nb_popo_agi--;
                                character->nb_tour_restant_agi = 5;
                                potion_utilise_bool = SDL_TRUE;
                            }

                            if (character->nb_popo_agi > 999)
                            {
                                character_nb_popo_agi[0] = '9';
                                character_nb_popo_agi[1] = '9';
                                character_nb_popo_agi[2] = '9';
                                character_nb_popo_agi[3] = '+';
                            }
                            else
                                itoa(character->nb_popo_agi, character_nb_popo_agi, 10);

                            surf_nb_popo_agi = TTF_RenderText_Blended(game->police, character_nb_popo_agi, blanc);
                            nb_popo_agi = SDL_CreateTextureFromSurface(game->render, surf_nb_popo_agi);
                            pos_nb_popo_agi.w = strlen(character_nb_popo_agi) * (*game->WINDOWWIDTH) * 6 / 1280;
                        }
                    }
                }

                if (combat && selection_vertical == 3)
                {
                    sac_bool = SDL_FALSE;
                }

                if (combat && potion_utilise_bool)
                {
                    sac_bool = SDL_FALSE;
                }
            }
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_sac);
    SDL_FreeSurface(surf_retour);
    SDL_FreeSurface(surf_cadre_sac);
    SDL_FreeSurface(surf_cadre_potions);
    SDL_FreeSurface(surf_cadre_rouge_potions);
    SDL_FreeSurface(surf_effet_petite_popo_soin);
    SDL_FreeSurface(surf_effet_moyenne_popo_soin);
    SDL_FreeSurface(surf_effet_petite_popo_mana);
    SDL_FreeSurface(surf_effet_moyenne_popo_mana);
    SDL_FreeSurface(surf_effet_popo_puissance);
    SDL_FreeSurface(surf_effet_popo_agi);
    SDL_FreeSurface(surf_possede);
    SDL_FreeSurface(surf_nb_petite_popo_soin);
    SDL_FreeSurface(surf_nb_moyenne_popo_soin);
    SDL_FreeSurface(surf_nb_petite_popo_mana);
    SDL_FreeSurface(surf_nb_moyenne_popo_mana);
    SDL_FreeSurface(surf_nb_popo_puissance);
    SDL_FreeSurface(surf_nb_popo_agi);

    SDL_DestroyTexture(sac);
    SDL_DestroyTexture(retour);
    SDL_DestroyTexture(cadre_sac);
    SDL_DestroyTexture(cadre_potions);
    SDL_DestroyTexture(cadre_rouge_potions);
    SDL_DestroyTexture(fond_cadre_sac);
    SDL_DestroyTexture(fond_petite_popo_soin);
    SDL_DestroyTexture(fond_moyenne_popo_soin);
    SDL_DestroyTexture(fond_petite_popo_mana);
    SDL_DestroyTexture(fond_moyenne_popo_mana);
    SDL_DestroyTexture(fond_popo_puissance);
    SDL_DestroyTexture(fond_popo_agi);
    SDL_DestroyTexture(effet_petite_popo_soin);
    SDL_DestroyTexture(effet_moyenne_popo_soin);
    SDL_DestroyTexture(effet_petite_popo_mana);
    SDL_DestroyTexture(effet_moyenne_popo_mana);
    SDL_DestroyTexture(effet_popo_puissance);
    SDL_DestroyTexture(effet_popo_agi);
    SDL_DestroyTexture(possede);
    SDL_DestroyTexture(nb_petite_popo_soin);
    SDL_DestroyTexture(nb_moyenne_popo_soin);
    SDL_DestroyTexture(nb_petite_popo_mana);
    SDL_DestroyTexture(nb_moyenne_popo_mana);
    SDL_DestroyTexture(nb_popo_puissance);
    SDL_DestroyTexture(nb_popo_agi);

    /*--- End Free Memory --------------------------------------------------------*/
}
