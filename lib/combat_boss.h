#ifndef _COMBAT_BOSS_H_
#define _COMBAT_BOSS_H_

#include "commun.h"

#include "game.h"
#include "character.h"
#include "map.h"

#define NB_MAX_ENEMIES_CBT 4

extern void combat_boss(game_t *game, character_t *character, map_t *map, SDL_Texture *texture_render_town, SDL_bool *floor_bool);

#endif
