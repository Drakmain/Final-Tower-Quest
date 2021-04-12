#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\character_attacks.h"

#include "..\lib\combat.h"
#include "..\lib\enemy_selection.h"
#include "..\lib\affichage_message.h"

/*!
 *
 * \file attaques.c
 * \brief A FINIR.
 * \author Enzo BRENNUS
 *
 */

/*!
 *
 * \fn _toEspace(char *string)
 * \brief A FINIR.
 *
 * \param string A FINIR.
 * \param length A FINIR.
 *
 */

extern void _toEspace(char *string)
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == '_')
        {
            string[i] = ' ';
        }
    }
}

/*!
 *
 * \fn character_attacks(game_t *game, character_t *character, enemy_t *enemies_cbt, int nb_enemies_combat, int nb_enemies_combat_actif, SDL_Texture *texture_render_combat, SDL_bool *character_turn_bool)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * \param texture_render_combat A FINIR.
 *
 */

extern void character_attacks(game_t *game, character_t *character, enemy_t *enemies_cbt, int nb_enemies_combat, int nb_enemies_combat_actif, SDL_Texture *texture_render_combat, SDL_bool *character_turn_bool)
{
    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Texture *texture_render = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};
    SDL_Color bleu = {0, 0, 255};
    SDL_Color gris = {100, 100, 100};

    int selection = 0;

    int selected_enemy;

    int dmg;

    int temp;

    int max_selec;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool attacks_bool = SDL_TRUE;

    SDL_Event event;

    //POS CHARACTER
    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->Attack.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->Attack.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 1.5;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;

    /*--- End Initialization Variable --------------------------------------------*/

    /*--- Loading texture "cadre selection attaques" ------------------------------*/

    SDL_Surface *surf_attaques_cadre = NULL;
    surf_attaques_cadre = SDL_LoadBMP("src\\image\\cadre_attaques.bmp");
    if (surf_attaques_cadre == NULL)
    {
        SDL_ExitWithError("Probleme chargement image surf_combat_cadre > attaques.c Line 114");
    }

    SDL_Texture *texture_attaques_cadre = SDL_CreateTextureFromSurface(game->render, surf_attaques_cadre);
    if (texture_attaques_cadre == NULL)
    {
        SDL_ExitWithError("Probleme texture texture_combat_cadre > attaques.c Line 120");
    }

    SDL_Rect pos_Wind_cadre_attaque;
    pos_Wind_cadre_attaque.h = (*game->WINDOWWIDTH) * 1248 / 2560;
    pos_Wind_cadre_attaque.w = (*game->WINDOWWIDTH) * (2560 / 3.3) / 2560;
    pos_Wind_cadre_attaque.x = (*game->WINDOWWIDTH) - pos_Wind_cadre_attaque.w;
    pos_Wind_cadre_attaque.y = 0;

    /*----------------------------------------------------------------------------*/

    /*--- Creation texture background "cadre attaques" ---------------------------*/

    SDL_Texture *texture_fond_attaques_cadre = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_Wind_cadre_attaque.w, pos_Wind_cadre_attaque.h);
    if (texture_fond_attaques_cadre == NULL)
    {
        SDL_ExitWithError("probleme texture texture_fond_attaques_cadre > attaques.c Line 189");
    }

    SDL_Rect pos_fond_attaques_cadre;
    pos_fond_attaques_cadre.x = pos_Wind_cadre_attaque.x;
    pos_fond_attaques_cadre.y = pos_Wind_cadre_attaque.y;
    pos_fond_attaques_cadre.w = pos_Wind_cadre_attaque.w;
    pos_fond_attaques_cadre.h = pos_Wind_cadre_attaque.h;

    SDL_Rect rect_fond_attaques_cadre;
    rect_fond_attaques_cadre.x = (*game->WINDOWWIDTH) * 12 / 1200;
    rect_fond_attaques_cadre.y = (*game->WINDOWHEIGHT) * 12 / 675;
    rect_fond_attaques_cadre.w = pos_fond_attaques_cadre.w - 2 * rect_fond_attaques_cadre.x + 1;
    rect_fond_attaques_cadre.h = pos_fond_attaques_cadre.h - 2 * rect_fond_attaques_cadre.y + 1;

    SDL_SetRenderTarget(game->render, texture_fond_attaques_cadre);
    SDL_SetRenderDrawColor(game->render, 25, 25, 25, 240);
    SDL_SetTextureBlendMode(texture_fond_attaques_cadre, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_attaques_cadre);
    SDL_SetRenderTarget(game->render, NULL);

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);

    /*----------------------------------------------------------------------------*/

    /*----------------------------------------------------------------------------*/

    for (int i = 0; i < NB_ATTACKS; i++)
    {
        _toEspace(character->attacks[i].name);
    }

    /*--- Creation text "attaque 1" ----------------------------------------------*/

    SDL_Surface *surf_attaque_1 = NULL;
    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, gris);
    if (surf_attaque_1 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 1 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_1 = SDL_CreateTextureFromSurface(game->render, surf_attaque_1);
    if (texture_attaque_1 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 1 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_1;
    pos_Wind_attaque_1.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_1.y = (*game->WINDOWWIDTH) * 34 / 2560;
    pos_Wind_attaque_1.w = (*game->WINDOWWIDTH) * strlen(character->attacks[0].name) * 25 / 2560;
    pos_Wind_attaque_1.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 2" ----------------------------------------------*/

    SDL_Surface *surf_attaque_2 = NULL;
    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, gris);
    if (surf_attaque_2 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 2 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_2 = SDL_CreateTextureFromSurface(game->render, surf_attaque_2);
    if (texture_attaque_2 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 2 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_2;
    pos_Wind_attaque_2.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_2.y = (*game->WINDOWWIDTH) * 125 / 2560;
    pos_Wind_attaque_2.w = (*game->WINDOWWIDTH) * strlen(character->attacks[1].name) * 25 / 2560;
    pos_Wind_attaque_2.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 3" ----------------------------------------------*/

    SDL_Surface *surf_attaque_3 = NULL;
    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, gris);
    if (surf_attaque_3 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 3 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_3 = SDL_CreateTextureFromSurface(game->render, surf_attaque_3);
    if (texture_attaque_3 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 3 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_3;
    pos_Wind_attaque_3.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_3.y = (*game->WINDOWWIDTH) * 216 / 2560;
    pos_Wind_attaque_3.w = (*game->WINDOWWIDTH) * strlen(character->attacks[2].name) * 25 / 2560;
    pos_Wind_attaque_3.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 4" ----------------------------------------------*/

    SDL_Surface *surf_attaque_4 = NULL;
    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, gris);
    if (surf_attaque_4 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 4 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_4 = SDL_CreateTextureFromSurface(game->render, surf_attaque_4);
    if (texture_attaque_4 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 4 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_4;
    pos_Wind_attaque_4.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_4.y = (*game->WINDOWWIDTH) * 307 / 2560;
    pos_Wind_attaque_4.w = (*game->WINDOWWIDTH) * strlen(character->attacks[3].name) * 25 / 2560;
    pos_Wind_attaque_4.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 5" ----------------------------------------------*/

    SDL_Surface *surf_attaque_5 = NULL;
    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, gris);
    if (surf_attaque_5 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 5 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_5 = SDL_CreateTextureFromSurface(game->render, surf_attaque_5);
    if (texture_attaque_5 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 5 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_5;
    pos_Wind_attaque_5.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_5.y = (*game->WINDOWWIDTH) * 398 / 2560;
    pos_Wind_attaque_5.w = (*game->WINDOWWIDTH) * strlen(character->attacks[4].name) * 25 / 2560;
    pos_Wind_attaque_5.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 6" ----------------------------------------------*/

    SDL_Surface *surf_attaque_6 = NULL;
    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, gris);
    if (surf_attaque_6 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 6 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_6 = SDL_CreateTextureFromSurface(game->render, surf_attaque_6);
    if (texture_attaque_6 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 6 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_6;
    pos_Wind_attaque_6.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_6.y = (*game->WINDOWWIDTH) * 489 / 2560;
    pos_Wind_attaque_6.w = (*game->WINDOWWIDTH) * strlen(character->attacks[5].name) * 25 / 2560;
    pos_Wind_attaque_6.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 7" ----------------------------------------------*/

    SDL_Surface *surf_attaque_7 = NULL;
    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, gris);
    if (surf_attaque_7 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 7 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_7 = SDL_CreateTextureFromSurface(game->render, surf_attaque_7);
    if (texture_attaque_7 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 7 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_7;
    pos_Wind_attaque_7.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_7.y = (*game->WINDOWWIDTH) * 580 / 2560;
    pos_Wind_attaque_7.w = (*game->WINDOWWIDTH) * strlen(character->attacks[6].name) * 25 / 2560;
    pos_Wind_attaque_7.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 8" ----------------------------------------------*/

    SDL_Surface *surf_attaque_8 = NULL;
    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, gris);
    if (surf_attaque_8 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 8 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_8 = SDL_CreateTextureFromSurface(game->render, surf_attaque_8);
    if (texture_attaque_8 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 8 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_8;
    pos_Wind_attaque_8.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_8.y = (*game->WINDOWWIDTH) * 671 / 2560;
    pos_Wind_attaque_8.w = (*game->WINDOWWIDTH) * strlen(character->attacks[7].name) * 25 / 2560;
    pos_Wind_attaque_8.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 9" ----------------------------------------------*/

    SDL_Surface *surf_attaque_9 = NULL;
    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, gris);
    if (surf_attaque_9 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 9 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_9 = SDL_CreateTextureFromSurface(game->render, surf_attaque_9);
    if (texture_attaque_9 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 9 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_9;
    pos_Wind_attaque_9.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_9.y = (*game->WINDOWWIDTH) * 762 / 2560;
    pos_Wind_attaque_9.w = (*game->WINDOWWIDTH) * strlen(character->attacks[8].name) * 25 / 2560;
    pos_Wind_attaque_9.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 10" ---------------------------------------------*/

    SDL_Surface *surf_attaque_10 = NULL;
    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[9].name, gris);
    if (surf_attaque_10 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 10 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_10 = SDL_CreateTextureFromSurface(game->render, surf_attaque_10);
    if (texture_attaque_10 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 10 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_10;
    pos_Wind_attaque_10.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_10.y = (*game->WINDOWWIDTH) * 853 / 2560;
    pos_Wind_attaque_10.w = (*game->WINDOWWIDTH) * strlen(character->attacks[9].name) * 25 / 2560;
    pos_Wind_attaque_10.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 11" ---------------------------------------------*/

    SDL_Surface *surf_attaque_11 = NULL;
    surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[10].name, gris);
    if (surf_attaque_11 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 11 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_11 = SDL_CreateTextureFromSurface(game->render, surf_attaque_11);
    if (texture_attaque_11 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 11 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_11;
    pos_Wind_attaque_11.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_11.y = (*game->WINDOWWIDTH) * 944 / 2560;
    pos_Wind_attaque_11.w = (*game->WINDOWWIDTH) * strlen(character->attacks[10].name) * 25 / 2560;
    pos_Wind_attaque_11.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 12" ---------------------------------------------*/

    SDL_Surface *surf_attaque_12 = NULL;
    surf_attaque_12 = TTF_RenderText_Blended(game->police, character->attacks[11].name, gris);
    if (surf_attaque_12 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 12 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_12 = SDL_CreateTextureFromSurface(game->render, surf_attaque_12);
    if (texture_attaque_12 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 12 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_12;
    pos_Wind_attaque_12.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_12.y = (*game->WINDOWWIDTH) * 1035 / 2560;
    pos_Wind_attaque_12.w = (*game->WINDOWWIDTH) * strlen(character->attacks[11].name) * 25 / 2560;
    pos_Wind_attaque_12.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 13" ---------------------------------------------*/

    SDL_Surface *surf_attaque_13 = NULL;
    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, gris);
    if (surf_attaque_13 == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 13 > attaques.c Line 194");
    }

    SDL_Texture *texture_attaque_13 = SDL_CreateTextureFromSurface(game->render, surf_attaque_13);
    if (texture_attaque_13 == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 13 > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_attaque_13;
    pos_Wind_attaque_13.x = (*game->WINDOWWIDTH) * 1850 / 2560;
    pos_Wind_attaque_13.y = (*game->WINDOWWIDTH) * 1126 / 2560;
    pos_Wind_attaque_13.w = (*game->WINDOWWIDTH) * strlen(character->attacks[12].name) * 25 / 2560;
    pos_Wind_attaque_13.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "cout attaque" -------------------------------------------*/

    SDL_Surface *surf_cout_attaque = NULL;
    surf_cout_attaque = TTF_RenderText_Blended(game->police, "Cout PM:", blanc);
    if (surf_cout_attaque == NULL)
    {
        SDL_ExitWithError("Probleme surface cout attaque > attaques.c Line 194");
    }

    SDL_Texture *texture_cout_attaque = SDL_CreateTextureFromSurface(game->render, surf_cout_attaque);
    if (texture_cout_attaque == NULL)
    {
        SDL_ExitWithError("Probleme texture cout attaque > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_cout_attaque;
    pos_Wind_cout_attaque.x = (*game->WINDOWWIDTH) * 1200 / 2560;
    pos_Wind_cout_attaque.y = (*game->WINDOWWIDTH) * 1200 / 2560;
    pos_Wind_cout_attaque.w = (*game->WINDOWWIDTH) * strlen("Cout PM") * 25 / 2560;
    pos_Wind_cout_attaque.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "cout attaque NB" -------------------------------------------*/

    char cout_PM_NB[3] = "0";

    SDL_Surface *surf_cout_attaque_NB = NULL;
    surf_cout_attaque_NB = TTF_RenderText_Blended(game->police, cout_PM_NB, bleu);
    if (surf_cout_attaque_NB == NULL)
    {
        SDL_ExitWithError("Probleme surface cout attaque > attaques.c Line 194");
    }

    SDL_Texture *texture_cout_attaque_NB = SDL_CreateTextureFromSurface(game->render, surf_cout_attaque_NB);
    if (texture_cout_attaque_NB == NULL)
    {
        SDL_ExitWithError("Probleme texture cout attaque > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_cout_attaque_NB;
    pos_Wind_cout_attaque_NB.x = (*game->WINDOWWIDTH) * 1400 / 2560;
    pos_Wind_cout_attaque_NB.y = (*game->WINDOWWIDTH) * 1200 / 2560;
    pos_Wind_cout_attaque_NB.w = (*game->WINDOWWIDTH) * strlen(cout_PM_NB) * 25 / 2560;
    pos_Wind_cout_attaque_NB.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "degat attaque" ------------------------------------------*/

    SDL_Surface *surf_degat_attaque = NULL;
    surf_degat_attaque = TTF_RenderText_Blended(game->police, "Degats:", blanc);
    if (surf_degat_attaque == NULL)
    {
        SDL_ExitWithError("Probleme surface degat attaque > attaques.c Line 194");
    }

    SDL_Texture *texture_degat_attaque = SDL_CreateTextureFromSurface(game->render, surf_degat_attaque);
    if (texture_degat_attaque == NULL)
    {
        SDL_ExitWithError("Probleme texture degat attaque > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_degat_attaque;
    pos_Wind_degat_attaque.x = (*game->WINDOWWIDTH) * 800 / 2560;
    pos_Wind_degat_attaque.y = (*game->WINDOWWIDTH) * 1200 / 2560;
    pos_Wind_degat_attaque.w = (*game->WINDOWWIDTH) * strlen("Degats:") * 25 / 2560;
    pos_Wind_degat_attaque.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "degat attaque NB" ------------------------------------------*/

    char degat_NB_min[3] = "0";
    char degat_NB_max[3] = "0";
    char degat_NB[15];

    SDL_Surface *surf_degat_attaque_NB = NULL;
    surf_degat_attaque_NB = TTF_RenderText_Blended(game->police, " ", blanc);
    if (surf_degat_attaque_NB == NULL)
    {
        SDL_ExitWithError("Probleme surface degat attaque > attaques.c Line 194");
    }

    SDL_Texture *texture_degat_attaque_NB = SDL_CreateTextureFromSurface(game->render, surf_degat_attaque_NB);
    if (texture_degat_attaque_NB == NULL)
    {
        SDL_ExitWithError("Probleme texture degat attaque > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_degat_attaque_NB;
    pos_Wind_degat_attaque_NB.x = (*game->WINDOWWIDTH) * 1000 / 2560;
    pos_Wind_degat_attaque_NB.y = (*game->WINDOWWIDTH) * 1200 / 2560;
    pos_Wind_degat_attaque_NB.w = (*game->WINDOWWIDTH) * strlen(" ") * 25 / 2560;
    pos_Wind_degat_attaque_NB.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "description attaque" ------------------------------------*/

    SDL_Surface *surf_description_attaque = NULL;
    surf_description_attaque = TTF_RenderText_Blended(game->police, " ", blanc);
    if (surf_description_attaque == NULL)
    {
        SDL_ExitWithError("Probleme surface degat attaque > attaques.c Line 194");
    }

    SDL_Texture *texture_description_attaque = SDL_CreateTextureFromSurface(game->render, surf_description_attaque);
    if (texture_description_attaque == NULL)
    {
        SDL_ExitWithError("Probleme texture degat attaque > attaques.c Line 194");
    }

    SDL_Rect pos_Wind_description_attaque;
    pos_Wind_description_attaque.x = (*game->WINDOWWIDTH) * 800 / 2560;
    pos_Wind_description_attaque.y = (*game->WINDOWWIDTH) * 1320 / 2560;
    pos_Wind_description_attaque.w = (*game->WINDOWWIDTH) * strlen(" ") * 25 / 2560;
    pos_Wind_description_attaque.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "PV personnage" ------------------------------------------*/

    char char_character_life[3];
    itoa(character->life, char_character_life, 10);

    SDL_Surface *surf_PV_personnage = NULL;
    surf_PV_personnage = TTF_RenderText_Blended(game->police, char_character_life, rouge);
    if (surf_PV_personnage == NULL)
    {
        SDL_ExitWithError("Probleme surface PV personnage > combat.c Line 192");
    }

    SDL_Texture *texture_PV_personnage = NULL;
    texture_PV_personnage = SDL_CreateTextureFromSurface(game->render, surf_PV_personnage);
    if (texture_PV_personnage == NULL)
    {
        SDL_ExitWithError("Probleme texture PV personnage > combat.c Line 198");
    }

    SDL_Rect pos_Wind_PV_personnage;
    pos_Wind_PV_personnage.x = (*game->WINDOWWIDTH) * 1050 / 2560;
    pos_Wind_PV_personnage.y = (*game->WINDOWWIDTH) * 1069 / 2560;
    pos_Wind_PV_personnage.w = (*game->WINDOWWIDTH) * strlen(char_character_life) * 25 / 2560;
    pos_Wind_PV_personnage.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "PM personnage" ------------------------------------------*/

    char char_character_mana[3];
    itoa(character->mana, char_character_mana, 10);

    SDL_Surface *surf_PM_personnage = NULL;
    surf_PM_personnage = TTF_RenderText_Blended(game->police, char_character_mana, bleu);
    if (surf_PM_personnage == NULL)
    {
        SDL_ExitWithError("Probleme surface PV personnage > combat.c Line 192");
    }

    SDL_Texture *texture_PM_personnage = NULL;
    texture_PM_personnage = SDL_CreateTextureFromSurface(game->render, surf_PM_personnage);
    if (texture_PM_personnage == NULL)
    {
        SDL_ExitWithError("Probleme texture PV personnage > combat.c Line 198");
    }

    SDL_Rect pos_Wind_PM_personnage;
    pos_Wind_PM_personnage.x = (*game->WINDOWWIDTH) * 1150 / 2560;
    pos_Wind_PM_personnage.y = (*game->WINDOWWIDTH) * 1069 / 2560;
    pos_Wind_PM_personnage.w = (*game->WINDOWWIDTH) * strlen(char_character_mana) * 25 / 2560;
    pos_Wind_PM_personnage.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    if (character->lvl >= 50)
    {
        max_selec = 13;
        surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);
    }
    if (character->lvl >= 45)
    {
        max_selec = 12;
        surf_attaque_12 = TTF_RenderText_Blended(game->police, character->attacks[11].name, blanc);
    }
    if (character->lvl >= 40)
    {
        max_selec = 11;
        surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[10].name, blanc);
    }
    if (character->lvl >= 35)
    {
        max_selec = 10;
        surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[9].name, blanc);
    }
    if (character->lvl >= 30)
    {
        max_selec = 9;
        surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);
    }
    if (character->lvl >= 25)
    {
        max_selec = 8;
        surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);
    }
    if (character->lvl >= 20)
    {
        max_selec = 7;
        surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);
    }
    if (character->lvl >= 15)
    {
        max_selec = 6;
        surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);
    }
    if (character->lvl >= 10)
    {
        max_selec = 5;
        surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
    }
    if (character->lvl >= 5)
    {
        max_selec = 4;
        surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
    }
    if (character->lvl >= 1)
    {
        surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
        surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
        surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
        max_selec = 3;
    }

    if (character->lvl >= 50)
    {
        max_selec = 13;
    }
    else if (character->lvl >= 45)
    {
        max_selec = 12;
    }
    else if (character->lvl >= 40)
    {
        max_selec = 11;
    }
    else if (character->lvl >= 35)
    {
        max_selec = 10;
    }
    else if (character->lvl >= 30)
    {
        max_selec = 9;
    }
    else if (character->lvl >= 25)
    {
        max_selec = 8;
    }
    else if (character->lvl >= 20)
    {
        max_selec = 7;
    }
    else if (character->lvl >= 15)
    {
        max_selec = 6;
    }
    else if (character->lvl >= 10)
    {
        max_selec = 5;
    }
    else if (character->lvl >= 5)
    {
        max_selec = 4;
    }
    else if (character->lvl >= 1)
    {
        max_selec = 3;
    }

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && attacks_bool)
    {
        while (SDL_PollEvent(&event))
        {
            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                (*game->program_launch) = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE])
            {
                attacks_bool = SDL_FALSE;
            }

            /*--- End Event to Exit Program --------------------------------------*/

            /*--- Event pour selectionner ----------------------------------------*/

            if (keyState[SDL_SCANCODE_DOWN] && event.type == SDL_KEYDOWN)
            {
                selection++;
            }

            if (keyState[SDL_SCANCODE_UP] && event.type == SDL_KEYDOWN)
            {
                selection--;
            }

            /*--------------------------------------------------------------------*/

            if (selection < 0)
                selection = max_selec - 1;
            selection %= max_selec;

            if (character->lvl >= 50)
            {
                if (selection == 0)
                {
                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
                }

                if (selection == 3)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
                }

                if (selection == 4)
                {
                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);
                }

                if (selection == 5)
                {
                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);
                }

                if (selection == 6)
                {
                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);
                }

                if (selection == 7)
                {
                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);
                }

                if (selection == 8)
                {
                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);

                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[9].name, blanc);
                }

                if (selection == 9)
                {
                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);

                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[10].name, blanc);
                }

                if (selection == 10)
                {
                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[9].name, blanc);

                    surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_12 = TTF_RenderText_Blended(game->police, character->attacks[11].name, blanc);
                }

                if (selection == 11)
                {
                    surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[10].name, blanc);

                    surf_attaque_12 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);
                }

                if (selection == 12)
                {
                    surf_attaque_12 = TTF_RenderText_Blended(game->police, character->attacks[11].name, blanc);

                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }
            if (character->lvl >= 45)
            {
                if (selection == 0)
                {
                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
                }

                if (selection == 3)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
                }

                if (selection == 4)
                {
                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);
                }

                if (selection == 5)
                {
                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);
                }

                if (selection == 6)
                {
                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);
                }

                if (selection == 7)
                {
                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);
                }

                if (selection == 8)
                {
                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);

                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[9].name, blanc);
                }

                if (selection == 9)
                {
                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);

                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[10].name, blanc);
                }

                if (selection == 10)
                {
                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[9].name, blanc);

                    surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_12 = TTF_RenderText_Blended(game->police, character->attacks[11].name, blanc);
                }

                if (selection == 11)
                {
                    surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[10].name, blanc);

                    surf_attaque_12 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }
            if (character->lvl >= 40)
            {
                if (selection == 0)
                {
                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
                }

                if (selection == 3)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
                }

                if (selection == 4)
                {
                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);
                }

                if (selection == 5)
                {
                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);
                }

                if (selection == 6)
                {
                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);
                }

                if (selection == 7)
                {
                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);
                }

                if (selection == 8)
                {
                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);

                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[9].name, blanc);
                }

                if (selection == 9)
                {
                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);

                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[10].name, blanc);
                }

                if (selection == 10)
                {
                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[9].name, blanc);

                    surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }
            if (character->lvl >= 35)
            {
                if (selection == 0)
                {
                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
                }

                if (selection == 3)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
                }

                if (selection == 4)
                {
                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);
                }

                if (selection == 5)
                {
                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);
                }

                if (selection == 6)
                {
                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);
                }

                if (selection == 7)
                {
                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);
                }

                if (selection == 8)
                {
                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);

                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[9].name, blanc);
                }

                if (selection == 9)
                {
                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);

                    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }
            if (character->lvl >= 30)
            {
                if (selection == 0)
                {
                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
                }

                if (selection == 3)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
                }

                if (selection == 4)
                {
                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);
                }

                if (selection == 5)
                {
                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);
                }

                if (selection == 6)
                {
                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);
                }

                if (selection == 7)
                {
                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);
                }

                if (selection == 8)
                {
                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);

                    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }
            if (character->lvl >= 25)
            {
                if (selection == 0)
                {
                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
                }

                if (selection == 3)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
                }

                if (selection == 4)
                {
                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);
                }

                if (selection == 5)
                {
                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);
                }

                if (selection == 6)
                {
                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);
                }

                if (selection == 7)
                {
                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);

                    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }
            if (character->lvl >= 20)
            {
                if (selection == 0)
                {
                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
                }

                if (selection == 3)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
                }

                if (selection == 4)
                {
                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);
                }

                if (selection == 5)
                {
                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);
                }

                if (selection == 6)
                {
                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);

                    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }
            if (character->lvl >= 15)
            {
                if (selection == 0)
                {
                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
                }

                if (selection == 3)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
                }

                if (selection == 4)
                {
                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);
                }

                if (selection == 5)
                {
                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);

                    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }
            if (character->lvl >= 10)
            {
                if (selection == 0)
                {
                    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
                }

                if (selection == 3)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
                }

                if (selection == 4)
                {
                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);

                    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }
            if (character->lvl >= 5)
            {
                if (selection == 0)
                {
                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
                }

                if (selection == 3)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }

            if (character->lvl >= 1)
            {
                if (selection == 0)
                {
                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, rouge);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
                }

                if (selection == 1)
                {
                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);

                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
                }

                if (selection == 2)
                {
                    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);

                    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[selection].name, rouge);

                    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
                }
            }

            //Mise a jour du cout en mana de l'attaque
            itoa(character->attacks[selection].mana, cout_PM_NB, 10);
            surf_cout_attaque_NB = TTF_RenderText_Blended(game->police, cout_PM_NB, bleu);
            pos_Wind_cout_attaque_NB.w = (*game->WINDOWWIDTH) * strlen(cout_PM_NB) * 25 / 2560;

            //Mise a jour des degats de l'attaque
            if (character->attacks[selection].dmg_min == -1 && character->attacks[selection].dmg_max == -1)
            {
                surf_degat_attaque_NB = TTF_RenderText_Blended(game->police, degat_NB, blanc);
            }
            else
            {
                itoa(character->attacks[selection].dmg_min, degat_NB_min, 10);
                itoa(character->attacks[selection].dmg_max, degat_NB_max, 10);
                strcpy(degat_NB, "");
                strcat(degat_NB, degat_NB_min);
                strcat(degat_NB, "-");
                strcat(degat_NB, degat_NB_max);
                surf_degat_attaque_NB = TTF_RenderText_Blended(game->police, degat_NB, blanc);
            }
            pos_Wind_degat_attaque_NB.w = (*game->WINDOWWIDTH) * strlen(degat_NB) * 25 / 2560;

            //Mise a jour de la description de l'attaque
            _toEspace(character->attacks[selection].description);
            surf_description_attaque = TTF_RenderText_Blended(game->police, character->attacks[selection].description, blanc);
            pos_Wind_description_attaque.w = (*game->WINDOWWIDTH) * strlen(character->attacks[selection].description) * 25 / 2560;

            texture_attaque_1 = SDL_CreateTextureFromSurface(game->render, surf_attaque_1);
            texture_attaque_2 = SDL_CreateTextureFromSurface(game->render, surf_attaque_2);
            texture_attaque_3 = SDL_CreateTextureFromSurface(game->render, surf_attaque_3);
            texture_attaque_4 = SDL_CreateTextureFromSurface(game->render, surf_attaque_4);
            texture_attaque_5 = SDL_CreateTextureFromSurface(game->render, surf_attaque_5);
            texture_attaque_6 = SDL_CreateTextureFromSurface(game->render, surf_attaque_6);
            texture_attaque_7 = SDL_CreateTextureFromSurface(game->render, surf_attaque_7);
            texture_attaque_8 = SDL_CreateTextureFromSurface(game->render, surf_attaque_8);
            texture_attaque_9 = SDL_CreateTextureFromSurface(game->render, surf_attaque_9);
            texture_attaque_10 = SDL_CreateTextureFromSurface(game->render, surf_attaque_10);
            texture_attaque_11 = SDL_CreateTextureFromSurface(game->render, surf_attaque_11);
            texture_attaque_12 = SDL_CreateTextureFromSurface(game->render, surf_attaque_12);
            texture_attaque_13 = SDL_CreateTextureFromSurface(game->render, surf_attaque_13);

            texture_cout_attaque_NB = SDL_CreateTextureFromSurface(game->render, surf_cout_attaque_NB);
            texture_degat_attaque_NB = SDL_CreateTextureFromSurface(game->render, surf_degat_attaque_NB);
            texture_description_attaque = SDL_CreateTextureFromSurface(game->render, surf_description_attaque);

            SDL_SetRenderTarget(game->render, texture_render);

            SDL_RenderClear(game->render);

            SDL_RenderCopy(game->render, texture_render_combat, NULL, NULL);

            SDL_RenderCopy(game->render, texture_fond_attaques_cadre, NULL, &pos_Wind_cadre_attaque);
            SDL_RenderCopy(game->render, texture_attaques_cadre, NULL, &pos_Wind_cadre_attaque);

            SDL_RenderCopy(game->render, texture_attaque_1, NULL, &pos_Wind_attaque_1);
            SDL_RenderCopy(game->render, texture_attaque_2, NULL, &pos_Wind_attaque_2);
            SDL_RenderCopy(game->render, texture_attaque_3, NULL, &pos_Wind_attaque_3);
            SDL_RenderCopy(game->render, texture_attaque_4, NULL, &pos_Wind_attaque_4);
            SDL_RenderCopy(game->render, texture_attaque_5, NULL, &pos_Wind_attaque_5);
            SDL_RenderCopy(game->render, texture_attaque_6, NULL, &pos_Wind_attaque_6);
            SDL_RenderCopy(game->render, texture_attaque_7, NULL, &pos_Wind_attaque_7);
            SDL_RenderCopy(game->render, texture_attaque_8, NULL, &pos_Wind_attaque_8);
            SDL_RenderCopy(game->render, texture_attaque_9, NULL, &pos_Wind_attaque_9);
            SDL_RenderCopy(game->render, texture_attaque_10, NULL, &pos_Wind_attaque_10);
            SDL_RenderCopy(game->render, texture_attaque_11, NULL, &pos_Wind_attaque_11);
            SDL_RenderCopy(game->render, texture_attaque_12, NULL, &pos_Wind_attaque_12);
            SDL_RenderCopy(game->render, texture_attaque_13, NULL, &pos_Wind_attaque_13);

            SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
            SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);
            SDL_RenderCopy(game->render, texture_cout_attaque, NULL, &pos_Wind_cout_attaque);
            SDL_RenderCopy(game->render, texture_cout_attaque_NB, NULL, &pos_Wind_cout_attaque_NB);
            SDL_RenderCopy(game->render, texture_degat_attaque, NULL, &pos_Wind_degat_attaque);
            SDL_RenderCopy(game->render, texture_degat_attaque_NB, NULL, &pos_Wind_degat_attaque_NB);
            SDL_RenderCopy(game->render, texture_description_attaque, NULL, &pos_Wind_description_attaque);

            //SDL_RenderCopy(game->render, character->texture, &character->Attack, &pos_Wind_character);
            SDL_SetRenderTarget(game->render, NULL);

            SDL_RenderCopy(game->render, texture_render, NULL, NULL);

            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {
                switch (character->attacks[selection].type)
                {
                case 0: //Attaque un ennemi
                    selected_enemy = enemy_selection(game, character, enemies_cbt, nb_enemies_combat, nb_enemies_combat_actif, texture_render);
                    if (selected_enemy == -1)
                    {
                        break;
                    }
                    else if (enemies_cbt[selected_enemy].life <= 0)
                    {
                        affichage_message(game, texture_render, "Cette ennemi est deja mort.", -1);
                        break;
                    }

                    dmg = rand() % character->attacks[selection].dmg_max + character->attacks[selection].dmg_min;
                    enemies_cbt[selected_enemy].life -= dmg;

                    character->mana -= character->attacks[selection].mana;

                    *character_turn_bool = SDL_FALSE;
                    attacks_bool = SDL_FALSE;
                    break;

                case 1: //Attaque tous les ennemis
                    for (int i = 0; i < nb_enemies_combat; i++)
                    {
                        dmg = rand() % character->attacks[selection].dmg_max + character->attacks[selection].dmg_min;
                        enemies_cbt[i].life -= dmg;
                    }

                    *character_turn_bool = SDL_FALSE;
                    attacks_bool = SDL_FALSE;
                    break;

                case 2: //Attaque 3x aleatoirement
                    for (int i = 0; i < 3; i++)
                    {
                        temp = rand() % nb_enemies_combat_actif;
                        dmg = rand() % character->attacks[selection].dmg_max + character->attacks[selection].dmg_min;
                        if (!(enemies_cbt[temp].life == 0))
                        {
                            enemies_cbt[temp].life -= dmg;
                        }
                    }

                    character->mana -= character->attacks[selection].mana;

                    *character_turn_bool = SDL_FALSE;
                    attacks_bool = SDL_FALSE;
                    break;

                case 3: //Restaure un certain % la sante
                    character->life += character->max_life * character->attacks[selection].modifier / 100;

                    character->mana -= character->attacks[selection].mana;

                    *character_turn_bool = SDL_FALSE;
                    attacks_bool = SDL_FALSE;
                    break;

                case 4: //Augmente legerement(15)/grandement(30) une stat du personnage pendant X tours
                    /* code */
                    break;

                case 5: //Une chance sur X de tuer l'ennemi
                    selected_enemy = enemy_selection(game, character, enemies_cbt, nb_enemies_combat, nb_enemies_combat_actif, texture_render);
                    if (selected_enemy == -1)
                    {
                        break;
                    }
                    else if (enemies_cbt[selected_enemy].life <= 0)
                    {
                        affichage_message(game, texture_render, "Cette ennemi est deja mort.", -1);
                        break;
                    }

                    if (selected_enemy == -1)
                    {
                        break;
                    }
                    temp = rand() % character->attacks[selection].modifier + 1;
                    if (temp == 1)
                    {
                        enemies_cbt[selected_enemy].life = 0;
                    }

                    character->mana -= character->attacks[selection].mana;

                    break;

                case 6:
                    /* code */
                    break;

                case 7:
                    /* code */
                    break;

                case 8:
                    /* code */
                    break;

                case 9:
                    /* code */
                    break;

                case 10:
                    /* code */
                    break;

                case 11:
                    /* code */
                    break;

                case 12:
                    /* code */
                    break;
                }
            }
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_attaques_cadre);
    SDL_FreeSurface(surf_attaque_1);
    SDL_FreeSurface(surf_attaque_2);
    SDL_FreeSurface(surf_attaque_3);
    SDL_FreeSurface(surf_attaque_4);
    SDL_FreeSurface(surf_attaque_5);
    SDL_FreeSurface(surf_attaque_6);
    SDL_FreeSurface(surf_attaque_7);
    SDL_FreeSurface(surf_attaque_8);
    SDL_FreeSurface(surf_attaque_9);
    SDL_FreeSurface(surf_attaque_10);
    SDL_FreeSurface(surf_attaque_11);
    SDL_FreeSurface(surf_attaque_12);
    SDL_FreeSurface(surf_attaque_13);
    SDL_FreeSurface(surf_cout_attaque);
    SDL_FreeSurface(surf_degat_attaque);
    SDL_FreeSurface(surf_degat_attaque_NB);
    SDL_FreeSurface(surf_description_attaque);
    SDL_FreeSurface(surf_PV_personnage);
    SDL_FreeSurface(surf_PM_personnage);

    SDL_DestroyTexture(texture_attaques_cadre);
    SDL_DestroyTexture(texture_fond_attaques_cadre);
    SDL_DestroyTexture(texture_attaque_1);
    SDL_DestroyTexture(texture_attaque_2);
    SDL_DestroyTexture(texture_attaque_3);
    SDL_DestroyTexture(texture_attaque_4);
    SDL_DestroyTexture(texture_attaque_5);
    SDL_DestroyTexture(texture_attaque_6);
    SDL_DestroyTexture(texture_attaque_7);
    SDL_DestroyTexture(texture_attaque_8);
    SDL_DestroyTexture(texture_attaque_9);
    SDL_DestroyTexture(texture_attaque_10);
    SDL_DestroyTexture(texture_attaque_12);
    SDL_DestroyTexture(texture_attaque_12);
    SDL_DestroyTexture(texture_attaque_13);
    SDL_DestroyTexture(texture_cout_attaque);
    SDL_DestroyTexture(texture_degat_attaque);
    SDL_DestroyTexture(texture_description_attaque);
    SDL_DestroyTexture(texture_degat_attaque_NB);
    SDL_DestroyTexture(texture_description_attaque);
    SDL_DestroyTexture(texture_PV_personnage);
    SDL_DestroyTexture(texture_PM_personnage);

    /*--- End Free Memory --------------------------------------------------------*/
}
