#ifndef _COMMUN_H_
#define _COMMUN_H_

#include <SDL.h>
#include "error.h"

#define MULTIPLIER 5

#define WINDOWWIDTH 1600
#define WINDOWHEIGHT 900

/**
 * @file commun.h
 * @brief Définitions de structure et constante commune
 *
 */


/*!
 * 
 * \struct tile_set_t commun.h "commun.h"
 * \brief Structure de l'objet tile set
 * 
 */

typedef struct tile_set_s tile_set_t;

struct tile_set_s 
{
    SDL_Rect rect;
    int limit;
};

#endif