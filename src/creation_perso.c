#include <stdio.h>
#include <stdlib.h>

#include "creation_perso.h"

/*!
 *
 * \file creation_perso.c
 * \brief Creation d'un perosnnage.
 * \author Alexis BOUFFARD
 * \date 12/03/21
 *
 */


/*!
 *
 * \fn creation_perso(game_t * game, char * actual_save)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param actual_save A FINIR.
 *
 */

extern
void creation_perso(game_t * game, char * actual_save){

    /*--- Initialization variable ----------------------------------------------------*/

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    SDL_Surface * surf_guerrier = NULL, * surf_mage = NULL, * surf_assassin = NULL, * surf_fond = NULL, * surf_spriteGuerrier = NULL, * surf_spriteMage = NULL, * surf_spriteAssassin = NULL, * surf_cadre = NULL;
    SDL_Surface *surf_desc1 = NULL, *surf_desc2 = NULL, *surf_desc3 = NULL, *surf_desc4 = NULL, *surf_desc5 = NULL;

    SDL_bool crea_perso_bool = SDL_TRUE;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    int selection = 0;

    /*--- End Initialization variable --------------------------------------------*/


    /*--- Initialization text "Guerrier" -----------------------------------------*/

    surf_guerrier = TTF_RenderText_Blended(game->police, "Guerrier", rouge);
    if(surf_guerrier == NULL)
    {
        SDL_ExitWithError("Probleme surface guerrier");
    }

    SDL_Texture * guerrier = SDL_CreateTextureFromSurface(game->render, surf_guerrier);
    if(guerrier == NULL)
    {
        SDL_ExitWithError("Probleme texture guerrier");
    }

    SDL_Rect pos_guerrier;
    pos_guerrier.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/2.2;
    pos_guerrier.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5;
    pos_guerrier.w = (*game->WINDOWWIDTH)/7;
    pos_guerrier.h = (*game->WINDOWHEIGHT)/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization text "Mage" ---------------------------------------------*/

    surf_mage = TTF_RenderText_Blended(game->police, "Mage", blanc);
    if(surf_mage == NULL)
    {
        SDL_ExitWithError("probleme surface mage");
    }
    SDL_Texture* mage = SDL_CreateTextureFromSurface(game->render, surf_mage);
    if(mage == NULL)
    {
        SDL_ExitWithError("probleme texture mage");
    }

    SDL_Rect pos_mage;
    pos_mage.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/2.2;
    pos_mage.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/29;
    pos_mage.w = (*game->WINDOWWIDTH)/11;
    pos_mage.h = (*game->WINDOWHEIGHT)/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization text "Assassin" ----------------------------------------*/

    surf_assassin = TTF_RenderText_Blended(game->police, "Assassin", blanc);
    if(surf_assassin == NULL)
    {
        SDL_ExitWithError("probleme surface assassin");
    }

    SDL_Texture* assassin = SDL_CreateTextureFromSurface(game->render, surf_assassin);
    if(assassin == NULL)
    {
        SDL_ExitWithError("probleme texture assassin");
    }

    SDL_Rect pos_assassin;
    pos_assassin.x = (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH)/2.2;
    pos_assassin.y = (*game->WINDOWHEIGHT)/2 + (*game->WINDOWWIDTH)/7.5;
    pos_assassin.w = (*game->WINDOWWIDTH)/7;
    pos_assassin.h = (*game->WINDOWHEIGHT)/13.5;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "Guerrier" --------------------------------------*/

    surf_spriteGuerrier = SDL_LoadBMP("src\\tileset\\PJ\\guerrier_frame.bmp");
    SDL_SetColorKey(surf_spriteGuerrier, SDL_TRUE, SDL_MapRGB(surf_spriteGuerrier->format, 255,255,255));
    if(surf_spriteGuerrier == NULL)
    {
        SDL_ExitWithError("probleme chargement sprite du guerrier");
    }

    SDL_Texture* spriteGuerrier = SDL_CreateTextureFromSurface(game->render, surf_spriteGuerrier);
    if(spriteGuerrier == NULL)
    {
        SDL_ExitWithError("probleme texture sprite du guerrier");
    }

    SDL_Rect pos_spriteGuerrier;
    pos_spriteGuerrier.x = (*game->WINDOWWIDTH)/2 + (*game->WINDOWWIDTH)/15;
    pos_spriteGuerrier.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5;
    pos_spriteGuerrier.w = (*game->WINDOWWIDTH) * 144 /1200;
    pos_spriteGuerrier.h = (*game->WINDOWHEIGHT) * 144 /675;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "Mage" ------------------------------------------*/

    surf_spriteMage = SDL_LoadBMP("src\\tileset\\PJ\\mage_frame.bmp");
    SDL_SetColorKey(surf_spriteMage, SDL_TRUE, SDL_MapRGB(surf_spriteMage->format, 255,255,255));
    if(surf_spriteMage == NULL)
    {
        SDL_ExitWithError("probleme chargement sprite du mage");
    }

    SDL_Texture* spriteMage = SDL_CreateTextureFromSurface(game->render, surf_spriteMage);
    if(spriteMage == NULL)
    {
        SDL_ExitWithError("probleme texture sprite du mage");
    }

    SDL_Rect pos_spriteMage;
    pos_spriteMage.x = (*game->WINDOWWIDTH)/2 + (*game->WINDOWWIDTH)/15;
    pos_spriteMage.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/5;
    pos_spriteMage.w = (*game->WINDOWWIDTH) * 144 /1200;
    pos_spriteMage.h = (*game->WINDOWHEIGHT) * 144 /675;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization texture "Assassin" --------------------------------------*/

    surf_spriteAssassin = SDL_LoadBMP("src\\tileset\\PJ\\assassin_frame.bmp");
    SDL_SetColorKey(surf_spriteAssassin, SDL_TRUE, SDL_MapRGB(surf_spriteAssassin->format, 255,255,255));
    if(surf_spriteAssassin == NULL)
    {
        SDL_ExitWithError("probleme chargement sprite du assassin");
    }

    SDL_Texture* spriteAssassin = SDL_CreateTextureFromSurface(game->render, surf_spriteAssassin);
    if(spriteAssassin == NULL)
    {
        SDL_ExitWithError("probleme texture sprite du assassin");
    }

    SDL_Rect pos_spriteAssassin;
    pos_spriteAssassin.x = (*game->WINDOWWIDTH)/2 + (*game->WINDOWWIDTH)/15;
    pos_spriteAssassin.y = (*game->WINDOWHEIGHT)/2 - (*game->WINDOWWIDTH)/4.6;
    pos_spriteAssassin.w = (*game->WINDOWWIDTH) * 108 /1200;
    pos_spriteAssassin.h = (*game->WINDOWHEIGHT) * 180 /675;

    /*----------------------------------------------------------------------------*/


    /*--- Initialization background image ----------------------------------------*/

    surf_fond = SDL_LoadBMP("src\\image\\ciel_sans_lune.bmp");
    if(surf_fond == NULL)
    {
        SDL_ExitWithError("probleme chargement image fond menu de creation de personnage");
    }

    SDL_Texture* fond = SDL_CreateTextureFromSurface(game->render, surf_fond);
    if(fond == NULL)
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

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_desc.bmp");
    if(surf_cadre == NULL)
    {
        SDL_ExitWithError("probleme chargement image cadre");
    }

    SDL_Texture* cadre_desc = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if(cadre_desc == NULL)
    {
        SDL_ExitWithError("probleme texture cadre_desc");
    }

    SDL_Rect pos_cadre_desc;
    pos_cadre_desc.x = (*game->WINDOWHEIGHT) * 400 /675;
    pos_cadre_desc.y = (*game->WINDOWHEIGHT) * 325 /675;
    pos_cadre_desc.w = (*game->WINDOWWIDTH) * 700 /1200;
    pos_cadre_desc.h = (*game->WINDOWHEIGHT) * 290 /675;

    /*----------------------------------------------------------------------------*/


    /*--- Creation texture background "cadre" ------------------------------------*/

    SDL_Texture* fond_cadre_desc = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos_cadre_desc.w, pos_cadre_desc.h);
    if(fond_cadre_desc == NULL)
    {
        SDL_ExitWithError("probleme texture fond_cadre_desc");
    }

    SDL_Rect pos_fond_cadre_desc;
    pos_fond_cadre_desc.x = pos_cadre_desc.x;
    pos_fond_cadre_desc.y = pos_cadre_desc.y;
    pos_fond_cadre_desc.w = pos_cadre_desc.w;
    pos_fond_cadre_desc.h = pos_cadre_desc.h;

    SDL_Rect rect_fond_cadre_desc;
    rect_fond_cadre_desc.x = pos_fond_cadre_desc.w*12/1600 ;
    rect_fond_cadre_desc.y = pos_fond_cadre_desc.h*12/900;
    rect_fond_cadre_desc.w = pos_fond_cadre_desc.w - 2*pos_fond_cadre_desc.w*12/1600;
    rect_fond_cadre_desc.h = pos_fond_cadre_desc.h - 2*pos_fond_cadre_desc.h*12/900;

    SDL_SetRenderDrawColor(game->render,0,0,0, 200);
    SDL_SetRenderTarget(game->render, fond_cadre_desc);
    SDL_SetTextureBlendMode(fond_cadre_desc, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_fond_cadre_desc);
    SDL_SetRenderTarget(game->render,NULL);

    /*----------------------------------------------------------------------------*/


    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
    SDL_RenderCopy(game->render, guerrier, NULL, &pos_guerrier);
    SDL_RenderCopy(game->render, mage, NULL, &pos_mage);
    SDL_RenderCopy(game->render, assassin, NULL, &pos_assassin);
    SDL_RenderCopy(game->render, spriteGuerrier, NULL, &pos_spriteGuerrier);
    SDL_RenderCopy(game->render, fond_cadre_desc, NULL, &pos_fond_cadre_desc);
    SDL_RenderCopy(game->render, cadre_desc, NULL, &pos_cadre_desc);

    SDL_RenderPresent(game->render);


    /*--- Main Loop --------------------------------------------------------------*/

    while (crea_perso_bool && *game->program_launch)
    {

        while (SDL_PollEvent(&event))
        {

            /*--- Event to Exit Program -----------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                *game->program_launch = SDL_FALSE;
                crea_perso_bool = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                crea_perso_bool = SDL_FALSE;
            }

            /*--- End Event to Exit Program -------------------------------------------*/


            /*--- Event pour selectionner ---------------------------------------------*/

            if (keyState[SDL_SCANCODE_DOWN] && event.type == SDL_KEYDOWN)
            {
                selection++;
            }

            if (keyState[SDL_SCANCODE_UP] && event.type == SDL_KEYDOWN)
            {
                selection--;
            }

            /*--- End Event pour selectionner -----------------------------------------*/


            SDL_RenderCopy(game->render, fond, NULL, &pos_fond);
            SDL_RenderCopy(game->render, guerrier, NULL, &pos_guerrier);
            SDL_RenderCopy(game->render, mage, NULL, &pos_mage);
            SDL_RenderCopy(game->render, assassin, NULL, &pos_assassin);
            SDL_RenderCopy(game->render, fond_cadre_desc, NULL, &pos_fond_cadre_desc);
            SDL_RenderCopy(game->render, cadre_desc, NULL, &pos_cadre_desc);

            if(selection < 0)selection = 2;
            selection %=3;

            if(selection == 0)
            {

                surf_guerrier = TTF_RenderText_Blended(game->police, "Guerrier", rouge);
                surf_mage = TTF_RenderText_Blended(game->police, "Mage", blanc);
                surf_assassin = TTF_RenderText_Blended(game->police, "Assassin", blanc);

                SDL_RenderCopy(game->render, spriteGuerrier, NULL, &pos_spriteGuerrier);

                /*---Description Guerrier ----------------------------------------*/

                surf_desc1 = TTF_RenderText_Blended(game->police, "Espiegle et temeraire, rien ne l'arrete. Le guerrier est", blanc);
                SDL_Texture* desc1 = SDL_CreateTextureFromSurface(game->render, surf_desc1);
                SDL_Rect pos_desc1;
                pos_desc1.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc1.y = (*game->WINDOWHEIGHT)/2;
                pos_desc1.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc1.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc2 = TTF_RenderText_Blended(game->police, "un heros de champ de bataille, habile, specialise dans le", blanc);
                SDL_Texture* desc2 = SDL_CreateTextureFromSurface(game->render, surf_desc2);
                SDL_Rect pos_desc2;
                pos_desc2.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc2.y = (*game->WINDOWHEIGHT) * 325 /570;
                pos_desc2.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc2.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc3 = TTF_RenderText_Blended(game->police, "combat rapproche, et capable de maitriser differents types", blanc);
                SDL_Texture* desc3 = SDL_CreateTextureFromSurface(game->render, surf_desc3);
                SDL_Rect pos_desc3;
                pos_desc3.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc3.y = (*game->WINDOWHEIGHT) * 325 /508;
                pos_desc3.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc3.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc4 = TTF_RenderText_Blended(game->police, "d'armes au cours d'un entrainement exigeant et intense, ce", blanc);
                SDL_Texture* desc4 = SDL_CreateTextureFromSurface(game->render, surf_desc4);
                SDL_Rect pos_desc4;
                pos_desc4.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc4.y = (*game->WINDOWHEIGHT) * 325 /460;
                pos_desc4.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc4.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc5 = TTF_RenderText_Blended(game->police, "qui fait de lui un redoutable combattant.                ", blanc);
                SDL_Texture* desc5 = SDL_CreateTextureFromSurface(game->render, surf_desc5);
                SDL_Rect pos_desc5;
                pos_desc5.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc5.y = (*game->WINDOWHEIGHT) * 325 /418;
                pos_desc5.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc5.h = (*game->WINDOWHEIGHT)/15;

                SDL_RenderCopy(game->render, desc1, NULL, &pos_desc1);
                SDL_RenderCopy(game->render, desc2, NULL, &pos_desc2);
                SDL_RenderCopy(game->render, desc3, NULL, &pos_desc3);
                SDL_RenderCopy(game->render, desc4, NULL, &pos_desc4);
                SDL_RenderCopy(game->render, desc5, NULL, &pos_desc5);


                /*---End Description Guerrier ----------------------------------------*/

            }

            if(selection == 1)
            {
                surf_guerrier = TTF_RenderText_Blended(game->police, "Guerrier", blanc);
                surf_mage = TTF_RenderText_Blended(game->police, "Mage", rouge);
                surf_assassin = TTF_RenderText_Blended(game->police, "Assassin", blanc);

                SDL_RenderCopy(game->render, spriteMage, NULL, &pos_spriteMage);

                /*---Description Mage ----------------------------------------*/

                surf_desc1 = TTF_RenderText_Blended(game->police, "Feu, glace, terre et air, il n'y a aucun element que le", blanc);
                SDL_Texture* desc1 = SDL_CreateTextureFromSurface(game->render, surf_desc1);
                SDL_Rect pos_desc1;
                pos_desc1.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc1.y = (*game->WINDOWHEIGHT)/2;
                pos_desc1.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc1.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc2 = TTF_RenderText_Blended(game->police, "mage ne sait maitriser. Apres de nombreuses decennies", blanc);
                SDL_Texture* desc2 = SDL_CreateTextureFromSurface(game->render, surf_desc2);
                SDL_Rect pos_desc2;
                pos_desc2.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc2.y = (*game->WINDOWHEIGHT) * 325 /570;
                pos_desc2.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc2.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc3 = TTF_RenderText_Blended(game->police, "a perfectionner l'art de la magie, aucun monstre ne", blanc);
                SDL_Texture* desc3 = SDL_CreateTextureFromSurface(game->render, surf_desc3);
                SDL_Rect pos_desc3;
                pos_desc3.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc3.y = (*game->WINDOWHEIGHT) * 325 /508;
                pos_desc3.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc3.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc4 = TTF_RenderText_Blended(game->police, "pourra s'opposer a sa puissance colossal.                 ", blanc);
                SDL_Texture* desc4 = SDL_CreateTextureFromSurface(game->render, surf_desc4);
                SDL_Rect pos_desc4;
                pos_desc4.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc4.y = (*game->WINDOWHEIGHT) * 325 /460;
                pos_desc4.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc4.h = (*game->WINDOWHEIGHT)/13.5;

                SDL_RenderCopy(game->render, desc1, NULL, &pos_desc1);
                SDL_RenderCopy(game->render, desc2, NULL, &pos_desc2);
                SDL_RenderCopy(game->render, desc3, NULL, &pos_desc3);
                SDL_RenderCopy(game->render, desc4, NULL, &pos_desc4);

                /*---End Description Mage ----------------------------------------*/

            }

            if(selection == 2)
            {
                surf_guerrier = TTF_RenderText_Blended(game->police, "Guerrier", blanc);
                surf_mage = TTF_RenderText_Blended(game->police, "Mage", blanc);
                surf_assassin = TTF_RenderText_Blended(game->police, "Assassin", rouge);

                SDL_RenderCopy(game->render, spriteAssassin, NULL, &pos_spriteAssassin);

                /*---Description Assassin ----------------------------------------*/

                surf_desc1 = TTF_RenderText_Blended(game->police, "Tapis dans l'ombre, l'assassin est comme un monstre dans", blanc);
                SDL_Texture* desc1 = SDL_CreateTextureFromSurface(game->render, surf_desc1);
                SDL_Rect pos_desc1;
                pos_desc1.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc1.y = (*game->WINDOWHEIGHT)/2;
                pos_desc1.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc1.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc2 = TTF_RenderText_Blended(game->police, "la nuit, qui observe, qui ecoute, qui chasse. Il peut se", blanc);
                SDL_Texture* desc2 = SDL_CreateTextureFromSurface(game->render, surf_desc2);
                SDL_Rect pos_desc2;
                pos_desc2.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc2.y = (*game->WINDOWHEIGHT) * 325 /570;
                pos_desc2.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc2.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc3 = TTF_RenderText_Blended(game->police, "camoufler tel le cameleon, et chasser tel le predateur qui", blanc);
                SDL_Texture* desc3 = SDL_CreateTextureFromSurface(game->render, surf_desc3);
                SDL_Rect pos_desc3;
                pos_desc3.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc3.y = (*game->WINDOWHEIGHT) * 325 /508;
                pos_desc3.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc3.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc4 = TTF_RenderText_Blended(game->police, "a repere sa proie...sa victime mourra avant de se rendre", blanc);
                SDL_Texture* desc4 = SDL_CreateTextureFromSurface(game->render, surf_desc4);
                SDL_Rect pos_desc4;
                pos_desc4.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc4.y = (*game->WINDOWHEIGHT) * 325 /460;
                pos_desc4.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc4.h = (*game->WINDOWHEIGHT)/13.5;

                surf_desc5 = TTF_RenderText_Blended(game->police, "compte ce qui lui arrive.                ", blanc);
                SDL_Texture* desc5 = SDL_CreateTextureFromSurface(game->render, surf_desc5);
                SDL_Rect pos_desc5;
                pos_desc5.x = (*game->WINDOWHEIGHT) * 400 /645;
                pos_desc5.y = (*game->WINDOWHEIGHT) * 325 /418;
                pos_desc5.w = (*game->WINDOWWIDTH)/1.8;
                pos_desc5.h = (*game->WINDOWHEIGHT)/15;

                SDL_RenderCopy(game->render, desc1, NULL, &pos_desc1);
                SDL_RenderCopy(game->render, desc2, NULL, &pos_desc2);
                SDL_RenderCopy(game->render, desc3, NULL, &pos_desc3);
                SDL_RenderCopy(game->render, desc4, NULL, &pos_desc4);
                SDL_RenderCopy(game->render, desc5, NULL, &pos_desc5);


                /*---End Description Assassin ----------------------------------------*/

            }

            guerrier = SDL_CreateTextureFromSurface(game->render, surf_guerrier);
            mage = SDL_CreateTextureFromSurface(game->render, surf_mage);
            assassin = SDL_CreateTextureFromSurface(game->render, surf_assassin);

            SDL_RenderPresent(game->render);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN)
            {

                if(selection == 0)
                {

                }

                if(selection == 1)
                {

                }
                
                if(selection == 2)
                {

                }

            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_guerrier);
    SDL_FreeSurface(surf_mage);
    SDL_FreeSurface(surf_assassin);
    SDL_FreeSurface(surf_fond);
    SDL_FreeSurface(surf_spriteGuerrier);
    SDL_FreeSurface(surf_spriteMage);
    SDL_FreeSurface(surf_spriteAssassin);


    SDL_DestroyTexture(guerrier);
    SDL_DestroyTexture(mage);
    SDL_DestroyTexture(assassin);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(spriteGuerrier);
    SDL_DestroyTexture(spriteMage);
    SDL_DestroyTexture(spriteAssassin);

    /*--- End Free Memory --------------------------------------------------------*/

}
