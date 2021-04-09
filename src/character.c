#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\lib\character.h"
#include "..\lib\attacks_character.h"

/*!
 *
 * \file character.c
 * \brief Gestion de l'objet character.
 * \author Enzo BRENNUS
 *
 */

/*!
 *
 * \struct attack_character_t character.h "character.h"
 * \brief Structure de l'objet attack_character_t.
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
 * \fn character_update(character_t *character, SDL_Renderer *render, tile_set_t base_rect, SDL_Rect pos_wind_rect)
 * \brief Permet la mise a jour d'un objet character_t.
 *
 * \param character est un pointeur sur un objet character_t.
 * \param render est un pointeur sur le rendu SDL.
 * \param base_rect A FINIR
 * \param pos_wind_rect A FINIR
 *
 */

static void character_update(character_t *character, SDL_Renderer *render, tile_set_t base_rect, SDL_Rect pos_wind_rect)
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
 * \fn character_free(character_t ** character)
 * \brief Permet la liberation d'un objet character.
 *
 * \param character est un objet character_t qui doit etre libéré.
 *
 */

static void character_free(character_t **character)
{
    SDL_DestroyTexture((*character)->texture);

    SDL_FreeSurface((*character)->surface);

    free((*character)->file_name_txt);
    free((*character)->file_name_bmp);
    free((*character)->file_name_save);

    free((*character)->save_name);
    free((*character)->classe_name);
    free((*character)->position);

    for (int i = 0; i < NB_ATTACKS; i++)
    {
        free((*character)->attacks[i].name);
        free((*character)->attacks[i].description);
    }

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

extern character_t *character_create(SDL_Renderer *render, char *file_name_save)
{
    /*--- Initialization variable ----------------------------------------------------*/

    FILE *file;

    character_t *character = NULL;
    character = malloc(sizeof(character_t));

    character->attacks = malloc(sizeof(attack_character_t) * NB_ATTACKS);

    character->file_name_txt = NULL;
    character->file_name_txt = malloc(sizeof(char) * 50);
    strcpy(character->file_name_txt, "src\\tileset\\PJ\\");

    character->file_name_bmp = NULL;
    character->file_name_bmp = malloc(sizeof(char) * 50);
    strcpy(character->file_name_bmp, "src\\tileset\\PJ\\");

    character->file_name_save = NULL;
    character->file_name_save = malloc(sizeof(char) * 50);
    strcpy(character->file_name_save, file_name_save);
    character->file_name_save = (char *)realloc(character->file_name_save, strlen(character->file_name_save) * sizeof(char) + 1);

    character->empty = SDL_FALSE;

    character->save_name = NULL;
    character->save_name = malloc(sizeof(char) * 20);

    character->classe_name = NULL;
    character->classe_name = malloc(sizeof(char) * 20);

    character->position = NULL;
    character->position = malloc(sizeof(char) * 20);

    for (int i = 0; i < NB_ATTACKS; i++)
    {
        character->attacks[i].name = calloc(50, sizeof(char));
        character->attacks[i].description = calloc(100, sizeof(char));
    }

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
    character->save_name = (char *)realloc(character->save_name, strlen(character->save_name) * sizeof(char) + 1);

    if (strcmp(character->save_name, ";") == 0)
    {
        character->empty = SDL_TRUE;
        fclose(file);
    }
    else
    {
        fscanf(file, "%*s %s ;\n", character->classe_name);
        character->classe_name = (char *)realloc(character->classe_name, strlen(character->classe_name) * sizeof(char) + 1);

        fscanf(file, "%*s %s ;\n", character->position);
        character->position = (char *)realloc(character->position, strlen(character->position) * sizeof(char) + 1);

        fscanf(file, "%*s %i ;\n", &character->x);
        fscanf(file, "%*s %i ;\n", &character->y);

        fscanf(file, "%*s %i ;\n", &character->lvl);
        fscanf(file, "%*s %i ;\n", &character->xp);

        fscanf(file, "%*s %i ;\n", &character->max_life);
        fscanf(file, "%*s %i ;\n", &character->life);
        fscanf(file, "%*s %i ;\n", &character->max_mana);
        fscanf(file, "%*s %i ;\n", &character->mana);

        fscanf(file, "%*s %i ;\n", &character->vitalite);
        fscanf(file, "%*s %i ;\n", &character->puissance);
        fscanf(file, "%*s %i ;\n", &character->intelligence);
        fscanf(file, "%*s %i ;\n", &character->agilite);
        fscanf(file, "%*s %i ;\n", &character->defense);
        fscanf(file, "%*s %i ;\n", &character->points_dispo);

        fscanf(file, "%*s %i ;\n", &character->nb_petite_popo_soin);
        fscanf(file, "%*s %i ;\n", &character->nb_moyenne_popo_soin);
        fscanf(file, "%*s %i ;\n", &character->nb_petite_popo_mana);
        fscanf(file, "%*s %i ;\n", &character->nb_moyenne_popo_mana);
        fscanf(file, "%*s %i ;\n", &character->nb_popo_puissance);
        fscanf(file, "%*s %i ;\n", &character->nb_popo_agi);

        fclose(file);

        /*----------------------------------------------------------------------------*/

        character->nb_tour_restant_puissance = 0;
        character->nb_tour_restant_agi = 0;

        /*--- Open txt file ----------------------------------------------------------*/

        strcat(character->file_name_txt, character->classe_name);
        strcat(character->file_name_txt, ".txt");
        character->file_name_txt = (char *)realloc(character->file_name_txt, strlen(character->file_name_txt) * sizeof(char) + 1);

        file = fopen(character->file_name_txt, "r");
        if (file == NULL)
        {
            exit_with_error("Loading of a file failed > character.c Line 158");
        }

        fscanf(file, "RGB:          %i, %i, %i;\n", &character->R, &character->G, &character->B);
        fscanf(file, "South_Walk:   %i, %i, %i, %i, %i;\n", &character->South_Walk.rect.x, &character->South_Walk.rect.y, &character->South_Walk.rect.w, &character->South_Walk.rect.h, &character->South_Walk.limit);
        fscanf(file, "East_Walk:    %i, %i, %i, %i, %i;\n", &character->East_Walk.rect.x, &character->East_Walk.rect.y, &character->East_Walk.rect.w, &character->East_Walk.rect.h, &character->East_Walk.limit);
        fscanf(file, "North_Walk:   %i, %i, %i, %i, %i;\n", &character->North_Walk.rect.x, &character->North_Walk.rect.y, &character->North_Walk.rect.w, &character->North_Walk.rect.h, &character->North_Walk.limit);
        fscanf(file, "West_Walk:    %i, %i, %i, %i, %i;\n", &character->West_Walk.rect.x, &character->West_Walk.rect.y, &character->West_Walk.rect.w, &character->West_Walk.rect.h, &character->West_Walk.limit);
        fscanf(file, "Damage_Taken: %i, %i, %i, %i;\n", &character->Damage_Taken.x, &character->Damage_Taken.y, &character->Damage_Taken.w, &character->Damage_Taken.h);
        fscanf(file, "Weak:         %i, %i, %i, %i;\n", &character->Weak.x, &character->Weak.y, &character->Weak.w, &character->Weak.h);
        fscanf(file, "Dead:         %i, %i, %i, %i;\n", &character->Dead.x, &character->Dead.y, &character->Dead.w, &character->Dead.h);

        fscanf(file, "Niveau 1:\n%s , %i, %i - %i, %s ;\n%s , %i, %i - %i, %s ;\n%s , %i, %i - %i, %s ;\n",
               character->attacks[0].name, &character->attacks[0].mana, &character->attacks[0].dmg_min, &character->attacks[0].dmg_max, character->attacks[0].description,
               character->attacks[1].name, &character->attacks[1].mana, &character->attacks[1].dmg_min, &character->attacks[1].dmg_max, character->attacks[1].description,
               character->attacks[2].name, &character->attacks[2].mana, &character->attacks[2].dmg_min, &character->attacks[2].dmg_max, character->attacks[2].description);
        fscanf(file, "Niveau 5: %s , %i, %i - %i, %s ;\n", character->attacks[3].name, &character->attacks[3].mana, &character->attacks[3].dmg_min, &character->attacks[3].dmg_max, character->attacks[3].description);
        fscanf(file, "Niveau 10: %s , %i, %i - %i, %s ;\n", character->attacks[4].name, &character->attacks[4].mana, &character->attacks[4].dmg_min, &character->attacks[4].dmg_max, character->attacks[4].description);
        fscanf(file, "Niveau 15: %s , %i, %i - %i, %s ;\n", character->attacks[5].name, &character->attacks[5].mana, &character->attacks[5].dmg_min, &character->attacks[5].dmg_max, character->attacks[5].description);
        fscanf(file, "Niveau 20: %s , %i, %i - %i, %s ;\n", character->attacks[6].name, &character->attacks[6].mana, &character->attacks[6].dmg_min, &character->attacks[6].dmg_max, character->attacks[6].description);
        fscanf(file, "Niveau 25: %s , %i, %i - %i, %s ;\n", character->attacks[7].name, &character->attacks[7].mana, &character->attacks[7].dmg_min, &character->attacks[7].dmg_max, character->attacks[7].description);
        fscanf(file, "Niveau 30: %s , %i, %i - %i, %s ;\n", character->attacks[8].name, &character->attacks[8].mana, &character->attacks[8].dmg_min, &character->attacks[8].dmg_max, character->attacks[8].description);
        fscanf(file, "Niveau 35: %s , %i, %i - %i, %s ;\n", character->attacks[9].name, &character->attacks[9].mana, &character->attacks[9].dmg_min, &character->attacks[9].dmg_max, character->attacks[9].description);
        fscanf(file, "Niveau 40: %s , %i, %i - %i, %s ;\n", character->attacks[10].name, &character->attacks[10].mana, &character->attacks[10].dmg_min, &character->attacks[10].dmg_max, character->attacks[10].description);
        fscanf(file, "Niveau 45: %s , %i, %i - %i, %s ;\n", character->attacks[11].name, &character->attacks[11].mana, &character->attacks[11].dmg_min, &character->attacks[11].dmg_max, character->attacks[11].description);
        fscanf(file, "Niveau 50: %s , %i, %i - %i, %s ;", character->attacks[12].name, &character->attacks[12].mana, &character->attacks[12].dmg_min, &character->attacks[12].dmg_max, character->attacks[12].description);

        fclose(file);

        for (int i = 0; i < NB_ATTACKS; i++)
        {
            character->attacks[i].name = (char *)realloc(character->attacks[i].name, strlen(character->attacks[i].name) * sizeof(char) + 1);
            character->attacks[i].description = (char *)realloc(character->attacks[i].description, strlen(character->attacks[i].description) * sizeof(char) + 1);
        }

        /*----------------------------------------------------------------------------*/

        /*--- Open bmp file ----------------------------------------------------------*/

        strcat(character->file_name_bmp, character->classe_name);
        strcat(character->file_name_bmp, ".bmp");
        character->file_name_bmp = (char *)realloc(character->file_name_bmp, strlen(character->file_name_bmp) * sizeof(char) + 1);

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

    return (character);
}

/*!
 *
 * \fn character_exist(character_t * const character)
 * \brief Permet de verifier l'existence du l'objet character_t.
 *
 * \param character est un pointeur sur un objet character_t.
 *
 * \retval SDL_bool Une variable booléenne SDL.
 *
 */

extern SDL_bool character_exist(character_t *const character)
{
    if (character == NULL)
    {
        return (SDL_FALSE);
    }
    else
    {
        return (SDL_TRUE);
    }
}
