#ifndef _SAC_H_
#define _SAC_H_

#include "commun.h"

#include "character.h"
#include "game.h"

void ouverture_sac(game_t *game, character_t *character, SDL_Texture *texture_render_menu_ig, SDL_bool *echap_relache, SDL_bool *combat);

#endif
