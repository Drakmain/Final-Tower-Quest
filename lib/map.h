#ifndef _MAP_H_
#define _MAP_H_

#include "commun.h"

#define NB_ENEMIES 6         /*!< Est le nombre d'ennemis max par etage. */
#define NB_ATTACKS_ENEMIES 2 /*!< Est le nombre max d'attaque par ennemis. */

typedef struct image_s image_t;

struct image_s
{
  char *nom_image;            /*!< A FINIR. */
  int position_x, position_y; /*!< A FINIR. */
  int largeur, hauteur;       /*!< A FINIR. */
  SDL_Rect src, dst;          /*!< A FINIR. */
  SDL_Texture *texture;       /*!< A FINIR. */
};

typedef struct attack_enemy_s attack_enemy_t;

struct attack_enemy_s
{
  char *name; /*!< Nom de l'attaque. */

  int dmg_min; /*!< Fourchette de degat min de l'attaque. */
  int dmg_max; /*!< Fourchette de degat max de l'attaque. */

  int effect;           /*!< Type d'effet de l'attaque */
  int effect_duration;  /*!< Duration de l'effet de l'attaque */
  int effect_remaining; /*!< Temps restant de l'effet de l'attaque */
  int modifier;         /*!< Modifieur de l'effet de l'attaque */
  int percentage;       /*!< Pourcentage de chance que l'attaque arrive */
};

typedef struct enemy_s enemy_t;

struct enemy_s
{
  SDL_Texture *texture; /*!< Pointeur sur une texture SDL de l'objet enemy_t. */

  SDL_Surface *surface; /*!< Pointeur sur une surface SDL de l'objet enemy_t. */

  int R, /*!< Code de la couleur rouge de la chroma key du .bmp */
      G, /*!< Code de la couleur verte de la chroma key du .bmp */
      B; /*!< Code de la couleur bleu de la chroma key du .bmp*/

  SDL_Rect tile_set; /*!< Tile set (SDL_Rect) A FINIR. */

  char *name; /*!< Nom de l'ennemi. */

  SDL_bool boss; /*!< Booléen qui dit si l'ennemi est un boss ou non. */

  attack_enemy_t *attack; /*!< Tableau des attaques du enemy_t. */

  int life;  /*!< Entier contenant le nombre de points de vie actuelle du enemy_t. */
  int speed; /*!< Entier contenant la vitesse du enemy_t. */
  int exp;   /*!< Entier contenant le nombre d'experience donnée par le enemy_t. */

  int atb; /*!< Entier contenant l'ATB du enemy_t. */
};

typedef struct map_s map_t;

struct map_s
{
  void (*update)(map_t *, SDL_Renderer *, SDL_Rect, SDL_Rect); /*!< Permet la mise a jour d'un objet map_t. */
  void (*free)(map_t **);                                      /*!< Permet la liberation d'un objet map_t. */

  SDL_Texture *texture; /*!< Pointeur sur une texture SDL de l'objet map_t. */

  SDL_Surface *surface; /*!< Pointeur sur une surface SDL de l'objet map_t. */

  SDL_Rect tile_set; /*!< Tile set de l'objet map_t. */

  char *name; /*!< Chaîne de caractères contenant le nom de la carte du map_t. */

  enemy_t *enemies; /*!< Tableau des ennemie du map_t. */

  enemy_t *boss;       /*!< Boss final du map_t. */
  int nb_attacks_boss; /*!< Entier contenant le nombre d'attaques du boss final du map_t. */
  int boss_W,          /*!< Entier contenant la largeur du boss final du map_t. */
      boss_H,          /*!< Entier contenant la hauteur du boss final du map_t. */
      boss_multiplier; /*!< Entier contenant le multiplier graphique du boss final du map_t. */
};

extern map_t *map_create(SDL_Renderer *render, char *name_map);
extern SDL_bool map_exist(map_t *const map);
extern void enemy_cpy(enemy_t *dst, enemy_t *const src, SDL_Renderer *render, int nb_attacks_boss);

#endif
