#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\enemy_selection.h"

#include "..\lib\combat.h"

/*!
 *
 * \file enemy_selection.c
 * \brief A FINIR.
 * \author Enzo BRENNUS
 *
 */

/*!
 *
 * \fn enemy_selection(game_t *game, character_t *character, enemy_t *enemies_cbt, int nb_enemies_combat, int nb_enemies_combat_actif, SDL_Texture *texture_render_attacks)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * \param texture_render_combat A FINIR.
 *
 */

extern int enemy_selection(game_t *game, character_t *character, enemy_t *enemies_cbt, int nb_enemies_combat, int nb_enemies_combat_actif, SDL_Texture *texture_render_attacks)
{
    /*--- Initialization Variable ------------------------------------------------*/

    int returnval;

    int selection = 0;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool enemy_selec_bool = SDL_TRUE;

    SDL_Event event;

    //POS CHARACTER
    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->Attack.h * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.w = character->Attack.w * (*game->WINDOWWIDTH) * 6.5 / 2560;
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 1.5;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2.8;

    
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

    /*--- End Initialization Variable --------------------------------------------*/

    /*--- Initialization texture "fleche" ----------------------------------------*/

    SDL_Surface *surf_fleche = SDL_LoadBMP("src\\image\\fleche.bmp");
    if (surf_fleche == NULL)
    {
        SDL_ExitWithError("probleme chargement image fleche gauche et droite");
    }

    SDL_Texture *texture_fleche_gauche = SDL_CreateTextureFromSurface(game->render, surf_fleche);
    if (texture_fleche_gauche == NULL)
    {
        SDL_ExitWithError("probleme texture fleche gauche");
    }

    SDL_Rect rect_fleche_gauche;
    rect_fleche_gauche.x = 39;
    rect_fleche_gauche.y = 0;
    rect_fleche_gauche.w = 38;
    rect_fleche_gauche.h = 28;

    SDL_Rect pos_fleche_gauche;
    pos_fleche_gauche.h = rect_fleche_gauche.h;
    pos_fleche_gauche.w = rect_fleche_gauche.w;

    switch (nb_enemies_combat_actif)
    {
    case 1: //POS ENEMIE 1
        selection = 0;
        pos_fleche_gauche.x = pos_Wind_enemie_1_1.x;
        pos_fleche_gauche.y = pos_Wind_enemie_1_1.y;
        break;

    case 2:
        if (!(enemies_cbt[0].life >= 0)) //POS ENEMIE 2_1
        {
            selection = 0;
            pos_fleche_gauche.x = pos_Wind_enemie_2_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
            pos_fleche_gauche.y = pos_Wind_enemie_2_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
        }
        else if (!(enemies_cbt[1].life >= 0)) //POS ENEMIE 2_2
        {
            selection = 1;
            pos_fleche_gauche.x = pos_Wind_enemie_2_2.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
            pos_fleche_gauche.y = pos_Wind_enemie_2_2.y + (*game->WINDOWWIDTH) * 100 / 2560;
        }
        break;

    case 3:
        if (!(enemies_cbt[0].life >= 0)) //POS ENEMIE 3_1
        {
            selection = 0;
            pos_fleche_gauche.x = pos_Wind_enemie_3_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
            pos_fleche_gauche.y = pos_Wind_enemie_3_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
        }
        else if (!(enemies_cbt[1].life >= 0)) //POS ENEMIE 1_1
        {
            selection = 1;
            pos_fleche_gauche.x = pos_Wind_enemie_1_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
            pos_fleche_gauche.y = pos_Wind_enemie_1_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
        }
        else if (!(enemies_cbt[2].life >= 0)) //POS ENEMIE 3_3
        {
            selection = 2;
            pos_fleche_gauche.x = pos_Wind_enemie_3_3.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
            pos_fleche_gauche.y = pos_Wind_enemie_3_3.y + (*game->WINDOWWIDTH) * 100 / 2560;
        }

        break;

    case 4:
        if (!(enemies_cbt[0].life >= 0)) //POS ENEMIE 4_1
        {
            selection = 0;
            pos_fleche_gauche.x = pos_Wind_enemie_4_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
            pos_fleche_gauche.y = pos_Wind_enemie_4_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
        }
        else if (!(enemies_cbt[1].life >= 0)) //POS ENEMIE 2_1
        {
            selection = 1;
            pos_fleche_gauche.x = pos_Wind_enemie_2_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
            pos_fleche_gauche.y = pos_Wind_enemie_2_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
        }
        else if (!(enemies_cbt[2].life >= 0)) //POS ENEMIE 2_2
        {
            selection = 2;
            pos_fleche_gauche.x = pos_Wind_enemie_2_2.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
            pos_fleche_gauche.y = pos_Wind_enemie_2_2.y + (*game->WINDOWWIDTH) * 100 / 2560;
        }
        else if (!(enemies_cbt[3].life >= 0)) //POS ENEMIE 4_4
        {
            selection = 3;
            pos_fleche_gauche.x = pos_Wind_enemie_4_4.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
            pos_fleche_gauche.y = pos_Wind_enemie_4_4.y + (*game->WINDOWWIDTH) * 100 / 2560;
        }
        break;
    }

    /*----------------------------------------------------------------------------*/

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && enemy_selec_bool)
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
                returnval = -1;
                enemy_selec_bool = SDL_FALSE;
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
            {
                selection = nb_enemies_combat - 1;
            }
            selection %= nb_enemies_combat;

            if (selection == 0)
            {
                switch (nb_enemies_combat)
                {
                case 1:
                    pos_fleche_gauche.x = pos_Wind_enemie_1_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
                    pos_fleche_gauche.y = pos_Wind_enemie_1_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
                    break;

                case 2:
                    pos_fleche_gauche.x = pos_Wind_enemie_2_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
                    pos_fleche_gauche.y = pos_Wind_enemie_2_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
                    break;

                case 3:
                    pos_fleche_gauche.x = pos_Wind_enemie_3_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
                    pos_fleche_gauche.y = pos_Wind_enemie_3_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
                    break;

                case 4:
                    pos_fleche_gauche.x = pos_Wind_enemie_4_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
                    pos_fleche_gauche.y = pos_Wind_enemie_4_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
                    break;
                }
            }

            if (selection == 1)
            {
                switch (nb_enemies_combat)
                {
                case 2:
                    pos_fleche_gauche.x = pos_Wind_enemie_2_2.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
                    pos_fleche_gauche.y = pos_Wind_enemie_2_2.y + (*game->WINDOWWIDTH) * 100 / 2560;
                    break;

                case 3:
                    pos_fleche_gauche.x = pos_Wind_enemie_1_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
                    pos_fleche_gauche.y = pos_Wind_enemie_1_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
                    break;

                case 4:
                    pos_fleche_gauche.x = pos_Wind_enemie_2_1.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
                    pos_fleche_gauche.y = pos_Wind_enemie_2_1.y + (*game->WINDOWWIDTH) * 100 / 2560;
                    break;
                }
            }

            if (selection == 2)
            {
                switch (nb_enemies_combat)
                {
                case 3:
                    pos_fleche_gauche.x = pos_Wind_enemie_3_3.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
                    pos_fleche_gauche.y = pos_Wind_enemie_3_3.y + (*game->WINDOWWIDTH) * 100 / 2560;
                    ;
                    break;

                case 4:
                    pos_fleche_gauche.x = pos_Wind_enemie_2_2.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
                    pos_fleche_gauche.y = pos_Wind_enemie_2_2.y + (*game->WINDOWWIDTH) * 100 / 2560;
                    break;
                }
            }

            if (selection == 3)
            {
                pos_fleche_gauche.x = pos_Wind_enemie_4_4.x + character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7 / 2560;
                pos_fleche_gauche.y = pos_Wind_enemie_4_4.y + (*game->WINDOWWIDTH) * 100 / 2560;
            }

            SDL_RenderClear(game->render);

            SDL_RenderCopy(game->render, texture_render_attacks, NULL, NULL);
            SDL_RenderCopy(game->render, texture_fleche_gauche, &rect_fleche_gauche, &pos_fleche_gauche);

            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {
                switch (selection)
                {
                case 0:
                    enemy_selec_bool = SDL_FALSE;
                    returnval = 0;
                    break;

                case 1:
                    enemy_selec_bool = SDL_FALSE;
                    returnval = 1;
                    break;

                case 2:
                    enemy_selec_bool = SDL_FALSE;
                    returnval = 2;
                    break;

                case 3:
                    enemy_selec_bool = SDL_FALSE;
                    returnval = 3;
                    break;
                }
            }
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_fleche);

    SDL_DestroyTexture(texture_fleche_gauche);

    /*--- End Free Memory --------------------------------------------------------*/

    return returnval;
}
