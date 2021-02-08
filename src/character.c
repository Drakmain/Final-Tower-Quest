#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "character.h"
#include "commun.h"
#include "error.h"

/*!
 * 
 * \file character.c
 * \brief Gestion objet character.
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
 * \struct character_t character.h "character.h"
 * \brief Objet character
 * 
 */


/*!
 *
 * \fn void character_update(SDL_Rect * src_rect) 
 * \brief
 *
 * \param src_rect 
 * 
 */

static
void character_update(rect_tile_set_t * src_rect) 
{

    src_rect->rect.x += src_rect->rect.w + 1;

    if (src_rect->rect.x > src_rect->limit)
        src_rect->rect.x = 2;

}


/*!
 *
 * \fn void character_display(character_t * const character) 
 * \brief
 *
 * \param character 
 * \param render 
 * \param src_rect 
 * \param pos_wind_rect
 * 
 */

static
void character_display(character_t * const character, SDL_Renderer * render, SDL_Rect src_rect, SDL_Rect pos_wind_rect) 
{

    if (SDL_RenderCopy(render, character->texture, &src_rect, &pos_wind_rect) != 0)
        SDL_ExitWithError("Copy of rendering failed");
    
    SDL_RenderPresent(render);

}


/*!
 *
 * \fn void character_free(character_t ** character)  
 * \brief
 *
 * \param character 
 * 
 */

static 
void character_free(character_t ** character) 
{

    SDL_DestroyTexture((*character)->texture);

    free(*character);

}


/*!
 *
 * \fn character_t * character_create(char * name_file) 
 * \brief
 *
 * \param name_file
 * 
 */

extern 
character_t * character_create(char * name_file) 
{

    character_t * character = NULL; 
    character = malloc(sizeof(character_t));

    character->texture = NULL;

    FILE * file = fopen(name_file, "r");

    if (!file)
    {
        printf("Loading of %s failed", name_file);
        return NULL;
    }

    fscanf(file,"%*s %i, %i, %i, %i, %i;\n", &character->North_Walk.rect.x, &character->North_Walk.rect.y, &character->North_Walk.rect.w, &character->North_Walk.rect.h, &character->North_Walk.limit);
    fscanf(file,"%*s %i, %i, %i, %i, %i;\n", &character->South_Walk.rect.x, &character->South_Walk.rect.y, &character->South_Walk.rect.w, &character->South_Walk.rect.h, &character->South_Walk.limit);
    fscanf(file,"%*s %i, %i, %i, %i, %i;\n", &character->Side_Walk.rect.x, &character->Side_Walk.rect.y, &character->Side_Walk.rect.w, &character->Side_Walk.rect.h, &character->Side_Walk.limit);
    fscanf(file,"%*s %i, %i, %i, %i, %i;\n", &character->Win.rect.x, &character->Win.rect.y, &character->Win.rect.w, &character->Win.rect.h, &character->Win.limit);

    character->update = character_update;
    character->display = character_display;
    character->free = character_free;

    return(character);
}


/*!
 *
 * \fn SDL_bool character_exist(character_t * const character)
 * \brief
 *
 * \param character
 * 
 */

extern 
SDL_bool character_exist(character_t * const character)
{

    if(character == NULL) 
        return(SDL_FALSE);
    else
        return(SDL_TRUE); 

}
