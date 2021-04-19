#include <stdio.h>
#include <stdlib.h>

#include "..\lib\options.h"
#include "..\lib\commandes.h"
/*!
 *
 * \file options.c
 * \brief Affichage et gestion des options.
 * \author Jeremy BOURGOUIN
 *
 */

/*!
 *
 * \fn options_f(game_t * game)
 * \brief Fonction pour afficher et gérer les options.
 *
 * \param game est un pointeur sur l'objet game_t du jeu.
 *
 */

extern void options_f(game_t *game)
{
    /*--- Initialization variable ------------------------------------------------*/

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};

    SDL_Surface *surf_options = NULL, *surf_retour = NULL, *surf_fond = NULL, *surf_cadre = NULL, *surf_opt_resolution = NULL, *surf_choix_resolution = NULL, *surf_opt_fullscreen = NULL, *surf_choix_fullscreen = NULL, *surf_fleche = NULL, *surf_commandes;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool options_bool = SDL_TRUE;

    SDL_Event event;

    int selection = 0;

    SDL_bool changement = SDL_FALSE;

    SDL_bool *echap_relache = malloc(sizeof(SDL_bool));
    *echap_relache = SDL_FALSE;

    SDL_Texture *texture_render_options;

    /*--- End Initialization variable --------------------------------------------*/

    /*--- Initialization text "options" ------------------------------------------*/

    surf_options = TTF_RenderText_Blended(game->police, "OPTIONS", blanc);
    if (surf_options == NULL)
    {
        SDL_ExitWithError("probleme surface options");
    }

    SDL_Texture *options = SDL_CreateTextureFromSurface(game->render, surf_options);
    if (options == NULL)
    {
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_options;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "resolution" ------------------------------------*/

    surf_opt_resolution = TTF_RenderText_Blended(game->police, "Resolution", rouge);
    if (surf_opt_resolution == NULL)
    {
        SDL_ExitWithError("probleme surface opt_resolution");
    }

    SDL_Texture *opt_resolution = SDL_CreateTextureFromSurface(game->render, surf_opt_resolution);
    if (opt_resolution == NULL)
    {
        SDL_ExitWithError("probleme texture opt_resolution");
    }

    SDL_Rect pos_opt_resolution;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization texture "choix resolution" ----------------------------*/

    resolution_e resolution;
    if ((*game->WINDOWWIDTH) == 1280 && (*game->WINDOWHEIGHT) == 720)
        resolution = 0;
    if ((*game->WINDOWWIDTH) == 1600 && (*game->WINDOWHEIGHT) == 900)
        resolution = 1;
    if ((*game->WINDOWWIDTH) == 1920 && (*game->WINDOWHEIGHT) == 1080)
        resolution = 2;
    if ((*game->WINDOWWIDTH) == 2560 && (*game->WINDOWHEIGHT) == 1440)
        resolution = 3;
    SDL_Texture *choix_resolution;

    SDL_Rect pos_choix_resolution;
    pos_choix_resolution.x = (*game->WINDOWWIDTH) / 6 + (*game->WINDOWWIDTH) * 500 / 1200;
    pos_choix_resolution.y = (*game->WINDOWHEIGHT) / 6.75 + (*game->WINDOWHEIGHT) * 30 / 675;
    pos_choix_resolution.w = (*game->WINDOWWIDTH) * 173 / 1200;
    pos_choix_resolution.h = (*game->WINDOWHEIGHT) / 13.5;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "Plein ecran" -----------------------------------*/

    surf_opt_fullscreen = TTF_RenderText_Blended(game->police, "Plein ecran", blanc);
    if (surf_opt_fullscreen == NULL)
    {
        SDL_ExitWithError("probleme surface opt_fullscreen");
    }

    SDL_Texture *opt_fullscreen = SDL_CreateTextureFromSurface(game->render, surf_opt_fullscreen);
    if (opt_fullscreen == NULL)
    {
        SDL_ExitWithError("probleme texture opt_fullscreen");
    }

    SDL_Rect pos_opt_fullscreen;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization texture "fullscreen" ---------------------------------*/

    if (*game->etat_fullscreen == SDL_FALSE)
    {
        surf_choix_fullscreen = TTF_RenderText_Blended(game->police, "Non", blanc);
        if (surf_choix_fullscreen == NULL)
        {
            SDL_ExitWithError("probleme surface choix_fullscreen");
        }
    }

    if (*game->etat_fullscreen == SDL_TRUE)
    {
        surf_choix_fullscreen = TTF_RenderText_Blended(game->police, "Oui", blanc);
        if (surf_choix_fullscreen == NULL)
        {
            SDL_ExitWithError("probleme surface choix_fullscreen");
        }
    }

    SDL_Texture *choix_fullscreen = SDL_CreateTextureFromSurface(game->render, surf_choix_fullscreen);
    if (choix_fullscreen == NULL)
    {
        SDL_ExitWithError("probleme texture choix_fullscreen");
    }

    SDL_Rect pos_choix_fullscreen;
    pos_choix_fullscreen.x = (*game->WINDOWWIDTH) / 6 + (*game->WINDOWWIDTH) * 500 / 1200;
    pos_choix_fullscreen.y = (*game->WINDOWHEIGHT) / 6.75 + (*game->WINDOWHEIGHT) * 100 / 675;
    pos_choix_fullscreen.w = (*game->WINDOWWIDTH) * 64 / 1200;
    pos_choix_fullscreen.h = (*game->WINDOWHEIGHT) / 13.5;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "Retour" ----------------------------------------*/

    surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
    if (surf_retour == NULL)
    {
        SDL_ExitWithError("probleme surface options");
    }

    SDL_Texture *retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
    if (retour == NULL)
    {
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_retour;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization texture background -----------------------------------*/

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

    /*-------------------------------------------------------------------------*/

    /*--- Initialization texture "cadre" --------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_options.bmp");
    if (surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture *cadre = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if (cadre == NULL)
    {
        SDL_ExitWithError("probleme texture nouvelle partie menu d'accueil");
    }

    SDL_Rect pos_cadre;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization texture "fond cadre" ---------------------------------*/

    SDL_Texture *fond_cadre = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) * 820 / 1200, (*game->WINDOWHEIGHT) * 460 / 675);
    if (fond_cadre == NULL)
    {
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_fond_cadre;

    SDL_Rect rect_fond_cadre;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization texture "fleche" -------------------------------------*/

    surf_fleche = SDL_LoadBMP("src\\image\\fleche.bmp");
    if (surf_fleche == NULL)
    {
        SDL_ExitWithError("probleme chargement image fleche gauche et droite");
    }

    SDL_Texture *fleche_gauche = SDL_CreateTextureFromSurface(game->render, surf_fleche);
    if (fleche_gauche == NULL)
    {
        SDL_ExitWithError("probleme texture fleche gauche");
    }

    SDL_Rect rect_fleche_gauche;
    rect_fleche_gauche.x = 39;
    rect_fleche_gauche.y = 0;
    rect_fleche_gauche.w = 38;
    rect_fleche_gauche.h = 28;

    SDL_Rect pos_fleche_gauche;

    SDL_Texture *fleche_droite = SDL_CreateTextureFromSurface(game->render, surf_fleche);
    if (fleche_droite == NULL)
    {
        SDL_ExitWithError("probleme texture fleche droite");
    }

    SDL_Rect rect_fleche_droite;
    rect_fleche_droite.x = 0;
    rect_fleche_droite.y = 0;
    rect_fleche_droite.w = 38;
    rect_fleche_droite.h = 28;

    SDL_Rect pos_fleche_droite;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "commandes" ------------------------------------------*/

    surf_commandes = TTF_RenderText_Blended(game->police, "Commandes", blanc);
    if (surf_commandes == NULL)
    {
        SDL_ExitWithError("probleme surface commandes");
    }
    SDL_Texture *commandes = SDL_CreateTextureFromSurface(game->render, surf_commandes);
    if (commandes == NULL)
    {
        SDL_ExitWithError("probleme texture commandes");
    }

    SDL_Rect pos_commandes;

    /*-------------------------------------------------------------------------*/

    /*--- Main Loop -----------------------------------------------------------*/

    while (options_bool && *game->program_launch)
    {
        while (SDL_PollEvent(&event))
        {
            if (!keyState[SDL_SCANCODE_ESCAPE])
            {
                *echap_relache = SDL_TRUE;
            }

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                *game->program_launch = SDL_FALSE;
                options_bool = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN && *echap_relache)
            {
                options_bool = SDL_FALSE;
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
                surf_opt_resolution = TTF_RenderText_Blended(game->police, "Resolution", rouge);
                surf_opt_fullscreen = TTF_RenderText_Blended(game->police, "Plein ecran", blanc);
                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);

                pos_fleche_gauche.x = pos_choix_resolution.x - (*game->WINDOWHEIGHT) * 40 / 1280 * 38 / 28 - (*game->WINDOWWIDTH) * 20 / 1280;
                pos_fleche_gauche.y = pos_choix_resolution.y + (*game->WINDOWWIDTH) * 19 / 1280;
                pos_fleche_gauche.w = (*game->WINDOWHEIGHT) * 40 / 1280 * 38 / 28;
                pos_fleche_gauche.h = (*game->WINDOWHEIGHT) * 40 / 1280;

                pos_fleche_droite.x = pos_choix_resolution.x + pos_choix_resolution.w + (*game->WINDOWWIDTH) * 20 / 1280;
                pos_fleche_droite.y = pos_choix_resolution.y + (*game->WINDOWWIDTH) * 19 / 1280;
                pos_fleche_droite.w = (*game->WINDOWHEIGHT) * 40 / 1280 * 38 / 28;
                pos_fleche_droite.h = (*game->WINDOWHEIGHT) * 40 / 1280;

                /*--- Event pour choix resolution ------------------------------------------*/

                if (keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN)
                {
                    if (resolution < 3)
                        resolution++;
                    changement = SDL_TRUE;
                }

                if (keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN)
                {
                    if (resolution > 0)
                        resolution--;
                    changement = SDL_TRUE;
                }

                switch (resolution)
                {
                case RES_720P:
                    (*game->WINDOWWIDTH) = 1280;
                    (*game->WINDOWHEIGHT) = 720;
                    surf_choix_resolution = TTF_RenderText_Blended(game->police, "1280x720", blanc);
                    choix_resolution = SDL_CreateTextureFromSurface(game->render, surf_choix_resolution);
                    fleche_gauche = NULL;
                    fleche_droite = SDL_CreateTextureFromSurface(game->render, surf_fleche);
                    if (*game->etat_fullscreen == SDL_FALSE)
                        SDL_SetWindowPosition(game->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                    break;

                case RES_900P:
                    (*game->WINDOWWIDTH) = 1600;
                    (*game->WINDOWHEIGHT) = 900;
                    surf_choix_resolution = TTF_RenderText_Blended(game->police, "1600x900", blanc);
                    choix_resolution = SDL_CreateTextureFromSurface(game->render, surf_choix_resolution);
                    fleche_gauche = SDL_CreateTextureFromSurface(game->render, surf_fleche);
                    fleche_droite = SDL_CreateTextureFromSurface(game->render, surf_fleche);
                    if (*game->etat_fullscreen == SDL_FALSE)
                        SDL_SetWindowPosition(game->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                    break;

                case RES_1080P:
                    (*game->WINDOWWIDTH) = 1920;
                    (*game->WINDOWHEIGHT) = 1080;
                    surf_choix_resolution = TTF_RenderText_Blended(game->police, "1920x1080", blanc);
                    choix_resolution = SDL_CreateTextureFromSurface(game->render, surf_choix_resolution);
                    fleche_droite = SDL_CreateTextureFromSurface(game->render, surf_fleche);
                    fleche_gauche = SDL_CreateTextureFromSurface(game->render, surf_fleche);
                    if (*game->etat_fullscreen == SDL_FALSE)
                        SDL_SetWindowPosition(game->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                    break;

                case RES_1440P:
                    (*game->WINDOWWIDTH) = 2560;
                    (*game->WINDOWHEIGHT) = 1440;
                    surf_choix_resolution = TTF_RenderText_Blended(game->police, "2560x1440", blanc);
                    choix_resolution = SDL_CreateTextureFromSurface(game->render, surf_choix_resolution);
                    fleche_droite = NULL;
                    fleche_gauche = SDL_CreateTextureFromSurface(game->render, surf_fleche);
                    if (*game->etat_fullscreen == SDL_FALSE)
                        SDL_SetWindowPosition(game->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                    break;
                }

                if (changement)
                    SDL_SetWindowSize(game->window, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));
                changement = SDL_FALSE;

                /*--- End Event pour choix resolution --------------------------------------*/
            }

            if (selection == 1)
            {
                surf_opt_resolution = TTF_RenderText_Blended(game->police, "Resolution", blanc);
                surf_opt_fullscreen = TTF_RenderText_Blended(game->police, "Plein ecran", rouge);
                surf_commandes = TTF_RenderText_Blended(game->police, "Commandes", blanc);

                pos_fleche_gauche.x = pos_choix_fullscreen.x - (*game->WINDOWHEIGHT) * 40 / 1280 * 38 / 28 - (*game->WINDOWWIDTH) * 20 / 1280;
                pos_fleche_gauche.y = pos_choix_fullscreen.y + (*game->WINDOWWIDTH) * 23 / 1280;
                pos_fleche_gauche.w = (*game->WINDOWHEIGHT) * 40 / 1280 * 38 / 28;
                pos_fleche_gauche.h = (*game->WINDOWHEIGHT) * 40 / 1280;

                pos_fleche_droite.x = pos_choix_fullscreen.x + pos_choix_fullscreen.w + (*game->WINDOWWIDTH) * 20 / 1280;
                pos_fleche_droite.y = pos_choix_fullscreen.y + (*game->WINDOWWIDTH) * 23 / 1280;
                pos_fleche_droite.w = (*game->WINDOWHEIGHT) * 40 / 1280 * 38 / 28;
                pos_fleche_droite.h = (*game->WINDOWHEIGHT) * 40 / 1280;

                /*--- Event pour choix plein ecran ------------------------------------------*/

                if (keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN)
                {
                    if (*game->etat_fullscreen == SDL_FALSE)
                        *game->etat_fullscreen = SDL_TRUE;
                }

                if (keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN)
                {
                    if (*game->etat_fullscreen == SDL_TRUE)
                        *game->etat_fullscreen = SDL_FALSE;
                }

                switch (*game->etat_fullscreen)
                {
                case SDL_FALSE:
                    SDL_SetWindowFullscreen(game->window, 0);
                    SDL_SetWindowPosition(game->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                    surf_choix_fullscreen = TTF_RenderText_Blended(game->police, "Non", blanc);
                    choix_fullscreen = SDL_CreateTextureFromSurface(game->render, surf_choix_fullscreen);
                    fleche_gauche = NULL;
                    fleche_droite = SDL_CreateTextureFromSurface(game->render, surf_fleche);
                    break;
                case SDL_TRUE:
                    SDL_SetWindowFullscreen(game->window, SDL_WINDOW_FULLSCREEN);
                    surf_choix_fullscreen = TTF_RenderText_Blended(game->police, "Oui", blanc);
                    choix_fullscreen = SDL_CreateTextureFromSurface(game->render, surf_choix_fullscreen);
                    fleche_droite = NULL;
                    fleche_gauche = SDL_CreateTextureFromSurface(game->render, surf_fleche);
                    break;
                }

                /*--- End Event pour choix resolution --------------------------------------*/
            }
            if (selection == 2)
            {
                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
                surf_opt_fullscreen = TTF_RenderText_Blended(game->police, "Plein ecran", blanc);
                surf_commandes = TTF_RenderText_Blended(game->police, "Commandes", rouge);
            }

            if (selection == 3)
            {
                surf_commandes = TTF_RenderText_Blended(game->police, "Commandes", blanc);
                surf_retour = TTF_RenderText_Blended(game->police, "Retour", rouge);
                surf_opt_resolution = TTF_RenderText_Blended(game->police, "Resolution", blanc);
            }

            opt_resolution = SDL_CreateTextureFromSurface(game->render, surf_opt_resolution);
            opt_fullscreen = SDL_CreateTextureFromSurface(game->render, surf_opt_fullscreen);
            commandes = SDL_CreateTextureFromSurface(game->render, surf_commandes);
            retour = SDL_CreateTextureFromSurface(game->render, surf_retour);

            pos_options.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) * 107 / 1200;
            pos_options.y = (*game->WINDOWHEIGHT) / 30;
            pos_options.w = (*game->WINDOWWIDTH) * 214 / 1200;
            pos_options.h = (*game->WINDOWHEIGHT) / 13.5;

            pos_opt_resolution.x = (*game->WINDOWWIDTH) / 6 + (*game->WINDOWWIDTH) * 50 / 1200;
            pos_opt_resolution.y = (*game->WINDOWHEIGHT) / 6.75 + (*game->WINDOWWIDTH) * 30 / 1200;
            pos_opt_resolution.w = (*game->WINDOWWIDTH) * 215 / 1200;
            pos_opt_resolution.h = (*game->WINDOWHEIGHT) / 13.5;

            pos_choix_resolution.x = (*game->WINDOWWIDTH) / 6 + (*game->WINDOWWIDTH) * 500 / 1200;
            pos_choix_resolution.y = (*game->WINDOWHEIGHT) / 6.75 + (*game->WINDOWHEIGHT) * 30 / 675;
            pos_choix_resolution.w = (*game->WINDOWWIDTH) * 173 / 1200;
            pos_choix_resolution.h = (*game->WINDOWHEIGHT) / 13.5;

            pos_opt_fullscreen.x = (*game->WINDOWWIDTH) / 6 + (*game->WINDOWWIDTH) * 50 / 1200;
            pos_opt_fullscreen.y = (*game->WINDOWHEIGHT) / 6.75 + (*game->WINDOWHEIGHT) * 100 / 675;
            pos_opt_fullscreen.w = (*game->WINDOWWIDTH) * 236 / 1200;
            pos_opt_fullscreen.h = (*game->WINDOWHEIGHT) / 13.5;

            pos_choix_fullscreen.x = (*game->WINDOWWIDTH) / 6 + (*game->WINDOWWIDTH) * 500 / 1200;
            pos_choix_fullscreen.y = (*game->WINDOWHEIGHT) / 6.75 + (*game->WINDOWHEIGHT) * 100 / 675;
            pos_choix_fullscreen.w = (*game->WINDOWWIDTH) * 64 / 1200;
            pos_choix_fullscreen.h = (*game->WINDOWHEIGHT) / 13.5;

            pos_retour.x = (*game->WINDOWWIDTH) / 20;
            pos_retour.y = (*game->WINDOWHEIGHT) - (*game->WINDOWHEIGHT) / 8;
            pos_retour.w = (*game->WINDOWWIDTH) / (1200 / 129);
            pos_retour.h = (*game->WINDOWHEIGHT) / 13.5;

            pos_fond.x = 0;
            pos_fond.y = 0;
            pos_fond.w = (*game->WINDOWWIDTH);
            pos_fond.h = (*game->WINDOWHEIGHT);

            pos_cadre.x = (*game->WINDOWWIDTH) / 6;
            pos_cadre.y = (*game->WINDOWHEIGHT) / 6.75;
            pos_cadre.w = (*game->WINDOWWIDTH) * 820 / 1200;
            pos_cadre.h = (*game->WINDOWHEIGHT) * 460 / 675;

            pos_fond_cadre.x = pos_cadre.x;
            pos_fond_cadre.y = pos_cadre.y;
            pos_fond_cadre.w = pos_cadre.w;
            pos_fond_cadre.h = pos_cadre.h;

            rect_fond_cadre.x = (*game->WINDOWWIDTH) * 12 / 1200;
            rect_fond_cadre.y = (*game->WINDOWHEIGHT) * 12 / 675;
            rect_fond_cadre.w = pos_fond_cadre.w - 2 * rect_fond_cadre.x + 1;
            rect_fond_cadre.h = pos_fond_cadre.h - 2 * rect_fond_cadre.y + 1;

            fond_cadre = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH) * 820 / 1200, (*game->WINDOWHEIGHT) * 460 / 675);

            rect_fleche_droite.x = 0;
            rect_fleche_droite.y = 0;
            rect_fleche_droite.w = 38;
            rect_fleche_droite.h = 28;

            rect_fleche_gauche.x = 39;
            rect_fleche_gauche.y = 0;
            rect_fleche_gauche.w = 38;
            rect_fleche_gauche.h = 28;

            pos_commandes.w = (*game->WINDOWWIDTH) * 193 / 1200;
            pos_commandes.h = (*game->WINDOWHEIGHT) / 13.5;
            pos_commandes.x = pos_opt_fullscreen.x;
            pos_commandes.y = pos_opt_fullscreen.y + (*game->WINDOWHEIGHT) * 70 / 720;

            SDL_SetRenderDrawColor(game->render, 0, 0, 0, 200);
            SDL_SetRenderTarget(game->render, fond_cadre);
            SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
            SDL_RenderFillRect(game->render, &rect_fond_cadre);
            SDL_SetRenderTarget(game->render, NULL);

            SDL_RenderClear(game->render);

            SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
            SDL_RenderCopy(game->render, options, NULL, &pos_options);
            SDL_RenderCopy(game->render, retour, NULL, &pos_retour);
            SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
            SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
            SDL_RenderCopy(game->render, opt_resolution, NULL, &pos_opt_resolution);
            SDL_RenderCopy(game->render, choix_resolution, NULL, &pos_choix_resolution);
            SDL_RenderCopy(game->render, opt_fullscreen, NULL, &pos_opt_fullscreen);
            SDL_RenderCopy(game->render, choix_fullscreen, NULL, &pos_choix_fullscreen);

            if (selection == 0 || selection == 1)
            {
                SDL_RenderCopy(game->render, fleche_gauche, &rect_fleche_gauche, &pos_fleche_gauche);
                SDL_RenderCopy(game->render, fleche_droite, &rect_fleche_droite, &pos_fleche_droite);
            }

            SDL_RenderCopy(game->render, commandes, NULL, &pos_commandes);

            SDL_RenderPresent(game->render);

            texture_render_options = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

            SDL_SetRenderTarget(game->render, texture_render_options);

            SDL_RenderClear(game->render);

            SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
            SDL_RenderCopy(game->render, options, NULL, &pos_options);

            SDL_SetRenderTarget(game->render, NULL);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {
                if (selection == 2)
                {
                    menu_commandes(game, texture_render_options, echap_relache);
                }

                if (selection == 3)
                {
                    options_bool = SDL_FALSE;
                }
            }

            if (options_bool == SDL_FALSE || *game->program_launch == SDL_FALSE)
            {
                FILE *opts = fopen("options.txt", "w");
                if (opts == NULL)
                {
                    exit_with_error("Fichier options.txt ne pas etre ouvert > options.c Line 398");
                }

                fprintf(opts, "WindowResolution: %i ;\nFullscreen: %i ;", resolution, *game->etat_fullscreen);

                fclose(opts);
            }
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_options);
    SDL_FreeSurface(surf_retour);
    SDL_FreeSurface(surf_fond);
    SDL_FreeSurface(surf_opt_resolution);
    SDL_FreeSurface(surf_commandes);

    SDL_DestroyTexture(options);
    SDL_DestroyTexture(retour);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(cadre);
    SDL_DestroyTexture(opt_resolution);
    SDL_DestroyTexture(fleche_droite);
    SDL_DestroyTexture(fleche_gauche);
    SDL_DestroyTexture(commandes);

    /*--- End Free Memory --------------------------------------------------------*/
}
