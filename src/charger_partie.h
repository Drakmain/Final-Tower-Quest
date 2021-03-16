#ifndef _CHARGER_PARTIE_H_
#define _CHARGER_PARTIE_H_

#include "commun.h"

#include "character.h"

void charger_partie_f(SDL_Renderer * render, int *windowwidth, int *windowheight, TTF_Font *police, SDL_bool * program_launch, character_t * actual_save);

#endif
