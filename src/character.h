#ifndef _CHARACTERE_H_
#define _CHARACTERE_H_

#include "commun.h"

typedef struct character_s character_t;

struct character_s 
{
    void (*update)(character_t *, SDL_Renderer *, tile_set_t, SDL_Rect); /*!< A FINIR */
    void (*free)(character_t **); /*!< A FINIR */

    SDL_Texture * texture; /*!< Pointeur sur une texture SDL de l'objet character_t. */

    SDL_Surface * surface; /*!< Pointeur sur une surface SDL de l'objet character_t. */

    SDL_Rect mov; /*!< Rectangle de "mouvement" de l'objet character_t. */

    tile_set_t North_Walk; /*!< Tile set (tile_set_t) pour la marche vers le nord de l'objet character_t. */
    tile_set_t South_Walk; /*!< Tile set (tile_set_t) pour la marche vers le sud de l'objet character_t. */
    tile_set_t West_Walk; /*!< Tile set (tile_set_t) pour la marche vers le ouest de l'objet character_t. */
    tile_set_t East_Walk; /*!< Tile set (tile_set_t) pour la marche vers le est de l'objet character_t. */
    tile_set_t Win; /*!< Tile set (tile_set_t) pour la victoire d'un combat de l'objet character_t. */
};

extern character_t * character_create(SDL_Renderer * render, char * file_name_bmp, char * file_name_txt) ;
extern SDL_bool character_exist(character_t * const character);

#endif