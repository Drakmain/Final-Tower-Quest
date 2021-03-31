#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "..\lib\enemie.h"

/*!
 *
 * \file enemie.c
 * \brief Gestion de l'objet enemie.
 * \author Enzo BRENNUS
 *
 */

/*!
 *
 * \struct enemie_t enemie.h "enemie.h"
 * \brief Structure de l'objet enemie_t.
 *
 */

/*!
 *
 * \fn void enemie_free(enemie_t ** enemie)
 * \brief Permet la liberation d'un objet enemie.
 *
 * \param enemie est un objet enemie_t qui doit etre libéré.
 *
 */

static void enemie_free(enemie_t **enemie)
{
    SDL_DestroyTexture((*enemie)->texture);

    SDL_FreeSurface((*enemie)->surface);

    free((*enemie)->file_name_bmp);

    free((*enemie)->name);

    free(*enemie);
    *enemie = NULL;
}

/*!
 *
 * \fn enemie_t * enemie_create(SDL_Renderer * render, char * file_name_enemies)
 * \brief Permet la creation du l'objet enemie.
 *
 * \param render est un pointeur sur le rendu SDL.
 * \param file_name_enemies est une chaîne de caractère contenant l'emplacement du fichier des informations de enemies.
 *
 * \return enemie Un objet enemie_t créé dans cette fonction.
 * \retval enemie_t * Un pointeur sur l'objet enemie_t.
 *
 */

extern enemie_t *enemie_create(SDL_Renderer *render, char *file_name_enemies)
{
    srand(time(NULL));

    /*--- Initialization variable ----------------------------------------------------*/

    enemie_t *enemie = NULL;
    enemie = malloc(sizeof(enemie_t));

    enemie->file_name_bmp = NULL;
    enemie->file_name_bmp = malloc(sizeof(char) * 50);
    strcpy(enemie->file_name_bmp, "src\\tileset\\Enemies\\");

    enemie->name = NULL;
    enemie->name = calloc(30, sizeof(char));

    enemie->boss = SDL_FALSE;

    enemie->texture = NULL;

    enemie->surface = NULL;

    int enemei_rand = 0;

    FILE *file;

    char temp[30];

    /*--- End Initialization variable --------------------------------------------*/

    /*--- Open txt file ----------------------------------------------------------*/

    char enemies[16][30];

    enemei_rand = rand() % 15;
    printf("enemei_rand: %i\n", enemei_rand);

    file = fopen(file_name_enemies, "r");

    for (int i = 0; i < 16; i++)
    {
        fscanf(file, "%s : %*s %i ;\n", temp, &enemie->life);
        strcpy(enemies[i], temp);
        strcpy(temp, "");
    }

    strcpy(enemie->name, enemies[enemei_rand]);

    fclose(file);

    /*----------------------------------------------------------------------------*/

    /*--- Open bmp file ----------------------------------------------------------*/

    strcat(enemie->file_name_bmp, enemie->name);
    strcat(enemie->file_name_bmp, ".bmp");

    enemie->surface = SDL_LoadBMP(enemie->file_name_bmp);
    if (!enemie->surface)
    {
        SDL_ExitWithError("Loading of a BMP failed > enemie.c Line 129");
    }

    SDL_SetColorKey(enemie->surface, SDL_TRUE, SDL_MapRGB(enemie->surface->format, enemie->R, enemie->G, enemie->B));

    enemie->texture = SDL_CreateTextureFromSurface(render, enemie->surface);
    if (!enemie->texture)
    {
        SDL_ExitWithError("Cannot create a texture from a surface > enemie.c Line 137");
    }

    /*----------------------------------------------------------------------------*/

    /*--- Initialization method --------------------------------------------------*/

    enemie->free = enemie_free;

    /*----------------------------------------------------------------------------*/

    return (enemie);
}

/*!
 *
 * \fn SDL_bool enemie_exist(enemie_t * const enemie)
 * \brief Permet de verifier l'existence du l'objet enemie_t.
 *
 * \param enemie est un pointeur sur un objet enemie_t.
 *
 * \retval SDL_bool Une variable booléenne SDL.
 *
 */

extern SDL_bool enemie_exist(enemie_t * const enemie)
{
    if (enemie == NULL)
        return (SDL_FALSE);
    else
        return (SDL_TRUE);
}