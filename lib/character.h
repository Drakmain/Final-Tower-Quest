#ifndef _CHARACTERE_H_
#define _CHARACTERE_H_

#include "commun.h"
#include "map.h"

typedef struct attack_character_s attack_character_t;

struct attack_character_s
{
  char *name;        /*!< Nom de l'attaque. */
  char *description; /*!< Description de l'attaqua. */

  int type;     /*!< Type de l'attaque */
  int dmg_min;  /*!< Fourchette de degat min de l'attaque. */
  int dmg_max;  /*!< Fourchette de degat max de l'attaque. */
  int modifier; /*!< Modifieur de l'attaque. */
  int mana;     /*!< Cout en mana de l'attaque. */
};

typedef struct character_s character_t;

struct character_s
{
  void (*update)(character_t *, SDL_Renderer *, tile_set_t, SDL_Rect); /*!< Permet la mise a jour d'un objet character_t. */
  void (*free)(character_t **);                                        /*!< Permet la liberation d'un objet character_t. */

  SDL_bool empty; /*!< Permet de savoir si un type character_t est vide ou non. */

  char *file_name_txt;  /*!< Chemin du fichier texte contenant les informations du character_t. */
  char *file_name_bmp;  /*!< Chemin du fichier BMP contenant les animation du character_t. */
  char *file_name_save; /*!< Chemin du fichier texte contenant les informations de sauvegarde du character_t. */

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
  SDL_Rect Attack;       /*!< Tile set (SDL_Rect) A FINIR. */

  attack_character_t *attacks; /*!< Tableau des attaques du character_t. */

  char *save_name;   /*!< Chaîne de caractères contenant le nom de la sauvegarde du character_t. */
  char *classe_name; /*!< Chaîne de caractères contenant le nom de la classe du character_t. */
  char *position;    /*!< Chaîne de caractères contenant la possition du character_t. */
  int x;             /*!< Entier contenant la possition en x du character_t. */
  int y;             /*!< Entier contenant la possition en y du character_t. */

  int lvl;            /*!< Entier contenant le level du character_t. */
  int xp;             /*!< Entier contenant l'experience du character_t.. */
  int tab_xp_max[50]; /*!< A FINIR. */
  int max_life;       /*!< Entier contenant les points de vie max du character_t. */
  int life;           /*!< Entier contenant les points de vie actuelle du character_t. */
  int max_mana;       /*!< Entier contenant les points de mana max du character_t. */
  int mana;           /*!< Entier contenant les points de mana actuelle du character_t. */

  int atb; /*!< Entier contenant l'ATB du character_t. */

  int vitalite;     /*!< Entier contenant les points de vitalite actuelle du character_t. */
  int puissance;    /*!< Entier contenant les points de puissance actuelle du character_t. */
  int intelligence; /*!< Entier contenant les points de intelligence actuelle du character_t. */
  int vitesse;      /*!< Entier contenant les points de vitesse actuelle du character_t. */
  int agilite;      /*!< Entier contenant les points de agilite actuelle du character_t. */
  int defense;      /*!< Entier contenant les points de defense actuelle du character_t. */
  int points_dispo; /*!< Entier contenant les points disponible actuelle du character_t. */

  int nb_petite_popo_soin;  /*!< Entier contenant le nombre de petite potion de soin du character_t. */
  int nb_moyenne_popo_soin; /*!< Entier contenant le nombre de moyenne potion de soin du character_t. */
  int nb_petite_popo_mana;  /*!< Entier contenant le nombre de petite potion de mana du character_t. */
  int nb_moyenne_popo_mana; /*!< Entier contenant le nombre de moyenne potion de mana du character_t. */
  int nb_popo_puissance;    /*!< Entier contenant le nombre de potion de puissance du character_t. */
  int nb_popo_agi;          /*!< Entier contenant le nombre de potion d'agilite du character_t. */

  int nb_tour_restant_puissance; /*!< Entier contenant le nombre de tour restant de l'effet de la potion de puissance du character_t. */
  int nb_tour_restant_agi;       /*!< Entier contenant le nombre de tour restant de l'effet de la potion d'agilite du character_t. */
};

extern character_t *character_create(SDL_Renderer *render, char *file_name_save);
extern SDL_bool character_exist(character_t *const character);

#endif
