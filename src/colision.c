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

//reglage pixel à faire

/*!
 * 
 * \file colision.c
 * \brief Systeme de colision.
 * \author Robin PAPILLON
 *
 */

void chargement_image(load_image_t tab_load_image[])
{
	tab_load_image[0].nom_image = "src\\tileset\\Maps\\town_hitbox.bmp";

	for (int i = 0; i < NB_IMAGE; i++)
	{
		tab_load_image[i].surface = SDL_LoadBMP(tab_load_image[i].nom_image);
	}
}

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

int character_moving(SDL_Renderer *pRenderer, SDL_Surface *couleur_image, load_image_t tab_load_image[NB_IMAGE], int x, int y, int direction)
{
	Uint8 r, rg, rd, rc, g, gg, gd, gc, b, bg, bd, bc;
	Uint32 pixel, pixelg, pixeld, pixelc;
	pixelc = getpixel(couleur_image, x, y);
	SDL_GetRGB(pixelc, couleur_image->format, &rc, &gc, &bc);
	printf("r = %i, rg = %i,rd =%i\n", r, rg, rd);
	//printf("rc = %i, gc = %i,bc =%i\n", rc, gc, bc);
	printf("x = %i, y = %i\n", x, y);
	if (direction == 0)
	{ //Haut
		pixel = getpixel(couleur_image, x + 68, y + 202); //Multiplier avec int pour arrondi en dessous
		pixeld = getpixel(couleur_image, x, y + 202);
		pixelg = getpixel(couleur_image, x + 135, y + 202);
		SDL_GetRGB(pixel, couleur_image->format, &r, &g, &b);
		SDL_GetRGB(pixelg, couleur_image->format, &rg, &gg, &bg);
		SDL_GetRGB(pixeld, couleur_image->format, &rd, &gd, &bd);
		if (y > 0 && r != 255 && rg != 255 && rd != 255) // && rc != 255)
		{
			return 1;
		}
		else
		{
			printf("Pas possible\n");
			return 0;
		}
	}

	else if (direction == 1)
	{ //Bas
		pixel = getpixel(couleur_image, x + 68, y + 240);
		pixeld = getpixel(couleur_image, x, y + 240);
		pixelg = getpixel(couleur_image, x + 135, y + 240);
		SDL_GetRGB(pixel, couleur_image->format, &r, &g, &b);
		SDL_GetRGB(pixelg, couleur_image->format, &rg, &gg, &bg);
		SDL_GetRGB(pixeld, couleur_image->format, &rd, &gd, &bd);
		if (y + 220 < 4185 && r != 255 && rg != 255 && rd != 255) // && rc != 255)
		{
			return 1;
		}
		else
		{
			printf("Pas possible\n");
			return 0;
		}
	}

	else if (direction == 2)
	{ //Droite
		pixel = getpixel(couleur_image, x + 165, y + 225);
		pixeld = getpixel(couleur_image, x + 165, y + 232);
		pixelg = getpixel(couleur_image, x + 165, y + 217);
		SDL_GetRGB(pixel, couleur_image->format, &r, &g, &b);
		SDL_GetRGB(pixelg, couleur_image->format, &rg, &gg, &bg);
		SDL_GetRGB(pixeld, couleur_image->format, &rd, &gd, &bd);
		if (x + 130 < 3660 && r != 255 && rg != 255 && rd != 255) // && rc != 255)
		{
			return 1;
		}
		else
		{
			printf("Pas possible\n");
			return 0;
		}
	}

	else if (direction == 3)
	{ //Gauche
		pixel = getpixel(couleur_image, x - 15, y + 225);
		pixeld = getpixel(couleur_image, x - 15, y + 217);
		pixelg = getpixel(couleur_image, x - 15, y + 232);
		SDL_GetRGB(pixel, couleur_image->format, &r, &g, &b);
		SDL_GetRGB(pixelg, couleur_image->format, &rg, &gg, &bg);
		SDL_GetRGB(pixeld, couleur_image->format, &rd, &gd, &bd);
		if (x > 0 && r != 255 && rg != 255 && rd != 255) // && rc != 255)
		{
			return 1;
		}
		else
		{
			printf("Pas possible\n");
			return 0;
		}
	}
}