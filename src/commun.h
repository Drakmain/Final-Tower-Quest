#ifndef _COMMUN_H_
#define _COMMUN_H_

#include <SDL.h>

/*!
 * 
 * \struct rect_tile_set_t commun.h "commun.h"
 * \brief Objet tile set
 * 
 */

typedef struct rect_tile_set_s rect_tile_set_t;

struct rect_tile_set_s 
{
    SDL_Rect rect;
    int limit;
};

#endif