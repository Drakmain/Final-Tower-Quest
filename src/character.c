#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\character.h"

/*!
 * 
 * \file character.c
 * \brief Gestion de l'objet character.
 * \author Enzo BRENNUS
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

    free((*character)->file_name_txt);
    free((*character)->file_name_bmp);
    free((*character)->file_name_save);

    free((*character)->save_name);
    free((*character)->charactere_name);
    free((*character)->position);

    free(*character);
    *character = NULL;

}


/*!
 *
 * \fn character_t * character_create(SDL_Renderer * render, char * file_name_save)
 * \brief Permet la creation du l'objet character.
 *
 * \param render est un pointeur sur le rendu SDL.
 * \param file_name_save A FINIR.
 * 
 * \return character Un objet character créé dans cette fonction.
 * \retval character_t * Un pointeur sur l'objet character.
 * 
 */

extern 
character_t * character_create(SDL_Renderer * render, char * file_name_save) 
{   

    /*--- Initialization variable ----------------------------------------------------*/

    FILE * file;

    character_t * character = NULL; 
    character = malloc(sizeof(character_t));

    character->file_name_txt = NULL;
    character->file_name_txt = malloc(sizeof(char) * 50);
    strcpy(character->file_name_txt, "src\\tileset\\PJ\\");

    character->file_name_bmp = NULL;
    character->file_name_bmp = malloc(sizeof(char) * 50);
    strcpy(character->file_name_bmp, "src\\tileset\\PJ\\");

    character->file_name_save = NULL;
    character->file_name_save = malloc(sizeof(char) * 50);
    strcpy(character->file_name_save, file_name_save);

    character->empty = SDL_FALSE;

    character->save_name = NULL;
    character->save_name = malloc(sizeof(char) * 20);

    character->charactere_name = NULL;
    character->charactere_name = malloc(sizeof(char) * 20);

    character->position = NULL;
    character->position = malloc(sizeof(char) * 20);

    character->texture = NULL;

    character->surface = NULL;

    /*--- End Initialization variable --------------------------------------------*/


    /*--- Open save file ---------------------------------------------------------*/

    file = fopen(character->file_name_save, "r");
    if (file == NULL)
    {
        exit_with_error("Loading of a file failed > character.c Line 114");
    }

    fscanf(file, "%*s %s ;\n", character->save_name);
    if (strcmp(character->save_name, ";") == 0)
    {
        character->empty = SDL_TRUE;
        fclose(file);
    }
    else
    {   
        fscanf(file, "%*s %s ;\n", character->charactere_name);

        fscanf(file, "%*s %s ;\n", character->position);
        fscanf(file, "%*s %i ;\n", &character->x);
        fscanf(file, "%*s %i ;\n", &character->y);

        fscanf(file, "%*s %i ;\n", &character->lvl);
        fscanf(file, "%*s %i ;\n", &character->xp);

        fscanf(file, "%*s %i ;\n", &character->life);
        fscanf(file, "%*s %i ;\n", &character->mana);

        fclose(file);

        /*----------------------------------------------------------------------------*/


        /*--- Open txt file ----------------------------------------------------------*/

        strcat(character->file_name_txt, character->charactere_name);
        strcat(character->file_name_txt, ".txt");

        file = fopen(character->file_name_txt, "r");
        if (file == NULL)
        {
            exit_with_error("Loading of a file failed > character.c Line 158");
        }

        fscanf(file, "%*s %i, %i, %i;\n", &character->R, &character->G, &character->B);
        fscanf(file, "%*s %i, %i, %i, %i, %i;\n", &character->South_Walk.rect.x, &character->South_Walk.rect.y, &character->South_Walk.rect.w, &character->South_Walk.rect.h, &character->South_Walk.limit);
        fscanf(file, "%*s %i, %i, %i, %i, %i;\n", &character->East_Walk.rect.x, &character->East_Walk.rect.y, &character->East_Walk.rect.w, &character->East_Walk.rect.h, &character->East_Walk.limit);
        fscanf(file, "%*s %i, %i, %i, %i, %i;\n", &character->North_Walk.rect.x, &character->North_Walk.rect.y, &character->North_Walk.rect.w, &character->North_Walk.rect.h, &character->North_Walk.limit);
        fscanf(file, "%*s %i, %i, %i, %i, %i;\n", &character->West_Walk.rect.x, &character->West_Walk.rect.y, &character->West_Walk.rect.w, &character->West_Walk.rect.h, &character->West_Walk.limit);
        fscanf(file, "%*s %i, %i, %i, %i;\n", &character->Damage_Taken.x, &character->Damage_Taken.y, &character->Damage_Taken.w, &character->Damage_Taken.h);
        fscanf(file, "%*s %i, %i, %i, %i;\n", &character->Weak.x, &character->Weak.y, &character->Weak.w, &character->Weak.h);
        fscanf(file, "%*s %i, %i, %i, %i;\n", &character->Dead.x, &character->Dead.y, &character->Dead.w, &character->Dead.h);

        fclose(file);

        /*----------------------------------------------------------------------------*/


        /*--- Open bmp file ----------------------------------------------------------*/

        strcat(character->file_name_bmp, character->charactere_name);
        strcat(character->file_name_bmp, ".bmp");

        character->surface = SDL_LoadBMP(character->file_name_bmp);
        if (!character->surface)
        {
            SDL_ExitWithError("Loading of a BMP failed > character.c Line 185");
        }

        SDL_SetColorKey(character->surface, SDL_TRUE, SDL_MapRGB(character->surface->format, character->R, character->G, character->B));

        character->texture = SDL_CreateTextureFromSurface(render, character->surface);
        if (!character->texture)
        {
            SDL_ExitWithError("Cannot create a texture from a surface > character.c Line 131");
        }

        /*----------------------------------------------------------------------------*/

    }

    /*--- Initialization method --------------------------------------------------*/

    character->update = character_update;
    character->free = character_free;

    /*----------------------------------------------------------------------------*/

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
    {
        return(SDL_FALSE);
    }  
    else
    {
        return(SDL_TRUE); 
    }

}