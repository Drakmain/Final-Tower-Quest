#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <SDL_image.h>

#include "..\lib\colision.h"

#include "..\lib\commun.h"
#include "..\lib\character.h"
#include "..\lib\map.h"
#include "..\lib\town.h"
#include "..\lib\game.h"

/*!
 *
 * \file colision.c
 * \brief Systeme de collision.
 * \author Robin PAPILLON
 *
 */

/*!
 *
 * \fn chargement_image(load_image_t tab_load_image[NB_IMAGE])
 * \brief permet de charger les images des hitboxs dans le programme
 *
 * \param load_image_t structure de chargement d'image
 *
 */

void chargement_image(load_image_t tab_load_image[NB_IMAGE])
{
	tab_load_image[0].nom_image = "src\\tileset\\Maps\\town_hitbox_720p.bmp";
	tab_load_image[1].nom_image = "src\\tileset\\Maps\\town_hitbox_900p.bmp";
	tab_load_image[2].nom_image = "src\\tileset\\Maps\\town_hitbox_1080p.bmp";
	tab_load_image[3].nom_image = "src\\tileset\\Maps\\town_hitbox_1440p.bmp";

	for (int i = 0; i < NB_IMAGE; i++)
	{
		tab_load_image[i].surface = SDL_LoadBMP(tab_load_image[i].nom_image);
	}
}

/*!
 *
 * \fn getpixel(SDL_Surface *surface, int x, int y)
 * \brief Fonction permettant de récupérer un pixel sur une carte.
 *
 * \param surface carte
 * \param x position x
 * \param y position y
 *
 */

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	// Fonction getpixel tirée de la SDL 1 non incluse dans la SDL 2
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		return *p;
	case 2:
		return *(Uint16 *)p;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
	case 4:
		return *(Uint32 *)p;
	default:
		return 0; /* shouldn't happen, but avoids warnings */
	}
}

//0 --> up, 1 --> down,2 --> right,3 --> left

/*!
 *
 * \fn character_moving(game_t *game, SDL_Renderer *pRenderer, SDL_Surface *couleur_image, int x, int y, int direction)
 * \brief Fonction permettant de savoir si le joueur à le droit de se déplacer
 *
 * \param game est un pointeur sur l'objet game_t du jeu.
 * \param pRenderer est un pointeur sur le rendu SDL du jeu.
 * \param couleur_image carte en couleur
 * \param x position x
 * \param y position y
 * \param direction direction du joueur
 *
 */

int character_moving(game_t *game, SDL_Renderer *pRenderer, SDL_Surface *couleur_image, int x, int y, int direction)
{
	Uint8 r, rg, rd, g, gg, gd, b, bg, bd;
	Uint32 pixel, pixelg, pixeld;

	if (direction == 0)
	{ //Haut
		pixel = getpixel(couleur_image, x + (*game->WINDOWWIDTH) * 38 / 1280, y + (*game->WINDOWWIDTH) * 83 / 1280);
		pixeld = getpixel(couleur_image, x + (*game->WINDOWWIDTH) * 9 / 1280, y + (*game->WINDOWWIDTH) * 83 / 1280);
		pixelg = getpixel(couleur_image, x + (*game->WINDOWWIDTH) * 62 / 1280, y + (*game->WINDOWWIDTH) * 83 / 1280);
		SDL_GetRGB(pixel, couleur_image->format, &r, &g, &b);
		SDL_GetRGB(pixelg, couleur_image->format, &rg, &gg, &bg);
		SDL_GetRGB(pixeld, couleur_image->format, &rd, &gd, &bd);

		if (r != 255 && rg != 255 && rd != 255)
		{
			return 1;
		}
		else if (r == 255 && g == 255 && rg == 255 && gg == 255 && rd == 255 && gd == 255)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}

	else if (direction == 1)
	{ //Bas
		pixel = getpixel(couleur_image, x + (*game->WINDOWWIDTH) * 38 / 1280, y + (*game->WINDOWWIDTH) * 124 / 1280);
		pixeld = getpixel(couleur_image, x + (*game->WINDOWWIDTH) * 9 / 1280, y + (*game->WINDOWWIDTH) * 124 / 1280);
		pixelg = getpixel(couleur_image, x + (*game->WINDOWWIDTH) * 62 / 1280, y + (*game->WINDOWWIDTH) * 124 / 1280);
		SDL_GetRGB(pixel, couleur_image->format, &r, &g, &b);
		SDL_GetRGB(pixelg, couleur_image->format, &rg, &gg, &bg);
		SDL_GetRGB(pixeld, couleur_image->format, &rd, &gd, &bd);

		if (r != 255 && rg != 255 && rd != 255)
		{
			return 1;
		}
		else if (r == 255 && g == 255 && rg == 255 && gg == 255 && rd == 255 && gd == 255)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}

	else if (direction == 2)
	{ //Droite
		pixel = getpixel(couleur_image, x + (*game->WINDOWWIDTH) * 83 / 1280, y + (*game->WINDOWWIDTH) * 97 / 1280);
		pixeld = getpixel(couleur_image, x + (*game->WINDOWWIDTH) * 83 / 1280, y + (*game->WINDOWWIDTH) * 112 / 1280);
		pixelg = getpixel(couleur_image, x + (*game->WINDOWWIDTH) * 83 / 1280, y + (*game->WINDOWWIDTH) * 105 / 1280);
		SDL_GetRGB(pixel, couleur_image->format, &r, &g, &b);
		SDL_GetRGB(pixelg, couleur_image->format, &rg, &gg, &bg);
		SDL_GetRGB(pixeld, couleur_image->format, &rd, &gd, &bd);
		if (r != 255 && rg != 255 && rd != 255)
		{
			return 1;
		}
		else if (r == 255 && g == 255 && rg == 255 && gg == 255 && rd == 255 && gd == 255)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}

	else if (direction == 3)
	{ //Gauche
		pixel = getpixel(couleur_image, x - (*game->WINDOWWIDTH) * 12 / 1280, y + (*game->WINDOWWIDTH) * 97 / 1280);
		pixeld = getpixel(couleur_image, x - (*game->WINDOWWIDTH) * 12 / 1280, y + (*game->WINDOWWIDTH) * 112 / 1280);
		pixelg = getpixel(couleur_image, x - (*game->WINDOWWIDTH) * 12 / 1280, y + (*game->WINDOWWIDTH) * 105 / 1280);
		SDL_GetRGB(pixel, couleur_image->format, &r, &g, &b);
		SDL_GetRGB(pixelg, couleur_image->format, &rg, &gg, &bg);
		SDL_GetRGB(pixeld, couleur_image->format, &rd, &gd, &bd);
		if (r != 255 && rg != 255 && rd != 255)
		{
			return 1;
		}
		else if (r == 255 && g == 255 && rg == 255 && gg == 255 && rd == 255 && gd == 255)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}

	return 1;
}
