#ifndef _COMBAT_H_
#define _COMBAT_H_

#include "commun.h"

#include "game.h"
#include "character.h"
#include "map.h"

#define NB_MAX_ENEMIES_CBT 4 /*!< Nombre d'ennemis max par combat. */

extern void combat(game_t *game, character_t *character, map_t *map, SDL_Texture *texture_render_town, SDL_bool *floor_bool);

#endif
