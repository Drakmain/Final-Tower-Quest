#include <stdio.h>
#include <stdlib.h>

#include "..\lib\caracteristiques.h"


/*!
 *
 * \file caracteristiques.c
 * \brief A FINIR.
 * \author Jeremy BOURGOUIN
 * \date 12/03/21
 *
 */


/*!
 *
 * \fn caracteristiques(game_t * game, char * actual_save, SDL_Texture * texture_render_menu_ig)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param actual_save A FINIR.
 * \param texture_render_menu_ig A FINIR.
 *
 */

void caracteristiques(game_t * game, char * actual_save, SDL_Texture * texture_render_menu_ig){

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    SDL_Surface * surf_;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool carac_bool = SDL_TRUE;
    SDL_Event event;


}
