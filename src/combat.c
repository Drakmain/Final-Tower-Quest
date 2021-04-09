#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "..\lib\combat.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\attacks_character.h"
#include "..\lib\sac.h"

/*!
 *
 * \file combat.c
 * \brief A FINIR.
 * \author Enzo BRENNUS
 *
 */

/*!
 *
 * \fn combat(game_t *game, character_t *character, map_t *map, SDL_Texture *texture_render_town)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * \param map A FINIR.
 * \param texture_render_town A FINIR.
 *
 */

extern void combat(game_t *game, character_t *character, map_t *map, SDL_Texture *texture_render_town)
{
    srand(time(NULL));

    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Texture *texture_render = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};
    SDL_Color bleu = {0, 0, 255};

    int nb_enemie;

    int rand_enemie_1;
    int rand_enemie_2;
    int rand_enemie_3;
    int rand_enemie_4;

    char temp[30];

    int selection = 0;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool combat_bool = SDL_TRUE;

    SDL_Event event;

    //POS CHARACTER
    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 1.5;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;

    /*--- End Initialization Variable --------------------------------------------*/

    /*--- Initialization ennemis -------------------------------------------------*/

    nb_enemie = rand() % 4 + 1;

    rand_enemie_1 = rand() % 4;
    rand_enemie_2 = rand() % 4;
    rand_enemie_3 = rand() % 4;
    rand_enemie_4 = rand() % 4;

    /*--- End Initialization ennemis ---------------------------------------------*/

    /*--- Initialization position ennemis  ---------------------------------------*/

    //POS ENEMIE 1
    SDL_Rect pos_Wind_enemie_1_1;
    pos_Wind_enemie_1_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_1_1.w = (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_1_1.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_1_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;

    //POS ENEMIE 2
    SDL_Rect pos_Wind_enemie_2_1;
    pos_Wind_enemie_2_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_2_1.w = (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_2_1.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_2_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 3.8;

    SDL_Rect pos_Wind_enemie_2_2;
    pos_Wind_enemie_2_2.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_2_2.w = (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_2_2.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_2_2.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.2;

    //POS ENEMIE 3
    SDL_Rect pos_Wind_enemie_3_1;
    pos_Wind_enemie_3_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_3_1.w = (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_3_1.x = (*game->WINDOWWIDTH) / 2.8;
    pos_Wind_enemie_3_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 6;

    SDL_Rect pos_Wind_enemie_3_3;
    pos_Wind_enemie_3_3.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_3_3.w = (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_3_3.x = (*game->WINDOWWIDTH) / 2.8;
    pos_Wind_enemie_3_3.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 1.8;

    //POS ENEMIE 4
    SDL_Rect pos_Wind_enemie_4_1;
    pos_Wind_enemie_4_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_4_1.w = (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_4_1.x = (*game->WINDOWWIDTH) / 2.8;
    pos_Wind_enemie_4_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 15;

    SDL_Rect pos_Wind_enemie_4_4;
    pos_Wind_enemie_4_4.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_4_4.w = (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_4_4.x = (*game->WINDOWWIDTH) / 2.8;
    pos_Wind_enemie_4_4.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 1.6;

    /*----------------------------------------------------------------------------*/

    /*--- Loading texture "cadre combat" -----------------------------------------*/

    SDL_Surface *surf_combat_cadre = NULL;
    surf_combat_cadre = SDL_LoadBMP("src\\image\\cadre_combat.bmp");
    if (surf_combat_cadre == NULL)
    {
        SDL_ExitWithError("Probleme chargement image surf_combat_cadre > combat.c Line 114");
    }

    SDL_Texture *texture_combat_cadre = SDL_CreateTextureFromSurface(game->render, surf_combat_cadre);
    if (texture_combat_cadre == NULL)
    {
        SDL_ExitWithError("Probleme texture texture_combat_cadre > combat.c Line 120");
    }

    SDL_Rect pos_Wind_cadre_combat;
    pos_Wind_cadre_combat.h = (*game->WINDOWWIDTH) * 400 / 2560;
    pos_Wind_cadre_combat.w = (*game->WINDOWWIDTH);
    pos_Wind_cadre_combat.x = 0;
    pos_Wind_cadre_combat.y = (*game->WINDOWHEIGHT) - pos_Wind_cadre_combat.h;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "Attaque" ----------------------------------------------*/

    SDL_Surface *surf_attaque = NULL;
    surf_attaque = TTF_RenderText_Blended(game->police, "Attaque", blanc);
    if (surf_attaque == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 3 > combat.c Line 194");
    }

    SDL_Texture *texture_attaque = SDL_CreateTextureFromSurface(game->render, surf_attaque);
    if (texture_attaque == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 3 > combat.c Line 194");
    }

    SDL_Rect pos_Wind_attaque;
    pos_Wind_attaque.x = (*game->WINDOWWIDTH) * 2300 / 2560;
    pos_Wind_attaque.y = (*game->WINDOWWIDTH) * 1085 / 2560;
    pos_Wind_attaque.w = (*game->WINDOWWIDTH) * strlen("Attaque") * 25 / 2560;
    pos_Wind_attaque.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "Sac" ----------------------------------------------*/

    SDL_Surface *surf_sac = NULL;
    surf_sac = TTF_RenderText_Blended(game->police, "Sac", blanc);
    if (surf_sac == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 3 > combat.c Line 194");
    }

    SDL_Texture *texture_sac = SDL_CreateTextureFromSurface(game->render, surf_sac);
    if (texture_sac == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 3 > combat.c Line 194");
    }

    SDL_Rect pos_Wind_sac;
    pos_Wind_sac.x = (*game->WINDOWWIDTH) * 2300 / 2560;
    pos_Wind_sac.y = (*game->WINDOWWIDTH) * 1202 / 2560;
    pos_Wind_sac.w = (*game->WINDOWWIDTH) * strlen("Sac") * 25 / 2560;
    pos_Wind_sac.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "Potion" ----------------------------------------------*/

    SDL_Surface *surf_fuite = NULL;
    surf_fuite = TTF_RenderText_Blended(game->police, "Fuite", blanc);
    if (surf_fuite == NULL)
    {
        SDL_ExitWithError("Probleme surface attaque 3 > combat.c Line 194");
    }

    SDL_Texture *texture_fuite = SDL_CreateTextureFromSurface(game->render, surf_fuite);
    if (texture_fuite == NULL)
    {
        SDL_ExitWithError("Probleme texture attaque 3 > combat.c Line 194");
    }

    SDL_Rect pos_Wind_fuite;
    pos_Wind_fuite.x = (*game->WINDOWWIDTH) * 2300 / 2560;
    pos_Wind_fuite.y = (*game->WINDOWWIDTH) * 1319 / 2560;
    pos_Wind_fuite.w = (*game->WINDOWWIDTH) * strlen("Fuite") * 25 / 2560;
    pos_Wind_fuite.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nom enemie 1" -------------------------------------------*/

    SDL_Rect pos_Wind_nom_enemie_1;
    SDL_Texture *texture_nom_enemie_1 = NULL;
    SDL_Surface *surf_nom_enemie_1 = NULL;
    if (nb_enemie >= 1)
    {
        surf_nom_enemie_1 = TTF_RenderText_Blended(game->police, map->enemies[rand_enemie_1].name, blanc);
        if (surf_nom_enemie_1 == NULL)
        {
            SDL_ExitWithError("Probleme surface nom enemie 1 > combat.c Line 192");
        }

        texture_nom_enemie_1 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_1);
        if (texture_nom_enemie_1 == NULL)
        {
            SDL_ExitWithError("Probleme texture nom enemie 1 > combat.c Line 198");
        }

        pos_Wind_nom_enemie_1.x = (*game->WINDOWWIDTH) * 59 / 2560;
        pos_Wind_nom_enemie_1.y = (*game->WINDOWWIDTH) * 1069 / 2560;
        pos_Wind_nom_enemie_1.w = (*game->WINDOWWIDTH) * strlen(map->enemies[rand_enemie_1].name) * 25 / 2560;
        pos_Wind_nom_enemie_1.h = (*game->WINDOWWIDTH) * 75 / 2560;
    }

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nom enemie 2" -------------------------------------------*/

    SDL_Rect pos_Wind_nom_enemie_2;
    SDL_Texture *texture_nom_enemie_2 = NULL;
    SDL_Surface *surf_nom_enemie_2 = NULL;
    if (nb_enemie >= 2)
    {
        surf_nom_enemie_2 = TTF_RenderText_Blended(game->police, map->enemies[rand_enemie_2].name, blanc);
        if (surf_nom_enemie_2 == NULL)
        {
            SDL_ExitWithError("Probleme surface nom enemie 2 > combat.c Line 192");
        }

        texture_nom_enemie_2 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_2);
        if (texture_nom_enemie_2 == NULL)
        {
            SDL_ExitWithError("Probleme texture nom enemie 2 > combat.c Line 198");
        }

        pos_Wind_nom_enemie_2.x = (*game->WINDOWWIDTH) * 59 / 2560;
        pos_Wind_nom_enemie_2.y = (*game->WINDOWWIDTH) * 1150 / 2560;
        pos_Wind_nom_enemie_2.w = (*game->WINDOWWIDTH) * strlen(map->enemies[rand_enemie_2].name) * 25 / 2560;
        pos_Wind_nom_enemie_2.h = (*game->WINDOWWIDTH) * 75 / 2560;
    }

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nom enemie 3" -------------------------------------------*/

    SDL_Rect pos_Wind_nom_enemie_3;
    SDL_Texture *texture_nom_enemie_3 = NULL;
    SDL_Surface *surf_nom_enemie_3 = NULL;
    if (nb_enemie >= 3)
    {
        surf_nom_enemie_3 = TTF_RenderText_Blended(game->police, map->enemies[rand_enemie_3].name, blanc);
        if (surf_nom_enemie_3 == NULL)
        {
            SDL_ExitWithError("Probleme surface nom enemie 3 > combat.c Line 192");
        }

        texture_nom_enemie_3 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_3);
        if (texture_nom_enemie_3 == NULL)
        {
            SDL_ExitWithError("Probleme texture nom enemie 3 > combat.c Line 198");
        }

        pos_Wind_nom_enemie_3.x = (*game->WINDOWWIDTH) * 59 / 2560;
        pos_Wind_nom_enemie_3.y = (*game->WINDOWWIDTH) * 1231 / 2560;
        pos_Wind_nom_enemie_3.w = (*game->WINDOWWIDTH) * strlen(map->enemies[rand_enemie_3].name) * 25 / 2560;
        pos_Wind_nom_enemie_3.h = (*game->WINDOWWIDTH) * 75 / 2560;
    }

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nom enemie 4" -------------------------------------------*/

    SDL_Rect pos_Wind_nom_enemie_4;
    SDL_Texture *texture_nom_enemie_4 = NULL;
    SDL_Surface *surf_nom_enemie_4 = NULL;
    if (nb_enemie >= 4)
    {
        surf_nom_enemie_4 = TTF_RenderText_Blended(game->police, map->enemies[rand_enemie_4].name, blanc);
        if (surf_nom_enemie_4 == NULL)
        {
            SDL_ExitWithError("Probleme surface nom enemie 4 > combat.c Line 192");
        }

        texture_nom_enemie_4 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_4);
        if (texture_nom_enemie_4 == NULL)
        {
            SDL_ExitWithError("Probleme texture nom enemie 4 > combat.c Line 198");
        }

        pos_Wind_nom_enemie_4.x = (*game->WINDOWWIDTH) * 59 / 2560;
        pos_Wind_nom_enemie_4.y = (*game->WINDOWWIDTH) * 1312 / 2560;
        pos_Wind_nom_enemie_4.w = (*game->WINDOWWIDTH) * strlen(map->enemies[rand_enemie_4].name) * 25 / 2560;
        pos_Wind_nom_enemie_4.h = (*game->WINDOWWIDTH) * 75 / 2560;
    }

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nom personnage" ----------------------------------------*/

    SDL_Surface *surf_nom_personnage = NULL;
    surf_nom_personnage = TTF_RenderText_Blended(game->police, character->classe_name, blanc);
    if (surf_nom_personnage == NULL)
    {
        SDL_ExitWithError("Probleme surface nom personnage > combat.c Line 192");
    }

    SDL_Texture *texture_nom_personnage = NULL;
    texture_nom_personnage = SDL_CreateTextureFromSurface(game->render, surf_nom_personnage);
    if (texture_nom_personnage == NULL)
    {
        SDL_ExitWithError("Probleme texture nom personnage > combat.c Line 198");
    }

    strcpy(temp, character->classe_name);

    SDL_Rect pos_Wind_nom_personnage;
    pos_Wind_nom_personnage.x = (*game->WINDOWWIDTH) * 800 / 2560;
    pos_Wind_nom_personnage.y = (*game->WINDOWWIDTH) * 1069 / 2560;
    pos_Wind_nom_personnage.w = (*game->WINDOWWIDTH) * strlen(temp) * 25 / 2560;
    pos_Wind_nom_personnage.h = (*game->WINDOWWIDTH) * 75 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "PV personnage" ----------------------------------------*/

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

    /*--- Creation text "PV personnage" ----------------------------------------*/

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

    SDL_RenderClear(game->render);

    switch (nb_enemie)
    {
    case 1:
        SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
        SDL_RenderCopy(game->render, map->enemies[rand_enemie_1].texture, NULL, &pos_Wind_enemie_1_1);
        break;

    case 2:
        SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
        SDL_RenderCopy(game->render, map->enemies[rand_enemie_1].texture, NULL, &pos_Wind_enemie_2_1);
        SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);
        SDL_RenderCopy(game->render, map->enemies[rand_enemie_2].texture, NULL, &pos_Wind_enemie_2_2);
        break;

    case 3:
        SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
        SDL_RenderCopy(game->render, map->enemies[rand_enemie_1].texture, NULL, &pos_Wind_enemie_3_1);
        SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);
        SDL_RenderCopy(game->render, map->enemies[rand_enemie_2].texture, NULL, &pos_Wind_enemie_1_1);
        SDL_RenderCopy(game->render, texture_nom_enemie_3, NULL, &pos_Wind_nom_enemie_3);
        SDL_RenderCopy(game->render, map->enemies[rand_enemie_3].texture, NULL, &pos_Wind_enemie_3_3);
        break;

    case 4:
        SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
        SDL_RenderCopy(game->render, map->enemies[rand_enemie_1].texture, NULL, &pos_Wind_enemie_4_1);
        SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);
        SDL_RenderCopy(game->render, map->enemies[rand_enemie_2].texture, NULL, &pos_Wind_enemie_2_1);
        SDL_RenderCopy(game->render, texture_nom_enemie_3, NULL, &pos_Wind_nom_enemie_3);
        SDL_RenderCopy(game->render, map->enemies[rand_enemie_3].texture, NULL, &pos_Wind_enemie_2_2);
        SDL_RenderCopy(game->render, texture_nom_enemie_4, NULL, &pos_Wind_nom_enemie_4);
        SDL_RenderCopy(game->render, map->enemies[rand_enemie_4].texture, NULL, &pos_Wind_enemie_4_4);
        break;
    }

    //SDL_RenderCopy(game->render, map->texture, &map->tile_set, &pos_Wind_town);
    SDL_RenderCopy(game->render, texture_combat_cadre, NULL, &pos_Wind_cadre_combat);
    SDL_RenderCopy(game->render, character->texture, &character->West_Walk.rect, &pos_Wind_character);
    SDL_RenderCopy(game->render, texture_nom_personnage, NULL, &pos_Wind_nom_personnage);
    SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);

    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && combat_bool)
    {
        while (SDL_PollEvent(&event))
        {
            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                (*game->program_launch) = SDL_FALSE;
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
                selection = 2;
            selection %= 3;

            if (selection == 0) //Attaque
            {
                surf_fuite = TTF_RenderText_Blended(game->police, "Fuite", blanc);

                surf_attaque = TTF_RenderText_Blended(game->police, "Attaque", rouge);

                surf_sac = TTF_RenderText_Blended(game->police, "Sac", blanc);
            }

            if (selection == 1) //Sac
            {
                surf_attaque = TTF_RenderText_Blended(game->police, "Attaque", blanc);

                surf_sac = TTF_RenderText_Blended(game->police, "Sac", rouge);

                surf_fuite = TTF_RenderText_Blended(game->police, "Fuite", blanc);
            }

            if (selection == 2) //Fuite
            {
                surf_sac = TTF_RenderText_Blended(game->police, "Sac", blanc);

                surf_fuite = TTF_RenderText_Blended(game->police, "Fuite", rouge);

                surf_attaque = TTF_RenderText_Blended(game->police, "Attaque", blanc);
            }

            texture_attaque = SDL_CreateTextureFromSurface(game->render, surf_attaque);
            texture_sac = SDL_CreateTextureFromSurface(game->render, surf_sac);
            texture_fuite = SDL_CreateTextureFromSurface(game->render, surf_fuite);

            if (event.key.keysym.sym == SDLK_p)
            {
                itoa(character->life, char_character_life, 10);

                surf_PV_personnage = TTF_RenderText_Blended(game->police, char_character_life, rouge);
                texture_PV_personnage = SDL_CreateTextureFromSurface(game->render, surf_PV_personnage);

                character->life++;
            }

            if (event.key.keysym.sym == SDLK_m)
            {
                itoa(character->life, char_character_life, 10);

                surf_PV_personnage = TTF_RenderText_Blended(game->police, char_character_life, rouge);
                texture_PV_personnage = SDL_CreateTextureFromSurface(game->render, surf_PV_personnage);

                character->life--;
            }
            pos_Wind_PV_personnage.w = (*game->WINDOWWIDTH) * strlen(char_character_life) * 25 / 2560;

            if (character->life < 0)
            {
                character->life = 0;
            }

            if (character->life > character->max_life)
            {
                character->life = character->max_life;
            }

            SDL_RenderClear(game->render);

            SDL_SetRenderTarget(game->render, texture_render);

            SDL_RenderClear(game->render);

            //SDL_RenderCopy(game->render, map->texture, &map->tile_set, &pos_Wind_town);
            SDL_RenderCopy(game->render, texture_combat_cadre, NULL, &pos_Wind_cadre_combat);

            switch (nb_enemie)
            {
            case 1:
                SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
                SDL_RenderCopy(game->render, map->enemies[rand_enemie_1].texture, NULL, &pos_Wind_enemie_1_1);
                break;

            case 2:
                SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
                SDL_RenderCopy(game->render, map->enemies[rand_enemie_1].texture, NULL, &pos_Wind_enemie_2_1);
                SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);
                SDL_RenderCopy(game->render, map->enemies[rand_enemie_2].texture, NULL, &pos_Wind_enemie_2_2);
                break;

            case 3:
                SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
                SDL_RenderCopy(game->render, map->enemies[rand_enemie_1].texture, NULL, &pos_Wind_enemie_3_1);
                SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);
                SDL_RenderCopy(game->render, map->enemies[rand_enemie_2].texture, NULL, &pos_Wind_enemie_1_1);
                SDL_RenderCopy(game->render, texture_nom_enemie_3, NULL, &pos_Wind_nom_enemie_3);
                SDL_RenderCopy(game->render, map->enemies[rand_enemie_3].texture, NULL, &pos_Wind_enemie_3_3);
                break;

            case 4:
                SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
                SDL_RenderCopy(game->render, map->enemies[rand_enemie_1].texture, NULL, &pos_Wind_enemie_4_1);
                SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);
                SDL_RenderCopy(game->render, map->enemies[rand_enemie_2].texture, NULL, &pos_Wind_enemie_2_1);
                SDL_RenderCopy(game->render, texture_nom_enemie_3, NULL, &pos_Wind_nom_enemie_3);
                SDL_RenderCopy(game->render, map->enemies[rand_enemie_3].texture, NULL, &pos_Wind_enemie_2_2);
                SDL_RenderCopy(game->render, texture_nom_enemie_4, NULL, &pos_Wind_nom_enemie_4);
                SDL_RenderCopy(game->render, map->enemies[rand_enemie_4].texture, NULL, &pos_Wind_enemie_4_4);
                break;
            }

            if (character->life == 0)
            {
                pos_Wind_character.h = character->Dead.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
                pos_Wind_character.w = character->Dead.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
                pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 1.5;
                pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;
                SDL_RenderCopy(game->render, character->texture, &character->Dead, &pos_Wind_character);
            }
            else if (character->life < character->max_life / 4)
            {
                pos_Wind_character.h = character->Weak.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
                pos_Wind_character.w = character->Weak.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
                pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 1.5;
                pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;
                SDL_RenderCopy(game->render, character->texture, &character->Weak, &pos_Wind_character);
            }
            else
            {
                pos_Wind_character.h = character->West_Walk.rect.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
                pos_Wind_character.w = character->West_Walk.rect.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
                pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 1.5;
                pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;
                SDL_RenderCopy(game->render, character->texture, &character->West_Walk.rect, &pos_Wind_character);
            }

            SDL_RenderCopy(game->render, texture_nom_personnage, NULL, &pos_Wind_nom_personnage);
            SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
            SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);

            SDL_SetRenderTarget(game->render, NULL);

            SDL_RenderCopy(game->render, texture_render, NULL, NULL);

            SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
            SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
            SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);

            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {
                if (selection == 0)
                {
                    attacks_character(game, character, texture_render);
                }

                if (selection == 1)
                {
                    ouverture_sac(game, character, texture_render, NULL, 1);
                    selection = 1;
                }

                if (selection == 2)
                {
                    combat_bool = SDL_FALSE;
                }
            }
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, texture_render_town, NULL, NULL);

    SDL_RenderPresent(game->render);

    /*--- Free Memory ------------------------------------------------------------*/

    if (/*enemie_exist(enemie_1) == SDL_TRUE*/ 1)
    {
        SDL_FreeSurface(surf_nom_enemie_1);
    }

    if (/*enemie_exist(enemie_2) == SDL_TRUE*/ 1)
    {
        SDL_FreeSurface(surf_nom_enemie_2);
    }

    if (/*enemie_exist(enemie_3) == SDL_TRUE*/ 1)
    {
        SDL_FreeSurface(surf_nom_enemie_3);
    }

    if (/*enemie_exist(enemie_4) == SDL_TRUE*/ 1)
    {
        SDL_FreeSurface(surf_nom_enemie_4);
    }

    SDL_FreeSurface(surf_combat_cadre);

    SDL_DestroyTexture(texture_combat_cadre);

    /*--- End Free Memory --------------------------------------------------------*/
}