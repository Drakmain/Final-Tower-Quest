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

typedef struct attack_enemie_s attack_enemie_t;

struct attack_enemie_s
{
  char *name;          /*!< A FINIR. */
  int mana;            /*!< A FINIR. */
  int dmg_min;         /*!< A FINIR. */
  int dmg_max;         /*!< A FINIR. */
  int effect;          /*!< A FINIR. */
  int effect_duration; /*!< A FINIR. */
  int modifier;        /*!< A FINIR. */
  int percetange;      /*!< A FINIR. */
  char *description;   /*!< A FINIR. */
};

typedef struct enemie_s enemie_t;

struct enemie_s
{
  void (*free)(enemie_t **); /*!< Permet la liberation d'un objet enemie_t. */

  SDL_Texture *texture; /*!< Pointeur sur une texture SDL de l'objet enemie_t. */

  SDL_Surface *surface; /*!< Pointeur sur une surface SDL de l'objet enemie_t. */

  int R, /*!< Code de la couleur rouge de la chroma key du .bmp */
      G, /*!< Code de la couleur verte de la chroma key du .bmp */
      B; /*!< Code de la couleur bleu de la chroma key du .bmp*/

  SDL_Rect tile_set; /*!< Tile set (SDL_Rect) A FINIR. */

  SDL_bool boss; /*!< A FINIR. */

  char *name; /*!< A FINIR. */

  attack_enemie_t *attack;

  int life;  /*!< A FINIR. */
  int speed; /*!< A FINIR. */
  int exp;   /*!< A FINIR. */
};

typedef struct map_s map_t;

struct map_s
{
  void (*update)(map_t *, SDL_Renderer *, SDL_Rect, SDL_Rect); /*!< Permet la mise a jour d'un objet map_t. */
  void (*free)(map_t **);                                      /*!< Permet la liberation d'un objet map_t. */

  SDL_Texture *texture; /*!< Pointeur sur une texture SDL de l'objet map_t. */

  SDL_Surface *surface; /*!< Pointeur sur une surface SDL de l'objet map_t. */

  SDL_Rect tile_set; /*!< Tile set de l'objet map_t. */

  char *name;

  enemie_t *enemies;

  //test
  image_t map_image; /*!< A FINIR. */

  SDL_Surface *map_couleur; /*!< A FINIR. */

  int hauteur_carte, largeur_carte; /*!< A FINIR. */
};

extern map_t *map_create(SDL_Renderer *render, char *name_map);
extern SDL_bool map_exist(map_t *const map);

#endif