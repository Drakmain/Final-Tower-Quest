#ifndef _ENEMIE_H_
#define _ENEMIE_H_

#include "commun.h"

typedef struct enemie_s enemie_t;

struct enemie_s
{
    void (*free)(enemie_t **); /*!< Permet la liberation d'un objet enemie_t. */

    SDL_bool boss; /*!< A FINIR. */

    char *file_name_bmp; /*!< A FINIR. */

    SDL_Texture *texture; /*!< Pointeur sur une texture SDL de l'objet enemie_t. */

    SDL_Surface *surface; /*!< Pointeur sur une surface SDL de l'objet enemie_t. */

    SDL_Rect mov; /*!< Rectangle de "mouvement" de l'objet enemie_t. */

    int R, /*!< Code de la couleur rouge de la chroma key du .bmp */
        G, /*!< Code de la couleur verte de la chroma key du .bmp */
        B; /*!< Code de la couleur bleu de la chroma key du .bmp*/

    SDL_Rect tile_set; /*!< Tile set (SDL_Rect) A FINIR. */

    char *name; /*!< A FINIR. */

    int life; /*!< A FINIR. */
};

extern enemie_t *enemie_create(SDL_Renderer *render, char *file_name_enemies, int enemei_rand);
extern SDL_bool enemie_exist(enemie_t *const enemie);

#endif