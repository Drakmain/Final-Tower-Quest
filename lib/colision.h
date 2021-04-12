#ifndef _COLISION_H_
#define _COLISION_H_

#include "commun.h"
#include "game.h"

#define NB_IMAGE 4

typedef struct load_image_s load_image_t;

struct load_image_s
{
  char * nom_image;
  SDL_Surface* surface;
};

extern void chargement_image(load_image_t tab_load_image[]);
extern int character_moving (game_t *game, SDL_Renderer* pRenderer, SDL_Surface* couleur_image, int x, int y, int direction);
Uint32 getpixel(SDL_Surface *surface, int x, int y);

#endif
