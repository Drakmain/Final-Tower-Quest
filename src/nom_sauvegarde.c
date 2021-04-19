#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\nom_sauvegarde.h"

/*!
 *
 * \file nom_sauvegarde.c
 * \brief A FINIR.
 * \author Alexis BOUFFARD, Enzo BRENNUS.
 *
 */

/*!
 *
 * \fn fcpy(FILE *source_file, FILE *dest_file)
 * \brief Fonction qui permet de copier une chaîne de caractères dans une autre.
 *
 * \param source_file est une chaîne de caractères source.
 * \param dest_file est une chaîne de caractères de destination.
 *
 */

static void fcpy(FILE *source_file, FILE *dest_file)
{
    char c;

    c = fgetc(source_file);
    while (c != EOF)
    {
        fputc(c, dest_file);
        c = fgetc(source_file);
    }
}

/*!
 *
 * \fn nom_sauvegarde(game_t *game, char *actual_save, char *base_save)
 * \brief Fonction qui permet la creation d'une nouvelle partie.
 *
 * \param game est un pointeur sur l'objet game_t du jeu.
 * \param actual_save représente le fichier initialisé lorsque le joueur sélectionne le personnage.
 * \param base_save est une chaîne de caractère que l'on récupère à la fin de la fonction et qui est copié dans actual_save
 *
 */

