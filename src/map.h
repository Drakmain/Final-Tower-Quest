#ifndef _MAP_H_
#define _MAP_H_

#include "commun.h"

typedef struct map_s map_t;

struct map_s 
{
    void (*update)(map_t *, SDL_Renderer *, SDL_Rect, SDL_Rect); /*!< A FINIR */
    void (*free)(map_t **); /*!< A FINIR */

    SDL_Texture * texture; /*!< Pointeur sur une texture SDL de l'objet map_t. */

    SDL_Surface * surface; /*!< Pointeur sur une surface SDL de l'objet map_t. */

    SDL_Rect tile_set; /*!< Tile set de l'objet map_t. */
};

extern map_t * map_create(SDL_Renderer * render, char * file_name_bmp, char * file_name_txt);
extern SDL_bool map_exist(map_t * const map);

#endif