#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\combat_boss.h"

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
 * \fn combat_boss(game_t *game, character_t *character, map_t *map, SDL_Texture *texture_render_town)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * \param map A FINIR.
 * \param texture_render_town A FINIR.
 *
 */

extern void combat_boss(game_t *game, character_t *character, map_t *map, SDL_Texture *texture_render_town, SDL_bool *floor_bool)
{
    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Texture *texture_render = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};
    SDL_Color bleu = {0, 0, 255};
    SDL_Color gris = {100, 100, 100};

    enemy_t *boss;

    SDL_bool *combat_boss_bool = malloc(sizeof(SDL_bool));
    *combat_boss_bool = SDL_TRUE;

    int temp;

    //POS CHARACTER
    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 1.5;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;

    /*--- End Initialization Variable --------------------------------------------*/

    /*--- Initialization enemies -------------------------------------------------*/

    boss = NULL;
    boss = malloc(sizeof(enemy_t));

    boss->texture = NULL;

    boss->surface = NULL;

    boss->name = NULL;
    boss->name = malloc(sizeof(char) * 50);

    boss->attack = malloc(sizeof(attack_enemie_t) * map->nb_attacks_boss);

    for (int i = 0; i < map->nb_attacks_boss; i++)
    {
        boss->attack[i].name = NULL;
        boss->attack[i].name = malloc(sizeof(char) * 50);
    }

    enemy_cpy(boss, map->boss, game->render, map->nb_attacks_boss);

    /*----------------------------------------------------------------------------*/

    /*--- Initialization position ennemis  ---------------------------------------*/

    //POS ENEMIE 1
    SDL_Rect pos_Wind_boss;
    pos_Wind_boss.h = map->boss_H * map->boss_multiplier;
    pos_Wind_boss.w = map->boss_W * map->boss_multiplier;
    pos_Wind_boss.x = (*game->WINDOWWIDTH) / 4;
    pos_Wind_boss.y = ((*game->WINDOWHEIGHT) - pos_Wind_boss.h) / 2.8;

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

    /*--- Creation text boss -----------------------------------------------------*/

    SDL_Surface *surf_nom_boss = NULL;
    surf_nom_boss = TTF_RenderText_Blended(game->police, boss->name, blanc);
    if (surf_nom_boss == NULL)
    {
        SDL_ExitWithError("Probleme surface nom enemie 1 > combat.c Line 192");
    }

    SDL_Texture *texture_nom_boss = NULL;
    texture_nom_boss = SDL_CreateTextureFromSurface(game->render, surf_nom_boss);
    if (texture_nom_boss == NULL)
    {
        SDL_ExitWithError("Probleme texture nom enemie 1 > combat.c Line 198");
    }

    SDL_Rect pos_Wind_nom_boss;
    pos_Wind_nom_boss.x = (*game->WINDOWWIDTH) * 59 / 2560;
    pos_Wind_nom_boss.y = (*game->WINDOWWIDTH) * 1180 / 2560;
    pos_Wind_nom_boss.w = (*game->WINDOWWIDTH) * strlen(boss->name) * 35 / 2560;
    pos_Wind_nom_boss.h = (*game->WINDOWWIDTH) * 80 / 2560;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nom personnage" -----------------------------------------*/

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

    SDL_RenderCopy(game->render, texture_nom_boss, NULL, &pos_Wind_nom_boss);
    SDL_RenderCopy(game->render, boss->texture, NULL, &pos_Wind_boss);

    //SDL_RenderCopy(game->render, map->texture, &map->tile_set, &pos_Wind_town);
    SDL_RenderCopy(game->render, texture_combat_cadre, NULL, &pos_Wind_cadre_combat);

    SDL_RenderCopy(game->render, texture_nom_personnage, NULL, &pos_Wind_nom_personnage);

    SDL_SetRenderTarget(game->render, NULL);

    SDL_RenderCopy(game->render, texture_render, NULL, NULL);
    SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
    SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);

    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && *combat_boss_bool)
    {
        printf("combat_boss_bool: %i\n", *combat_boss_bool);
        printf("game->program_launch: %i\n", *game->program_launch);

        do
        {
            boss->atb += boss->speed;

            character->atb += character->vitesse;

        } while (character->atb <= 100 && boss->atb <= 100);

        if (boss->atb >= 100 && boss->life > 0)
        {
            printf("Tour enemies 1\n");
            enemy_turn(game, character, boss, 0, map, texture_render, map->nb_attacks_boss);
            boss->atb = 0;
        }

        if (character->life < 0)
        {
            character->life = 0;
        }

        if (character->atb >= 100 && character->life > 0)
        {
            printf("Tour character\n");
            character_turn(game, character, boss, 1, 1, texture_render, combat_boss_bool);
            character->atb = 0;
        }

        SDL_RenderClear(game->render);

        SDL_SetRenderTarget(game->render, texture_render);

        SDL_RenderClear(game->render);

        //SDL_RenderCopy(game->render, map->texture, &map->tile_set, &pos_Wind_town);
        SDL_RenderCopy(game->render, texture_combat_cadre, NULL, &pos_Wind_cadre_combat);

        if (boss->life <= 0)
        {
            surf_nom_boss = TTF_RenderText_Blended(game->police, boss->name, gris);
        }
        else
        {
            SDL_RenderCopy(game->render, boss->texture, NULL, &pos_Wind_boss);
        }
        texture_nom_boss = SDL_CreateTextureFromSurface(game->render, surf_nom_boss);
        SDL_RenderCopy(game->render, texture_nom_boss, NULL, &pos_Wind_nom_boss);

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

        if (boss->life <= 0)
        {
            fin_combat(game, character, texture_render, map, boss, 1);
            *combat_boss_bool = SDL_FALSE;
        }

        if (character->life == 0)
        {
            game_over(game, floor_bool, combat_boss_bool, character);
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, texture_render_town, NULL, NULL);

    SDL_RenderPresent(game->render);

    /*--- Free Memory ------------------------------------------------------------*/

    for (int y = 0; y < map->nb_attacks_boss; y++)
    {
        free(boss->attack[y].name);
    }
    free(boss->attack);

    free(boss->name);

    SDL_DestroyTexture(boss->texture);

    SDL_FreeSurface(boss->surface);

    SDL_FreeSurface(surf_combat_cadre);
    SDL_FreeSurface(surf_attaque);
    SDL_FreeSurface(surf_sac);
    SDL_FreeSurface(surf_fuite);
    SDL_FreeSurface(surf_nom_boss);
    SDL_FreeSurface(surf_nom_personnage);
    SDL_FreeSurface(surf_PV_personnage);
    SDL_FreeSurface(surf_PM_personnage);

    SDL_DestroyTexture(texture_combat_cadre);
    SDL_DestroyTexture(texture_attaque);
    SDL_DestroyTexture(texture_sac);
    SDL_DestroyTexture(texture_fuite);
    SDL_DestroyTexture(texture_nom_boss);
    SDL_DestroyTexture(texture_nom_personnage);
    SDL_DestroyTexture(texture_PV_personnage);
    SDL_DestroyTexture(texture_PM_personnage);

    /*--- End Free Memory --------------------------------------------------------*/
}