#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "commun.h"

#include "game.h"
#include "character.h"
#include "map.h"

extern void _toEspace(char *string, int length);
extern void combat(game_t *game, character_t *character, map_t *map, SDL_Texture *texture_render_town);

#endif