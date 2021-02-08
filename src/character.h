#ifndef _CHARACTERE_H_
#define _CHARACTERE_H_

#include <SDL.h>
#include "commun.h"


typedef struct character_s character_t;

struct character_s 
{ 
    void (*update)(rect_tile_set_t *);
    void (*display)(character_t * const, SDL_Renderer *, SDL_Rect, SDL_Rect);
    void (*free)(character_t **);

    SDL_Texture * texture;

    rect_tile_set_t North_Walk;
    rect_tile_set_t South_Walk;
    rect_tile_set_t Side_Walk;
    rect_tile_set_t Win;
};

extern character_t * character_create(char * name_file);
extern SDL_bool character_exist(character_t * const character);


#endif