#ifndef _COMMUN_H_
#define _COMMUN_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include "..\lib\error.h"

/*!
 *
 * @file commun.h
 * @brief Définitions de structure et de constante commune
 * \author Enzo BRENNUS
 *
 */

/*!
 *
 * \enum resolution_e
 * \brief A FINIR
 *
 */

typedef enum
{
    RES_720P,  /*!< Type énuméré pour la resolution 720p (16:9). */
    RES_900P,  /*!< Type énuméré pour la resolution 900p (16:9). */
    RES_1080P, /*!< Type énuméré pour la resolution 1080 (16:9). */
    RES_1440P  /*!< Type énuméré pour la resolution 1440p (16:9). */
} resolution_e;

#define WINDOWWIDTH_720P 1280 /*!< Constante de la largeur d'une reoslution 720p (16:9). */
#define WINDOWHEIGHT_720P 720 /*!< Constante de la hauteur d'une reoslution 720p (16:9). */

#define WINDOWWIDTH_900P 1600 /*!< Constante de la largeur d'une reoslution 900p (16:9). */
#define WINDOWHEIGHT_900P 900 /*!< Constante de la hauteur d'une reoslution 900p (16:9). */

#define WINDOWWIDTH_1080P 1920  /*!< Constante de la largeur d'une reoslution 1080 (16:9). */
#define WINDOWHEIGHT_1080P 1080 /*!< Constante de la hauteur d'une reoslution 1080 (16:9). */

#define WINDOWWIDTH_1440P 2560  /*!< Constante de la largeur d'une reoslution 1440p (16:9). */
#define WINDOWHEIGHT_1440P 1440 /*!< Constante de la hauteur d'une reoslution 1440p (16:9). */

#define CHANCE_CBT 20
#define CHANCE_CBT_MAX 651

/*!
 *
 * \struct tile_set_t commun.h "commun.h"
 * \brief Structure de l'objet tile_set_t
 *
 */

typedef struct tile_set_s tile_set_t;

struct tile_set_s
{
    SDL_Rect rect; /*!< A FINIR */
    int limit;     /*!< A FINIR */
};

#endif
