#ifndef _CHARACTER_TURN_H_
#define _CHARACTER_TURN_H_

#include "commun.h"

#include "game.h"
#include "character.h"
#include "map.h"

extern void character_turn(game_t *game, character_t *character, map_t *map, int nb_enemies_combat, int nb_enemies_combat_actif, int rand_enemies[], SDL_Texture *texture_render_combat);

#endif