#include <stdio.h>
#include <stdlib.h>

#include "..\lib\sauvegarder.h"
#include "..\lib\character.h"



void sauvegarde(game_t * game, character_t * character, SDL_Texture * texture_render_menu_ig, SDL_bool *echap_relache){

    SDL_Color blanc = {255,255,255};
    SDL_Color rouge = {255,0,0};

    //SDL_Surface * surf = NULL;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_bool sauvegarde_bool = SDL_TRUE;
    SDL_Event event;

    SDL_Rect pos_texture_render_menu_ig;
    pos_texture_render_menu_ig.x = 0;
    pos_texture_render_menu_ig.y = 0;
    pos_texture_render_menu_ig.w = (*game->WINDOWWIDTH);
    pos_texture_render_menu_ig.h = (*game->WINDOWHEIGHT);



    /*--- Main Loop --------------------------------------------------------------*/

    while (sauvegarde_bool && (*game->program_launch))
    {

        while (SDL_PollEvent(&event))
        {


            /*--- Event pour selectionner ------------------------------------------*/

            if (keyState[SDL_SCANCODE_DOWN] && event.type == SDL_KEYDOWN){

            }

            if (keyState[SDL_SCANCODE_UP] && event.type == SDL_KEYDOWN){

            }

            /*--- End Event pour selectionner --------------------------------------*/

            /*--- Event to Exit Program ------------------------------------------*/

            if (event.type == SDL_QUIT)
            {
                (*game->program_launch) = SDL_FALSE;
            }

            if (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
            {
                sauvegarde_bool = SDL_FALSE;
                *echap_relache = SDL_FALSE;
            }

            /*--- End Event to Exit Program --------------------------------------*/
        }

    }
    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/


    /*--- End Free Memory --------------------------------------------------------*/
}
