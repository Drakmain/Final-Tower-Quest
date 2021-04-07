#ifndef _CHARACTERE_H_
#define _CHARACTERE_H_

#include "commun.h"
#include "map.h"

typedef struct attack_s attack_t;

struct attack_s
{
  char *name;   /*!< A FINIR. */
  int mana;   /*!< A FINIR. */
  int dmg_min;   /*!< A FINIR. */
  int dmg_max;   /*!< A FINIR. */
  char *description;   /*!< A FINIR. */
};

typedef struct character_s character_t;

struct character_s
{
  void (*update)(character_t *, SDL_Renderer *, tile_set_t, SDL_Rect); /*!< Permet la mise a jour d'un objet character_t. */
  void (*free)(character_t **);                                        /*!< Permet la liberation d'un objet character_t. */

  SDL_bool empty; /*!< A FINIR. */

  char *file_name_txt;  /*!< A FINIR. */
  char *file_name_bmp;  /*!< A FINIR. */
  char *file_name_save; /*!< A FINIR. */

  SDL_Texture *texture; /*!< Pointeur sur une texture SDL de l'objet character_t. */

  SDL_Surface *surface; /*!< Pointeur sur une surface SDL de l'objet character_t. */

  SDL_Rect mov; /*!< Rectangle de "mouvement" de l'objet character_t. */

  int R, /*!< Code de la couleur rouge de la chroma key du .bmp */
      G, /*!< Code de la couleur verte de la chroma key du .bmp */
      B; /*!< Code de la couleur bleu de la chroma key du .bmp*/

  tile_set_t North_Walk; /*!< Tile set (tile_set_t) pour la marche vers le nord de l'objet character_t. */
  tile_set_t East_Walk;  /*!< Tile set (tile_set_t) pour la marche vers le est de l'objet character_t. */
  tile_set_t South_Walk; /*!< Tile set (tile_set_t) pour la marche vers le sud de l'objet character_t. */
  tile_set_t West_Walk;  /*!< Tile set (tile_set_t) pour la marche vers le ouest de l'objet character_t. */
  SDL_Rect Weak;         /*!< Tile set (SDL_Rect) A FINIR. */
  SDL_Rect Damage_Taken; /*!< Tile set (SDL_Rect) A FINIR. */
  SDL_Rect Dead;         /*!< Tile set (SDL_Rect) A FINIR. */

  attack_t *attacks;

  char *save_name;   /*!< A FINIR. */
  char *classe_name; /*!< A FINIR. */
  char *position;    /*!< A FINIR. */
  int x;             /*!< A FINIR. */
  int y;             /*!< A FINIR. */

  int lvl;      /*!< A FINIR. */
  int xp;       /*!< A FINIR. */
  int max_life; /*!< A FINIR. */
  int life;     /*!< A FINIR. */
  int max_mana; /*!< A FINIR. */
  int mana;     /*!< A FINIR. */

  int vitalite;     /*!< A FINIR. */
  int force;        /*!< A FINIR. */
  int intelligence; /*!< A FINIR. */
  int agilite;      /*!< A FINIR. */
  int defense;      /*!< A FINIR. */

  int points_dispo; /*!< A FINIR. */
};

extern character_t *character_create(SDL_Renderer *render, char *file_name_save);
extern SDL_bool character_exist(character_t *const character);

#endif
