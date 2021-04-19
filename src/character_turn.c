#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\character_turn.h"

#include "..\lib\frame.h"
#include "..\lib\character_attacks.h"
#include "..\lib\sac.h"
#include "..\lib\affichage_message.h"

/*!
 *
 * \file combat.c
 * \brief Gestion du tour de character_t en combat.
 * \author Enzo BRENNUS
 *
 */

/*!
 *
 * \fn character_turn(game_t *game, character_t *character, enemy_t *enemies_cbt, int nb_enemies_combat, int nb_enemies_combat_actif, SDL_Texture *texture_render_combat, SDL_bool *combat_bool)
 * \brief Fonction permettant de gerer le tour du personnage en combat.
 *
 * \param game est un pointeur sur l'objet game_t du jeu.
 * \param character est un pointeur sur l'objet character_t actuel.
 * \param map est un pointeur sur l'objet map_t actuel.
 * \param texture_render est un pointeur sur une texture représentant le fond d'avant le lancement de la fonction.
 * \param combat_bool A FINIR.
 *
 */

extern void character_turn(game_t *game, character_t *character, enemy_t *enemies_cbt, int nb_enemies_combat, int nb_enemies_combat_actif, SDL_Texture *texture_render_combat, SDL_bool *combat_bool)
{
    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};
    SDL_Color bleu = {0, 0, 255};
    SDL_Color gris = {100, 100, 100};

    int selection = 0;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool character_turn_bool = SDL_TRUE;

    SDL_Event event;

    int temp;

    //POS CHARACTER
    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->Attack.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->Attack.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 1.5;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;

    /*--- End Initialization Variable --------------------------------------------*/

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

    /*--- Creation text "Fuite" --------------------------------------------------*/

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

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, texture_render_combat, NULL, NULL);

    SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
    SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);

    SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
    SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
    SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);

    //Affichage du character vers le nord
    SDL_RenderClear(game->render);

    pos_Wind_character.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    SDL_RenderCopy(game->render, texture_render_combat, NULL, NULL);
    SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
    SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);
    SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
    SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
    SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);
    SDL_RenderCopy(game->render, character->texture, &character->North_Walk.rect, &pos_Wind_character);

    SDL_RenderPresent(game->render);
    SDL_Delay(100);

    //Affichage du character vers le est
    SDL_RenderClear(game->render);

    pos_Wind_character.h = character->East_Walk.rect.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->East_Walk.rect.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    SDL_RenderCopy(game->render, texture_render_combat, NULL, NULL);
    SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
    SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);
    SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
    SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
    SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);
    SDL_RenderCopy(game->render, character->texture, &character->East_Walk.rect, &pos_Wind_character);

    SDL_RenderPresent(game->render);
    SDL_Delay(100);

    //Affichage du character vers le sud
    SDL_RenderClear(game->render);

    pos_Wind_character.h = character->South_Walk.rect.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->South_Walk.rect.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    SDL_RenderCopy(game->render, texture_render_combat, NULL, NULL);
    SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
    SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);
    SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
    SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
    SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);
    SDL_RenderCopy(game->render, character->texture, &character->South_Walk.rect, &pos_Wind_character);

    SDL_RenderPresent(game->render);
    SDL_Delay(100);

    //Affichage du character vers le ouest
    SDL_RenderClear(game->render);

    pos_Wind_character.h = character->West_Walk.rect.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->West_Walk.rect.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    SDL_RenderCopy(game->render, texture_render_combat, NULL, NULL);
    SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
    SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);
    SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
    SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
    SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);
    SDL_RenderCopy(game->render, character->texture, &character->West_Walk.rect, &pos_Wind_character);

    SDL_RenderPresent(game->render);
    SDL_Delay(100);

    //Affichage du character avec une animation d'attaque
    SDL_RenderClear(game->render);

    pos_Wind_character.h = character->Attack.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->Attack.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    SDL_RenderCopy(game->render, texture_render_combat, NULL, NULL);
    SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
    SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);
    SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
    SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
    SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);
    SDL_RenderCopy(game->render, character->texture, &character->Attack, &pos_Wind_character);

    surf_attaque = TTF_RenderText_Blended(game->police, "Attaque", rouge);
    surf_sac = TTF_RenderText_Blended(game->police, "Sac", blanc);
    surf_fuite = TTF_RenderText_Blended(game->police, "Fuite", blanc);
    texture_attaque = SDL_CreateTextureFromSurface(game->render, surf_attaque);
    texture_sac = SDL_CreateTextureFromSurface(game->render, surf_sac);
    texture_fuite = SDL_CreateTextureFromSurface(game->render, surf_fuite);
    SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
    SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
    SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);

    SDL_RenderPresent(game->render);
    SDL_Delay(100);

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && character_turn_bool)
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

            SDL_SetRenderTarget(game->render, texture_render_combat);

            SDL_RenderCopy(game->render, character->texture, &character->Attack, &pos_Wind_character);

            SDL_SetRenderTarget(game->render, NULL);

            SDL_RenderClear(game->render);

            SDL_RenderCopy(game->render, texture_render_combat, NULL, NULL);
            SDL_RenderCopy(game->render, texture_PV_personnage, NULL, &pos_Wind_PV_personnage);
            SDL_RenderCopy(game->render, texture_PM_personnage, NULL, &pos_Wind_PM_personnage);

            SDL_RenderCopy(game->render, texture_attaque, NULL, &pos_Wind_attaque);
            SDL_RenderCopy(game->render, texture_sac, NULL, &pos_Wind_sac);
            SDL_RenderCopy(game->render, texture_fuite, NULL, &pos_Wind_fuite);
            SDL_RenderCopy(game->render, character->texture, &character->Attack, &pos_Wind_character);

            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {
                if (selection == 0)
                {
                    character_attacks(game, character, enemies_cbt, nb_enemies_combat, nb_enemies_combat_actif, texture_render_combat, &character_turn_bool);
                }

                if (selection == 1)
                {
                    ouverture_sac(game, character, texture_render_combat, NULL, &character_turn_bool);
                    selection = 1;
                }

                if (selection == 2)
                {
                    if (enemies_cbt->boss == SDL_FALSE)
                    {
                        temp = rand() % 101;
                        affichage_message(game, texture_render_combat, "Vous essayez de fuir...", NULL, -1);
                        switch (nb_enemies_combat)
                        {
                        case 1:
                            if (temp >= 0 && temp <= 80)
                            {
                                affichage_message(game, texture_render_combat, "...et c'est un succes.", NULL, -1);
                                character_turn_bool = SDL_FALSE;
                                *combat_bool = SDL_FALSE;
                                break;
                            }
                            affichage_message(game, texture_render_combat, "Mais l'ennemi vous en empeche.", NULL, -1);
                            character_turn_bool = SDL_FALSE;
                            break;

                        case 2:
                            if (temp >= 0 && temp <= 70)
                            {
                                affichage_message(game, texture_render_combat, "...et c'est un succes.", NULL, -1);
                                character_turn_bool = SDL_FALSE;
                                *combat_bool = SDL_FALSE;
                                break;
                            }
                            affichage_message(game, texture_render_combat, "Mais l'ennemi vous en empeche.", NULL, -1);
                            character_turn_bool = SDL_FALSE;
                            break;

                        case 3:
                            if (temp >= 0 && temp <= 60)
                            {
                                affichage_message(game, texture_render_combat, "...et c'est un succes.", NULL, -1);
                                character_turn_bool = SDL_FALSE;
                                *combat_bool = SDL_FALSE;
                                break;
                            }
                            affichage_message(game, texture_render_combat, "Mais l'ennemi vous en empeche.", NULL, -1);
                            character_turn_bool = SDL_FALSE;
                            break;

                        case 4:
                            if (temp >= 0 && temp <= 50)
                            {
                                affichage_message(game, texture_render_combat, "...et c'est un succes.", NULL, -1);
                                character_turn_bool = SDL_FALSE;
                                *combat_bool = SDL_FALSE;
                                break;
                            }
                            affichage_message(game, texture_render_combat, "Mais l'ennemi vous en empeche.", NULL, -1);
                            character_turn_bool = SDL_FALSE;
                            break;
                        }
                    }
                    else
                    {
                        affichage_message(game, texture_render_combat, "Vous essayez de fuir...", NULL, -1);
                        affichage_message(game, texture_render_combat, "La défaite est inévitable.", NULL, -1);
                        character_turn_bool = SDL_FALSE;
                        *combat_bool = SDL_FALSE;
                    }
                }
            }
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_attaque);
    SDL_FreeSurface(surf_sac);
    SDL_FreeSurface(surf_fuite);
    SDL_FreeSurface(surf_PV_personnage);
    SDL_FreeSurface(surf_PM_personnage);

    SDL_DestroyTexture(texture_attaque);
    SDL_DestroyTexture(texture_sac);
    SDL_DestroyTexture(texture_fuite);
    SDL_DestroyTexture(texture_PV_personnage);
    SDL_DestroyTexture(texture_PM_personnage);

    /*--- End Free Memory --------------------------------------------------------*/
}