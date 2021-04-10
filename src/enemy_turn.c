#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "..\lib\enemy_turn.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\affichage_message.h"

/*!
 *
 * \file combat.c
 * \brief A FINIR.
 * \author Enzo BRENNUS
 *
 */

/*!
 *
 * \fn enemy_turn(game_t *game, character_t *character, enemy_t *enemy, map_t *map, SDL_Texture *texture_render_combat)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * \param map A FINIR.
 * \param texture_render_town A FINIR.
 *
 */

extern void enemy_turn(game_t *game, character_t *character, enemy_t *enemy, map_t *map, SDL_Texture *texture_render_combat)
{
    srand(time(NULL));

    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Color bleu = {0, 0, 255};
    SDL_Color rouge = {255, 0, 0};
    SDL_Color gris = {100, 100, 100};

    int attack_spe;

    int dmg;
    int dmg_modifier = 0;

    char char_dmg;

    char *msg;
    msg = malloc(sizeof(char) * 50);

    //POS CHARACTER
    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 1.5;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;

    /*--- End Initialization Variable --------------------------------------------*/

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

    /*--- Main Loop --------------------------------------------------------------*/

    attack_spe = rand() % 101;

    if (enemy->attack[1].effect_remaining == 0)
    {
        dmg_modifier = 0;
    }
    else
    {
        enemy->attack[1].effect_remaining--;
    }

    strcpy(msg, enemy->name);
    strcat(msg, " vous a fait ");

    if (attack_spe >= 0 && attack_spe <= enemy->attack[1].percentage && enemy->attack[1].percentage != -1)
    {
        switch (enemy->attack[1].effect)
        {
        case 0: //Buff d'attaque pendant un certain nombre de tours
            dmg = rand() % enemy->attack[1].dmg_max + enemy->attack[1].dmg_min;
            character->life -= dmg + dmg_modifier;
            dmg += dmg_modifier;

            enemy->attack[1].effect_remaining = enemy->attack[1].effect_duration;
            dmg_modifier = enemy->attack[1].modifier;

            char_dmg = dmg + '0';
            strncat(msg, &char_dmg, 1);
            strcat(msg, " degats avec une attaque spe.");
            break;

        case 1: //Empêche l'ennemi d'attaquer pendant un certain nombre de tour
            /* code */
            break;
        }

        surf_PV_personnage = TTF_RenderText_Blended(game->police, char_character_life, rouge);
    }
    else
    {
        dmg = rand() % enemy->attack[0].dmg_max + enemy->attack[0].dmg_min;
        character->life -= dmg + dmg_modifier;
        dmg += dmg_modifier;

        char_dmg = dmg + '0';
        strncat(msg, &char_dmg, 1);
        strcat(msg, " de degats.");

        surf_PV_personnage = TTF_RenderText_Blended(game->police, char_character_life, rouge);
    }
    texture_PV_personnage = SDL_CreateTextureFromSurface(game->render, surf_PV_personnage);

    SDL_RenderCopy(game->render, texture_render_combat, NULL, NULL);
    SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
    SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);
    SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
    SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
    SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);
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
    affichage_message(game, msg, -1);

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_PV_personnage);
    SDL_FreeSurface(surf_PM_personnage);
    SDL_FreeSurface(surf_attaque);
    SDL_FreeSurface(surf_sac);
    SDL_FreeSurface(surf_fuite);

    SDL_DestroyTexture(texture_PV_personnage);
    SDL_DestroyTexture(texture_PM_personnage);
    SDL_DestroyTexture(texture_attaque);
    SDL_DestroyTexture(texture_sac);
    SDL_DestroyTexture(texture_fuite);

    /*--- End Free Memory --------------------------------------------------------*/
}