extern void nom_sauvegarde(game_t *game, char *actual_save, char *base_save)
{
    /*--- Initialization variable ----------------------------------------------------*/

    SDL_Color blanc = {255, 255, 255};

    SDL_Surface *surf_fond = NULL, *surf_demande = NULL, *surf_cadre = NULL, *surf_nom_save = NULL;

    SDL_bool nom_sauvegarde_bool = SDL_TRUE;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    char nom_save[11];

    FILE *src;
    FILE *dst;

    int touche;

    /*--- End Initialization variable --------------------------------------------*/

    /*--- Initialization background image ----------------------------------------*/

    surf_fond = SDL_LoadBMP("src\\image\\ciel_sans_lune.bmp");
    if (surf_fond == NULL)
    {
        SDL_ExitWithError("probleme chargement image fond menu de creation de personnage");
    }

    SDL_Texture *fond = SDL_CreateTextureFromSurface(game->render, surf_fond);
    if (fond == NULL)
    {
        SDL_ExitWithError("probleme texture fond menu de creation de personnage");
    }

    SDL_Rect pos_fond;
    pos_fond.x = 0;
    pos_fond.y = 0;
    pos_fond.w = (*game->WINDOWWIDTH);
    pos_fond.h = (*game->WINDOWHEIGHT);

    /*----------------------------------------------------------------------------*/

    /*--- Initialization texture "cadre" -----------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_nom_save.bmp");
    if (surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre");
    }

    SDL_Texture *cadre_nom_save = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if (cadre_nom_save == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_nom_save");
    }

    SDL_Rect pos_cadre_nom_save;
    pos_cadre_nom_save.x = (*game->WINDOWHEIGHT) * 271 / 720;
    pos_cadre_nom_save.y = (*game->WINDOWHEIGHT) * 325 / 720;
    pos_cadre_nom_save.w = (*game->WINDOWWIDTH) * 720 / 1280;
    pos_cadre_nom_save.h = (*game->WINDOWHEIGHT) * 110 / 720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation texture background "cadre" ------------------------------------*/

    SDL_Texture *fond_cadre_nom_save = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre_nom_save.w, pos_cadre_nom_save.h);
    if (fond_cadre_nom_save == NULL)
    {
        SDL_ExitWithError("probleme texture fond_cadre_nom_save");
    }

    SDL_Rect pos_fond_cadre_nom_save;
    pos_fond_cadre_nom_save.x = pos_cadre_nom_save.x;
    pos_fond_cadre_nom_save.y = pos_cadre_nom_save.y;
    pos_fond_cadre_nom_save.w = pos_cadre_nom_save.w;
    pos_fond_cadre_nom_save.h = pos_cadre_nom_save.h;

    SDL_Rect rect_fond_cadre_nom_save;
    rect_fond_cadre_nom_save.x = (*game->WINDOWWIDTH) * 12 / 1280;
    rect_fond_cadre_nom_save.y = (*game->WINDOWHEIGHT) * 12 / 720;
    rect_fond_cadre_nom_save.w = pos_fond_cadre_nom_save.w - 2 * rect_fond_cadre_nom_save.x + 1;
    rect_fond_cadre_nom_save.h = pos_fond_cadre_nom_save.h - 2 * rect_fond_cadre_nom_save.y + 1;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 200);
    SDL_SetRenderTarget(game->render, fond_cadre_nom_save);
    SDL_SetTextureBlendMode(fond_cadre_nom_save, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre_nom_save);
    SDL_SetRenderTarget(game->render, NULL);

    /*----------------------------------------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
    SDL_RenderCopy(game->render, fond_cadre_nom_save, NULL, &pos_fond_cadre_nom_save);
    SDL_RenderCopy(game->render, cadre_nom_save, NULL, &pos_cadre_nom_save);

    SDL_RenderPresent(game->render);

    /*--- Initialization text "Demande" -----------------------------------------*/

    surf_demande = TTF_RenderText_Blended(game->police, "Votre nom de sauvegarde doit etre compris entre 1 et 10 caracteres :", blanc);
    if (surf_demande == NULL)
    {
        SDL_ExitWithError("Probleme surface demande");
    }

    SDL_Texture *demande = SDL_CreateTextureFromSurface(game->render, surf_demande);
    if (demande == NULL)
    {
        SDL_ExitWithError("Probleme texture demande");
    }

    SDL_Rect pos_demande;
    pos_demande.x = (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) / 2.11;
    pos_demande.y = (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWWIDTH) / 5;
    pos_demande.w = (*game->WINDOWWIDTH) / 1.05;
    pos_demande.h = (*game->WINDOWHEIGHT) / 13.5;

    /*----------------------------------------------------------------------------*/

    /*--- Initialization text "surf_nom_save" ------------------------------------*/

    surf_nom_save = TTF_RenderText_Blended(game->police, "", blanc);

    SDL_Texture *texture_nom_save;

    SDL_Rect pos_Wind_nom_save;
    pos_Wind_nom_save.x = (*game->WINDOWHEIGHT) * 330 / 720;
    pos_Wind_nom_save.y = (*game->WINDOWHEIGHT) * 315 / 720;
    pos_Wind_nom_save.h = (*game->WINDOWHEIGHT) * 110 / 720;

    /*----------------------------------------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
    SDL_RenderCopy(game->render, demande, NULL, &pos_demande);
    SDL_RenderCopy(game->render, fond_cadre_nom_save, NULL, &pos_fond_cadre_nom_save);
    SDL_RenderCopy(game->render, cadre_nom_save, NULL, &pos_cadre_nom_save);

    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    while (nom_sauvegarde_bool && *game->program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program -----------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                *game->program_launch = SDL_FALSE;
                nom_sauvegarde_bool = SDL_FALSE;
            }

            /*--- End Event to Exit Program -------------------------------------------*/

            if (strlen(nom_save) < 10)
            {
                if ((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) && event.type == SDL_KEYDOWN)
                {
                    touche = event.key.keysym.sym;
                    if (event.key.keysym.mod == KMOD_LSHIFT)
                    {
                        nom_save[strlen(nom_save)] = touche - ('a' - 'A');
                    }
                    else
                    {
                        nom_save[strlen(nom_save)] = touche;
                    }
                }
            }

            SDL_RenderClear(game->render);

            SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
            SDL_RenderCopy(game->render, demande, NULL, &pos_demande);
            SDL_RenderCopy(game->render, fond_cadre_nom_save, NULL, &pos_fond_cadre_nom_save);
            SDL_RenderCopy(game->render, cadre_nom_save, NULL, &pos_cadre_nom_save);

            if (keyState[SDL_SCANCODE_BACKSPACE] && event.type == SDL_KEYDOWN)
            {
                nom_save[strlen(nom_save) - 1] = '\0';
            }

            if (strcmp(nom_save, ""))
            {
                surf_nom_save = TTF_RenderText_Blended(game->police, nom_save, blanc);
                if (surf_nom_save == NULL)
                {
                    SDL_ExitWithError("Probleme surface surf_nom_save > nom_sauvegarde.c Line 229");
                }

                texture_nom_save = SDL_CreateTextureFromSurface(game->render, surf_nom_save);
                if (texture_nom_save == NULL)
                {
                    SDL_ExitWithError("Probleme texture texture_nom_save > nom_sauvegarde.c Line 304");
                }

                pos_Wind_nom_save.w = strlen(nom_save) * (*game->WINDOWHEIGHT) * 119 / 1440;

                SDL_RenderCopy(game->render, texture_nom_save, NULL, &pos_Wind_nom_save);
            }

            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN])
            {
                dst = fopen(actual_save, "w");

                fprintf(dst, "save_name: %s ;\n", nom_save);

                fclose(dst);
                dst = NULL;

                dst = fopen(actual_save, "a");
                src = fopen(base_save, "r");

                fcpy(src, dst);

                fclose(dst);
                fclose(src);

                nom_sauvegarde_bool = SDL_FALSE;
            }
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_fond);
    SDL_FreeSurface(surf_demande);
    SDL_FreeSurface(surf_cadre);
    SDL_FreeSurface(surf_nom_save);

    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(cadre_nom_save);
    SDL_DestroyTexture(fond_cadre_nom_save);
    SDL_DestroyTexture(texture_nom_save);

    /*--- End Free Memory --------------------------------------------------------*/
}
