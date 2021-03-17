#ifndef _GAME_H_
#define _GAME_H_

#include "commun.h"

typedef struct game_s game_t;

struct game_s 
{
    void (*free)(game_t **); /*!< A FINIR. */

    SDL_Window * window;
    SDL_Renderer * render;

    TTF_Font * police;

    SDL_bool * program_launch;
    SDL_bool * etat_fullscreen; 

    int * WINDOWHEIGHT;
    int * WINDOWWIDTH;


};

extern game_t * game_create();
extern SDL_bool game_exist(game_t * const game);

#endif