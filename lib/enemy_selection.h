#ifndef _ENEMY_SELECTION_H_
#define _ENEMY_SELECTION_H_

#include "commun.h"

#include "game.h"
#include "map.h"
#include "character.h"

extern int enemy_selection(game_t *game, character_t *character, map_t *map, int nb_enemies_combat, int nb_enemies_combat_actif, int rand_enemies[], SDL_Texture *texture_render_attacks);

#endif