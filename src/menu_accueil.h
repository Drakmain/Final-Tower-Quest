#ifndef _MENU_ACCUEIL_H_
#define _MENU_ACCUEIL_H_

#include "commun.h"

#include "character.h"

void menu_accueil(SDL_Window * window, SDL_Renderer * render, int * windowwidth, int * windowheight, TTF_Font * police,SDL_bool * etat_fullscreen, SDL_bool * program_launch, character_t * actual_save);

#endif