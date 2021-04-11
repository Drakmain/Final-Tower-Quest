#ifndef _ATTACKS_CHARACTER_H_
#define _ATTACKS_CHARACTER_H_

#include "commun.h"

#include "game.h"
#include "map.h"
#include "character.h"

#define NB_ATTACKS 13 /*!< A FINIR. */

extern void _toEspace(char *string);
extern void attacks_character(game_t *game, character_t *character, map_t *map, int nb_enemies_combat, int nb_enemies_combat_actif, int rand_enemies[], SDL_Texture *texture_render_combat, SDL_bool *character_turn_bool);

#endif