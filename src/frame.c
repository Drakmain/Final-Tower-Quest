#include "frame.h"

/*!
 * 
 * \file frame.c
 * \brief Gestion des FPS.
 * \author Robin PAPILLON, Alexis BOUFFARD, Jeremy BOURGOUIN, Enzo BRENNUS
 * \date 12/02/21
 *
 * \section DESCRIPTION
 * Ficher frame.c ... A FINIR
 * 
 */


const int FPS = 10;
int frame_delay = 1000 / FPS;

Uint32 frame_start;
int frame_time = 0;


/*!
 *
 * \fn void render_frame(SDL_Renderer* render)
 * \brief A FINIR
 *
 * \param render Pointeur sur le rendu SDL.
 * 
 */

extern
void render_frame(SDL_Renderer* render)
{

    SDL_RenderPresent(render);

    frame_time = SDL_GetTicks() - frame_start;

    if (frame_delay > frame_time)
    {
        SDL_Delay(frame_delay - frame_time);
    }

}