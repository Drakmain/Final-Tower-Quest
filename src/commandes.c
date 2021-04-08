#include <stdio.h>
#include <stdlib.h>

#include "..\lib\options.h"

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
 * \brief A FINIR.
 *
 * \param game A FINIR.
 *
 */

void menu_commandes(game_t * game, SDL_Texture * texture, SDL_bool *echap_relache){

    /*--- Initialization variable ------------------------------------------------*/

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    SDL_Surface* surf_commandes = NULL, *surf_retour = NULL, *surf_cadre = NULL, *surf_deplacer_selectionner = NULL, *surf_ouv_fer_menu = NULL, *surf_valider = NULL, *surf_interagir = NULL, *surf_image_fleche = NULL, *surf_image_echap = NULL, *surf_image_return = NULL, *surf_image_E = NULL, *surf_2point = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool commandes_bool = SDL_TRUE;
    SDL_Event event;


    /*--- End Initialization variable --------------------------------------------*/

    /*--- Initialization texture "cadre" --------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_options.bmp");
    if(surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement cadre option dans commandes menu_in_game");
    }

    SDL_Texture* cadre = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if(cadre == NULL)
    {
        SDL_ExitWithError("probleme texture cadre option dans commandes menu_in_game");
    }

    SDL_Rect pos_cadre;
    pos_cadre.x = (*game->WINDOWWIDTH)/6;
    pos_cadre.y = (*game->WINDOWHEIGHT)/6.75;
    pos_cadre.w = (*game->WINDOWWIDTH)*820/1200;
    pos_cadre.h = (*game->WINDOWHEIGHT)*460/675;
    
    /*-------------------------------------------------------------------------*/


    /*--- Initialization texture "fond cadre" ---------------------------------*/

    SDL_Texture* fond_cadre = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH)*820/1200, (*game->WINDOWHEIGHT)*460/675);
    if(fond_cadre == NULL)
    {
        SDL_ExitWithError("probleme texture fond cadre");
    }

    SDL_Rect pos_fond_cadre;
    pos_fond_cadre.x = pos_cadre.x;
    pos_fond_cadre.y = pos_cadre.y;
    pos_fond_cadre.w = pos_cadre.w;
    pos_fond_cadre.h = pos_cadre.h;


    SDL_Rect rect_fond_cadre;
    rect_fond_cadre.x = (*game->WINDOWWIDTH)*12/1200;
    rect_fond_cadre.y = (*game->WINDOWHEIGHT)*12/675;
    rect_fond_cadre.w = pos_fond_cadre.w - 2*rect_fond_cadre.x;
    rect_fond_cadre.h = pos_fond_cadre.h - 2*rect_fond_cadre.y;

    SDL_SetRenderDrawColor(game->render,0,0,0, 240);
    SDL_SetRenderTarget(game->render,fond_cadre);
    SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre);
    SDL_SetRenderTarget(game->render,NULL);

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "commandes" ------------------------------------------*/

    surf_commandes = TTF_RenderText_Blended(game->police, "COMMANDES", blanc);
    if(surf_commandes == NULL)
    {
        SDL_ExitWithError("probleme surface commandes");
    }
    SDL_Texture* commandes = SDL_CreateTextureFromSurface(game->render, surf_commandes);
    if(commandes == NULL)
    {
        SDL_ExitWithError("probleme texture commandes");
    }

    SDL_Rect pos_commandes;
    pos_commandes.w = (*game->WINDOWWIDTH)*193/1200;
    pos_commandes.h = (*game->WINDOWHEIGHT)/13.5;
    pos_commandes.x = (*game->WINDOWWIDTH)/2 - pos_commandes.w/2;
    pos_commandes.y = pos_cadre.y + rect_fond_cadre.y + (*game->WINDOWHEIGHT)*15/720;

    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "Retour" ----------------------------------------*/

    surf_retour = TTF_RenderText_Blended(game->police, "Retour", rouge);
    if(surf_retour == NULL)
    {
        SDL_ExitWithError("probleme surface retour");
    }
    SDL_Texture* retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
    if(retour == NULL)
    {
        SDL_ExitWithError("probleme texture retour");
    }

    SDL_Rect pos_retour;
    pos_retour.w = (*game->WINDOWWIDTH) * 129 / 1200;
    pos_retour.h = (*game->WINDOWHEIGHT)/13.5;
    pos_retour.x = pos_cadre.x + rect_fond_cadre.x + (*game->WINDOWWIDTH) * 15 / 1280;
    pos_retour.y = pos_cadre.y + pos_cadre.h - rect_fond_cadre.y - pos_retour.h - (*game->WINDOWHEIGHT)*20/720;
    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "se déplacer/selectionner" ----------------------------------------*/

    surf_deplacer_selectionner = TTF_RenderText_Blended(game->police, "Se deplacer/Selectionner", blanc);
    if(surf_deplacer_selectionner == NULL)
    {
        SDL_ExitWithError("probleme surface deplacer/selectionner");
    }
    SDL_Texture* deplacer_selectionner = SDL_CreateTextureFromSurface(game->render, surf_deplacer_selectionner);
    if(deplacer_selectionner == NULL)
    {
        SDL_ExitWithError("probleme texture deplacer_selectionner");
    }

    SDL_Rect pos_deplacer_selectionner;
    pos_deplacer_selectionner.w = (*game->WINDOWWIDTH) * 360 / 1200;
    pos_deplacer_selectionner.h = (*game->WINDOWHEIGHT) * 50 / 675;
    pos_deplacer_selectionner.x = (*game->WINDOWWIDTH) / 2 - pos_deplacer_selectionner.w/2 - (*game->WINDOWWIDTH) * 135 / 1280;
    pos_deplacer_selectionner.y = pos_commandes.y + pos_commandes.h + (*game->WINDOWHEIGHT)*40/720;
    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "ouvrir/fermer menu" ----------------------------------------*/

    surf_ouv_fer_menu = TTF_RenderText_Blended(game->police, "Ouvrir/Fermer Menu      ", blanc);
    if(surf_ouv_fer_menu == NULL)
    {
        SDL_ExitWithError("probleme surface ouvrir/fermer menu");
    }
    SDL_Texture* ouv_fer_menu = SDL_CreateTextureFromSurface(game->render, surf_ouv_fer_menu);
    if(ouv_fer_menu == NULL)
    {
        SDL_ExitWithError("probleme texture ouvrir/fermer menu");
    }

    SDL_Rect pos_ouv_fer_menu;
    pos_ouv_fer_menu.w = (*game->WINDOWWIDTH) * 360 / 1200;
    pos_ouv_fer_menu.h = (*game->WINDOWHEIGHT)/13.5;
    pos_ouv_fer_menu.x = pos_deplacer_selectionner.x;
    pos_ouv_fer_menu.y = pos_deplacer_selectionner.y + pos_deplacer_selectionner.h + (*game->WINDOWHEIGHT)*20/720;
    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "valider" ----------------------------------------*/

    surf_valider = TTF_RenderText_Blended(game->police, "Valider                 ", blanc);
    if(surf_valider == NULL)
    {
        SDL_ExitWithError("probleme surface valider");
    }
    SDL_Texture* valider = SDL_CreateTextureFromSurface(game->render, surf_valider);
    if(valider == NULL)
    {
        SDL_ExitWithError("probleme texture valider");
    }

    SDL_Rect pos_valider;
    pos_valider.w = (*game->WINDOWWIDTH) * 360 / 1200;
    pos_valider.h = (*game->WINDOWHEIGHT)/13.5;
    pos_valider.x = pos_deplacer_selectionner.x;
    pos_valider.y = pos_ouv_fer_menu.y + pos_ouv_fer_menu.h + (*game->WINDOWHEIGHT)*20/720;
    /*-------------------------------------------------------------------------*/

    /*--- Initialization text "interagir" ----------------------------------------*/

    surf_interagir = TTF_RenderText_Blended(game->police, "Interagir               ", blanc);
    if(surf_interagir == NULL)
    {
        SDL_ExitWithError("probleme surface interagir");
    }
    SDL_Texture* interagir = SDL_CreateTextureFromSurface(game->render, surf_interagir);
    if(interagir == NULL)
    {
        SDL_ExitWithError("probleme texture interagir");
    }

    SDL_Rect pos_interagir;
    pos_interagir.w = (*game->WINDOWWIDTH) * 360 / 1200;
    pos_interagir.h = (*game->WINDOWHEIGHT)/13.5;
    pos_interagir.x = pos_deplacer_selectionner.x;
    pos_interagir.y = pos_valider.y + pos_valider.h + (*game->WINDOWHEIGHT)*20/720;
    /*-------------------------------------------------------------------------*/

    SDL_Rect pos_2points_deplacer_select;
    pos_2points_deplacer_select.x = pos_deplacer_selectionner.x + pos_deplacer_selectionner.w;
    pos_2points_deplacer_select.y = pos_deplacer_selectionner.y;
    pos_2points_deplacer_select.w = (*game->WINDOWWIDTH) * 45 / 1280;
    pos_2points_deplacer_select.h = pos_deplacer_selectionner.h;

    SDL_Rect pos_2points_ouv_fer_menu;
    pos_2points_ouv_fer_menu.x = pos_ouv_fer_menu.x + pos_ouv_fer_menu.w;
    pos_2points_ouv_fer_menu.y = pos_ouv_fer_menu.y;
    pos_2points_ouv_fer_menu.w = (*game->WINDOWWIDTH) * 45 / 1280;
    pos_2points_ouv_fer_menu.h = pos_ouv_fer_menu.h;

    SDL_Rect pos_2points_valider;
    pos_2points_valider.x = pos_valider.x + pos_valider.w;
    pos_2points_valider.y = pos_valider.y;
    pos_2points_valider.w = (*game->WINDOWWIDTH) * 45 / 1280;
    pos_2points_valider.h = pos_valider.h;

    SDL_Rect pos_2points_interagir;
    pos_2points_interagir.x = pos_interagir.x + pos_interagir.w;
    pos_2points_interagir.y = pos_interagir.y;
    pos_2points_interagir.w = (*game->WINDOWWIDTH) * 45 / 1280;
    pos_2points_interagir.h = pos_interagir.h;

    /*--- Initialization texture "image fleche" --------------------------------------*/

    surf_image_fleche = SDL_LoadBMP("src\\image\\touche_fleche_clavier.bmp");
    if(surf_image_fleche == NULL)
    {
        SDL_ExitWithError("probleme chargement image touche fleche clavier dans commandes menu_in_game");
    }

    SDL_Texture* image_fleche = SDL_CreateTextureFromSurface(game->render, surf_image_fleche);
    if(image_fleche == NULL)
    {
        SDL_ExitWithError("probleme texture image touche fleche clavier dans commandes menu_in_game");
    }

    SDL_Rect pos_image_fleche;
    pos_image_fleche.x = pos_deplacer_selectionner.x + pos_deplacer_selectionner.w + pos_2points_deplacer_select.w + (*game->WINDOWWIDTH)*25/1280;
    pos_image_fleche.y = pos_deplacer_selectionner.y + (*game->WINDOWHEIGHT) * 8 / 1280;
    pos_image_fleche.w = (*game->WINDOWWIDTH) * 91 / 1200;
    pos_image_fleche.h = pos_deplacer_selectionner.h;
    /*-------------------------------------------------------------------------*/

    /*--- Initialization texture "echap" --------------------------------------*/

    surf_image_echap = SDL_LoadBMP("src\\image\\touche_echap_clavier.bmp");
    if(surf_image_echap == NULL)
    {
        SDL_ExitWithError("probleme chargement image touche echap clavier dans commandes menu_in_game");
    }

    SDL_Texture* image_echap = SDL_CreateTextureFromSurface(game->render, surf_image_echap);
    if(image_echap == NULL)
    {
        SDL_ExitWithError("probleme texture image touche echap clavier dans commandes menu_in_game");
    }

    SDL_Rect pos_image_echap;
    pos_image_echap.x = pos_ouv_fer_menu.x + pos_ouv_fer_menu.w + pos_2points_ouv_fer_menu.w + (*game->WINDOWWIDTH)*25/1280;
    pos_image_echap.y = pos_ouv_fer_menu.y + (*game->WINDOWHEIGHT) * 8 / 1280;
    pos_image_echap.w = (*game->WINDOWWIDTH) * 50 / 1200;
    pos_image_echap.h = pos_ouv_fer_menu.h;
    /*-------------------------------------------------------------------------*/

    /*--- Initialization texture "entrée" --------------------------------------*/

    surf_image_return = SDL_LoadBMP("src\\image\\touche_return_clavier.bmp");
    if(surf_image_return == NULL)
    {
        SDL_ExitWithError("probleme chargement image touche return clavier dans commandes menu_in_game");
    }

    SDL_Texture* image_return = SDL_CreateTextureFromSurface(game->render, surf_image_return);
    if(image_return == NULL)
    {
        SDL_ExitWithError("probleme texture image touche return clavier dans commandes menu_in_game");
    }

    SDL_Rect pos_image_return;
    pos_image_return.x = pos_valider.x + pos_valider.w + pos_2points_valider.w + (*game->WINDOWWIDTH)*25/1280;
    pos_image_return.y = pos_valider.y + (*game->WINDOWHEIGHT) * 8 / 1280;
    pos_image_return.w = (*game->WINDOWWIDTH) * 50 / 1200;
    pos_image_return.h = pos_valider.h;
    /*-------------------------------------------------------------------------*/

    /*--- Initialization texture "image E" --------------------------------------*/

    surf_image_E = SDL_LoadBMP("src\\image\\touche_E_clavier.bmp");
    if(surf_image_E == NULL)
    {
        SDL_ExitWithError("probleme chargement image touche E clavier dans commandes menu_in_game");
    }

    SDL_Texture* image_E = SDL_CreateTextureFromSurface(game->render, surf_image_E);
    if(image_E == NULL)
    {
        SDL_ExitWithError("probleme texture image touche E clavier dans commandes menu_in_game");
    }

    SDL_Rect pos_image_E;
    pos_image_E.x = pos_interagir.x + pos_interagir.w + pos_2points_interagir.w + (*game->WINDOWWIDTH)*25/1280;
    pos_image_E.y = pos_interagir.y + (*game->WINDOWHEIGHT) * 8 / 1280;
    pos_image_E.w = (*game->WINDOWWIDTH) * 50 / 1200;
    pos_image_E.h = pos_interagir.h;
    /*-------------------------------------------------------------------------*/

    /*--- Creation text " : " ----------------------------------------*/

    surf_2point = TTF_RenderText_Blended(game->police, " : ", blanc);
    if (surf_2point == NULL)
    {
        SDL_ExitWithError("probleme surface : commandes.c");
    }

    SDL_Texture *t_2point = SDL_CreateTextureFromSurface(game->render, surf_2point);
    if (t_2point == NULL)
    {
        SDL_ExitWithError("probleme texture : commandes.c");
    }

    /*----------------------------------------------------------------------------*/

    SDL_Rect pos_texture;
    pos_texture.x = 0;
    pos_texture.y = 0;
    pos_texture.w = (*game->WINDOWWIDTH);
    pos_texture.h = (*game->WINDOWHEIGHT);

        /*--- Main Loop -----------------------------------------------------------*/

    while (commandes_bool && *game->program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                *game->program_launch = SDL_FALSE;
                commandes_bool = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                *echap_relache = SDL_FALSE;
                commandes_bool = SDL_FALSE;
            }

            /*--- End Event to Exit Program --------------------------------------*/


            SDL_RenderClear(game->render);

            SDL_RenderCopy(game->render, texture, NULL, &pos_texture);
            SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
            SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
            SDL_RenderCopy(game->render, commandes, NULL, &pos_commandes);
            SDL_RenderCopy(game->render, retour, NULL, &pos_retour);
            SDL_RenderCopy(game->render, deplacer_selectionner, NULL, &pos_deplacer_selectionner);
            SDL_RenderCopy(game->render, ouv_fer_menu, NULL, &pos_ouv_fer_menu);
            SDL_RenderCopy(game->render, valider, NULL, &pos_valider);
            SDL_RenderCopy(game->render, interagir, NULL, &pos_interagir);
            SDL_RenderCopy(game->render, image_fleche, NULL, &pos_image_fleche);
            SDL_RenderCopy(game->render, image_echap, NULL, &pos_image_echap);
            SDL_RenderCopy(game->render, image_return, NULL, &pos_image_return);
            SDL_RenderCopy(game->render, image_E, NULL, &pos_image_E);
            SDL_RenderCopy(game->render, t_2point, NULL, &pos_2points_deplacer_select);
            SDL_RenderCopy(game->render, t_2point, NULL, &pos_2points_ouv_fer_menu);
            SDL_RenderCopy(game->render, t_2point, NULL, &pos_2points_valider);
            SDL_RenderCopy(game->render, t_2point, NULL, &pos_2points_interagir);
            SDL_RenderPresent(game->render);


            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {
                    commandes_bool = SDL_FALSE;
            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_commandes);
    SDL_FreeSurface(surf_retour);
    SDL_FreeSurface(surf_deplacer_selectionner);
    SDL_FreeSurface(surf_ouv_fer_menu);
    SDL_FreeSurface(surf_valider);
    SDL_FreeSurface(surf_interagir);
    SDL_FreeSurface(surf_image_fleche);
    SDL_FreeSurface(surf_image_echap);
    SDL_FreeSurface(surf_image_return);
    SDL_FreeSurface(surf_image_E);
    SDL_FreeSurface(surf_2point);

    SDL_DestroyTexture(commandes);
    SDL_DestroyTexture(retour);
    SDL_DestroyTexture(cadre);
    SDL_DestroyTexture(deplacer_selectionner);
    SDL_DestroyTexture(ouv_fer_menu);
    SDL_DestroyTexture(valider);
    SDL_DestroyTexture(interagir);
    SDL_DestroyTexture(image_fleche);
    SDL_DestroyTexture(image_echap);
    SDL_DestroyTexture(image_return);
    SDL_DestroyTexture(image_E);
    SDL_DestroyTexture(t_2point);
    SDL_DestroyTexture(fond_cadre);

    /*--- End Free Memory --------------------------------------------------------*/

}
