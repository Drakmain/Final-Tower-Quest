#include <stdio.h>
#include <stdlib.h>

#include "menu_accueil.h"

#include "options.h"
#include "nouvelle_partie.h"
#include "charger_partie.h"


/*!
 *
 * \file menu_accueil.c
 * \brief Menu d'accueil.
 * \author Jeremy BOURGOUIN
 * \date 10/02/21
 *
 */


/*!
 *
 * \fn menu_accueil(SDL_Window * window, SDL_Renderer * render, int *windowwidth, int *windowheight,SDL_bool * program_launch)
 * \brief A FINIR
 *
 * \param render render est un pointeur sur le rendu SDL.s
 * \param *windowwidth A FINIR
 * \param *windowheight A FINIR
 * \param program_launch est un pointeur booléen.
 *
 */

extern
void menu_accueil(SDL_Window * window, SDL_Renderer * render, int *windowwidth, int *windowheight, TTF_Font *police, SDL_bool * program_launch){

    /*--- Initialization variable ------------------------------------------------*/
    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    SDL_Surface *surf_nouvelle_partie = NULL, *surf_charger_partie = NULL, *surf_options = NULL, *surf_quitter = NULL, *surf_logo = NULL, *surf_fond = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool menu_ac = SDL_TRUE;

    SDL_Event event;

    int selection = 0;

    /*--- End Initialization variable --------------------------------------------*/


    /*--- Creation text "nouvelle partie" ----------------------------------------*/
    surf_nouvelle_partie = TTF_RenderText_Blended(police, "Nouvelle partie", rouge);
    if(surf_nouvelle_partie == NULL){
        SDL_ExitWithError("probleme surface nouvelle partie menu d'accueil");
    }

    SDL_Texture* nouvelle_partie = SDL_CreateTextureFromSurface(render, surf_nouvelle_partie);
    if(nouvelle_partie == NULL){
        SDL_ExitWithError("probleme texture nouvelle partie menu d'accueil");
    }

    SDL_Rect pos_nouvelle_partie;
    pos_nouvelle_partie.x = *windowwidth/2 - *windowwidth/6;
    pos_nouvelle_partie.y = *windowheight/2;
    pos_nouvelle_partie.w = *windowwidth/3.74;
    pos_nouvelle_partie.h = *windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation text "charger partie" -----------------------------------------*/

    surf_charger_partie = TTF_RenderText_Blended(police, "Charger partie", blanc);
    if(surf_charger_partie == NULL){
        SDL_ExitWithError("probleme surface charger partie menu d'accueil");
    }
    SDL_Texture* charger_partie = SDL_CreateTextureFromSurface(render, surf_charger_partie);
    if(charger_partie == NULL){
        SDL_ExitWithError("probleme texture charger partie menu d'accueil");
    }

    SDL_Rect pos_charger_partie;
    pos_charger_partie.x = *windowwidth/2 - *windowwidth/6;
    pos_charger_partie.y = *windowheight/2 + *windowheight/9;
    pos_charger_partie.w = *windowwidth/4;
    pos_charger_partie.h = *windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation text "options" ------------------------------------------------*/

    surf_options = TTF_RenderText_Blended(police, "Options", blanc);
    if(surf_options == NULL){
        SDL_ExitWithError("probleme surface options menu d'accueil");
    }

    SDL_Texture* options = SDL_CreateTextureFromSurface(render, surf_options);
    if(options == NULL){
        SDL_ExitWithError("probleme texture options menu d'accueil");
    }

    SDL_Rect pos_options;
    pos_options.x = *windowwidth/2 - *windowwidth/6;
    pos_options.y = *windowheight/2 + *windowheight/4.5;
    pos_options.w = *windowwidth/8;
    pos_options.h = *windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation text "quitter" ------------------------------------------------*/

    surf_quitter = TTF_RenderText_Blended(police, "Quitter le jeu", blanc);
    if(surf_quitter == NULL){
        SDL_ExitWithError("probleme surface quitter menu d'accueil");
    }

    SDL_Texture* quitter = SDL_CreateTextureFromSurface(render, surf_quitter);
    if(quitter == NULL){
        SDL_ExitWithError("probleme texture quitter menu d'accueil");
    }

    SDL_Rect pos_quitter;
    pos_quitter.x = *windowwidth/2 - *windowwidth/6;
    pos_quitter.y = *windowheight/2 + *windowheight/3;
    pos_quitter.w = *windowwidth/4;
    pos_quitter.h = *windowheight/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture logo --------------------------------------------------*/

    surf_logo = SDL_LoadBMP("src\\image\\Final-Tower-Quest.bmp");
    if(surf_logo == NULL){
        SDL_ExitWithError("probleme chargement image logo menu d'accueil");
    }

    SDL_Texture* logo = SDL_CreateTextureFromSurface(render, surf_logo);
    if(logo == NULL){
        SDL_ExitWithError("probleme texture image logo menu d'accueil");
    }

    SDL_Rect pos_logo;
    pos_logo.x = *windowwidth/2 - 275;
    pos_logo.y = *windowheight/2 - 250;
    pos_logo.w = 552.5;
    pos_logo.h = 145;

    /*----------------------------------------------------------------------------*/


   /*--- Creation texture background ---------------------------------------------*/

    surf_fond = SDL_LoadBMP("src\\image\\fond_menu_accueil.bmp");
    if(surf_fond == NULL){
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture* fond = SDL_CreateTextureFromSurface(render, surf_fond);
    if(fond == NULL){
        SDL_ExitWithError("probleme texture fond menu d'accueil");
    }

    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;
    pos_fond.w = *windowwidth;
    pos_fond.h = *windowheight;

    /*----------------------------------------------------------------------------*/


    SDL_RenderClear(render);

    SDL_RenderCopy(render, fond, NULL, &pos_fond);
    SDL_RenderCopy(render, nouvelle_partie, NULL, &pos_nouvelle_partie);
    SDL_RenderCopy(render, charger_partie, NULL, &pos_charger_partie);
    SDL_RenderCopy(render, options, NULL, &pos_options);
    SDL_RenderCopy(render, quitter, NULL, &pos_quitter);
    SDL_RenderCopy(render, logo, NULL, &pos_logo);

    SDL_RenderPresent(render);


    /*--- Main Loop --------------------------------------------------------------*/

    while (menu_ac && *program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                menu_ac = SDL_FALSE;
                *program_launch = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                menu_ac = SDL_FALSE;
                *program_launch = SDL_FALSE;
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


            if(selection < 0)selection = 3;
            selection %=4;

            if(selection == 0)
            {
                surf_nouvelle_partie = TTF_RenderText_Blended(police, "Nouvelle partie", rouge);
                surf_charger_partie = TTF_RenderText_Blended(police, "Charger partie", blanc);
                surf_options = TTF_RenderText_Blended(police, "Options", blanc);
                surf_quitter = TTF_RenderText_Blended(police, "Quitter le jeu", blanc);
            }
            if(selection == 1)
            {
                surf_nouvelle_partie = TTF_RenderText_Blended(police, "Nouvelle partie", blanc);
                surf_charger_partie = TTF_RenderText_Blended(police, "Charger partie", rouge);
                surf_options = TTF_RenderText_Blended(police, "Options", blanc);
                surf_quitter = TTF_RenderText_Blended(police, "Quitter le jeu", blanc);
            }
            if(selection == 2)
            {
                surf_nouvelle_partie = TTF_RenderText_Blended(police, "Nouvelle partie", blanc);
                surf_charger_partie = TTF_RenderText_Blended(police, "Charger partie", blanc);
                surf_options = TTF_RenderText_Blended(police, "Options", rouge);
                surf_quitter = TTF_RenderText_Blended(police, "Quitter le jeu", blanc);
            }
            if(selection == 3)
            {
                surf_nouvelle_partie = TTF_RenderText_Blended(police, "Nouvelle partie", blanc);
                surf_charger_partie = TTF_RenderText_Blended(police, "Charger partie", blanc);
                surf_options = TTF_RenderText_Blended(police, "Options", blanc);
                surf_quitter = TTF_RenderText_Blended(police, "Quitter le jeu", rouge);
            }

            nouvelle_partie = SDL_CreateTextureFromSurface(render, surf_nouvelle_partie);
            charger_partie = SDL_CreateTextureFromSurface(render, surf_charger_partie);
            options = SDL_CreateTextureFromSurface(render, surf_options);
            quitter = SDL_CreateTextureFromSurface(render, surf_quitter);

            SDL_RenderClear(render);
            SDL_RenderCopy(render, fond, NULL, &pos_fond);
            SDL_RenderCopy(render, nouvelle_partie, NULL, &pos_nouvelle_partie);
            SDL_RenderCopy(render, charger_partie, NULL, &pos_charger_partie);
            SDL_RenderCopy(render, options, NULL, &pos_options);
            SDL_RenderCopy(render, quitter, NULL, &pos_quitter);
            SDL_RenderCopy(render, logo, NULL, &pos_logo);
            SDL_RenderPresent(render);





            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {

                if(selection == 0)
                {
                    nouvelle_partie_f(render, windowwidth, windowheight, police, program_launch);
                }
                if(selection == 1)
                {
                    charger_partie_f(render, windowwidth, windowheight, police, program_launch);
                }
                if(selection == 2)
                {
                    options_f(window, render, windowwidth, windowheight, police, program_launch);
                }
                if(selection == 3)
                {
                    menu_ac = SDL_FALSE;
                    *program_launch = SDL_FALSE;
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
