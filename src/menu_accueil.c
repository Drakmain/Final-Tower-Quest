#include <stdio.h>
#include <stdlib.h>

#include "..\lib\menu_accueil.h"

#include "..\lib\options.h"
#include "..\lib\nouvelle_partie.h"
#include "..\lib\charger_partie.h"

/*!
 *
 * \file menu_accueil.c
 * \brief Gestion du menu d'accueil du jeu.
 * \author Jeremy BOURGOUIN
 *
 */

/*!
 *
 * \fn menu_accueil(game_t *game, char *actual_save)
 * \brief Fonction de gestion du menu d'accueil du jeu.
 *
 * \param game A FINIR.
 * \param actual_save A FINIR.
 *
 */

extern void menu_accueil(game_t *game, char *actual_save)
{
    /*--- Initialization variable ------------------------------------------------*/

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};

    SDL_Surface *surf_nouvelle_partie = NULL, *surf_charger_partie = NULL, *surf_options = NULL, *surf_quitter = NULL, *surf_logo = NULL, *surf_fond = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool menu_ac_bool = SDL_TRUE;

    SDL_Event event;

    int selection = 0;

    /*--- End Initialization variable --------------------------------------------*/

    /*--- Creation text "nouvelle partie" ----------------------------------------*/

    surf_nouvelle_partie = TTF_RenderText_Blended(game->police, "Nouvelle partie", rouge);
    if (surf_nouvelle_partie == NULL)
    {
        SDL_ExitWithError("probleme surface nouvelle partie menu d'accueil");
    }

    SDL_Texture *nouvelle_partie = SDL_CreateTextureFromSurface(game->render, surf_nouvelle_partie);
    if (nouvelle_partie == NULL)
    {
        SDL_ExitWithError("probleme texture nouvelle partie menu d'accueil");
    }

    SDL_Rect pos_nouvelle_partie;
    pos_nouvelle_partie.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6;
    pos_nouvelle_partie.y = (*game->WINDOWHEIGHT) / 2;
    pos_nouvelle_partie.w = (*game->WINDOWWIDTH) / 3.74;
    pos_nouvelle_partie.h = (*game->WINDOWHEIGHT) / 13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "charger partie" -----------------------------------------*/

    surf_charger_partie = TTF_RenderText_Blended(game->police, "Charger partie", blanc);
    if (surf_charger_partie == NULL)
    {
        SDL_ExitWithError("probleme surface charger partie menu d'accueil");
    }

    SDL_Texture *charger_partie = SDL_CreateTextureFromSurface(game->render, surf_charger_partie);
    if (charger_partie == NULL)
    {
        SDL_ExitWithError("probleme texture charger partie menu d'accueil");
    }

    SDL_Rect pos_charger_partie;
    pos_charger_partie.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6;
    pos_charger_partie.y = (*game->WINDOWHEIGHT) / 2 + (*game->WINDOWHEIGHT) / 9;
    pos_charger_partie.w = (*game->WINDOWWIDTH) / 4;
    pos_charger_partie.h = (*game->WINDOWHEIGHT) / 13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "options" ------------------------------------------------*/

    surf_options = TTF_RenderText_Blended(game->police, "Options", blanc);
    if (surf_options == NULL)
    {
        SDL_ExitWithError("probleme surface options menu d'accueil");
    }

    SDL_Texture *options = SDL_CreateTextureFromSurface(game->render, surf_options);
    if (options == NULL)
    {
        SDL_ExitWithError("probleme texture options menu d'accueil");
    }

    SDL_Rect pos_options;
    pos_options.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6;
    pos_options.y = (*game->WINDOWHEIGHT) / 2 + (*game->WINDOWHEIGHT) / 4.5;
    pos_options.w = (*game->WINDOWWIDTH) / 8;
    pos_options.h = (*game->WINDOWHEIGHT) / 13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "quitter" ------------------------------------------------*/

    surf_quitter = TTF_RenderText_Blended(game->police, "Quitter le jeu", blanc);
    if (surf_quitter == NULL)
    {
        SDL_ExitWithError("probleme surface quitter menu d'accueil");
    }

    SDL_Texture *quitter = SDL_CreateTextureFromSurface(game->render, surf_quitter);
    if (quitter == NULL)
    {
        SDL_ExitWithError("probleme texture quitter menu d'accueil");
    }

    SDL_Rect pos_quitter;
    pos_quitter.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6;
    pos_quitter.y = (*game->WINDOWHEIGHT) / 2 + (*game->WINDOWHEIGHT) / 3;
    pos_quitter.w = (*game->WINDOWWIDTH) / 4;
    pos_quitter.h = (*game->WINDOWHEIGHT) / 13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Creation texture logo --------------------------------------------------*/

    surf_logo = SDL_LoadBMP("src\\image\\Final-Tower-Quest.bmp");
    if (surf_logo == NULL)
    {
        SDL_ExitWithError("probleme chargement image logo menu d'accueil");
    }

    SDL_Texture *logo = SDL_CreateTextureFromSurface(game->render, surf_logo);
    if (logo == NULL)
    {
        SDL_ExitWithError("probleme texture image logo menu d'accueil");
    }

    SDL_Rect pos_logo;
    pos_logo.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) * 275 / 1280;
    pos_logo.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWHEIGHT) * 300 / 720;
    pos_logo.w = (*game->WINDOWWIDTH) * 552 / 1280;
    pos_logo.h = (*game->WINDOWHEIGHT) * 145 / 720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation texture background ---------------------------------------------*/

    surf_fond = SDL_LoadBMP("src\\image\\fond_menu_accueil.bmp");
    if (surf_fond == NULL)
    {
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture *fond = SDL_CreateTextureFromSurface(game->render, surf_fond);
    if (fond == NULL)
    {
        SDL_ExitWithError("probleme texture fond menu d'accueil");
    }

    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;
    pos_fond.w = (*game->WINDOWWIDTH);
    pos_fond.h = (*game->WINDOWHEIGHT);

    /*----------------------------------------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
    SDL_RenderCopy(game->render, nouvelle_partie, NULL, &pos_nouvelle_partie);
    SDL_RenderCopy(game->render, charger_partie, NULL, &pos_charger_partie);
    SDL_RenderCopy(game->render, options, NULL, &pos_options);
    SDL_RenderCopy(game->render, quitter, NULL, &pos_quitter);
    SDL_RenderCopy(game->render, logo, NULL, &pos_logo);

    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    while (menu_ac_bool == SDL_TRUE && (*game->program_launch))
    {
        while (SDL_PollEvent(&event))
        {
            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                menu_ac_bool = SDL_FALSE;
                (*game->program_launch) = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                menu_ac_bool = SDL_FALSE;
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
                selection = 3;
            selection %= 4;

            if (selection == 0)
            {
                surf_nouvelle_partie = TTF_RenderText_Blended(game->police, "Nouvelle partie", rouge);
                surf_charger_partie = TTF_RenderText_Blended(game->police, "Charger partie", blanc);
                surf_options = TTF_RenderText_Blended(game->police, "Options", blanc);
                surf_quitter = TTF_RenderText_Blended(game->police, "Quitter le jeu", blanc);
            }

            if (selection == 1)
            {
                surf_nouvelle_partie = TTF_RenderText_Blended(game->police, "Nouvelle partie", blanc);
                surf_charger_partie = TTF_RenderText_Blended(game->police, "Charger partie", rouge);
                surf_options = TTF_RenderText_Blended(game->police, "Options", blanc);
                surf_quitter = TTF_RenderText_Blended(game->police, "Quitter le jeu", blanc);
            }

            if (selection == 2)
            {
                surf_nouvelle_partie = TTF_RenderText_Blended(game->police, "Nouvelle partie", blanc);
                surf_charger_partie = TTF_RenderText_Blended(game->police, "Charger partie", blanc);
                surf_options = TTF_RenderText_Blended(game->police, "Options", rouge);
                surf_quitter = TTF_RenderText_Blended(game->police, "Quitter le jeu", blanc);
            }

            if (selection == 3)
            {
                surf_nouvelle_partie = TTF_RenderText_Blended(game->police, "Nouvelle partie", blanc);
                surf_charger_partie = TTF_RenderText_Blended(game->police, "Charger partie", blanc);
                surf_options = TTF_RenderText_Blended(game->police, "Options", blanc);
                surf_quitter = TTF_RenderText_Blended(game->police, "Quitter le jeu", rouge);
            }

            nouvelle_partie = SDL_CreateTextureFromSurface(game->render, surf_nouvelle_partie);
            charger_partie = SDL_CreateTextureFromSurface(game->render, surf_charger_partie);
            options = SDL_CreateTextureFromSurface(game->render, surf_options);
            quitter = SDL_CreateTextureFromSurface(game->render, surf_quitter);

            pos_nouvelle_partie.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6;
            pos_nouvelle_partie.y = (*game->WINDOWHEIGHT) / 2;
            pos_nouvelle_partie.w = (*game->WINDOWWIDTH) / 3.74;
            pos_nouvelle_partie.h = (*game->WINDOWHEIGHT) / 13.5;

            pos_charger_partie.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6;
            pos_charger_partie.y = (*game->WINDOWHEIGHT) / 2 + (*game->WINDOWHEIGHT) / 9;
            pos_charger_partie.w = (*game->WINDOWWIDTH) / 4;
            pos_charger_partie.h = (*game->WINDOWHEIGHT) / 13.5;

            pos_options.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6;
            pos_options.y = (*game->WINDOWHEIGHT) / 2 + (*game->WINDOWHEIGHT) / 4.5;
            pos_options.w = (*game->WINDOWWIDTH) / 8;
            pos_options.h = (*game->WINDOWHEIGHT) / 13.5;

            pos_quitter.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 6;
            pos_quitter.y = (*game->WINDOWHEIGHT) / 2 + (*game->WINDOWHEIGHT) / 3;
            pos_quitter.w = (*game->WINDOWWIDTH) / 4;
            pos_quitter.h = (*game->WINDOWHEIGHT) / 13.5;

            pos_logo.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) * 275 / 1280;
            pos_logo.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWHEIGHT) * 300 / 720;
            pos_logo.w = (*game->WINDOWWIDTH) * 552 / 1280;
            pos_logo.h = (*game->WINDOWHEIGHT) * 145 / 720;

            pos_fond.x = 0;
            pos_fond.y = 0;
            pos_fond.w = (*game->WINDOWWIDTH);
            pos_fond.h = (*game->WINDOWHEIGHT);

            SDL_RenderClear(game->render);

            SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
            SDL_RenderCopy(game->render, nouvelle_partie, NULL, &pos_nouvelle_partie);
            SDL_RenderCopy(game->render, charger_partie, NULL, &pos_charger_partie);
            SDL_RenderCopy(game->render, options, NULL, &pos_options);
            SDL_RenderCopy(game->render, quitter, NULL, &pos_quitter);
            SDL_RenderCopy(game->render, logo, NULL, &pos_logo);

            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {

                if (selection == 0)
                {
                    nouvelle_partie_f(game, actual_save);
                    if (strcmp(actual_save, "\0"))
                    {
                        menu_ac_bool = SDL_FALSE;
                    }
                }

                if (selection == 1)
                {
                    charger_partie_f(game, actual_save);
                    if (strcmp(actual_save, "\0"))
                    {
                        menu_ac_bool = SDL_FALSE;
                    }
                }

                if (selection == 2)
                {
                    options_f(game);
                }

                if (selection == 3)
                {
                    menu_ac_bool = SDL_FALSE;
                    (*game->program_launch) = SDL_FALSE;
                }
            }
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_nouvelle_partie);
    SDL_FreeSurface(surf_charger_partie);
    SDL_FreeSurface(surf_options);
    SDL_FreeSurface(surf_quitter);
    SDL_FreeSurface(surf_logo);
    SDL_FreeSurface(surf_fond);

    SDL_DestroyTexture(nouvelle_partie);
    SDL_DestroyTexture(charger_partie);
    SDL_DestroyTexture(options);
    SDL_DestroyTexture(quitter);
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(fond);

    /*--- End Free Memory --------------------------------------------------------*/
}