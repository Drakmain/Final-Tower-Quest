#include "..\lib\frame.h"

/*!
 * 
 * \file frame.c
 * \brief Gestion des FPS.
 * \author Enzo BRENNUS
 * 
 */

const int FPS = 15;           /*!< Nombre maximum d'FPS. */
int frame_delay = 1000 / FPS; /*!< Le delai en MS (milliseconde) d'une frame. */

Uint32 frame_start; /*!< Debut d'une frame. */
int frame_time = 0; /*!< Différence entre la frame de debut (frame_start) et un instant T (SDL_GetTicks()). */

/*!
 *
 * \fn void render_frame(SDL_Renderer * render)
 * \brief A FINIR
 *
 * \param render est un pointeur sur le rendu SDL.
 * 
 */

extern void render_frame(SDL_Renderer *render)
{
    SDL_RenderPresent(render);

    frame_time = SDL_GetTicks() - frame_start;

    if (frame_delay > frame_time)
    {
        SDL_Delay(frame_delay - frame_time);
    }
}