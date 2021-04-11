#ifndef _ENEMY_TURN_H_
#define _ENEMY_TURN_H_

#include "commun.h"

#include "game.h"
#include "character.h"
#include "map.h"

extern void enemy_turn(game_t *game, character_t *character, enemy_t *enemies_cbt, int num, map_t *map, SDL_Texture *texture_render_combat);

#endif