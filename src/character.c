#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"

/*!
 * 
 * \file character.c
 * \brief Gestion de l'objet character.
 * \author Enzo BRENNUS
 * \date 18/02/21
 *
 */


/*!
 * 
 * \struct character_t character.h "character.h"
 * \brief Structure de l'objet character_t.
 * 
 */


/*!
 *
 * \fn void character_update(character_t * character, SDL_Renderer * render, tile_set_t base_rect, SDL_Rect pos_wind_rect)
 * \brief Permet la mise a jour d'un objet character_t.
 *
 * \param character est un pointeur sur un objet character_t.
 * \param render est un pointeur sur le rendu SDL.
 * \param base_rect A FINIR
 * \param pos_wind_rect A FINIR
 * 
 */

static
void character_update(character_t * character, SDL_Renderer * render, tile_set_t base_rect, SDL_Rect pos_wind_rect) 
{

    character->mov.x += base_rect.rect.w + 1;

    if (character->mov.x > base_rect.limit || character->mov.y != base_rect.rect.y)
    {
        character->mov.w = base_rect.rect.w;
        character->mov.h = base_rect.rect.h;
        character->mov.x = base_rect.rect.x;
        character->mov.y = base_rect.rect.y;
    }

    if (SDL_RenderCopy(render, character->texture, &character->mov, &pos_wind_rect) != 0)
    {
        SDL_ExitWithError("Copy of rendering failed > character.c Line 51");
    }

}


/*!
 *
 * \fn void character_free(character_t ** character)
 * \brief Permet la liberation d'un objet character.
 *
 * \param character est un objet character_t qui doit etre libéré.
 * 
 */

static 
void character_free(character_t ** character) 
{

    SDL_DestroyTexture((*character)->texture);

    SDL_FreeSurface((*character)->surface);

    free(*character);

}


/*!
 *
 * \fn character_t * character_create(SDL_Renderer * render, char * file_name_bmp, char * file_name_txt)
 * \brief Permet la creation du l'objet character.
 *
 * \param render est un pointeur sur le rendu SDL.
 * \param file_name_bmp est une chaîne de caractères contenant le nom du fichier bmp.
 * \param file_name_txt est une chaîne de caractères contenant le nom du fichier txt.
 * 
 * \return character Un objet character créé dans cette fonction.
 * \retval character_t * Un pointeur sur l'objet character.
 * 
 */

extern 
character_t * character_create(SDL_Renderer * render, char * file_name_bmp, char * file_name_txt) 
{

    character_t * character = NULL; 
    character = malloc(sizeof(character_t));

    FILE * file = fopen(file_name_txt, "r");
    if (file == NULL)
    {
        exit_with_error("Loading of a file failed > character.c Line 102");
    }

    fscanf(file,"%*s %i, %i, %i;\n", &character->R, &character->G, &character->B);
    fscanf(file,"%*s %i, %i, %i, %i, %i;\n", &character->North_Walk.rect.x, &character->North_Walk.rect.y, &character->North_Walk.rect.w, &character->North_Walk.rect.h, &character->North_Walk.limit);
    fscanf(file,"%*s %i, %i, %i, %i, %i;\n", &character->East_Walk.rect.x, &character->East_Walk.rect.y, &character->East_Walk.rect.w, &character->East_Walk.rect.h, &character->East_Walk.limit);
    fscanf(file,"%*s %i, %i, %i, %i, %i;\n", &character->South_Walk.rect.x, &character->South_Walk.rect.y, &character->South_Walk.rect.w, &character->South_Walk.rect.h, &character->South_Walk.limit);
    fscanf(file,"%*s %i, %i, %i, %i, %i;\n", &character->West_Walk.rect.x, &character->West_Walk.rect.y, &character->West_Walk.rect.w, &character->West_Walk.rect.h, &character->West_Walk.limit);
    fscanf(file,"%*s %i, %i, %i, %i;\n", &character->Damage_Taken.x, &character->Damage_Taken.y, &character->Damage_Taken.w, &character->Damage_Taken.h);
    fscanf(file,"%*s %i, %i, %i, %i;\n", &character->Weak.x, &character->Weak.y, &character->Weak.w, &character->Weak.h);
    fscanf(file,"%*s %i, %i, %i, %i;\n", &character->Dead.x, &character->Dead.y, &character->Dead.w, &character->Dead.h);

    fclose(file);

    character->texture = NULL;

    character->surface = NULL;

    character->surface = SDL_LoadBMP(file_name_bmp);
    if (!character->surface)
    {
        SDL_ExitWithError("Loading of a BMP failed > character.c Line 123");
    }

    SDL_SetColorKey(character->surface, SDL_TRUE, SDL_MapRGB(character->surface->format, character->R, character->G, character->B));

    character->texture = SDL_CreateTextureFromSurface(render, character->surface);
    if (!character->texture)
    {
        SDL_ExitWithError("Cannot create a texture from a surface > character.c Line 131");
    }

    character->update = character_update;
    character->free = character_free;

    return(character);
}


/*!
 *
 * \fn SDL_bool character_exist(character_t * const character)
 * \brief Permet de verifier l'existence du l'objet character_t.
 *
 * \param character est un pointeur sur un objet character_t.
 * 
 * \retval SDL_bool Une variable booléenne SDL.
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