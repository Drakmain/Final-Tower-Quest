#include <stdio.h>
#include <stdlib.h>

#include "options.h"

/*!
 *
 * \file options.c
 * \brief Affichage et gestion des options.
 * \author Jeremy BOURGOUIN
 * \date 12/03/21
 *
 */


/*!
 *
 * \fn options_f(SDL_Window * window, SDL_Renderer *render, int * windowwidth, int * windowheight, TTF_Font * police, SDL_bool * etat_fullscreen, SDL_bool * program_launch)
 * \brief A FINIR.
 *
 * \param render est un pointeur sur le rendu SDL.
 * \param window A FINIR.
 * \param windowwidth est la largeur de la fenetre.
 * \param windowheight est la hauteur de la fenetre.
 * \param police A FINIR.
 * \param etat_fullscreen A FINIR.
 * \param program_launch est un pointeur sur un booléen.
 *
 */

extern
void options_f(SDL_Window *window, SDL_Renderer *render, int *windowwidth, int *windowheight, TTF_Font *police, SDL_bool * etat_fullscreen, SDL_bool* program_launch){

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    SDL_Surface* surf_options = NULL, *surf_retour = NULL, *surf_fond = NULL, *surf_cadre = NULL, *surf_opt_resolution = NULL, *surf_choix_resolution = NULL, *surf_opt_fullscreen = NULL, *surf_choix_fullscreen = NULL, *surf_fleche = NULL;

    /*---texture "options"--------------------------------------------------------*/
    surf_options = TTF_RenderText_Blended(police, "OPTIONS", blanc);
    if(surf_options == NULL){
        SDL_ExitWithError("probleme surface options");
    }
    SDL_Texture* options = SDL_CreateTextureFromSurface(render, surf_options);
    if(options == NULL){
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_options;
    /*------------------------------------------------------------------------------------*/

    /*---texture "resolution"--------------------------------------------------------*/
    surf_opt_resolution = TTF_RenderText_Blended(police, "Resolution", rouge);
    if(surf_opt_resolution == NULL){
        SDL_ExitWithError("probleme surface opt_resolution");
    }
    SDL_Texture* opt_resolution = SDL_CreateTextureFromSurface(render, surf_opt_resolution);
    if(opt_resolution == NULL){
        SDL_ExitWithError("probleme texture opt_resolution");
    }

    SDL_Rect pos_opt_resolution;
    /*------------------------------------------------------------------------------------*/

    /*---texture "choix resolution"--------------------------------------------------------*/
    int resolution;
    if(*windowwidth == 1280 && *windowheight == 720)resolution=0;
    if(*windowwidth == 1600 && *windowheight == 900)resolution=1;
    if(*windowwidth == 1920 && *windowheight == 1080)resolution=2;
    if(*windowwidth == 2560 && *windowheight == 1440)resolution=3;
    SDL_Texture* choix_resolution;

    SDL_Rect pos_choix_resolution;
    pos_choix_resolution.x = *windowwidth/6 + *windowwidth*500/1200;
    pos_choix_resolution.y = *windowheight/6.75 + *windowheight*30/675;
    pos_choix_resolution.w = *windowwidth*173/1200;
    pos_choix_resolution.h = *windowheight/13.5;
    /*------------------------------------------------------------------------------------*/

    /*---texture "option fullscreen"--------------------------------------------------------*/
    surf_opt_fullscreen = TTF_RenderText_Blended(police, "Plein ecran", blanc);
    if(surf_opt_fullscreen == NULL){
        SDL_ExitWithError("probleme surface opt_fullscreen");
    }
    SDL_Texture* opt_fullscreen = SDL_CreateTextureFromSurface(render, surf_opt_fullscreen);
    if(opt_fullscreen == NULL){
        SDL_ExitWithError("probleme texture opt_fullscreen");
    }

    SDL_Rect pos_opt_fullscreen;
    /*------------------------------------------------------------------------------------*/

    /*---texture "fullscreen"--------------------------------------------------------*/


    if(*etat_fullscreen == SDL_FALSE){
        surf_choix_fullscreen = TTF_RenderText_Blended(police, "non", blanc);
        if(surf_choix_fullscreen == NULL){
            SDL_ExitWithError("probleme surface choix_fullscreen");
        }
    }

    if(*etat_fullscreen == SDL_TRUE){
        surf_choix_fullscreen = TTF_RenderText_Blended(police, "oui", blanc);
        if(surf_choix_fullscreen == NULL){
            SDL_ExitWithError("probleme surface choix_fullscreen");
        }
    }

    SDL_Texture* choix_fullscreen = SDL_CreateTextureFromSurface(render, surf_choix_fullscreen);
    if(choix_fullscreen == NULL){
        SDL_ExitWithError("probleme texture choix_fullscreen");
    }

    SDL_Rect pos_choix_fullscreen;
    pos_choix_fullscreen.x = *windowwidth/6 + *windowwidth*500/1200;
    pos_choix_fullscreen.y = *windowheight/6.75 + *windowheight*100/675;
    pos_choix_fullscreen.w = *windowwidth*64/1200;
    pos_choix_fullscreen.h = *windowheight/13.5;
    /*------------------------------------------------------------------------------------*/

    /*---texture "retour"--------------------------------------------------------*/
    surf_retour = TTF_RenderText_Blended(police, "Retour", blanc);
    if(surf_retour == NULL){
        SDL_ExitWithError("probleme surface options");
    }
    SDL_Texture* retour = SDL_CreateTextureFromSurface(render, surf_retour);
    if(retour == NULL){
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_retour;
    /*------------------------------------------------------------------------------------*/

    /*---texture fond--------------------------------------------------------*/

    surf_fond = SDL_LoadBMP("src\\image\\fond_menu_accueil.bmp");
    if(surf_fond == NULL){
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture* fond = SDL_CreateTextureFromSurface(render, surf_fond);
    if(fond == NULL){
        SDL_ExitWithError("probleme texture fond menu d'accueil");
    }

    SDL_Rect pos_fond;
    /*------------------------------------------------------------------------------------*/

    /*---texture "cadre"--------------------------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_options.bmp");
    if(surf_cadre == NULL){
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture* cadre = SDL_CreateTextureFromSurface(render, surf_cadre);
    if(cadre == NULL){
        SDL_ExitWithError("probleme texture nouvelle partie menu d'accueil");
    }

    SDL_Rect pos_cadre;
    /*------------------------------------------------------------------------------------*/

    /*---texture "fond cadre"--------------------------------------------------------*/
    SDL_Texture* fond_cadre = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, *windowwidth*820/1200, *windowheight*460/675);
    if(fond_cadre == NULL){
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_fond_cadre;

    SDL_Rect rect_fond_cadre;

    SDL_SetRenderDrawColor(render,0,0,0, 200);
    SDL_SetRenderTarget(render,fond_cadre);
    SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(render, &rect_fond_cadre);
    SDL_SetRenderTarget(render,NULL);

    /*------------------------------------------------------------------------------------*/
    /*---texture fleche--------------------------------------------------------*/

    surf_fleche = SDL_LoadBMP("src\\image\\fleche.bmp");
    if(surf_fleche == NULL){
        SDL_ExitWithError("probleme chargement image fleche gauche et droite");
    }

    SDL_Rect rect_fleche_gauche;
    rect_fleche_gauche.x = 39;
    rect_fleche_gauche.y = 0;
    rect_fleche_gauche.w = 38;
    rect_fleche_gauche.h = 28;

    SDL_Texture* fleche_gauche = SDL_CreateTextureFromSurface(render, surf_fleche);
    if(fleche_gauche == NULL){
        SDL_ExitWithError("probleme texture fleche gauche");
    }

    SDL_Rect pos_fleche_gauche;

    SDL_Texture* fleche_droite = SDL_CreateTextureFromSurface(render, surf_fleche);
    if(fleche_droite == NULL){
        SDL_ExitWithError("probleme texture fleche droite");
    }
    SDL_Rect rect_fleche_droite;
    rect_fleche_droite.x = 0;
    rect_fleche_droite.y = 0;
    rect_fleche_droite.w = 38;
    rect_fleche_droite.h = 28;

    SDL_Rect pos_fleche_droite;
    /*------------------------------------------------------------------------------------*/

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool continu = SDL_TRUE;
    SDL_Event event;

    int selection = 0;
    SDL_bool changement = SDL_FALSE;

    while (continu && *program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT){
                *program_launch = SDL_FALSE;
                continu = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
                continu = SDL_FALSE;
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


            if(selection < 0)selection = 2;
            selection %= 3;

            if(selection == 0){
                surf_opt_resolution = TTF_RenderText_Blended(police, "Resolution", rouge);
                surf_opt_fullscreen = TTF_RenderText_Blended(police, "Plein ecran", blanc);
                surf_retour = TTF_RenderText_Blended(police, "Retour", blanc);

                pos_fleche_gauche.x = pos_choix_resolution.x - *windowheight*40/1280 * 38 / 28 - *windowwidth*20/1280;
                pos_fleche_gauche.y = pos_choix_resolution.y + *windowwidth*19/1280;
                pos_fleche_gauche.w = *windowheight*40/1280 * 38 / 28;
                pos_fleche_gauche.h = *windowheight*40/1280;

                pos_fleche_droite.x = pos_choix_resolution.x + pos_choix_resolution.w + *windowwidth*20/1280;
                pos_fleche_droite.y = pos_choix_resolution.y + *windowwidth*19/1280;
                pos_fleche_droite.w = *windowheight*40/1280 * 38 / 28;
                pos_fleche_droite.h = *windowheight*40/1280;
                /*--- Event pour choix resolution ------------------------------------------*/
                if (keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN)
                {
                    if(resolution < 3)resolution++;
                    changement = SDL_TRUE;
                }

                if (keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN)
                {
                    if(resolution > 0)resolution--;
                    changement = SDL_TRUE;
                }
                switch (resolution) {
                    case 0: *windowwidth = 1280;
                            *windowheight = 720;
                            surf_choix_resolution = TTF_RenderText_Blended(police, "1280x720", blanc);
                            choix_resolution = SDL_CreateTextureFromSurface(render, surf_choix_resolution);
                            fleche_gauche = NULL;
                            fleche_droite = SDL_CreateTextureFromSurface(render, surf_fleche);
                            break;
                    case 1: *windowwidth = 1600;
                            *windowheight = 900;
                            surf_choix_resolution = TTF_RenderText_Blended(police, "1600x900", blanc);
                            choix_resolution = SDL_CreateTextureFromSurface(render, surf_choix_resolution);
                            fleche_gauche = SDL_CreateTextureFromSurface(render, surf_fleche);
                            fleche_droite = SDL_CreateTextureFromSurface(render, surf_fleche);
                            break;
                    case 2: *windowwidth = 1920;
                            *windowheight = 1080;
                            surf_choix_resolution = TTF_RenderText_Blended(police, "1920x1080", blanc);
                            choix_resolution = SDL_CreateTextureFromSurface(render, surf_choix_resolution);
                            fleche_droite = SDL_CreateTextureFromSurface(render, surf_fleche);
                            fleche_gauche = SDL_CreateTextureFromSurface(render, surf_fleche);
                            break;
                    case 3: *windowwidth = 2560;
                            *windowheight = 1440;
                            surf_choix_resolution = TTF_RenderText_Blended(police, "2560x1440", blanc);
                            choix_resolution = SDL_CreateTextureFromSurface(render, surf_choix_resolution);
                            fleche_droite = NULL;
                            fleche_gauche = SDL_CreateTextureFromSurface(render, surf_fleche);
                            break;
                }
                if(changement)SDL_SetWindowSize(window, *windowwidth, *windowheight);
                changement = SDL_FALSE;
                /*--- End Event pour choix resolution --------------------------------------*/
            }

            if(selection == 1){
                surf_opt_resolution = TTF_RenderText_Blended(police, "Resolution", blanc);
                surf_opt_fullscreen = TTF_RenderText_Blended(police, "Plein ecran", rouge);
                surf_retour = TTF_RenderText_Blended(police, "Retour", blanc);

                pos_fleche_gauche.x = pos_choix_fullscreen.x - *windowheight*40/1280 * 38 / 28 - *windowwidth*20/1280;
                pos_fleche_gauche.y = pos_choix_fullscreen.y + *windowwidth*23/1280;
                pos_fleche_gauche.w = *windowheight*40/1280 * 38 / 28;
                pos_fleche_gauche.h = *windowheight*40/1280;

                pos_fleche_droite.x = pos_choix_fullscreen.x + pos_choix_fullscreen.w + *windowwidth*20/1280;
                pos_fleche_droite.y = pos_choix_fullscreen.y + *windowwidth*23/1280;
                pos_fleche_droite.w = *windowheight*40/1280 * 38 / 28;
                pos_fleche_droite.h = *windowheight*40/1280;

                /*--- Event pour choix plein ecran ------------------------------------------*/
                if (keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN)
                {
                    if(*etat_fullscreen == SDL_FALSE)*etat_fullscreen = SDL_TRUE;
                }

                if (keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN)
                {
                    if(*etat_fullscreen == SDL_TRUE)*etat_fullscreen = SDL_FALSE;
                }

                switch (*etat_fullscreen) {
                    case 0: SDL_SetWindowFullscreen(window, 0);
                            surf_choix_fullscreen = TTF_RenderText_Blended(police, "non", blanc);
                            choix_fullscreen = SDL_CreateTextureFromSurface(render, surf_choix_fullscreen);
                            fleche_gauche = NULL;
                            fleche_droite = SDL_CreateTextureFromSurface(render, surf_fleche);
                            break;
                    case 1: SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                            surf_choix_fullscreen = TTF_RenderText_Blended(police, "oui", blanc);
                            choix_fullscreen = SDL_CreateTextureFromSurface(render, surf_choix_fullscreen);
                            fleche_droite = NULL;
                            fleche_gauche = SDL_CreateTextureFromSurface(render, surf_fleche);
                            break;
                }
                /*--- End Event pour choix resolution --------------------------------------*/

            }
            if(selection == 2){
                surf_opt_resolution = TTF_RenderText_Blended(police, "Resolution", blanc);
                surf_opt_fullscreen = TTF_RenderText_Blended(police, "Plein ecran", blanc);
                surf_retour = TTF_RenderText_Blended(police, "Retour", rouge);
            }

            opt_resolution = SDL_CreateTextureFromSurface(render, surf_opt_resolution);
            opt_fullscreen = SDL_CreateTextureFromSurface(render, surf_opt_fullscreen);
            retour = SDL_CreateTextureFromSurface(render, surf_retour);

            pos_options.x = *windowwidth/2 - *windowwidth*107/1200;
            pos_options.y = *windowheight/30;
            pos_options.w = *windowwidth*214/1200;
            pos_options.h = *windowheight/13.5;

            pos_opt_resolution.x = *windowwidth/6 + *windowwidth*50/1200;
            pos_opt_resolution.y = *windowheight/6.75 + *windowwidth*30/1200;
            pos_opt_resolution.w = *windowwidth*215/1200;
            pos_opt_resolution.h = *windowheight/13.5;

            pos_choix_resolution.x = *windowwidth/6 + *windowwidth*500/1200;
            pos_choix_resolution.y = *windowheight/6.75 + *windowheight*30/675;
            pos_choix_resolution.w = *windowwidth*173/1200;
            pos_choix_resolution.h = *windowheight/13.5;

            pos_opt_fullscreen.x = *windowwidth/6 + *windowwidth*50/1200;
            pos_opt_fullscreen.y = *windowheight/6.75 + *windowheight*100/675;
            pos_opt_fullscreen.w = *windowwidth*236/1200;
            pos_opt_fullscreen.h = *windowheight/13.5;

            pos_choix_fullscreen.x = *windowwidth/6 + *windowwidth*500/1200;
            pos_choix_fullscreen.y = *windowheight/6.75 + *windowheight*100/675;
            pos_choix_fullscreen.w = *windowwidth*64/1200;
            pos_choix_fullscreen.h = *windowheight/13.5;

            pos_retour.x = *windowwidth/20;
            pos_retour.y = *windowheight - *windowheight/8;
            pos_retour.w = *windowwidth/(1200/129);
            pos_retour.h = *windowheight/13.5;

            pos_fond.x = 0;
            pos_fond.y = 0;
            pos_fond.w = *windowwidth;
            pos_fond.h = *windowheight;

            pos_cadre.x = *windowwidth/6;
            pos_cadre.y = *windowheight/6.75;
            pos_cadre.w = *windowwidth*820/1200;
            pos_cadre.h = *windowheight*460/675;

            pos_fond_cadre.x = pos_cadre.x;
            pos_fond_cadre.y = pos_cadre.y;
            pos_fond_cadre.w = pos_cadre.w;
            pos_fond_cadre.h = pos_cadre.h;

            rect_fond_cadre.x = *windowwidth*12/1200;
            rect_fond_cadre.y = *windowheight*12/675;
            rect_fond_cadre.w = pos_fond_cadre.w - 2*rect_fond_cadre.x;
            rect_fond_cadre.h = pos_fond_cadre.h - 2*rect_fond_cadre.y;

            rect_fleche_droite.x = 0;
            rect_fleche_droite.y = 0;
            rect_fleche_droite.w = 38;
            rect_fleche_droite.h = 28;

            rect_fleche_gauche.x = 39;
            rect_fleche_gauche.y = 0;
            rect_fleche_gauche.w = 38;
            rect_fleche_gauche.h = 28;

            SDL_SetRenderDrawColor(render,0,0,0, 200);
            SDL_SetRenderTarget(render,fond_cadre);
            SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
            SDL_RenderFillRect(render, &rect_fond_cadre);
            SDL_SetRenderTarget(render,NULL);

            SDL_RenderClear(render);
            SDL_RenderCopy(render, fond, NULL, &pos_fond);
            SDL_RenderCopy(render, options, NULL, &pos_options);
            SDL_RenderCopy(render, retour, NULL, &pos_retour);
            SDL_RenderCopy(render, fond_cadre, NULL, &pos_fond_cadre);
            SDL_RenderCopy(render, cadre, NULL, &pos_cadre);
            SDL_RenderCopy(render, opt_resolution, NULL, &pos_opt_resolution);
            SDL_RenderCopy(render, choix_resolution, NULL, &pos_choix_resolution);
            SDL_RenderCopy(render, opt_fullscreen, NULL, &pos_opt_fullscreen);
            SDL_RenderCopy(render, choix_fullscreen, NULL, &pos_choix_fullscreen);
            SDL_RenderCopy(render, fleche_gauche, &rect_fleche_gauche, &pos_fleche_gauche);
            SDL_RenderCopy(render, fleche_droite, &rect_fleche_droite, &pos_fleche_droite);
            SDL_RenderPresent(render);



            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN){
                if(selection == 2){
                    continu = SDL_FALSE;
                }
            }
        }
    }




    SDL_FreeSurface(surf_options);
    SDL_FreeSurface(surf_retour);
    SDL_FreeSurface(surf_fond);
    SDL_FreeSurface(surf_opt_resolution);

    SDL_DestroyTexture(options);
    SDL_DestroyTexture(retour);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(cadre);
    SDL_DestroyTexture(opt_resolution);

}