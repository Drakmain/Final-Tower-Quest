#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\game_over.h"
#include "..\lib\character.h"


/*!
 *
 * \file game_over.c
 * \brief A FINIR.
 * \author Alexis BOUFFARD
 *
 */

/*!
 *
 * \fn game_over(game_t *game,  char *actual_save)
 * \brief A FINIR.
 *
 *
 */

extern void game_over(game_t *game, SDL_bool *floor_bool, SDL_bool *combat_bool, character_t *character)
{

    /*--- Initialization variable ------------------------------------------------*/

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};

    SDL_Surface *surf_text_gameOver = NULL, *surf_cadre = NULL, *surf_confirmation = NULL, *surf_choix_oui = NULL, *surf_choix_non = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    SDL_bool gameover_bool = SDL_TRUE;

    int selection = 0;

    /*--- End Initialization variable --------------------------------------------*/


    /*--- Creation text "Game Over" ----------------------------------------*/

    surf_text_gameOver = TTF_RenderText_Blended(game->police, "GAME OVER", blanc);
    if (surf_text_gameOver == NULL)
    {
        SDL_ExitWithError("probleme surface text_gameOver");
    }

    SDL_Texture *text_gameOver = SDL_CreateTextureFromSurface(game->render, surf_text_gameOver);
    if (text_gameOver == NULL)
    {
        SDL_ExitWithError("probleme texture text_gameOver");
    }

    SDL_Rect pos_text_gameOver;
    pos_text_gameOver.w = (*game->WINDOWWIDTH) * 1000 / 1920;
    pos_text_gameOver.h = (*game->WINDOWHEIGHT) * 320 / 1080;
    pos_text_gameOver.x = (*game->WINDOWWIDTH)/2 - pos_text_gameOver.w/2;
    pos_text_gameOver.y = (*game->WINDOWHEIGHT)/3.5 - pos_text_gameOver.h/2;

    /*----------------------------------------------------------------------------*/

    /*---texture "cadre"--------------------------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_texte_confirmation.bmp");
    if (surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre texte_confirmation");
    }

    SDL_Texture *cadre = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if (cadre == NULL)
    {
        SDL_ExitWithError("probleme texture cadre texte confirmation");
    }

    SDL_Rect pos_cadre;
    pos_cadre.w = (*game->WINDOWWIDTH) * 900 / 1280;
    pos_cadre.h = (*game->WINDOWHEIGHT) * 200 / 720;
    pos_cadre.x = (*game->WINDOWWIDTH) / 2 - pos_cadre.w / 2;
    pos_cadre.y = (*game->WINDOWHEIGHT) / 1.5 - pos_cadre.h / 2;

    /*------------------------------------------------------------------------------------*/

    /*---texture fond--------------------------------------------------------*/

    SDL_Texture *fond_cadre = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre.w, pos_cadre.h);
    if (fond_cadre == NULL)
    {
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_fond_cadre;
    pos_fond_cadre.x = pos_cadre.x;
    pos_fond_cadre.y = pos_cadre.y;
    pos_fond_cadre.w = pos_cadre.w;
    pos_fond_cadre.h = pos_cadre.h;

    SDL_Rect rect_fond_cadre;
    rect_fond_cadre.x = (*game->WINDOWWIDTH) * 12 / 1280;
    rect_fond_cadre.y = (*game->WINDOWHEIGHT) * 12 / 720;
    rect_fond_cadre.w = pos_fond_cadre.w - 2 * rect_fond_cadre.x + 1;
    rect_fond_cadre.h = pos_fond_cadre.h - 2 * rect_fond_cadre.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 240);
    SDL_SetRenderTarget(game->render, fond_cadre);
    SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    /*--- Creation text "texte de confirmation" ----------------------------------------*/
    surf_confirmation = TTF_RenderText_Blended(game->police, "Souhaitez-vous continuer ?", blanc);
    if (surf_confirmation == NULL)
    {
        SDL_ExitWithError("probleme surface texte de confirmation texte confimation");
    }

    SDL_Texture *confirmation = SDL_CreateTextureFromSurface(game->render, surf_confirmation);
    if (confirmation == NULL)
    {
        SDL_ExitWithError("probleme texture texte de confirmation texte confimation");
    }

    SDL_Rect pos_confirmation;
    pos_confirmation.w = (*game->WINDOWWIDTH) * 500 / 1200;
    pos_confirmation.h = (*game->WINDOWHEIGHT) / 13.5;
    pos_confirmation.x = (*game->WINDOWWIDTH) / 2 - pos_confirmation.w/2;
    pos_confirmation.y = (*game->WINDOWHEIGHT) / 1.8;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "oui" ----------------------------------------*/

    surf_choix_oui = TTF_RenderText_Blended(game->police, "Oui", rouge);
    if (surf_choix_oui == NULL)
    {
        SDL_ExitWithError("probleme surface choix oui texte confimation");
    }

    SDL_Texture *choix_oui = SDL_CreateTextureFromSurface(game->render, surf_choix_oui);
    if (choix_oui == NULL)
    {
        SDL_ExitWithError("probleme texture choix oui texte confimation");
    }

    SDL_Rect pos_choix_oui;
    pos_choix_oui.w = (*game->WINDOWWIDTH) * 64 / 1200;
    pos_choix_oui.h = (*game->WINDOWHEIGHT) / 13.5;
    pos_choix_oui.x = (*game->WINDOWWIDTH) / 2 - pos_choix_oui.w/2;
    pos_choix_oui.y = (*game->WINDOWHEIGHT) / 1.58;


    /*----------------------------------------------------------------------------*/

    /*--- Creation text "non" ----------------------------------------*/

    surf_choix_non = TTF_RenderText_Blended(game->police, "Non", blanc);
    if (surf_choix_non == NULL)
    {
        SDL_ExitWithError("probleme surface choix non texte confimation");
    }

    SDL_Texture *choix_non = SDL_CreateTextureFromSurface(game->render, surf_choix_non);
    if (choix_non == NULL)
    {
        SDL_ExitWithError("probleme texture choix non texte confimation");
    }

    SDL_Rect pos_choix_non;
    pos_choix_non.w = (*game->WINDOWWIDTH) * 64 / 1200;
    pos_choix_non.h = (*game->WINDOWHEIGHT) / 13.5;
    pos_choix_non.x = (*game->WINDOWWIDTH) / 2 - pos_choix_non.w/2;
    pos_choix_non.y = (*game->WINDOWHEIGHT) / 1.42;


    /*----------------------------------------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, text_gameOver, NULL, &pos_text_gameOver);
    SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
    SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
    SDL_RenderCopy(game->render, confirmation, NULL, &pos_confirmation);
    SDL_RenderCopy(game->render, choix_oui, NULL, &pos_choix_oui);
    SDL_RenderCopy(game->render, choix_non, NULL, &pos_choix_non);

    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    /*--- Main Loop --------------------------------------------------------------*/

    while (gameover_bool && (*game->program_launch))
    {

        while (SDL_PollEvent(&event))
        {

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
                selection = 1;
            selection %= 2;

            if (selection == 0)
            {
                surf_choix_oui = TTF_RenderText_Blended(game->police, "Oui", rouge);
                surf_choix_non = TTF_RenderText_Blended(game->police, "Non", blanc);
            }

            if (selection == 1)
            {
                surf_choix_oui = TTF_RenderText_Blended(game->police, "Oui", blanc);
                surf_choix_non = TTF_RenderText_Blended(game->police, "Non", rouge);
            }

            choix_oui = SDL_CreateTextureFromSurface(game->render, surf_choix_oui);
            choix_non = SDL_CreateTextureFromSurface(game->render, surf_choix_non);

            SDL_RenderCopy(game->render, choix_oui, NULL, &pos_choix_oui);
            SDL_RenderCopy(game->render, choix_non, NULL, &pos_choix_non);
            SDL_RenderPresent(game->render);


        }
        if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
        {
            SDL_RenderClear(game->render);
            if (selection == 0){
                character = character_create(game->render, character->file_name_save);
                *combat_bool = SDL_FALSE;
                gameover_bool = SDL_FALSE;
            }

            if (selection == 1){
                *floor_bool = SDL_FALSE;
                *combat_bool = SDL_FALSE;
                gameover_bool = SDL_FALSE;
            }

    }


    }

    /*--- End Main Loop ----------------------------------------------------------*/



    /*--- Free Memory ------------------------------------------------------------*/

    /*--- End Free Memory --------------------------------------------------------*/



}
