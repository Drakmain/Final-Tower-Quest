#include <stdio.h>
#include <stdlib.h>

#include "..\lib\sauvegarder.h"
#include "..\lib\character.h"



void sauvegarde(game_t * game, character_t * character, SDL_Texture * texture_render_menu_ig){

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    SDL_Surface * surf_cadre = NULL, *surf_confirmation = NULL, *surf_choix_oui = NULL, *surf_choix_non = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool sauvegarde_bool = SDL_TRUE;
    SDL_Event event;

    int selection = 0;

    /*---texture "cadre"--------------------------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_texte_confirmation_sauvegarde.bmp");
    if(surf_cadre == NULL){
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture* cadre = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if(cadre == NULL){
        SDL_ExitWithError("probleme texture nouvelle partie menu d'accueil");
    }

    SDL_Rect pos_cadre;
    pos_cadre.w = (*game->WINDOWWIDTH)*900/1280;
    pos_cadre.h = (*game->WINDOWHEIGHT)*200/720;
    pos_cadre.x = (*game->WINDOWWIDTH)/2 - pos_cadre.w/2;
    pos_cadre.y = (*game->WINDOWHEIGHT)/2 - pos_cadre.h/2;
    /*------------------------------------------------------------------------------------*/

    /*---texture fond--------------------------------------------------------*/

    SDL_Texture* fond_cadre = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre.w, pos_cadre.h);
    if(fond_cadre == NULL){
        SDL_ExitWithError("probleme texture options");
    }

    SDL_Rect pos_fond_cadre;
    pos_fond_cadre.x = pos_cadre.x;
    pos_fond_cadre.y = pos_cadre.y;
    pos_fond_cadre.w = pos_cadre.w;
    pos_fond_cadre.h = pos_cadre.h;

    SDL_Rect rect_fond_cadre;
    rect_fond_cadre.x = (*game->WINDOWWIDTH)*12/1280;
    rect_fond_cadre.y = (*game->WINDOWHEIGHT)*12/720;
    rect_fond_cadre.w = pos_fond_cadre.w - 2*rect_fond_cadre.x;
    rect_fond_cadre.h = pos_fond_cadre.h - 2*rect_fond_cadre.y;

    SDL_SetRenderDrawColor(game->render,0,0,0, 240);
    SDL_SetRenderTarget(game->render,fond_cadre);
    SDL_SetTextureBlendMode(fond_cadre, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre);
    SDL_SetRenderTarget(game->render,NULL);
    /*------------------------------------------------------------------------------------*/

    /*--- Creation text "texte de confirmation" ----------------------------------------*/
    surf_confirmation = TTF_RenderText_Blended(game->police, "Etes-vous sur de vouloir ecraser vos donnees precedentes ?", blanc);
    if(surf_confirmation == NULL){
        SDL_ExitWithError("probleme surface texte de confirmation sauvegarde menu in game");
    }

    SDL_Texture* confirmation = SDL_CreateTextureFromSurface(game->render, surf_confirmation);
    if(confirmation == NULL){
        SDL_ExitWithError("probleme texture texte de confirmation sauvegarde menu in game");
    }

    SDL_Rect pos_confirmation;
    pos_confirmation.w = pos_cadre.w - 50;
    pos_confirmation.h = (*game->WINDOWHEIGHT)*50/720;
    pos_confirmation.x = (*game->WINDOWWIDTH)/2 - pos_confirmation.w/2;
    pos_confirmation.y = pos_cadre.y + 22;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "oui" ----------------------------------------*/
    surf_choix_oui = TTF_RenderText_Blended(game->police, "Oui", rouge);
    if(surf_choix_oui == NULL){
        SDL_ExitWithError("probleme surface choix oui sauvegarde menu in game");
    }

    SDL_Texture* choix_oui = SDL_CreateTextureFromSurface(game->render, surf_choix_oui);
    if(choix_oui == NULL){
        SDL_ExitWithError("probleme texture choix oui sauvegarde menu in game");
    }

    SDL_Rect pos_choix_oui;
    pos_choix_oui.w = pos_confirmation.w/59*3;
    pos_choix_oui.h = (*game->WINDOWHEIGHT)*50/720;
    pos_choix_oui.x = (*game->WINDOWWIDTH)/2 - pos_choix_oui.w;
    pos_choix_oui.y = pos_cadre.y + 75;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "non" ----------------------------------------*/
    surf_choix_non = TTF_RenderText_Blended(game->police, "Non", blanc);
    if(surf_choix_non == NULL){
        SDL_ExitWithError("probleme surface choix non sauvegarde menu in game");
    }

    SDL_Texture* choix_non = SDL_CreateTextureFromSurface(game->render, surf_choix_non);
    if(choix_non == NULL){
        SDL_ExitWithError("probleme texture choix non sauvegarde menu in game");
    }

    SDL_Rect pos_choix_non;
    pos_choix_non.w = pos_confirmation.w/59*3;
    pos_choix_non.h = (*game->WINDOWHEIGHT)*50/720;
    pos_choix_non.x = (*game->WINDOWWIDTH)/2 - pos_choix_non.w;
    pos_choix_non.y = pos_cadre.y + 125;

    /*----------------------------------------------------------------------------*/

    SDL_Rect pos_texture_render_menu_ig;
    pos_texture_render_menu_ig.x = 0;
    pos_texture_render_menu_ig.y = 0;
    pos_texture_render_menu_ig.w = (*game->WINDOWWIDTH);
    pos_texture_render_menu_ig.h = (*game->WINDOWHEIGHT);


    SDL_RenderClear(game->render);
    SDL_RenderCopy(game->render, texture_render_menu_ig, NULL, &pos_texture_render_menu_ig);
    SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
    SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
    SDL_RenderCopy(game->render, confirmation, NULL, &pos_confirmation);
    SDL_RenderCopy(game->render, choix_oui, NULL, &pos_choix_oui);
    SDL_RenderCopy(game->render, choix_non, NULL, &pos_choix_non);
    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    while (sauvegarde_bool && (*game->program_launch))
    {

        while (SDL_PollEvent(&event))
        {


            /*--- Event pour selectionner ------------------------------------------*/

            if (keyState[SDL_SCANCODE_DOWN] && event.type == SDL_KEYDOWN){
                selection++;
            }

            if (keyState[SDL_SCANCODE_UP] && event.type == SDL_KEYDOWN){
                selection--;
            }

            /*--- End Event pour selectionner --------------------------------------*/

            if(selection < 0)selection = 1;
            selection %=2;

            if(selection == 0){
                surf_choix_oui = TTF_RenderText_Blended(game->police, "Oui", rouge);
                surf_choix_non = TTF_RenderText_Blended(game->police, "Non", blanc);
            }

            if(selection == 1){
                surf_choix_oui = TTF_RenderText_Blended(game->police, "Oui", blanc);
                surf_choix_non = TTF_RenderText_Blended(game->police, "Non", rouge);
            }

            choix_oui = SDL_CreateTextureFromSurface(game->render, surf_choix_oui);
            choix_non = SDL_CreateTextureFromSurface(game->render, surf_choix_non);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN){
                if(selection == 0);
                if(selection == 1);
            }
            SDL_RenderClear(game->render);
            SDL_RenderCopy(game->render, texture_render_menu_ig, NULL, &pos_texture_render_menu_ig);
            SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
            SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
            SDL_RenderCopy(game->render, confirmation, NULL, &pos_confirmation);
            SDL_RenderCopy(game->render, choix_oui, NULL, &pos_choix_oui);
            SDL_RenderCopy(game->render, choix_non, NULL, &pos_choix_non);
            SDL_RenderPresent(game->render);

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                (*game->program_launch) = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                sauvegarde_bool = SDL_FALSE;
            }

            /*--- End Event to Exit Program --------------------------------------*/
        }

    }
    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/
    SDL_FreeSurface(surf_cadre);
    SDL_FreeSurface(surf_confirmation);
    SDL_FreeSurface(surf_choix_oui);
    SDL_FreeSurface(surf_choix_non);

    SDL_DestroyTexture(confirmation);
    SDL_DestroyTexture(cadre);
    SDL_DestroyTexture(fond_cadre);
    SDL_DestroyTexture(choix_oui);
    SDL_DestroyTexture(choix_non);

    /*--- End Free Memory --------------------------------------------------------*/
}
