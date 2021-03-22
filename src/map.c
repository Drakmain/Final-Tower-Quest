#include <stdio.h>
#include <stdlib.h>

#include "..\lib\map.h"

/*!
 * 
 * \file map.c
 * \brief Gestion de l'objet map.
 * \author Enzo BRENNUS
 * \date 18/02/21
 * 
 */


/*!
 * 
 * \struct map_t map.h "map.h"
 * \brief Structure de l'objet map_t.
 * 
 */


/*!
 *
 * \fn void map_update(map_t * map, SDL_Renderer * render, SDL_Rect src_rect, SDL_Rect pos_wind_rect)
 * \brief Permet la mise a jour d'un objet map_t.
 *
 * \param map est un pointeur sur un objet map_t.
 * \param render est un pointeur sur le rendu SDL.
 * \param src_rect A FINIR
 * \param pos_wind_rect A FINIR
 * 
 */

static
void map_update(map_t * map, SDL_Renderer * render, SDL_Rect src_rect, SDL_Rect pos_wind_rect) 
{

    if (SDL_RenderCopy(render, map->texture, &src_rect, &pos_wind_rect) != 0)
    {
        SDL_ExitWithError("Copy of rendering failed, map.c Line 40");
    }
        
}


/*!
 *
 * \fn void map_free(map_t ** map)
 * \brief Permet la liberation d'un objet map_t.
 *
 * \param map est un objet map_t qui doit etre libéré.
 * 
 */

static 
void map_free(map_t ** map) 
{
    
    SDL_DestroyTexture((*map)->texture);

    SDL_FreeSurface((*map)->surface);

    free(*map);

}


/*!
 *
 * \fn map_t * map_create(SDL_Renderer * render, char * file_name_bmp, char * file_name_txt)
 * \brief Permet la creation du l'objet map_t.
 *
 * \param render est un pointeur sur le rendu SDL.
 * \param file_name_bmp est une chaîne de caractères contenant le nom du fichier bmp.
 * \param file_name_txt est une chaîne de caractères contenant le nom du fichier txt.
 * 
 * \return map Un objet map_t créé dans cette fonction.
 * \retval map_t * Un pointeur sur l'objet map_t.
 * 
 */

extern 
map_t * map_create(SDL_Renderer * render, char * file_name_bmp, char * file_name_txt) 
{

    map_t * map = NULL; 
    map = malloc(sizeof(map_t));

    map->texture = NULL;
    
    FILE * file = fopen(file_name_txt, "r");
    if (!file)
    {
        exit_with_error("Loading of a txt file failed, map.c Line 93");
    }

    fscanf(file,"%*s %i, %i, %i, %i;\n", &map->tile_set.x, &map->tile_set.y, &map->tile_set.w, &map->tile_set.h);

    map->surface = SDL_LoadBMP(file_name_bmp);
    if (!map->surface)
    {
        SDL_ExitWithError("Loading of a bmp file failed, map.c Line 101");
    }

    map->texture = SDL_CreateTextureFromSurface(render, map->surface);
    if (!map->texture)
    {
        SDL_ExitWithError("Cannot create a texture from a surface, map.c Line 107");
    }
    
    map->update = map_update;
    map->free = map_free;

    return(map);
}


/*!
 *
 * \fn SDL_bool map_exist(map_t * const map)
 * \brief Permet de verifier l'existence du l'objet map.
 *
 * \param map est pointeur sur un objet map_t.
 * 
 * \retval SDL_bool Une variable booléenne SDL.
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