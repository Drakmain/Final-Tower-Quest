#ifndef _ATTAQUES_H_
#define _ATTAQUES_H_

#include "commun.h"

#include "game.h"
#include "character.h"

#define NB_ATTACKS 13 /*!< A FINIR. */

extern void attaques(game_t *game, character_t *character, SDL_Texture *texture_render_combat);

#endif