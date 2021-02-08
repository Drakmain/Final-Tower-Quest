#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "error.h"

/*!
 * 
 * \file map.c
 * \brief Gestion objet map.
 * \author Robin PAPILLON, Alexis BOUFFARD, Jeremy BOURGOUIN, Enzo BRENNUS
 * \version 0.1
 * \date 22/01/21
 *
 * \section DESCRIPTION
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 */


/*!
 * 
 * \struct map_t map.h "map.h"
 * \brief Objet map
 * 
 */


/*!
 *
 * \fn void map_update(SDL_Rect * src_rect) 
 * \brief
 *
 * \param src_rect 
 * 
 */

static
void map_update(rect_tile_set_t * src_rect) 
{

    src_rect->rect.x += src_rect->rect.w + 1;

    if (src_rect->rect.x > src_rect->limit)
        src_rect->rect.x = 2;

}


/*!
 *
 * \fn void map_display(map_t * const map, SDL_Renderer * render, SDL_Rect src_rect, SDL_Rect pos_wind_rect)
 * \brief
 *
 * \param personnage 
 * \param render 
 * \param src_rect 
 * \param pos_wind_rect
 * 
 */

static
void map_display(map_t * const map, SDL_Renderer * render, SDL_Rect src_rect, SDL_Rect pos_wind_rect) 
{

    if (SDL_RenderCopy(render, map->texture, &src_rect, &pos_wind_rect) != 0)
        SDL_ExitWithError("Copy of rendering failed");
    
    SDL_RenderPresent(render);

}


/*!
 *
 * \fn void map_free(map_t ** map) 
 * \brief
 *
 * \param map 
 * 
 */

static 
void map_free(map_t ** map) 
{
    
    SDL_DestroyTexture((*map)->texture);

    free(*map);

}


/*!
 *
 * \fn map_t * map_create(char * name_file) 
 * \brief
 *
 * \param name_file 
 * 
 */

extern 
map_t * map_create(char * name_file) 
{

    map_t * map = NULL; 
    map = malloc(sizeof(map_t));

    map->texture = NULL;
    
    FILE * file = fopen(name_file, "r");

    if (!file)
    {
        printf("Loading of %s failed", name_file);
        return NULL;
    }

    fscanf(file,"%*s %i, %i, %i, %i;\n",&map->tile_set.rect.x, &map->tile_set.rect.y, &map->tile_set.rect.w, &map->tile_set.rect.h);

    map->update = map_update;
    map->display = map_display;
    map->free = map_free;

    return(map);
}


/*!
 *
 * \fn SDL_bool map_exist(map_t * const map)
 * \brief
 *
 * \param map 
 * 
 */

extern 
SDL_bool map_exist(map_t * const map)
{

    if(map == NULL) 
        return(SDL_FALSE);
    else
        return(SDL_TRUE); 

}
