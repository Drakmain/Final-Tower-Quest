#ifndef _MAP_H_
#define _MAP_H_

#include "commun.h"

#define NB_IMAGE 1

typedef struct image_s image_t;

struct image_s
{
  char *nom_image; /*!< A FINIR. */

  int position_x, position_y; /*!< A FINIR. */

  int largeur, hauteur; /*!< A FINIR. */

  SDL_Rect src, dst; /*!< A FINIR. */

  SDL_Texture *texture; /*!< A FINIR. */
};

typedef struct map_s map_t;

struct map_s
{
  void (*update)(map_t *, SDL_Renderer *, SDL_Rect, SDL_Rect); /*!< Permet la mise a jour d'un objet map_t. */
  void (*free)(map_t **);                                      /*!< Permet la liberation d'un objet map_t. */

  SDL_Texture *texture; /*!< Pointeur sur une texture SDL de l'objet map_t. */

  SDL_Surface *surface; /*!< Pointeur sur une surface SDL de l'objet map_t. */

  SDL_Rect tile_set; /*!< Tile set de l'objet map_t. */

  //test
  image_t map_image; /*!< A FINIR. */

  SDL_Surface *map_couleur; /*!< A FINIR. */

  int hauteur_carte, largeur_carte; /*!< A FINIR. */
};

extern map_t *map_create(SDL_Renderer *render, char *name_map);
extern SDL_bool map_exist(map_t *const map);

#endif