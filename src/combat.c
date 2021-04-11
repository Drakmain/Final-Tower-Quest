#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\combat.h"

#include "..\lib\frame.h"
#include "..\lib\character_turn.h"
#include "..\lib\enemy_turn.h"
#include "..\lib\character_attacks.h"
#include "..\lib\sac.h"
#include "..\lib\fin_combat.h"
#include "..\lib\game_over.h"

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

extern void combat(game_t *game, character_t *character, map_t *map, SDL_Texture *texture_render_town, SDL_bool *floor_bool)
{
    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Texture *texture_render = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};
    SDL_Color bleu = {0, 0, 255};
    SDL_Color gris = {100, 100, 100};

    int nb_enemies_combat;

    int nb_enemies_combat_actif;

    enemy_t *enemies_cbt;

    SDL_bool *combat_bool = malloc(sizeof(SDL_bool));
    *combat_bool = SDL_TRUE;

    SDL_Event event;

    int temp;

    //POS CHARACTER
    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 1.5;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;

    /*--- End Initialization Variable --------------------------------------------*/

    /*--- Initialization number of ennemis ---------------------------------------*/

    nb_enemies_combat = rand() % NB_MAX_ENEMIES_CBT + 1;
    nb_enemies_combat_actif = nb_enemies_combat;

    /*--- End Initialization number of ennemis -----------------------------------*/

    /*--- Initialization enemies -------------------------------------------------*/

    enemies_cbt = NULL;
    enemies_cbt = malloc(sizeof(enemy_t) * nb_enemies_combat);

    for (int i = 0; i < nb_enemies_combat; i++)
    {
        enemies_cbt[i].texture = NULL;

        enemies_cbt[i].surface = NULL;

        enemies_cbt[i].name = NULL;
        enemies_cbt[i].name = malloc(sizeof(char) * 50);

        enemies_cbt[i].attack = malloc(sizeof(attack_enemie_t) * NB_ATTACKS_ENEMIES);

        for (int y = 0; y < NB_ATTACKS_ENEMIES; y++)
        {
            enemies_cbt[i].attack[y].name = NULL;
            enemies_cbt[i].attack[y].name = malloc(sizeof(char) * 50);
        }
    }

    /*----------------------------------------------------------------------------*/

    /*--- Copy of enemies --------------------------------------------------------*/

    for (int i = 0; i < nb_enemies_combat; i++)
    {
        temp = rand() % NB_ENEMIES;
        enemy_cpy(&(enemies_cbt[i]), &(map->enemies[temp]), game->render);
    }

    /*----------------------------------------------------------------------------*/

    /*--- Initialization position ennemis  ---------------------------------------*/

    //POS ENEMIE 1
    SDL_Rect pos_Wind_enemie_1_1;
    pos_Wind_enemie_1_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_1_1.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_1_1.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_1_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;

    //POS ENEMIE 2
    SDL_Rect pos_Wind_enemie_2_1;
    pos_Wind_enemie_2_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_2_1.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_2_1.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_2_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 3.8;

    SDL_Rect pos_Wind_enemie_2_2;
    pos_Wind_enemie_2_2.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_2_2.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_2_2.x = (*game->WINDOWWIDTH) / 3;
    pos_Wind_enemie_2_2.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.2;

    //POS ENEMIE 3
    SDL_Rect pos_Wind_enemie_3_1;
    pos_Wind_enemie_3_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_3_1.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_3_1.x = (*game->WINDOWWIDTH) / 2.8;
    pos_Wind_enemie_3_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 6;

    SDL_Rect pos_Wind_enemie_3_3;
    pos_Wind_enemie_3_3.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_3_3.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_3_3.x = (*game->WINDOWWIDTH) / 2.8;
    pos_Wind_enemie_3_3.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 1.8;

    //POS ENEMIE 4
    SDL_Rect pos_Wind_enemie_4_1;
    pos_Wind_enemie_4_1.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_4_1.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_4_1.x = (*game->WINDOWWIDTH) / 2.8;
    pos_Wind_enemie_4_1.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 15;

    SDL_Rect pos_Wind_enemie_4_4;
    pos_Wind_enemie_4_4.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7 / 2560;
    pos_Wind_enemie_4_4.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
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
    surf_attaque = TTF_RenderText_Blended(game->police, "Attaque", gris);
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
    surf_sac = TTF_RenderText_Blended(game->police, "Sac", gris);
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

    /*--- Creation text "Fuite" ----------------------------------------------*/

    SDL_Surface *surf_fuite = NULL;
    surf_fuite = TTF_RenderText_Blended(game->police, "Fuite", gris);
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
    if (nb_enemies_combat >= 1)
    {
        surf_nom_enemie_1 = TTF_RenderText_Blended(game->police, enemies_cbt[0].name, blanc);
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
        pos_Wind_nom_enemie_1.w = (*game->WINDOWWIDTH) * strlen(enemies_cbt[0].name) * 25 / 2560;
        pos_Wind_nom_enemie_1.h = (*game->WINDOWWIDTH) * 75 / 2560;
    }

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nom enemie 2" -------------------------------------------*/

    SDL_Rect pos_Wind_nom_enemie_2;
    SDL_Texture *texture_nom_enemie_2 = NULL;
    SDL_Surface *surf_nom_enemie_2 = NULL;
    if (nb_enemies_combat >= 2)
    {
        surf_nom_enemie_2 = TTF_RenderText_Blended(game->police, enemies_cbt[1].name, blanc);
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
        pos_Wind_nom_enemie_2.w = (*game->WINDOWWIDTH) * strlen(enemies_cbt[1].name) * 25 / 2560;
        pos_Wind_nom_enemie_2.h = (*game->WINDOWWIDTH) * 75 / 2560;
    }

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nom enemie 3" -------------------------------------------*/

    SDL_Rect pos_Wind_nom_enemie_3;
    SDL_Texture *texture_nom_enemie_3 = NULL;
    SDL_Surface *surf_nom_enemie_3 = NULL;
    if (nb_enemies_combat >= 3)
    {
        surf_nom_enemie_3 = TTF_RenderText_Blended(game->police, enemies_cbt[2].name, blanc);
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
        pos_Wind_nom_enemie_3.w = (*game->WINDOWWIDTH) * strlen(enemies_cbt[2].name) * 25 / 2560;
        pos_Wind_nom_enemie_3.h = (*game->WINDOWWIDTH) * 75 / 2560;
    }

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nom enemie 4" -------------------------------------------*/

    SDL_Rect pos_Wind_nom_enemie_4;
    SDL_Texture *texture_nom_enemie_4 = NULL;
    SDL_Surface *surf_nom_enemie_4 = NULL;
    if (nb_enemies_combat >= 4)
    {
        surf_nom_enemie_4 = TTF_RenderText_Blended(game->police, enemies_cbt[3].name, blanc);
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
        pos_Wind_nom_enemie_4.w = (*game->WINDOWWIDTH) * strlen(enemies_cbt[3].name) * 25 / 2560;
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

    SDL_Rect pos_Wind_nom_personnage;
    pos_Wind_nom_personnage.x = (*game->WINDOWWIDTH) * 800 / 2560;
    pos_Wind_nom_personnage.y = (*game->WINDOWWIDTH) * 1069 / 2560;
    pos_Wind_nom_personnage.w = (*game->WINDOWWIDTH) * strlen(character->classe_name) * 25 / 2560;
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

    SDL_SetRenderTarget(game->render, texture_render);

    switch (nb_enemies_combat)
    {
    case 1:
        SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
        SDL_RenderCopy(game->render, enemies_cbt[0].texture, NULL, &pos_Wind_enemie_1_1);
        break;

    case 2:
        SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
        SDL_RenderCopy(game->render, enemies_cbt[0].texture, NULL, &pos_Wind_enemie_2_1);
        SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);
        SDL_RenderCopy(game->render, enemies_cbt[1].texture, NULL, &pos_Wind_enemie_2_2);
        break;

    case 3:
        SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
        SDL_RenderCopy(game->render, enemies_cbt[0].texture, NULL, &pos_Wind_enemie_3_1);
        SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);
        SDL_RenderCopy(game->render, enemies_cbt[1].texture, NULL, &pos_Wind_enemie_1_1);
        SDL_RenderCopy(game->render, texture_nom_enemie_3, NULL, &pos_Wind_nom_enemie_3);
        SDL_RenderCopy(game->render, enemies_cbt[2].texture, NULL, &pos_Wind_enemie_3_3);
        break;

    case 4:
        SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
        SDL_RenderCopy(game->render, enemies_cbt[0].texture, NULL, &pos_Wind_enemie_4_1);
        SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);
        SDL_RenderCopy(game->render, enemies_cbt[1].texture, NULL, &pos_Wind_enemie_2_1);
        SDL_RenderCopy(game->render, texture_nom_enemie_3, NULL, &pos_Wind_nom_enemie_3);
        SDL_RenderCopy(game->render, enemies_cbt[2].texture, NULL, &pos_Wind_enemie_2_2);
        SDL_RenderCopy(game->render, texture_nom_enemie_4, NULL, &pos_Wind_nom_enemie_4);
        SDL_RenderCopy(game->render, enemies_cbt[3].texture, NULL, &pos_Wind_enemie_4_4);
        break;
    }

    //SDL_RenderCopy(game->render, map->texture, &map->tile_set, &pos_Wind_town);
    SDL_RenderCopy(game->render, texture_combat_cadre, NULL, &pos_Wind_cadre_combat);

    SDL_RenderCopy(game->render, texture_nom_personnage, NULL, &pos_Wind_nom_personnage);

    SDL_SetRenderTarget(game->render, NULL);

    SDL_RenderCopy(game->render, texture_render, NULL, NULL);
    SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
    SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);

    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && *combat_bool)
    {
        SDL_PollEvent(&event);
        do
        {
            switch (nb_enemies_combat)
            {
            case 1:
                enemies_cbt[0].atb += enemies_cbt[0].speed;
                break;

            case 2:
                enemies_cbt[0].atb += enemies_cbt[0].speed;
                enemies_cbt[1].atb += enemies_cbt[1].speed;
                break;

            case 3:
                enemies_cbt[0].atb += enemies_cbt[0].speed;
                enemies_cbt[1].atb += enemies_cbt[1].speed;
                enemies_cbt[2].atb += enemies_cbt[2].speed;
                break;

            case 4:
                enemies_cbt[0].atb += enemies_cbt[0].speed;
                enemies_cbt[1].atb += enemies_cbt[1].speed;
                enemies_cbt[2].atb += enemies_cbt[2].speed;
                enemies_cbt[3].atb += enemies_cbt[3].speed;
                break;
            }
            character->atb += character->vitesse;
            /*
            printf("character->atb: %i\n", character->atb);
            printf("enemies_cbt[0].atb: %i\n", enemies_cbt[0].atb);
            printf("enemies_cbt[0].atb: %i\n", enemies_cbt[0].atb);
            printf("enemies_cbt[0].atb: %i\n", enemies_cbt[0].atb);
            printf("enemies_cbt[0].atb: %i\n\n", enemies_cbt[0].atb);*/
        } while (character->atb <= 100 && enemies_cbt[0].atb <= 100 && enemies_cbt[1].atb <= 100 && enemies_cbt[2].atb <= 100 && enemies_cbt[3].atb <= 100);

        switch (nb_enemies_combat)
        {
        case 1:
            if (enemies_cbt[0].atb >= 100 && enemies_cbt[0].life > 0)
            {
                printf("Tour enemies 1\n");
                enemy_turn(game, character, enemies_cbt, 0, map, texture_render);
                enemies_cbt[0].atb = 0;
            }

            if (character->life < 0)
            {
                character->life = 0;
            }
            break;

        case 2:
            if (enemies_cbt[0].atb >= 100 && enemies_cbt[0].life > 0)
            {
                printf("Tour enemies 1\n");
                enemy_turn(game, character, enemies_cbt, 0, map, texture_render);
                enemies_cbt[0].atb = 0;
            }
            else if (enemies_cbt[1].atb >= 100 && enemies_cbt[1].life > 0)
            {
                printf("Tour enemies 2\n");
                enemy_turn(game, character, enemies_cbt, 1, map, texture_render);
                enemies_cbt[1].atb = 0;
            }

            if (character->life < 0)
            {
                character->life = 0;
            }
            break;

        case 3:
            if (enemies_cbt[0].atb >= 100 && enemies_cbt[0].life > 0)
            {
                printf("Tour enemies 1\n");
                enemy_turn(game, character, enemies_cbt, 0, map, texture_render);
                enemies_cbt[0].atb = 0;
            }
            else if (enemies_cbt[1].atb >= 100 && enemies_cbt[1].life > 0)
            {
                printf("Tour enemies 2\n");
                enemy_turn(game, character, enemies_cbt, 1, map, texture_render);
                enemies_cbt[1].atb = 0;
            }
            else if (enemies_cbt[2].atb >= 100 && enemies_cbt[2].life > 0)
            {
                printf("Tour enemies 3\n");
                enemy_turn(game, character, enemies_cbt, 2, map, texture_render);
                enemies_cbt[2].atb = 0;
            }

            if (character->life < 0)
            {
                character->life = 0;
            }
            break;

        case 4:
            if (enemies_cbt[0].atb >= 100 && enemies_cbt[0].life > 0)
            {
                printf("Tour enemies 1\n");
                enemy_turn(game, character, enemies_cbt, 0, map, texture_render);
                enemies_cbt[0].atb = 0;
            }
            else if (enemies_cbt[1].atb >= 100 && enemies_cbt[1].life > 0)
            {
                printf("Tour enemies 2\n");
                enemy_turn(game, character, enemies_cbt, 1, map, texture_render);
                enemies_cbt[1].atb = 0;
            }
            else if (enemies_cbt[2].atb >= 100 && enemies_cbt[2].life > 0)
            {
                printf("Tour enemies 3\n");
                enemy_turn(game, character, enemies_cbt, 2, map, texture_render);
                enemies_cbt[2].atb = 0;
            }
            else if (enemies_cbt[3].atb >= 100 && enemies_cbt[3].life > 0)
            {
                printf("Tour enemies 4\n");
                enemy_turn(game, character, enemies_cbt, 3, map, texture_render);
                enemies_cbt[3].atb = 0;
            }

            if (character->life < 0)
            {
                character->life = 0;
            }
            break;
        }

        if (character->atb >= 100)
        {
            printf("Tour character\n");
            character_turn(game, character, enemies_cbt, nb_enemies_combat, nb_enemies_combat_actif, texture_render, combat_bool);
            character->atb = 0;
        }

        if (enemies_cbt[0].life <= 0 && enemies_cbt[1].life <= 0 && enemies_cbt[2].life <= 0 && enemies_cbt[3].life <= 0)
        {
            fin_combat(game, character, texture_render, map, enemies_cbt, nb_enemies_combat);
        }

        SDL_RenderClear(game->render);

        SDL_SetRenderTarget(game->render, texture_render);

        SDL_RenderClear(game->render);

        //SDL_RenderCopy(game->render, map->texture, &map->tile_set, &pos_Wind_town);
        SDL_RenderCopy(game->render, texture_combat_cadre, NULL, &pos_Wind_cadre_combat);

        switch (nb_enemies_combat)
        {
        case 1:
            if (enemies_cbt[0].life <= 0)
            {
                surf_nom_enemie_1 = TTF_RenderText_Blended(game->police, enemies_cbt[0].name, gris);
            }
            else
            {
                SDL_RenderCopy(game->render, enemies_cbt[0].texture, NULL, &pos_Wind_enemie_1_1);
            }
            texture_nom_enemie_1 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_1);
            SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);
            break;

        case 2:
            if (enemies_cbt[0].life <= 0)
            {
                surf_nom_enemie_1 = TTF_RenderText_Blended(game->police, enemies_cbt[0].name, gris);
            }
            else
            {
                SDL_RenderCopy(game->render, enemies_cbt[0].texture, NULL, &pos_Wind_enemie_2_1);
            }
            texture_nom_enemie_1 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_1);
            SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);

            if (enemies_cbt[1].life <= 0)
            {
                surf_nom_enemie_2 = TTF_RenderText_Blended(game->police, enemies_cbt[1].name, gris);
            }
            else
            {
                SDL_RenderCopy(game->render, enemies_cbt[1].texture, NULL, &pos_Wind_enemie_2_2);
            }
            texture_nom_enemie_2 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_2);
            SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);
            break;

        case 3:
            if (enemies_cbt[0].life <= 0)
            {
                surf_nom_enemie_1 = TTF_RenderText_Blended(game->police, enemies_cbt[0].name, gris);
            }
            else
            {
                SDL_RenderCopy(game->render, enemies_cbt[0].texture, NULL, &pos_Wind_enemie_3_1);
            }
            texture_nom_enemie_1 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_1);
            SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);

            if (enemies_cbt[1].life <= 0)
            {
                surf_nom_enemie_2 = TTF_RenderText_Blended(game->police, enemies_cbt[1].name, gris);
            }
            else
            {
                SDL_RenderCopy(game->render, enemies_cbt[1].texture, NULL, &pos_Wind_enemie_1_1);
            }
            texture_nom_enemie_2 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_2);
            SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);

            if (enemies_cbt[2].life <= 0)
            {
                surf_nom_enemie_3 = TTF_RenderText_Blended(game->police, enemies_cbt[2].name, gris);
            }
            else
            {
                SDL_RenderCopy(game->render, enemies_cbt[2].texture, NULL, &pos_Wind_enemie_3_3);
            }
            texture_nom_enemie_3 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_3);
            SDL_RenderCopy(game->render, texture_nom_enemie_3, NULL, &pos_Wind_nom_enemie_3);
            break;

        case 4:
            if (enemies_cbt[0].life <= 0)
            {
                surf_nom_enemie_1 = TTF_RenderText_Blended(game->police, enemies_cbt[0].name, gris);
            }
            else
            {
                SDL_RenderCopy(game->render, enemies_cbt[0].texture, NULL, &pos_Wind_enemie_4_1);
            }
            texture_nom_enemie_1 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_1);
            SDL_RenderCopy(game->render, texture_nom_enemie_1, NULL, &pos_Wind_nom_enemie_1);

            if (enemies_cbt[1].life <= 0)
            {
                surf_nom_enemie_2 = TTF_RenderText_Blended(game->police, enemies_cbt[1].name, gris);
            }
            else
            {
                SDL_RenderCopy(game->render, enemies_cbt[1].texture, NULL, &pos_Wind_enemie_2_1);
            }
            texture_nom_enemie_2 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_2);
            SDL_RenderCopy(game->render, texture_nom_enemie_2, NULL, &pos_Wind_nom_enemie_2);

            if (enemies_cbt[2].life <= 0)
            {
                surf_nom_enemie_3 = TTF_RenderText_Blended(game->police, enemies_cbt[2].name, gris);
            }
            else
            {
                SDL_RenderCopy(game->render, enemies_cbt[2].texture, NULL, &pos_Wind_enemie_2_2);
            }
            texture_nom_enemie_3 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_3);
            SDL_RenderCopy(game->render, texture_nom_enemie_3, NULL, &pos_Wind_nom_enemie_3);

            if (enemies_cbt[3].life <= 0)
            {
                surf_nom_enemie_4 = TTF_RenderText_Blended(game->police, enemies_cbt[3].name, gris);
            }
            else
            {
                SDL_RenderCopy(game->render, enemies_cbt[3].texture, NULL, &pos_Wind_enemie_4_4);
            }
            texture_nom_enemie_4 = SDL_CreateTextureFromSurface(game->render, surf_nom_enemie_4);
            SDL_RenderCopy(game->render, texture_nom_enemie_4, NULL, &pos_Wind_nom_enemie_4);
            break;
        }

        SDL_RenderCopy(game->render, texture_nom_personnage, NULL, &pos_Wind_nom_personnage);

        SDL_SetRenderTarget(game->render, NULL);

        if (character->life <= 0)
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

        SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
        SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);

        SDL_RenderCopy(game->render, texture_render, NULL, NULL);
        SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
        SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
        SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);

        SDL_RenderPresent(game->render);

        switch (nb_enemies_combat)
        {
        case 1:
            if (enemies_cbt[0].life <= 0)
            {
                fin_combat(game, character, texture_render, map, enemies_cbt, nb_enemies_combat);
                *combat_bool = SDL_FALSE;
            }
            break;

        case 2:
            if (enemies_cbt[0].life <= 0 && enemies_cbt[1].life <= 0)
            {
                fin_combat(game, character, texture_render, map, enemies_cbt, nb_enemies_combat);
                *combat_bool = SDL_FALSE;
            }
            break;

        case 3:
            if (enemies_cbt[0].life <= 0 && enemies_cbt[1].life <= 0 && enemies_cbt[2].life <= 0)
            {
                fin_combat(game, character, texture_render, map, enemies_cbt, nb_enemies_combat);
                *combat_bool = SDL_FALSE;
            }
            break;

        case 4:
            if (enemies_cbt[0].life <= 0 && enemies_cbt[1].life <= 0 && enemies_cbt[2].life <= 0 && enemies_cbt[3].life <= 0)
            {
                fin_combat(game, character, texture_render, map, enemies_cbt, nb_enemies_combat);
                *combat_bool = SDL_FALSE;
            }
            break;
        }

        if (character->life == 0)
        {
            game_over(game, floor_bool, combat_bool, character);
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, texture_render_town, NULL, NULL);

    SDL_RenderPresent(game->render);

    /*--- Free Memory ------------------------------------------------------------*/

    for (int i = 0; i < nb_enemies_combat - 1; i++)
    {
        for (int y = 0; y < NB_ATTACKS_ENEMIES; y++)
        {
            free(enemies_cbt[i].attack[y].name);
        }
        free(enemies_cbt[i].attack);

        free(enemies_cbt[i].name);

        SDL_DestroyTexture(enemies_cbt[i].texture);

        SDL_FreeSurface(enemies_cbt[i].surface);
    }

    SDL_FreeSurface(surf_combat_cadre);
    SDL_FreeSurface(surf_attaque);
    SDL_FreeSurface(surf_sac);
    SDL_FreeSurface(surf_fuite);
    SDL_FreeSurface(surf_nom_enemie_1);
    SDL_FreeSurface(surf_nom_enemie_2);
    SDL_FreeSurface(surf_nom_enemie_3);
    SDL_FreeSurface(surf_nom_enemie_4);
    SDL_FreeSurface(surf_nom_personnage);
    SDL_FreeSurface(surf_PV_personnage);
    SDL_FreeSurface(surf_PM_personnage);

    SDL_DestroyTexture(texture_combat_cadre);
    SDL_DestroyTexture(texture_attaque);
    SDL_DestroyTexture(texture_sac);
    SDL_DestroyTexture(texture_fuite);
    SDL_DestroyTexture(texture_nom_enemie_1);
    SDL_DestroyTexture(texture_nom_enemie_2);
    SDL_DestroyTexture(texture_nom_enemie_3);
    SDL_DestroyTexture(texture_nom_enemie_4);
    SDL_DestroyTexture(texture_nom_personnage);
    SDL_DestroyTexture(texture_PV_personnage);
    SDL_DestroyTexture(texture_PM_personnage);

    /*--- End Free Memory --------------------------------------------------------*/
}