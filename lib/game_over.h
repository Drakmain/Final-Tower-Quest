#ifndef _TRANSITION_H_
#define _TRANSITION_H_

#include "commun.h"

#include "game.h"
#include "character.h"

extern void game_over(game_t *game,  SDL_bool *floor_bool, SDL_bool *combat_bool, character_t *character);

#endif
