#ifndef _GAME_H_
#define _GAME_H_

#include "commun.h"

typedef struct game_s game_t;

struct game_s 
{
    void (*free)(game_t **); /*!< A FINIR. */

    SDL_Window * window; /*!< A FINIR. */
    SDL_Renderer * render; /*!< A FINIR. */

    TTF_Font * police; /*!< A FINIR. */

    SDL_bool * program_launch; /*!< A FINIR. */
    SDL_bool * etat_fullscreen; /*!< A FINIR. */

    int * WINDOWHEIGHT; /*!< A FINIR. */
    int * WINDOWWIDTH; /*!< A FINIR. */
};

extern game_t * game_create();
extern SDL_bool game_exist(game_t * const game);

#endif