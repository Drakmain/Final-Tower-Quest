#include <stdio.h>
#include <stdlib.h>

#include "..\lib\caracteristiques.h"
#include "..\lib\character.h"
#include "..\lib\texte_confirmation.h"

/*!
 *
 * \file caracteristiques.c
 * \brief A FINIR.
 * \author Jeremy BOURGOUIN
 *
 */


/*!
 *
 * \fn caracteristiques(game_t * game, character_t * character, SDL_Texture * texture_render_menu_ig, SDL_bool *echap_relache)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * \param texture_render_menu_ig A FINIR.
 * \param echap_relache A FINIR.
 *
 */

void caracteristiques(game_t * game, character_t * character, SDL_Texture * texture_render_menu_ig, SDL_bool *echap_relache){

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    SDL_Surface * surf_cadre = NULL, *surf_caracteristiques = NULL, *surf_retour = NULL, *surf_vitalite = NULL, *surf_force = NULL, *surf_2point = NULL, *surf_intell = NULL, *surf_agi = NULL, *surf_def = NULL, *surf_point_dispo = NULL, *surf_nb_vitalite = NULL, *surf_nb_force = NULL, *surf_nb_intell = NULL, *surf_nb_agi = NULL, *surf_nb_def = NULL, *surf_nb_point_dispo = NULL;
    SDL_Surface *surf_valider = NULL, *surf_fleche = NULL;
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool carac_bool = SDL_TRUE, select_ret_val = SDL_TRUE;
    SDL_Event event;

    int selection = 0;
    int points_uti_vitalite = 0, points_uti_force = 0, points_uti_intell = 0, points_uti_agi = 0, points_uti_def = 0;;
    int character_vitalite = character->vitalite;
    int character_force = character->force;
    int character_intell = character->intelligence;
    int character_agi = character->agilite;
    int character_def = character->defense;
    int character_points_dispo = character->points_dispo;
    /*---texture "cadre"--------------------------------------------------------*/

    surf_cadre = SDL_LoadBMP("src\\image\\cadre_caracteristiques.bmp");
    if(surf_cadre == NULL){
        SDL_ExitWithError("probleme chargement image fond menu accueil");
    }

    SDL_Texture* cadre = SDL_CreateTextureFromSurface(game->render, surf_cadre);
    if(cadre == NULL){
        SDL_ExitWithError("probleme texture nouvelle partie menu d'accueil");
    }

    SDL_Rect pos_cadre;
    pos_cadre.w = (*game->WINDOWWIDTH)*900/1280;
    pos_cadre.h = (*game->WINDOWHEIGHT)*600/720;
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

    /*--- Creation text "caracteristiques" ----------------------------------------*/

    surf_caracteristiques = TTF_RenderText_Blended(game->police, "CARACTERISTIQUES", blanc);
    if(surf_caracteristiques == NULL){
        SDL_ExitWithError("probleme surface caracteristiques caracteristiques.c");
    }

    SDL_Texture* caracteristiques = SDL_CreateTextureFromSurface(game->render, surf_caracteristiques);
    if(caracteristiques == NULL){
        SDL_ExitWithError("probleme texture caracteristiques caracteristiques.c");
    }

    SDL_Rect pos_caracteristiques;
    pos_caracteristiques.w = (*game->WINDOWWIDTH)*344/1200;
    pos_caracteristiques.h = (*game->WINDOWHEIGHT)*50/720;
    pos_caracteristiques.x = (*game->WINDOWWIDTH)/2 - pos_caracteristiques.w/2  ;
    pos_caracteristiques.y = pos_cadre.y + rect_fond_cadre.y + (*game->WINDOWHEIGHT)*15/720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "Retour" ----------------------------------------*/

    surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
    if(surf_retour == NULL){
        SDL_ExitWithError("probleme surface retour caracteristiques.c");
    }

    SDL_Texture* retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
    if(retour == NULL){
        SDL_ExitWithError("probleme texture retour caracteristiques.c");
    }

    SDL_Rect pos_retour;
    pos_retour.w = (*game->WINDOWWIDTH)*129/1200;
    pos_retour.h = (*game->WINDOWHEIGHT)*50/720;
    pos_retour.x = pos_cadre.x + rect_fond_cadre.x + (*game->WINDOWWIDTH)*15/1280 ;
    pos_retour.y = pos_cadre.y + pos_cadre.h - rect_fond_cadre.y - pos_retour.h - (*game->WINDOWHEIGHT)*15/720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "Valider" ----------------------------------------*/

    surf_valider = TTF_RenderText_Blended(game->police, "Valider", blanc);
    if(surf_valider == NULL){
        SDL_ExitWithError("probleme surface valider caracteristiques.c");
    }

    SDL_Texture* valider = SDL_CreateTextureFromSurface(game->render, surf_valider);
    if(valider == NULL){
        SDL_ExitWithError("probleme texture valider caracteristiques.c");
    }

    SDL_Rect pos_valider;
    pos_valider.w = (*game->WINDOWWIDTH)*150.5/1200;
    pos_valider.h = (*game->WINDOWHEIGHT)*50/720;
    pos_valider.x = pos_cadre.x + pos_cadre.w - rect_fond_cadre.x - pos_valider.w - (*game->WINDOWWIDTH)*15/1280 ;
    pos_valider.y = pos_retour.y;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "Force" ----------------------------------------*/

    surf_2point = TTF_RenderText_Blended(game->police, " : ", blanc);
    if(surf_2point == NULL){
        SDL_ExitWithError("probleme surface : caracteristiques.c");
    }

    SDL_Texture* t_2point = SDL_CreateTextureFromSurface(game->render, surf_2point);
    if(t_2point == NULL){
        SDL_ExitWithError("probleme texture : caracteristiques.c");
    }
    /*----------------------------------------------------------------------------*/

    /*--- Creation text "Vitalite" ----------------------------------------*/

    surf_vitalite = TTF_RenderText_Blended(game->police, "Vitalite    ", blanc);
    if(surf_vitalite == NULL){
        SDL_ExitWithError("probleme surface vitalite caracteristiques.c");
    }

    SDL_Texture* vitalite = SDL_CreateTextureFromSurface(game->render, surf_vitalite);
    if(vitalite == NULL){
        SDL_ExitWithError("probleme texture vitalite caracteristiques.c");
    }

    SDL_Rect pos_vitalite;
    pos_vitalite.w = (*game->WINDOWWIDTH)*180/1200;
    pos_vitalite.h = (*game->WINDOWHEIGHT)*50/720;
    pos_vitalite.x = (*game->WINDOWWIDTH)/2 - pos_vitalite.w/2 - (*game->WINDOWWIDTH)*60/1280;
    pos_vitalite.y = pos_caracteristiques.y + pos_caracteristiques.h + (*game->WINDOWHEIGHT)*50/720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "Force" ----------------------------------------*/

    surf_force = TTF_RenderText_Blended(game->police, "Force       ", blanc);
    if(surf_force == NULL){
        SDL_ExitWithError("probleme surface force caracteristiques.c");
    }

    SDL_Texture* force = SDL_CreateTextureFromSurface(game->render, surf_force);
    if(force == NULL){
        SDL_ExitWithError("probleme texture force caracteristiques.c");
    }

    SDL_Rect pos_force;
    pos_force.w = (*game->WINDOWWIDTH)*180/1200;
    pos_force.h = (*game->WINDOWHEIGHT)*50/720;
    pos_force.x = (*game->WINDOWWIDTH)/2 - pos_force.w/2 - (*game->WINDOWWIDTH)*60/1280;
    pos_force.y = pos_vitalite.y + pos_vitalite.h + (*game->WINDOWHEIGHT)*20/720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "intelligence" ----------------------------------------*/

    surf_intell = TTF_RenderText_Blended(game->police, "Intelligence", blanc);
    if(surf_intell == NULL){
        SDL_ExitWithError("probleme surface intell caracteristiques.c");
    }

    SDL_Texture* intell = SDL_CreateTextureFromSurface(game->render, surf_intell);
    if(intell == NULL){
        SDL_ExitWithError("probleme texture intell caracteristiques.c");
    }

    SDL_Rect pos_intell;
    pos_intell.w = (*game->WINDOWWIDTH)*180/1200;
    pos_intell.h = (*game->WINDOWHEIGHT)*50/720;
    pos_intell.x = (*game->WINDOWWIDTH)/2 - pos_intell.w/2 - (*game->WINDOWWIDTH)*60/1280;
    pos_intell.y = pos_force.y + pos_force.h + (*game->WINDOWHEIGHT)*20/720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "agilite" ----------------------------------------*/

    surf_agi = TTF_RenderText_Blended(game->police, "Agilite     ", blanc);
    if(surf_agi == NULL){
        SDL_ExitWithError("probleme surface agi caracteristiques.c");
    }

    SDL_Texture* agi = SDL_CreateTextureFromSurface(game->render, surf_agi);
    if(agi == NULL){
        SDL_ExitWithError("probleme texture agi caracteristiques.c");
    }

    SDL_Rect pos_agi;
    pos_agi.w = (*game->WINDOWWIDTH)*180/1200;
    pos_agi.h = (*game->WINDOWHEIGHT)*50/720;
    pos_agi.x = (*game->WINDOWWIDTH)/2 - pos_agi.w/2 - (*game->WINDOWWIDTH)*60/1280;
    pos_agi.y = pos_intell.y + pos_intell.h + (*game->WINDOWHEIGHT)*20/720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "defense" ----------------------------------------*/

    surf_def = TTF_RenderText_Blended(game->police, "Defense     ", blanc);
    if(surf_def == NULL){
        SDL_ExitWithError("probleme surface def caracteristiques.c");
    }

    SDL_Texture* def = SDL_CreateTextureFromSurface(game->render, surf_def);
    if(def == NULL){
        SDL_ExitWithError("probleme texture def caracteristiques.c");
    }

    SDL_Rect pos_def;
    pos_def.w = (*game->WINDOWWIDTH)*180/1200;
    pos_def.h = (*game->WINDOWHEIGHT)*50/720;
    pos_def.x = (*game->WINDOWWIDTH)/2 - pos_def.w/2 - (*game->WINDOWWIDTH)*60/1280;
    pos_def.y = pos_agi.y + pos_agi.h + (*game->WINDOWHEIGHT)*20/720;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "defense" ----------------------------------------*/

    surf_point_dispo = TTF_RenderText_Blended(game->police, "Point(s) disponible(s)", blanc);
    if(surf_point_dispo == NULL){
        SDL_ExitWithError("probleme surface point dispo caracteristiques.c");
    }

    SDL_Texture* point_dispo = SDL_CreateTextureFromSurface(game->render, surf_point_dispo);
    if(point_dispo == NULL){
        SDL_ExitWithError("probleme texture point dispo caracteristiques.c");
    }

    SDL_Rect pos_point_dispo;
    pos_point_dispo.w = (*game->WINDOWWIDTH)*330/1200;
    pos_point_dispo.h = (*game->WINDOWHEIGHT)*50/720;
    pos_point_dispo.x = (*game->WINDOWWIDTH)/2 - pos_point_dispo.w/2 - (*game->WINDOWWIDTH)*60/1280;
    pos_point_dispo.y = pos_retour.y;

    /*----------------------------------------------------------------------------*/

    SDL_Rect pos_2point_v;
    pos_2point_v.w = (*game->WINDOWWIDTH)*45/1200;
    pos_2point_v.h = (*game->WINDOWHEIGHT)*50/720;
    pos_2point_v.x = pos_vitalite.x + pos_vitalite.w;
    pos_2point_v.y = pos_vitalite.y;

    SDL_Rect pos_2point_f;
    pos_2point_f.w = (*game->WINDOWWIDTH)*45/1200;
    pos_2point_f.h = (*game->WINDOWHEIGHT)*50/720;
    pos_2point_f.x = pos_force.x + pos_force.w;
    pos_2point_f.y = pos_force.y;

    SDL_Rect pos_2point_i;
    pos_2point_i.w = (*game->WINDOWWIDTH)*45/1200;
    pos_2point_i.h = (*game->WINDOWHEIGHT)*50/720;
    pos_2point_i.x = pos_intell.x + pos_intell.w;
    pos_2point_i.y = pos_intell.y;

    SDL_Rect pos_2point_a;
    pos_2point_a.w = (*game->WINDOWWIDTH)*45/1200;
    pos_2point_a.h = (*game->WINDOWHEIGHT)*50/720;
    pos_2point_a.x = pos_agi.x + pos_agi.w;
    pos_2point_a.y = pos_agi.y;

    SDL_Rect pos_2point_d;
    pos_2point_d.w = (*game->WINDOWWIDTH)*45/1200;
    pos_2point_d.h = (*game->WINDOWHEIGHT)*50/720;
    pos_2point_d.x = pos_def.x + pos_def.w;
    pos_2point_d.y = pos_def.y;

    SDL_Rect pos_2point_point_dispo;
    pos_2point_point_dispo.w = (*game->WINDOWWIDTH)*45/1200;
    pos_2point_point_dispo.h = (*game->WINDOWHEIGHT)*50/720;
    pos_2point_point_dispo.x = pos_point_dispo.x + pos_point_dispo.w;
    pos_2point_point_dispo.y = pos_point_dispo.y;

    /*--- Creation text "nb vitalite" ----------------------------------------*/
    char character_nb_vitalite[10];
    itoa(character_vitalite, character_nb_vitalite, 10);

    surf_nb_vitalite = TTF_RenderText_Blended(game->police, character_nb_vitalite, blanc);
    if(surf_nb_vitalite == NULL){
        SDL_ExitWithError("probleme surface nb vitalite caracteristiques.c");
    }

    SDL_Texture* nb_vitalite = SDL_CreateTextureFromSurface(game->render, surf_nb_vitalite);
    if(nb_vitalite == NULL){
        SDL_ExitWithError("probleme texture nb vitalite caracteristiques.c");
    }

    SDL_Rect pos_nb_vitalite;
    pos_nb_vitalite.w = strlen(character_nb_vitalite)*(*game->WINDOWWIDTH)*15/1280;
    pos_nb_vitalite.h = (*game->WINDOWHEIGHT)*50/720;
    pos_nb_vitalite.x = pos_vitalite.x + pos_vitalite.w + pos_2point_v.w + (*game->WINDOWWIDTH)*35/1280;
    pos_nb_vitalite.y = pos_vitalite.y;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nb force" ----------------------------------------*/
    char character_nb_force[10];
    itoa(character_force, character_nb_force, 10);

    surf_nb_force = TTF_RenderText_Blended(game->police, character_nb_force, blanc);
    if(surf_nb_force == NULL){
        SDL_ExitWithError("probleme surface nb force caracteristiques.c");
    }

    SDL_Texture* nb_force = SDL_CreateTextureFromSurface(game->render, surf_nb_force);
    if(nb_force == NULL){
        SDL_ExitWithError("probleme texture nb force caracteristiques.c");
    }

    SDL_Rect pos_nb_force;
    pos_nb_force.w = strlen(character_nb_force)*(*game->WINDOWWIDTH)*15/1280;
    pos_nb_force.h = (*game->WINDOWHEIGHT)*50/720;
    pos_nb_force.x = pos_force.x + pos_force.w + pos_2point_f.w + (*game->WINDOWWIDTH)*35/1280;
    pos_nb_force.y = pos_force.y;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nb intelligence" ----------------------------------------*/
    char character_nb_intell[10];
    itoa(character_intell, character_nb_intell, 10);

    surf_nb_intell = TTF_RenderText_Blended(game->police, character_nb_intell, blanc);
    if(surf_nb_intell == NULL){
        SDL_ExitWithError("probleme surface nb intell caracteristiques.c");
    }

    SDL_Texture* nb_intell = SDL_CreateTextureFromSurface(game->render, surf_nb_intell);
    if(nb_intell == NULL){
        SDL_ExitWithError("probleme texture nb intell caracteristiques.c");
    }

    SDL_Rect pos_nb_intell;
    pos_nb_intell.w = strlen(character_nb_intell)*(*game->WINDOWWIDTH)*15/1280;
    pos_nb_intell.h = (*game->WINDOWHEIGHT)*50/720;
    pos_nb_intell.x = pos_intell.x + pos_intell.w + pos_2point_i.w + (*game->WINDOWWIDTH)*35/1280;
    pos_nb_intell.y = pos_intell.y;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nb agilite" ----------------------------------------*/
    char character_nb_agi[10];
    itoa(character_agi, character_nb_agi, 10);

    surf_nb_agi = TTF_RenderText_Blended(game->police, character_nb_agi, blanc);
    if(surf_nb_agi == NULL){
        SDL_ExitWithError("probleme surface nb agi caracteristiques.c");
    }

    SDL_Texture* nb_agi = SDL_CreateTextureFromSurface(game->render, surf_nb_agi);
    if(nb_agi == NULL){
        SDL_ExitWithError("probleme texture nb agi caracteristiques.c");
    }

    SDL_Rect pos_nb_agi;
    pos_nb_agi.w = strlen(character_nb_agi)*(*game->WINDOWWIDTH)*15/1280;
    pos_nb_agi.h = (*game->WINDOWHEIGHT)*50/720;
    pos_nb_agi.x = pos_agi.x + pos_agi.w + pos_2point_a.w + (*game->WINDOWWIDTH)*35/1280;
    pos_nb_agi.y = pos_agi.y;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nb defense" ----------------------------------------*/
    char character_nb_defense[10];
    itoa(character_def, character_nb_defense, 10);

    surf_nb_def = TTF_RenderText_Blended(game->police, character_nb_defense, blanc);
    if(surf_nb_def == NULL){
        SDL_ExitWithError("probleme surface nb def caracteristiques.c");
    }

    SDL_Texture* nb_def = SDL_CreateTextureFromSurface(game->render, surf_nb_def);
    if(nb_def == NULL){
        SDL_ExitWithError("probleme texture nb def caracteristiques.c");
    }

    SDL_Rect pos_nb_def;
    pos_nb_def.w = strlen(character_nb_defense)*(*game->WINDOWWIDTH)*15/1280;
    pos_nb_def.h = (*game->WINDOWHEIGHT)*50/720;
    pos_nb_def.x = pos_def.x + pos_def.w + pos_2point_d.w + (*game->WINDOWWIDTH)*35/1280;
    pos_nb_def.y = pos_def.y;

    /*----------------------------------------------------------------------------*/

    /*--- Creation text "nb points dispo" ----------------------------------------*/
    char character_nb_points_dispo[10];
    itoa(character_points_dispo, character_nb_points_dispo, 10);

    surf_nb_point_dispo = TTF_RenderText_Blended(game->police, character_nb_points_dispo, blanc);
    if(surf_nb_point_dispo == NULL){
        SDL_ExitWithError("probleme surface nb points dispo caracteristiques.c");
    }

    SDL_Texture* nb_point_dispo = SDL_CreateTextureFromSurface(game->render, surf_nb_point_dispo);
    if(nb_point_dispo == NULL){
        SDL_ExitWithError("probleme texture nb points dispo caracteristiques.c");
    }

    SDL_Rect pos_nb_point_dispo;
    pos_nb_point_dispo.w = strlen(character_nb_points_dispo)*(*game->WINDOWWIDTH)*15/1280;
    pos_nb_point_dispo.h = (*game->WINDOWHEIGHT)*50/720;
    pos_nb_point_dispo.x = pos_point_dispo.x + pos_point_dispo.w + pos_2point_point_dispo.w + (*game->WINDOWWIDTH)*15/1280;
    pos_nb_point_dispo.y = pos_point_dispo.y;

    /*----------------------------------------------------------------------------*/

    /*--- Initialization texture "fleche" -------------------------------------*/

    surf_fleche = SDL_LoadBMP("src\\image\\fleche.bmp");
    if(surf_fleche == NULL){
        SDL_ExitWithError("probleme chargement image fleche gauche et droite");
    }

    SDL_Rect rect_fleche_gauche;
    rect_fleche_gauche.x = 39;
    rect_fleche_gauche.y = 0;
    rect_fleche_gauche.w = 38;
    rect_fleche_gauche.h = 28;

    SDL_Texture* fleche_gauche = SDL_CreateTextureFromSurface(game->render, surf_fleche);
    if(fleche_gauche == NULL)
    {
        SDL_ExitWithError("probleme texture fleche gauche");
    }

    SDL_Rect pos_fleche_gauche;
    pos_fleche_gauche.w = (*game->WINDOWHEIGHT)*40/1280 * 38 / 28;
    pos_fleche_gauche.h = (*game->WINDOWHEIGHT)*40/1280;

    SDL_Texture* fleche_droite = SDL_CreateTextureFromSurface(game->render, surf_fleche);
    if(fleche_droite == NULL)
    {
        SDL_ExitWithError("probleme texture fleche droite");
    }
    SDL_Rect rect_fleche_droite;
    rect_fleche_droite.x = 0;
    rect_fleche_droite.y = 0;
    rect_fleche_droite.w = 38;
    rect_fleche_droite.h = 28;

    SDL_Rect pos_fleche_droite;
    pos_fleche_droite.w = (*game->WINDOWHEIGHT)*40/1280 * 38 / 28;
    pos_fleche_droite.h = (*game->WINDOWHEIGHT)*40/1280;
    /*-------------------------------------------------------------------------*/

    SDL_Rect pos_texture_render_menu_ig;
    pos_texture_render_menu_ig.x = 0;
    pos_texture_render_menu_ig.y = 0;
    pos_texture_render_menu_ig.w = (*game->WINDOWWIDTH);
    pos_texture_render_menu_ig.h = (*game->WINDOWHEIGHT);

    /*--- Main Loop --------------------------------------------------------------*/

    while ((*game->program_launch) && carac_bool)
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

            if(selection < 0)selection = 5;
            selection %=6;

            if(selection == 0){
                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
                retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
                surf_valider = TTF_RenderText_Blended(game->police, "Valider", blanc);
                valider = SDL_CreateTextureFromSurface(game->render, surf_valider);

                if(character_points_dispo > 0){
                    if(keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN){
                        character_points_dispo--;
                        points_uti_vitalite++;
                        character_vitalite++;
                        rect_fleche_droite.y = 29;
                    }
                }

                if(points_uti_vitalite > 0){
                    if(keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN){
                        character_points_dispo++;
                        points_uti_vitalite--;
                        character_vitalite--;
                        rect_fleche_gauche.y = 29;
                    }
                }

                itoa(character_vitalite, character_nb_vitalite, 10);
                pos_nb_vitalite.w = strlen(character_nb_vitalite)*(*game->WINDOWWIDTH)*15/1280;
                surf_nb_vitalite = TTF_RenderText_Blended(game->police, character_nb_vitalite, blanc);
                nb_vitalite = SDL_CreateTextureFromSurface(game->render, surf_nb_vitalite);

                pos_fleche_droite.x = pos_nb_vitalite.x + pos_nb_vitalite.w + (*game->WINDOWWIDTH)*10/1280 ;
                pos_fleche_droite.y = pos_vitalite.y - pos_fleche_droite.h/2 + (*game->WINDOWHEIGHT)*55/1280 ;

                pos_fleche_gauche.x = pos_nb_vitalite.x - pos_fleche_gauche.w - (*game->WINDOWWIDTH)*10/1280 ;
                pos_fleche_gauche.y = pos_vitalite.y - pos_fleche_gauche.h/2 + (*game->WINDOWHEIGHT)*55/1280 ;
            }

            if(selection == 1){
                if(character_points_dispo > 0){
                    if(keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN){
                        character_points_dispo--;
                        points_uti_force++;
                        character_force++;
                        rect_fleche_droite.y = 29;
                    }
                }

                if(points_uti_force > 0){
                    if(keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN){
                        character_points_dispo++;
                        points_uti_force--;
                        character_force--;
                        rect_fleche_gauche.y = 29;
                    }
                }

                itoa(character_force, character_nb_force, 10);
                pos_nb_force.w = strlen(character_nb_force)*(*game->WINDOWWIDTH)*15/1280;
                surf_nb_force = TTF_RenderText_Blended(game->police, character_nb_force, blanc);
                nb_force = SDL_CreateTextureFromSurface(game->render, surf_nb_force);

                pos_fleche_droite.x = pos_nb_force.x + pos_nb_force.w + (*game->WINDOWWIDTH)*10/1280 ;
                pos_fleche_droite.y = pos_force.y - pos_fleche_droite.h/2 + (*game->WINDOWHEIGHT)*55/1280 ;

                pos_fleche_gauche.x = pos_nb_force.x - pos_fleche_gauche.w - (*game->WINDOWWIDTH)*10/1280 ;
                pos_fleche_gauche.y = pos_force.y - pos_fleche_gauche.h/2 + (*game->WINDOWHEIGHT)*55/1280 ;
            }

            if(selection == 2){
                if(character_points_dispo > 0){
                    if(keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN){
                        character_points_dispo--;
                        points_uti_intell++;
                        character_intell++;
                        rect_fleche_droite.y = 29;
                    }
                }

                if(points_uti_intell > 0){
                    if(keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN){
                        character_points_dispo++;
                        points_uti_intell--;
                        character_intell--;
                        rect_fleche_gauche.y = 29;
                    }
                }

                itoa(character_intell, character_nb_intell, 10);
                pos_nb_intell.w = strlen(character_nb_intell)*(*game->WINDOWWIDTH)*15/1280;
                surf_nb_intell = TTF_RenderText_Blended(game->police, character_nb_intell, blanc);
                nb_intell = SDL_CreateTextureFromSurface(game->render, surf_nb_intell);

                pos_fleche_droite.x = pos_nb_intell.x + pos_nb_intell.w + (*game->WINDOWWIDTH)*10/1280 ;
                pos_fleche_droite.y = pos_intell.y - pos_fleche_droite.h/2 + (*game->WINDOWHEIGHT)*55/1280 ;

                pos_fleche_gauche.x = pos_nb_intell.x - pos_fleche_gauche.w - (*game->WINDOWWIDTH)*10/1280 ;
                pos_fleche_gauche.y = pos_intell.y - pos_fleche_gauche.h/2 + (*game->WINDOWHEIGHT)*55/1280 ;
            }

            if(selection == 3){
                if(character_points_dispo > 0){
                    if(keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN){
                        character_points_dispo--;
                        points_uti_agi++;
                        character_agi++;
                        rect_fleche_droite.y = 29;
                    }
                }

                if(points_uti_agi > 0){
                    if(keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN){
                        character_points_dispo++;
                        points_uti_agi--;
                        character_agi--;
                        rect_fleche_gauche.y = 29;
                    }
                }

                    itoa(character_agi, character_nb_agi, 10);
                pos_nb_agi.w = strlen(character_nb_agi)*(*game->WINDOWWIDTH)*15/1280;
                surf_nb_agi = TTF_RenderText_Blended(game->police, character_nb_agi, blanc);
                nb_agi = SDL_CreateTextureFromSurface(game->render, surf_nb_agi);

                pos_fleche_droite.x = pos_nb_agi.x + pos_nb_agi.w + (*game->WINDOWWIDTH)*10/1280 ;
                pos_fleche_droite.y = pos_agi.y - pos_fleche_droite.h/2 + (*game->WINDOWHEIGHT)*55/1280 ;

                pos_fleche_gauche.x = pos_nb_agi.x - pos_fleche_gauche.w - (*game->WINDOWWIDTH)*10/1280 ;
                pos_fleche_gauche.y = pos_agi.y - pos_fleche_gauche.h/2 + (*game->WINDOWHEIGHT)*55/1280 ;
            }

            if(selection == 4){

                surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
                retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
                surf_valider = TTF_RenderText_Blended(game->police, "Valider", blanc);
                valider = SDL_CreateTextureFromSurface(game->render, surf_valider);

                if(character_points_dispo > 0){
                    if(keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN){
                        character_points_dispo--;
                        points_uti_def++;
                        character_def++;
                        rect_fleche_droite.y = 29;
                    }
                }

                if(points_uti_def > 0){
                    if(keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN){
                        character_points_dispo++;
                        points_uti_def--;
                        character_def--;
                        rect_fleche_gauche.y = 29;
                    }
                }

                itoa(character_def, character_nb_defense, 10);
                pos_nb_def.w = strlen(character_nb_defense)*(*game->WINDOWWIDTH)*15/1280;
                surf_nb_def = TTF_RenderText_Blended(game->police, character_nb_defense, blanc);
                nb_def = SDL_CreateTextureFromSurface(game->render, surf_nb_def);

                pos_fleche_droite.x = pos_nb_def.x + pos_nb_def.w + (*game->WINDOWWIDTH)*10/1280 ;
                pos_fleche_droite.y = pos_def.y - pos_fleche_droite.h/2 + (*game->WINDOWHEIGHT)*55/1280 ;

                pos_fleche_gauche.x = pos_nb_def.x - pos_fleche_gauche.w - (*game->WINDOWWIDTH)*10/1280 ;
                pos_fleche_gauche.y = pos_def.y - pos_fleche_gauche.h/2 + (*game->WINDOWHEIGHT)*55/1280 ;
            }

            if(selection == 5){
                if(keyState[SDL_SCANCODE_RIGHT] && event.type == SDL_KEYDOWN && select_ret_val && (points_uti_vitalite > 0 || points_uti_force > 0 || points_uti_intell > 0 || points_uti_agi > 0 || points_uti_def > 0)){
                    select_ret_val = SDL_FALSE;
                }
                if(keyState[SDL_SCANCODE_LEFT] && event.type == SDL_KEYDOWN && !select_ret_val){
                    select_ret_val = SDL_TRUE;
                }
                if(select_ret_val){
                    surf_retour = TTF_RenderText_Blended(game->police, "Retour", rouge);
                    surf_valider = TTF_RenderText_Blended(game->police, "Valider", blanc);
                }
                else{
                    surf_retour = TTF_RenderText_Blended(game->police, "Retour", blanc);
                    surf_valider = TTF_RenderText_Blended(game->police, "Valider", rouge);
                }
                retour = SDL_CreateTextureFromSurface(game->render, surf_retour);
                valider = SDL_CreateTextureFromSurface(game->render, surf_valider);
            }
            itoa(character_points_dispo, character_nb_points_dispo, 10);
            pos_nb_point_dispo.w = strlen(character_nb_points_dispo)*(*game->WINDOWWIDTH)*15/1280;
            surf_nb_point_dispo = TTF_RenderText_Blended(game->police, character_nb_points_dispo, blanc);
            nb_point_dispo = SDL_CreateTextureFromSurface(game->render, surf_nb_point_dispo);

            if (keyState[SDL_SCANCODE_RETURN] && event.type == SDL_KEYDOWN){
                if(selection == 5 && !select_ret_val){
                    if(texte_confirmation(game,"Validez vos choix ?")){
                        character->vitalite = character_vitalite;
                        character->force = character_force;
                        character->intelligence = character_intell;
                        character->agilite = character_agi;
                        character->defense = character_def;
                        character->points_dispo = character_points_dispo;
                        carac_bool = SDL_FALSE;
                    }
                }
            }

            if(character_points_dispo == character->points_dispo)select_ret_val = SDL_TRUE;

            SDL_RenderClear(game->render);
            SDL_RenderCopy(game->render, texture_render_menu_ig, NULL, &pos_texture_render_menu_ig);
            SDL_RenderCopy(game->render, fond_cadre, NULL, &pos_fond_cadre);
            SDL_RenderCopy(game->render, cadre, NULL, &pos_cadre);
            SDL_RenderCopy(game->render, caracteristiques, NULL, &pos_caracteristiques);
            SDL_RenderCopy(game->render, retour, NULL, &pos_retour);
            SDL_RenderCopy(game->render, vitalite, NULL, &pos_vitalite);
            SDL_RenderCopy(game->render, force, NULL, &pos_force);
            SDL_RenderCopy(game->render, intell, NULL, &pos_intell);
            SDL_RenderCopy(game->render, agi, NULL, &pos_agi);
            SDL_RenderCopy(game->render, def, NULL, &pos_def);
            SDL_RenderCopy(game->render, point_dispo, NULL, &pos_point_dispo);
            SDL_RenderCopy(game->render, nb_vitalite, NULL, &pos_nb_vitalite);
            SDL_RenderCopy(game->render, nb_force, NULL, &pos_nb_force);
            SDL_RenderCopy(game->render, nb_intell, NULL, &pos_nb_intell);
            SDL_RenderCopy(game->render, nb_agi, NULL, &pos_nb_agi);
            SDL_RenderCopy(game->render, nb_def, NULL, &pos_nb_def);
            SDL_RenderCopy(game->render, nb_point_dispo, NULL, &pos_nb_point_dispo);
            if(selection < 5 && character_points_dispo > 0)SDL_RenderCopy(game->render, fleche_droite, &rect_fleche_droite, &pos_fleche_droite);
            switch(selection){
                case 0:if(points_uti_vitalite > 0)SDL_RenderCopy(game->render, fleche_gauche, &rect_fleche_gauche, &pos_fleche_gauche);break;
                case 1:if(points_uti_force > 0)SDL_RenderCopy(game->render, fleche_gauche, &rect_fleche_gauche, &pos_fleche_gauche);break;
                case 2:if(points_uti_intell > 0)SDL_RenderCopy(game->render, fleche_gauche, &rect_fleche_gauche, &pos_fleche_gauche);break;
                case 3:if(points_uti_agi > 0)SDL_RenderCopy(game->render, fleche_gauche, &rect_fleche_gauche, &pos_fleche_gauche);break;
                case 4:if(points_uti_def > 0)SDL_RenderCopy(game->render, fleche_gauche, &rect_fleche_gauche, &pos_fleche_gauche);break;
            }
            SDL_RenderCopy(game->render, t_2point, NULL, &pos_2point_v);
            SDL_RenderCopy(game->render, t_2point, NULL, &pos_2point_f);
            SDL_RenderCopy(game->render, t_2point, NULL, &pos_2point_i);
            SDL_RenderCopy(game->render, t_2point, NULL, &pos_2point_a);
            SDL_RenderCopy(game->render, t_2point, NULL, &pos_2point_d);
            SDL_RenderCopy(game->render, t_2point, NULL, &pos_2point_point_dispo);
            if(points_uti_vitalite > 0 || points_uti_force > 0 || points_uti_intell > 0 || points_uti_agi > 0 || points_uti_def > 0)SDL_RenderCopy(game->render, valider, NULL, &pos_valider);
            SDL_RenderPresent(game->render);

            rect_fleche_droite.y = 0;
            rect_fleche_gauche.y = 0;
            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                (*game->program_launch) = SDL_FALSE;
            }

            if(keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN){
                carac_bool = SDL_FALSE;
                *echap_relache = SDL_FALSE;
            }

            /*--- End Event to Exit Program --------------------------------------*/
        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_cadre);
    SDL_FreeSurface(surf_caracteristiques);
    SDL_FreeSurface(surf_retour);
    SDL_FreeSurface(surf_vitalite);
    SDL_FreeSurface(surf_force);
    SDL_FreeSurface(surf_intell);
    SDL_FreeSurface(surf_agi);
    SDL_FreeSurface(surf_def);
    SDL_FreeSurface(surf_nb_vitalite);
    SDL_FreeSurface(surf_nb_force);
    SDL_FreeSurface(surf_nb_intell);
    SDL_FreeSurface(surf_nb_agi);
    SDL_FreeSurface(surf_nb_def);
    SDL_FreeSurface(surf_2point);
    SDL_FreeSurface(surf_point_dispo);
    SDL_FreeSurface(surf_nb_point_dispo);
    SDL_FreeSurface(surf_valider);

    SDL_DestroyTexture(cadre);
    SDL_DestroyTexture(fond_cadre);
    SDL_DestroyTexture(caracteristiques);
    SDL_DestroyTexture(retour);
    SDL_DestroyTexture(vitalite);
    SDL_DestroyTexture(force);
    SDL_DestroyTexture(intell);
    SDL_DestroyTexture(agi);
    SDL_DestroyTexture(def);
    SDL_DestroyTexture(nb_vitalite);
    SDL_DestroyTexture(nb_force);
    SDL_DestroyTexture(nb_intell);
    SDL_DestroyTexture(nb_agi);
    SDL_DestroyTexture(nb_def);
    SDL_DestroyTexture(t_2point);
    SDL_DestroyTexture(point_dispo);
    SDL_DestroyTexture(nb_point_dispo);
    SDL_DestroyTexture(valider);

    /*--- End Free Memory --------------------------------------------------------*/

}
