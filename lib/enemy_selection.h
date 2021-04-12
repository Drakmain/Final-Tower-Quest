#ifndef _ENEMY_SELECTION_H_
#define _ENEMY_SELECTION_H_

#include "commun.h"

#include "game.h"
#include "map.h"
#include "character.h"

extern int enemy_selection(game_t *game, character_t *character, enemy_t *enemies_cbt, int nb_enemies_combat, SDL_Texture *texture_render_attacks);

#endif