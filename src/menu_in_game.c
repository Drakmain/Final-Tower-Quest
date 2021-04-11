#include <stdio.h>
#include <stdlib.h>

#include "..\lib\menu_in_game.h"
#include "..\lib\sauvegarder.h"
#include "..\lib\character.h"
#include "..\lib\texte_confirmation.h"
#include "..\lib\caracteristiques.h"
#include "..\lib\commandes.h"
#include "..\lib\sac.h"

/*!
 *
 * \file menu_in_game.c
 * \brief Menu dans le jeu.
 * \author Jeremy BOURGOUIN
 *
 */

/*!
 *
 * \fn menu_in_game(game_t *game, SDL_bool *map_bool, character_t *character, SDL_Texture *texture_render)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param map_bool A FINIR.
 * \param character A FINIR.
 * \param texture_render A FINIR.
 *
 */

void menu_in_game(game_t *game, SDL_bool *map_bool, character_t *character, SDL_Texture *texture_render)
{

    /*--- Initialization variable ------------------------------------------------*/

    SDL_Color blanc = {255, 255, 255};
    SDL_Color rouge = {255, 0, 0};

    SDL_Surface *surf_sac = NULL, *surf_caracteristique = NULL, *surf_sauvegarder = NULL, *surf_commandes = NULL, *surf_retourner_menu = NULL, *surf_cadre = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool menu_bool = SDL_TRUE;
    SDL_bool *echap_relache = malloc(sizeof(SDL_bool));
    *echap_relache = SDL_FALSE;
    SDL_Event event;

    int selection = 0;

    SDL_Texture *texture_render_menu_ig = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

    /*--- End Initialization variable --------------------------------------------*/

    /*--- Creation text "nouvelle partie" ----------------------------------------*/

    surf_sac = TTF_RenderText_Blended(game->police, "Sac", rouge);
    if (surf_sac == NULL)
    {
        SDL_ExitWithError("probleme surface sac menu in game");
    }

    SDL_Texture *sac = SDL_CreateTextureFromSurface(game->render, surf_sac);
    if (sac == NULL)
    {
        SDL_ExitWithError("probleme texture sac menu in game");
    }

    SDL_Rect pos_sac;
    pos_sac.x = (*game->WINDOWWIDTH) - (*game->WINDOWWIDTH) * 410 / 1280;
    pos_sac.y = (*game->WINDOWHEIGHT) * 25 / 720;
    pos_sac.w = (*game->WINDOWWIDTH) * 64.5 / 1200;
    pos_sac.h = (*game->WINDOWHEIGHT) * 50 / 720;
    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nouvelle partie" ----------------------------------------*/

    surf_caracteristique = TTF_RenderText_Blended(game->police, "Caracteristiques", blanc);
    if (surf_caracteristique == NULL)
    {
        SDL_ExitWithError("probleme surface caracteristique menu in game");
    }

    SDL_Texture *caracteristique = SDL_CreateTextureFromSurface(game->render, surf_caracteristique);
    if (caracteristique == NULL)
    {
        SDL_ExitWithError("probleme texture caracteristique menu in game");
    }

    SDL_Rect pos_caracteristique;
    pos_caracteristique.x = (*game->WINDOWWIDTH) - (*game->WINDOWWIDTH) * 410 / 1280;
    pos_caracteristique.y = (*game->WINDOWHEIGHT) * 100 / 720;
    pos_caracteristique.w = (*game->WINDOWWIDTH) * 322 / 1200;
    pos_caracteristique.h = (*game->WINDOWHEIGHT) * 50 / 720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nouvelle partie" ----------------------------------------*/

    surf_sauvegarder = TTF_RenderText_Blended(game->police, "Sauvegarder", blanc);
    if (surf_sauvegarder == NULL)
    {
        SDL_ExitWithError("probleme surface sauvegarder menu in game");
    }

    SDL_Texture *sauvegarder = SDL_CreateTextureFromSurface(game->render, surf_sauvegarder);
    if (sauvegarder == NULL)
    {
        SDL_ExitWithError("probleme texture sauvegarder menu in game");
    }

    SDL_Rect pos_sauvegarder;
    pos_sauvegarder.x = (*game->WINDOWWIDTH) - (*game->WINDOWWIDTH) * 410 / 1280;
    pos_sauvegarder.y = (*game->WINDOWHEIGHT) * 175 / 720;
    pos_sauvegarder.w = (*game->WINDOWWIDTH) * 236 / 1200;
    pos_sauvegarder.h = (*game->WINDOWHEIGHT) * 50 / 720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nouvelle partie" ----------------------------------------*/

    surf_commandes = TTF_RenderText_Blended(game->police, "Commandes", blanc);
    if (surf_commandes == NULL)
    {
        SDL_ExitWithError("probleme surface commandes menu in game");
    }

    SDL_Texture *commandes = SDL_CreateTextureFromSurface(game->render, surf_commandes);
    if (commandes == NULL)
    {
        SDL_ExitWithError("probleme texture commandes menu in game");
    }

    SDL_Rect pos_commandes;
    pos_commandes.x = (*game->WINDOWWIDTH) - (*game->WINDOWWIDTH) * 410 / 1280;
    pos_commandes.y = (*game->WINDOWHEIGHT) * 250 / 720;
    pos_commandes.w = (*game->WINDOWWIDTH) * 215 / 1200;
    pos_commandes.h = (*game->WINDOWHEIGHT) * 50 / 720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nouvelle partie" ----------------------------------------*/

    surf_retourner_menu = TTF_RenderText_Blended(game->police, "Retourner au Menu", blanc);
    if (surf_retourner_menu == NULL)
    {
        SDL_ExitWithError("probleme surface retourner_menu menu in game");
    }

    SDL_Texture *retourner_menu = SDL_CreateTextureFromSurface(game->render, surf_retourner_menu);
    if (retourner_menu == NULL)
    {
        SDL_ExitWithError("probleme texture retourner_menu menu in game");
    }

    SDL_Rect pos_retourner_menu;
    pos_retourner_menu.x = (*game->WINDOWWIDTH) - (*game->WINDOWWIDTH) * 410 / 1280;
    pos_retourner_menu.y = (*game->WINDOWHEIGHT) * 325 / 720;
    pos_retourner_menu.w = (*game->WINDOWWIDTH) * 365 / 1200;
    pos_retourner_menu.h = (*game->WINDOWHEIGHT) * 50 / 720;

    /*----------------------------------------------------------------------------*/

    /*---texture "cadre"--------------------------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_menu_in_game.bmp");
    if (surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre menu in game");
    }

    SDL_Texture *cadre = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if (cadre == NULL)
    {
        SDL_ExitWithError("probleme texture cadre menu in game");
    }

    SDL_Rect pos_cadre;
    pos_cadre.x = (*game->WINDOWWIDTH) - (*game->WINDOWWIDTH) * 435 / 1280;
    pos_cadre.y = 0;
    pos_cadre.w = (*game->WINDOWWIDTH) * 435 / 1280;
    pos_cadre.h = (*game->WINDOWHEIGHT) * 400 / 720;

    /*------------------------------------------------------------------------------------*/

    /*---texture fond--------------------------------------------------------*/

    SDL_Texture *fond_cadre = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre.w, pos_cadre.h);
    if (fond_cadre == NULL)
    {
        SDL_ExitWithError("probleme texture fond cadre");
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

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, 200);
    SDL_SetRenderTarget(game->render, fond_cadre);
    SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, texture_render, NULL, NULL);
    SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
    SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
    SDL_RenderCopy(game->render, sac, NULL, &pos_sac);
    SDL_RenderCopy(game->render, caracteristique, NULL, &pos_caracteristique);
    SDL_RenderCopy(game->render, sauvegarder, NULL, &pos_sauvegarder);
    SDL_RenderCopy(game->render, commandes, NULL, &pos_commandes);
    SDL_RenderCopy(game->render, retourner_menu, NULL, &pos_retourner_menu);

    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    while (menu_bool && (*game->program_launch))
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
                selection = 4;
            selection %= 5;

            if (selection == 0)
            {
                surf_sac = TTF_RenderText_Blended(game->police, "Sac", rouge);
                surf_caracteristique = TTF_RenderText_Blended(game->police, "Caracteristiques", blanc);
                surf_retourner_menu = TTF_RenderText_Blended(game->police, "Retourner au Menu", blanc);
            }

            if (selection == 1)
            {
                surf_sac = TTF_RenderText_Blended(game->police, "Sac", blanc);
                surf_caracteristique = TTF_RenderText_Blended(game->police, "Caracteristiques", rouge);
                surf_sauvegarder = TTF_RenderText_Blended(game->police, "Sauvegarder", blanc);
            }

            if (selection == 2)
            {
                surf_caracteristique = TTF_RenderText_Blended(game->police, "Caracteristiques", blanc);
                surf_sauvegarder = TTF_RenderText_Blended(game->police, "Sauvegarder", rouge);
                surf_commandes = TTF_RenderText_Blended(game->police, "Commandes", blanc);
            }

            if (selection == 3)
            {
                surf_sauvegarder = TTF_RenderText_Blended(game->police, "Sauvegarder", blanc);
                surf_commandes = TTF_RenderText_Blended(game->police, "Commandes", rouge);
                surf_retourner_menu = TTF_RenderText_Blended(game->police, "Retourner au Menu", blanc);
            }

            if (selection == 4)
            {
                surf_sac = TTF_RenderText_Blended(game->police, "Sac", blanc);
                surf_commandes = TTF_RenderText_Blended(game->police, "Commandes", blanc);
                surf_retourner_menu = TTF_RenderText_Blended(game->police, "Retourner au Menu", rouge);
            }

            sac = SDL_CreateTextureFromSurface(game->render, surf_sac);
            caracteristique = SDL_CreateTextureFromSurface(game->render, surf_caracteristique);
            sauvegarder = SDL_CreateTextureFromSurface(game->render, surf_sauvegarder);
            commandes = SDL_CreateTextureFromSurface(game->render, surf_commandes);
            retourner_menu = SDL_CreateTextureFromSurface(game->render, surf_retourner_menu);

            SDL_SetRenderTarget(game->render, texture_render_menu_ig);

            SDL_RenderClear(game->render);
            SDL_RenderCopy(game->render, texture_render, NULL, NULL);
            SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
            SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
            SDL_RenderCopy(game->render, sac, NULL, &pos_sac);
            SDL_RenderCopy(game->render, caracteristique, NULL, &pos_caracteristique);
            SDL_RenderCopy(game->render, sauvegarder, NULL, &pos_sauvegarder);
            SDL_RenderCopy(game->render, commandes, NULL, &pos_commandes);
            SDL_RenderCopy(game->render, retourner_menu, NULL, &pos_retourner_menu);
            SDL_SetRenderTarget(game->render, NULL);
            SDL_RenderCopy(game->render, texture_render_menu_ig, NULL, NULL);

            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {
                if (selection == 0)
                    ouverture_sac(game, character, texture_render_menu_ig, echap_relache, SDL_FALSE);
                if (selection == 1)
                    caracteristiques(game, character, texture_render_menu_ig, echap_relache);
                if (selection == 2)
                {
                    if (texte_confirmation(game, "Etes-vous sur de vouloir ecraser vos donnees precedentes ?"))
                        sauvegarde(game, character);
                }
                if (selection == 3)
                    menu_commandes(game, texture_render_menu_ig, echap_relache);
                if (selection == 4)
                {
                    if (texte_confirmation(game, "Voulez-vous retourner au menu principal ?"))
                    {
                        menu_bool = SDL_FALSE;
                        *map_bool = SDL_FALSE;
                    }
                }
            }

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                (*game->program_launch) = SDL_FALSE;
            }

            if (!keyState[SDL_SCANCODE_ESCAPE])
            {
                *echap_relache = SDL_TRUE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN && *echap_relache)
            {
                menu_bool = SDL_FALSE;
                SDL_RenderClear(game->render);
                SDL_RenderCopy(game->render, texture_render, NULL, NULL);
                SDL_RenderPresent(game->render);
                while (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
                    SDL_PollEvent(&event);
            }

            /*--- End Event to Exit Program --------------------------------------*/
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_cadre);
    SDL_FreeSurface(surf_sac);
    SDL_FreeSurface(surf_caracteristique);
    SDL_FreeSurface(surf_sauvegarder);
    SDL_FreeSurface(surf_commandes);
    SDL_FreeSurface(surf_retourner_menu);

    SDL_DestroyTexture(sac);
    SDL_DestroyTexture(caracteristique);
    SDL_DestroyTexture(sauvegarder);
    SDL_DestroyTexture(commandes);
    SDL_DestroyTexture(retourner_menu);
    SDL_DestroyTexture(cadre);
    SDL_DestroyTexture(fond_cadre);
    SDL_DestroyTexture(texture_render_menu_ig);

    /*--- End Free Memory --------------------------------------------------------*/
}
