#ifndef _MAP_H_
#define _MAP_H_

#include <SDL.h>
#include "commun.h"


typedef struct map_s map_t;

struct map_s 
{
    void (*update)(rect_tile_set_t *);
    void (*display)(map_t * const, SDL_Renderer *, SDL_Rect, SDL_Rect);
    void (*free)(map_t **);

    SDL_Texture * texture;
    
    rect_tile_set_t tile_set;
};

extern map_t * map_create(char * name_file);
extern SDL_bool map_exist(map_t * const map);


#endif