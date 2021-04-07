#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\attaques.h"

#include "..\lib\frame.h"
#include "..\lib\character.h"
#include "..\lib\enemie.h"
#include "..\lib\combat.h"

/*!
 *
 * \file attaques.c
 * \brief A FINIR.
 * \author Enzo BRENNUS
 *
 */

/*!
 *
 * \fn attaques(game_t *game, character_t *character, map_t *map, SDL_Texture *texture_render_combat)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * \param map A FINIR.
 * \param texture_render_combat A FINIR.
 *
 */

extern void attaques(game_t *game, character_t *character, SDL_Texture *texture_render_combat)
{
    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};
    SDL_Color bleu = {0, 0, 255};

    int selection = 0;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool attaques_bool = SDL_TRUE;

    SDL_Event event;

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
    pos_Wind_cadre_attaque.h = 1248;
    pos_Wind_cadre_attaque.w = 2560 / 3.3;
    pos_Wind_cadre_attaque.x = 2560 - pos_Wind_cadre_attaque.w;
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

    for (int i = 0; i < 13; i++)
    {
        _toEspace(character->attacks[i].name, strlen(character->attacks[i].name));
    }

    /*--- Creation text "attaque 1" ----------------------------------------------*/

    SDL_Surface *surf_attaque_1 = NULL;
    surf_attaque_1 = TTF_RenderText_Blended(game->police, character->attacks[0].name, blanc);
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
    pos_Wind_attaque_1.x = 1850;
    pos_Wind_attaque_1.y = 34;
    pos_Wind_attaque_1.w = (*game->WINDOWWIDTH) * strlen(character->attacks[0].name) * 25 / 2560;
    pos_Wind_attaque_1.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 2" ----------------------------------------------*/

    SDL_Surface *surf_attaque_2 = NULL;
    surf_attaque_2 = TTF_RenderText_Blended(game->police, character->attacks[1].name, blanc);
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
    pos_Wind_attaque_2.x = 1850;
    pos_Wind_attaque_2.y = 125;
    pos_Wind_attaque_2.w = (*game->WINDOWWIDTH) * strlen(character->attacks[1].name) * 25 / 2560;
    pos_Wind_attaque_2.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 3" ----------------------------------------------*/

    SDL_Surface *surf_attaque_3 = NULL;
    surf_attaque_3 = TTF_RenderText_Blended(game->police, character->attacks[2].name, blanc);
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
    pos_Wind_attaque_3.x = 1850;
    pos_Wind_attaque_3.y = 216;
    pos_Wind_attaque_3.w = (*game->WINDOWWIDTH) * strlen(character->attacks[2].name) * 25 / 2560;
    pos_Wind_attaque_3.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 4" ----------------------------------------------*/

    SDL_Surface *surf_attaque_4 = NULL;
    surf_attaque_4 = TTF_RenderText_Blended(game->police, character->attacks[3].name, blanc);
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
    pos_Wind_attaque_4.x = 1850;
    pos_Wind_attaque_4.y = 307;
    pos_Wind_attaque_4.w = (*game->WINDOWWIDTH) * strlen(character->attacks[3].name) * 25 / 2560;
    pos_Wind_attaque_4.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 5" ----------------------------------------------*/

    SDL_Surface *surf_attaque_5 = NULL;
    surf_attaque_5 = TTF_RenderText_Blended(game->police, character->attacks[4].name, blanc);
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
    pos_Wind_attaque_5.x = 1850;
    pos_Wind_attaque_5.y = 398;
    pos_Wind_attaque_5.w = (*game->WINDOWWIDTH) * strlen(character->attacks[4].name) * 25 / 2560;
    pos_Wind_attaque_5.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 6" ----------------------------------------------*/

    SDL_Surface *surf_attaque_6 = NULL;
    surf_attaque_6 = TTF_RenderText_Blended(game->police, character->attacks[5].name, blanc);
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
    pos_Wind_attaque_6.x = 1850;
    pos_Wind_attaque_6.y = 489;
    pos_Wind_attaque_6.w = (*game->WINDOWWIDTH) * strlen(character->attacks[5].name) * 25 / 2560;
    pos_Wind_attaque_6.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 7" ----------------------------------------------*/

    SDL_Surface *surf_attaque_7 = NULL;
    surf_attaque_7 = TTF_RenderText_Blended(game->police, character->attacks[6].name, blanc);
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
    pos_Wind_attaque_7.x = 1850;
    pos_Wind_attaque_7.y = 580;
    pos_Wind_attaque_7.w = (*game->WINDOWWIDTH) * strlen(character->attacks[6].name) * 25 / 2560;
    pos_Wind_attaque_7.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 8" ----------------------------------------------*/

    SDL_Surface *surf_attaque_8 = NULL;
    surf_attaque_8 = TTF_RenderText_Blended(game->police, character->attacks[7].name, blanc);
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
    pos_Wind_attaque_8.x = 1850;
    pos_Wind_attaque_8.y = 671;
    pos_Wind_attaque_8.w = (*game->WINDOWWIDTH) * strlen(character->attacks[7].name) * 25 / 2560;
    pos_Wind_attaque_8.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 9" ----------------------------------------------*/

    SDL_Surface *surf_attaque_9 = NULL;
    surf_attaque_9 = TTF_RenderText_Blended(game->police, character->attacks[8].name, blanc);
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
    pos_Wind_attaque_9.x = 1850;
    pos_Wind_attaque_9.y = 762;
    pos_Wind_attaque_9.w = (*game->WINDOWWIDTH) * strlen(character->attacks[8].name) * 25 / 2560;
    pos_Wind_attaque_9.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 10" ---------------------------------------------*/

    SDL_Surface *surf_attaque_10 = NULL;
    surf_attaque_10 = TTF_RenderText_Blended(game->police, character->attacks[9].name, blanc);
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
    pos_Wind_attaque_10.x = 1850;
    pos_Wind_attaque_10.y = 853;
    pos_Wind_attaque_10.w = (*game->WINDOWWIDTH) * strlen(character->attacks[9].name) * 25 / 2560;
    pos_Wind_attaque_10.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 11" ---------------------------------------------*/

    SDL_Surface *surf_attaque_11 = NULL;
    surf_attaque_11 = TTF_RenderText_Blended(game->police, character->attacks[10].name, blanc);
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
    pos_Wind_attaque_11.x = 1850;
    pos_Wind_attaque_11.y = 944;
    pos_Wind_attaque_11.w = (*game->WINDOWWIDTH) * strlen(character->attacks[10].name) * 25 / 2560;
    pos_Wind_attaque_11.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 12" ---------------------------------------------*/

    SDL_Surface *surf_attaque_12 = NULL;
    surf_attaque_12 = TTF_RenderText_Blended(game->police, character->attacks[11].name, blanc);
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
    pos_Wind_attaque_12.x = 1850;
    pos_Wind_attaque_12.y = 1035;
    pos_Wind_attaque_12.w = (*game->WINDOWWIDTH) * strlen(character->attacks[11].name) * 25 / 2560;
    pos_Wind_attaque_12.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "attaque 13" ---------------------------------------------*/

    SDL_Surface *surf_attaque_13 = NULL;
    surf_attaque_13 = TTF_RenderText_Blended(game->police, character->attacks[12].name, blanc);
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
    pos_Wind_attaque_13.x = 1850;
    pos_Wind_attaque_13.y = 1126;
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
    pos_Wind_description_attaque.x = 800;
    pos_Wind_description_attaque.y = 1320;
    pos_Wind_description_attaque.w = (*game->WINDOWWIDTH) * strlen(" ") * 25 / 2560;
    pos_Wind_description_attaque.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && attaques_bool)
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
                attaques_bool = SDL_FALSE;
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

            if (selection < 0)
                selection = 12;
            selection %= 13;

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
            _toEspace(character->attacks[selection].description, strlen(character->attacks[selection].description));
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

            SDL_RenderCopy(game->render, texture_cout_attaque, NULL, &pos_Wind_cout_attaque);
            SDL_RenderCopy(game->render, texture_cout_attaque_NB, NULL, &pos_Wind_cout_attaque_NB);
            SDL_RenderCopy(game->render, texture_degat_attaque, NULL, &pos_Wind_degat_attaque);
            SDL_RenderCopy(game->render, texture_degat_attaque_NB, NULL, &pos_Wind_degat_attaque_NB);
            SDL_RenderCopy(game->render, texture_description_attaque, NULL, &pos_Wind_description_attaque);

            SDL_RenderPresent(game->render);

            switch (selection)
            {
            case 0:
                /* code */
                break;

            case 1:
                /* code */
                break;

            case 2:
                /* code */
                break;

            case 3:
                /* code */
                break;

            case 4:
                /* code */
                break;

            case 5:
                /* code */
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
    SDL_FreeSurface(surf_description_attaque);

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

    /*--- End Free Memory --------------------------------------------------------*/
}
