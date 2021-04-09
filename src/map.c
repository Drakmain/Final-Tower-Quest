#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\map.h"
#include "..\lib\attacks_character.h"

/*!
 * 
 * \file map.c
 * \brief Gestion de l'objet map.
 * \author Enzo BRENNUS
 * 
 */

#define NB_ATTACKS_ENEMIES 2

/*!
 *
 * \struct attack_enemie_t map.h "map.h"
 * \brief Structure de l'objet attack_enemie_t.
 *
 */

/*!
 *
 * \struct enemie_t map.h "map.h"
 * \brief Structure de l'objet enemie_t.
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
 * \fn map_update(map_t * map, SDL_Renderer * render, SDL_Rect src_rect, SDL_Rect pos_wind_rect)
 * \brief Permet la mise a jour d'un objet map_t.
 *
 * \param map est un pointeur sur un objet map_t.
 * \param render est un pointeur sur le rendu SDL.
 * \param src_rect A FINIR.
 * \param pos_wind_rect A FINIR.
 * 
 */

static void map_update(map_t *map, SDL_Renderer *render, SDL_Rect src_rect, SDL_Rect pos_wind_rect)
{
    if (SDL_RenderCopy(render, map->texture, &src_rect, &pos_wind_rect) != 0)
    {
        SDL_ExitWithError("Copy of rendering failed > map.c Line 40");
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

static void map_free(map_t **map)
{
    SDL_DestroyTexture((*map)->texture);

    SDL_FreeSurface((*map)->surface);

    if (strcmp((*map)->name, "town"))
    {
        for (int i = 0; i < NB_ATTACKS_ENEMIES; i++)
        {
            free((*map)->enemies[i].attack[0].name);
            free((*map)->enemies[i].attack[1].name);

            free((*map)->enemies[i].attack[0].description);
            free((*map)->enemies[i].attack[1].description);
        }

        for (int i = 0; i < NB_ENEMIES; i++)
        {
            free((*map)->enemies[i].name);

            SDL_DestroyTexture((*map)->enemies[i].texture);

            SDL_FreeSurface((*map)->enemies[i].surface);
        }
    }

    free(*map);
}

/*!
 *
 * \fn map_create(SDL_Renderer *render, char *name_map)
 * \brief Permet la creation du l'objet map_t.
 *
 * \param render est un pointeur sur le rendu SDL.
 * \param name_map A FINIR.
 * 
 * \return map Un objet map_t créé dans cette fonction.
 * \retval map_t * Un pointeur sur l'objet map_t.
 * 
 */

extern map_t *map_create(SDL_Renderer *render, char *name_map)
{
    /*--- Initialization variable ----------------------------------------------------*/
    map_t *map = NULL;
    map = malloc(sizeof(map_t));

    map->texture = NULL;

    map->surface = NULL;

    map->name = NULL;
    map->name = malloc(sizeof(char) * 50);
    strcpy(map->name, name_map);
    map->name = (char *)realloc(map->name, strlen(map->name) * sizeof(char) + 1);

    char *file_name = malloc(sizeof(char) * 50);

    char *path_map = NULL;
    path_map = malloc(sizeof(char) * 50);
    strcpy(path_map, "src\\tileset\\Maps\\");
    path_map = (char *)realloc(path_map, strlen(path_map) * sizeof(char) + 1);

    char *path_enemies = NULL;
    path_enemies = malloc(sizeof(char) * 50);
    strcpy(path_enemies, "src\\tileset\\Enemies\\");
    path_enemies = (char *)realloc(path_enemies, strlen(path_enemies) * sizeof(char) + 1);

    FILE *file;

    /*--- End Initialization variable --------------------------------------------*/

    /*--- Open map txt file ------------------------------------------------------*/

    strcpy(file_name, path_map);
    strcat(file_name, name_map);
    strcat(file_name, ".txt");

    file = fopen(file_name, "r");
    if (!file)
    {
        exit_with_error("Loading of a txt file failed > map.c Line 173");
    }

    fscanf(file, "%*s %i, %i, %i, %i;\n", &map->tile_set.x, &map->tile_set.y, &map->tile_set.w, &map->tile_set.h);

    fclose(file);

    /*----------------------------------------------------------------------------*/

    /*--- Open map bmp file ------------------------------------------------------*/

    strcpy(file_name, path_map);
    strcat(file_name, name_map);
    strcat(file_name, ".bmp");

    map->surface = SDL_LoadBMP(file_name);
    if (!map->surface)
    {
        SDL_ExitWithError("Loading of a bmp file failed > map.c Line 101");
    }

    map->texture = SDL_CreateTextureFromSurface(render, map->surface);
    if (!map->texture)
    {
        SDL_ExitWithError("Cannot create a texture from a surface > map.c Line 107");
    }

    /*----------------------------------------------------------------------------*/

    if (strcmp(name_map, "town"))
    {
        /*--- Initialization enemies ----------------------------------------------------*/

        map->enemies = malloc(sizeof(enemie_t) * NB_ENEMIES);

        for (int i = 0; i < NB_ENEMIES; i++)
        {
            map->enemies[i].texture = NULL;

            map->enemies[i].surface = NULL;

            map->enemies[i].name = NULL;
            map->enemies[i].name = malloc(sizeof(char) * 50);

            map->enemies[i].attack = malloc(sizeof(attack_enemie_t) * NB_ATTACKS_ENEMIES);

            for (int y = 0; y < NB_ATTACKS_ENEMIES; y++)
            {
                map->enemies[i].attack[y].name = NULL;
                map->enemies[i].attack[y].name = malloc(sizeof(char) * 50);

                map->enemies[i].attack[y].description = NULL;
            }
        }

        /*----------------------------------------------------------------------------*/

        /*--- Open enemies txt file --------------------------------------------------*/

        strcpy(file_name, path_enemies);
        strcat(file_name, name_map);
        strcat(file_name, ".txt");

        file = fopen(file_name, "r");
        if (!file)
        {
            exit_with_error("Loading of a txt file failed > map.c Line 211");
        }

        for (int i = 0; i < NB_ENEMIES; i++)
        {
            fscanf(file, "%s :\n", map->enemies[i].name);
            fscanf(file, "RGB: %i, %i, %i ;\n", &map->enemies[i].R, &map->enemies[i].G, &map->enemies[i].B);
            fscanf(file, "PV: %i ;\n", &map->enemies[i].life);
            fscanf(file, "%s : %i - %i ;\n", map->enemies[i].attack[0].name, &map->enemies[i].attack[0].dmg_min, &map->enemies[i].attack[0].dmg_max);
            fscanf(file, "%s : %i, %i - %i, %i, %i, %i ;\n", map->enemies[i].attack[1].name, &map->enemies[i].attack[1].percetange, &map->enemies[i].attack[1].dmg_min, &map->enemies[i].attack[1].dmg_max, &map->enemies[i].attack[1].modifier, &map->enemies[i].attack[1].effect_duration, &map->enemies[i].attack[1].effect_duration);
            fscanf(file, "EXP: %i ;\n\n", &map->enemies[i].exp);
        }

        fclose(file);

        /*----------------------------------------------------------------------------*/

        /*--- Open enemies bmp file --------------------------------------------------*/

        for (int i = 0; i < NB_ENEMIES; i++)
        {
            strcpy(file_name, path_enemies);
            strcat(file_name, map->enemies[i].name);
            strcat(file_name, ".bmp");

            map->enemies[i].surface = SDL_LoadBMP(file_name);
            if (!map->surface)
            {
                SDL_ExitWithError("Loading of a bmp file failed > map.c Line 101");
            }

            if (map->enemies[i].R != -1 && map->enemies[i].G != -1 && map->enemies[i].B != -1)
            {
                SDL_SetColorKey(map->enemies[i].surface, SDL_TRUE, SDL_MapRGB(map->enemies[i].surface->format, map->enemies[i].R, map->enemies[i].G, map->enemies[i].B));
            }

            map->enemies[i].texture = SDL_CreateTextureFromSurface(render, map->enemies[i].surface);
            if (!map->texture)
            {
                SDL_ExitWithError("Cannot create a texture from a surface > map.c Line 107");
            }
        }

        /*----------------------------------------------------------------------------*/

        /*--- Converting _ to espace -------------------------------------------------*/

        for (int i = 0; i < NB_ENEMIES; i++)
        {
            _toEspace(map->enemies[i].name);
            _toEspace(map->enemies[i].attack[0].name);
            _toEspace(map->enemies[i].attack[1].name);
        }

        /*----------------------------------------------------------------------------*/
    }

    /*--- Initialization method --------------------------------------------------*/

    map->update = map_update;
    map->free = map_free;

    /*----------------------------------------------------------------------------*/

    return (map);
}

/*!
 *
 * \fn map_exist(map_t * const map)
 * \brief Permet de verifier l'existence du l'objet map.
 *
 * \param map est pointeur sur un objet map_t.
 * 
 * \retval SDL_bool Une variable booléenne SDL.
 * 
 */

extern SDL_bool map_exist(map_t *const map)
{
    if (map == NULL)
        return (SDL_FALSE);
    else
        return (SDL_TRUE);
}