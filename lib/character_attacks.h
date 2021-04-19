#ifndef _CHARACTER_ATTACKS_H_
#define _CHARACTER_ATTACKS_H_

#include "commun.h"

#include "game.h"
#include "map.h"
#include "character.h"

#define NB_ATTACKS 13 /*!< Nombre total d'attaques du character_t. */

extern void _toEspace(char *string);
extern void character_attacks(game_t *game, character_t *character, enemy_t *enemies_cbt, int nb_enemies_combat, int nb_enemies_combat_actif, SDL_Texture *texture_render_combat, SDL_bool *character_turn_bool);

#endif