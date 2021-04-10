#ifndef _FIN_COMBAT_H_
#define _FIN_COMBAT_H_

#include "commun.h"
#include "character.h"
#include "game.h"

extern
void fin_combat(game_t *game, character_t *character, SDL_Texture * texture_render_combat, map_t *map, int nb_enemie_combat, int rand_enemie[]);

#endif
