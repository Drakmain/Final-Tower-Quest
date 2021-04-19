#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\map.h"
#include "..\lib\character_attacks.h"

/*!
 * 
 * \file map.c
 * \brief Gestion de l'objet map.
 * \author Enzo BRENNUS
 * 
 */

/*!
 *
 * \struct attack_enemy_t map.h "map.h"
 * \brief Structure de l'objet attack_enemy_t.
 *
 */

/*!
 *
 * \struct enemy_t map.h "map.h"
 * \brief Structure de l'objet enemy_t.
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

    if (strcmp((*map)->name, "town") && strcmp((*map)->name, "tower"))
    {
        for (int i = 0; i < NB_ENEMIES; i++)
        {
            for (int y = 0; y < NB_ATTACKS_ENEMIES; y++)
            {
                free((*map)->enemies[i].attack[y].name);
            }

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
 * \param render est un pointeur sur le rendu SDL du jeu.
 * \param name_map Nom de la carte a mettre dans l'objet map_t.
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

    if (strcmp(name_map, "town") && strcmp(name_map, "tower"))
    {
        /*--- Initialization enemies ----------------------------------------------------*/

        map->enemies = NULL;
        map->enemies = malloc(sizeof(enemy_t) * NB_ENEMIES);

        for (int i = 0; i < NB_ENEMIES; i++)
        {
            map->enemies[i].texture = NULL;

            map->enemies[i].surface = NULL;

            map->enemies[i].name = NULL;
            map->enemies[i].name = malloc(sizeof(char) * 50);

            map->enemies[i].attack = malloc(sizeof(attack_enemy_t) * NB_ATTACKS_ENEMIES);

            for (int y = 0; y < NB_ATTACKS_ENEMIES; y++)
            {
                map->enemies[i].attack[y].name = NULL;
                map->enemies[i].attack[y].name = malloc(sizeof(char) * 50);
            }
        }

        map->boss = NULL;
        map->boss = malloc(sizeof(enemy_t));

        map->boss->name = NULL;
        map->boss->name = malloc(sizeof(char) * 50);

        map->boss->attack = malloc(sizeof(attack_enemy_t) * 5);

        for (int i = 0; i < 5; i++)
        {
            map->boss->attack[i].name = NULL;
            map->boss->attack[i].name = malloc(sizeof(char) * 50);
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
            fscanf(file, "VIT: %i ;\n", &map->enemies[i].speed);
            fscanf(file, "%s : %i - %i ;\n", map->enemies[i].attack[0].name, &map->enemies[i].attack[0].dmg_min, &map->enemies[i].attack[0].dmg_max);
            fscanf(file, "%s : %i, %i - %i, %i, %i, %i ;\n", map->enemies[i].attack[1].name, &map->enemies[i].attack[1].percentage, &map->enemies[i].attack[1].dmg_min, &map->enemies[i].attack[1].dmg_max, &map->enemies[i].attack[1].modifier, &map->enemies[i].attack[1].effect_duration, &map->enemies[i].attack[1].effect);
            fscanf(file, "EXP: %i ;\n\n", &map->enemies[i].exp);
            map->enemies[i].atb = 0;
            map->enemies[i].attack[i].effect_remaining = 0;
            map->enemies[i].boss = SDL_FALSE;
        }

        fscanf(file, "%s : %i ;\n", map->boss->name, &map->nb_attacks_boss);
        fscanf(file, "W: %i H: %i M: %i ;\n", &map->boss_W, &map->boss_H, &map->boss_multiplier);
        fscanf(file, "RGB: %i, %i, %i ;\n", &map->boss->R, &map->boss->G, &map->boss->B);
        fscanf(file, "PV: %i ;\n", &map->boss->life);
        fscanf(file, "VIT: %i ;\n", &map->boss->speed);
        fscanf(file, "%s : %i - %i ;\n", map->boss->attack[0].name, &map->boss->attack[0].dmg_min, &map->boss->attack[0].dmg_max);

        for (int i = 1; i < map->nb_attacks_boss; i++)
        {
            fscanf(file, "%s : %i, %i - %i, %i, %i, %i ;\n", map->boss->attack[i].name, &map->boss->attack[i].percentage, &map->boss->attack[i].dmg_min, &map->boss->attack[i].dmg_max, &map->boss->attack[i].modifier, &map->boss->attack[i].effect_duration, &map->boss->attack[i].effect_duration);
        }

        map->boss->atb = 0;

        map->boss->boss = SDL_TRUE;

        fclose(file);

        /*----------------------------------------------------------------------------*/

        /*--- Open enemies bmp file --------------------------------------------------*/

        for (int i = 0; i < NB_ENEMIES; i++)
        {
            strcpy(file_name, path_enemies);
            strcat(file_name, map->enemies[i].name);
            strcat(file_name, ".bmp");

            map->enemies[i].surface = SDL_LoadBMP(file_name);
            if (!map->enemies[i].surface)
            {
                SDL_ExitWithError("Loading of a bmp file failed > map.c Line 101");
            }

            if (map->enemies[i].R != -1 && map->enemies[i].G != -1 && map->enemies[i].B != -1)
            {
                SDL_SetColorKey(map->enemies[i].surface, SDL_TRUE, SDL_MapRGB(map->enemies[i].surface->format, map->enemies[i].R, map->enemies[i].G, map->enemies[i].B));
            }

            map->enemies[i].texture = SDL_CreateTextureFromSurface(render, map->enemies[i].surface);
            if (!map->enemies[i].texture)
            {
                SDL_ExitWithError("Cannot create a texture from a surface > map.c Line 107");
            }
        }

        strcpy(file_name, "src\\tileset\\Bosses\\");
        strcat(file_name, map->boss->name);
        strcat(file_name, ".bmp");

        map->boss->surface = SDL_LoadBMP(file_name);
        if (!map->boss->surface)
        {
            SDL_ExitWithError("Loading of a bmp file failed > map.c Line 101");
        }

        if (map->boss->R != -1 && map->boss->G != -1 && map->boss->B != -1)
        {
            SDL_SetColorKey(map->boss->surface, SDL_TRUE, SDL_MapRGB(map->boss->surface->format, map->boss->R, map->boss->G, map->boss->B));
        }

        map->boss->texture = SDL_CreateTextureFromSurface(render, map->boss->surface);
        if (!map->boss->texture)
        {
            SDL_ExitWithError("Cannot create a texture from a surface > map.c Line 107");
        }

        /*----------------------------------------------------------------------------*/

        /*--- Converting _ to espace -------------------------------------------------*/

        for (int i = 0; i < NB_ENEMIES; i++)
        {
            map->enemies[i].name = (char *)realloc(map->enemies[i].name, strlen(map->enemies[i].name) * sizeof(char) + 1);
            _toEspace(map->enemies[i].name);
            map->enemies[i].attack[0].name = (char *)realloc(map->enemies[i].attack[0].name, strlen(map->enemies[i].attack[0].name) * sizeof(char) + 1);
            _toEspace(map->enemies[i].attack[0].name);
            map->enemies[i].attack[1].name = (char *)realloc(map->enemies[i].attack[1].name, strlen(map->enemies[i].attack[1].name) * sizeof(char) + 1);
            _toEspace(map->enemies[i].attack[1].name);
        }

        for (int i = 0; i < map->nb_attacks_boss; i++)
        {
            map->boss->name = (char *)realloc(map->boss->name, strlen(map->boss->name) * sizeof(char) + 1);
            _toEspace(map->boss->name);
            map->boss->attack[i].name = (char *)realloc(map->boss->attack[i].name, strlen(map->boss->attack[i].name) * sizeof(char) + 1);
            _toEspace(map->boss->attack[i].name);
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
 * \fn enemy_cpy(enemy_t *dst, enemy_t *const src, SDL_Renderer *render, int nb_attacks_boss)
 * \brief Permet la copie d'un type enemy_t dans un autre.
 *
 * \param dst est le type enemy_t de destination.
 * \param src est le type enemy_t source.
 * \param render est un pointeur sur le rendu SDL du jeu.
 * \param nb_attacks_boss est le nombre d'attaques si l'ennemi est un boss.
 * 
 */

extern void enemy_cpy(enemy_t *dst, enemy_t *const src, SDL_Renderer *render, int nb_attacks_boss)
{
    dst->surface = SDL_ConvertSurface(src->surface, src->surface->format, src->surface->flags);
    if (!dst->surface)
    {
        SDL_ExitWithError("Erreur de duplication de la surface > map.c Line 343");
    }

    dst->texture = SDL_CreateTextureFromSurface(render, dst->surface);
    if (!dst->texture)
    {
        SDL_ExitWithError("Cannot create a texture from a surface > map.c Line 348");
    }

    dst->R = src->R;
    dst->G = src->G;
    dst->B = src->B;

    dst->tile_set.x = src->tile_set.x;
    dst->tile_set.y = src->tile_set.y;
    dst->tile_set.w = src->tile_set.w;
    dst->tile_set.h = src->tile_set.h;

    strcpy(dst->name, src->name);

    dst->boss = src->boss;

    if (src->boss == SDL_TRUE)
    {
        for (int i = 0; i < nb_attacks_boss; i++)
        {
            strcpy(dst->attack[i].name, src->attack[i].name);

            dst->attack[i].dmg_min = src->attack[i].dmg_min;
            dst->attack[i].dmg_max = src->attack[i].dmg_max;

            dst->attack[i].effect = src->attack[i].effect;
            dst->attack[i].effect_duration = src->attack[i].effect_duration;
            dst->attack[i].effect_remaining = src->attack[i].effect_remaining;
            dst->attack[i].modifier = src->attack[i].modifier;
            dst->attack[i].percentage = src->attack[i].percentage;
        }
    }
    else
    {
        for (int i = 0; i < NB_ATTACKS_ENEMIES; i++)
        {
            strcpy(dst->attack[i].name, src->attack[i].name);

            dst->attack[i].dmg_min = src->attack[i].dmg_min;
            dst->attack[i].dmg_max = src->attack[i].dmg_max;

            dst->attack[i].effect = src->attack[i].effect;
            dst->attack[i].effect_duration = src->attack[i].effect_duration;
            dst->attack[i].effect_remaining = src->attack[i].effect_remaining;
            dst->attack[i].modifier = src->attack[i].modifier;
            dst->attack[i].percentage = src->attack[i].percentage;
        }
    }

    dst->life = src->life;
    dst->speed = src->speed;
    dst->exp = src->exp;

    dst->atb = src->atb;
}

/*!
 *
 * \fn map_exist(map_t *const map)
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