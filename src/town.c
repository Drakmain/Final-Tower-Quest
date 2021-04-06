#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "town.h"
#include "frame.h"
#include "map.h"
#include "character.h"



/*!
 *
 * \file town.c
 * \brief Gestion de la map town.
 * \author Enzo BRENNUS
 * \date 18/02/21
 *
 */

Uint8 * pixel(SDL_Surface * surface, int x, int y)
{
    Uint8 * pixels = (Uint8*)surface->pixels;
    Uint8 * pixel = pixels+y*surface->pitch+x;
    return pixel;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y){
	// Fonction getpixel tirée de la SDL 1 non incluse dans la SDL 2
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
    case 2:
        return *(Uint16 *)p;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
        return *(Uint32 *)p;
    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void chargement_image(load_image_t tab_load_image[NB_IMAGE]){

    tab_load_image[0].nom_image = "src\\tileset\\Maps\\town_hitbox.bmp";

    for (int i = 0; i < NB_IMAGE ; i++)
    {
        tab_load_image[i].surface = SDL_LoadBMP(tab_load_image[i].nom_image);
    }

}


 /*!
  *
  * \fn town(SDL_Renderer * render, int * WINDOWWIDTH, int * WINDOWHEIGHT, SDL_bool * program_launch)
  * \brief Permet la gestion de la premier map du jeu (town).
  *
  * \param render est un pointeur sur le rendu SDL.
  * \param WINDOWWIDTH est la largeur de la fenetre.
  * \param WINDOWHEIGHT est la hauteur de la fenetre.
  * \param program_launch A FINIR.
  *
  */

extern
void town(SDL_Renderer * render, int * WINDOWWIDTH, int * WINDOWHEIGHT, SDL_bool * program_launch){

    /*--- Initialization Variable ------------------------------------------------*/

    map_t* town = NULL;
    town = map_create(render, "src\\tileset\\Maps\\town.bmp", "src\\tileset\\Maps\\town.txt");

    load_image_t tab_load_image[NB_IMAGE];
    chargement_image(tab_load_image);

    if (town == NULL)
    {
        exit_with_error("Cannot create a map_t object > town.c Line 35");
    }

    character_t* Assassin = NULL;
    Assassin = character_create(render, "src\\tileset\\PJ\\Assassin.bmp", "src\\tileset\\PJ\\Assassin.txt");
    if (Assassin == NULL)
    {
        exit_with_error("Cannot create a character_t object > town.c Line 42");
    }

    SDL_Surface * surface = NULL;

    surface = SDL_LoadBMP("src\\tileset\\Maps\\town_hitbox.bmp");
    if (!surface)
    {
        SDL_ExitWithError("Loading of a BMP failed > character.c Line 123");
    }

    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    SDL_bool town_bool = SDL_TRUE;

    SDL_Event event;

    SDL_Rect pos_Wind_Assassin;
    pos_Wind_Assassin.h = Assassin->North_Walk.rect.h * MULTIPLIER;
    pos_Wind_Assassin.w = Assassin->North_Walk.rect.w * MULTIPLIER;
    printf("HAUTEUR = %d et LARGEUR = %d \n", pos_Wind_Assassin.h, pos_Wind_Assassin.w);
    pos_Wind_Assassin.x = (*WINDOWWIDTH - pos_Wind_Assassin.w) / 2;
    pos_Wind_Assassin.y = (*WINDOWHEIGHT - pos_Wind_Assassin.h) / 2;

    SDL_Rect pos_Wind_town;
    pos_Wind_town.x = town->tile_set.x;
    pos_Wind_town.y = town->tile_set.y;
    pos_Wind_town.h = town->tile_set.h * MULTIPLIER;
    pos_Wind_town.w = town->tile_set.w * MULTIPLIER;
    printf("POUR LA MAP : HAUTEUR = %d et LARGEUR = %d \n", pos_Wind_town.h, pos_Wind_town.w);

    int East_Walk = 0;
    int West_Walk = 0;
    int South_Walk = 0;
    int North_Walk = 0;

    /*int x = town->tile_set.w - (*WINDOWHEIGHT / 2);
    int y = town->tile_set.h - (*WINDOWWIDTH / 2);*/
    int x = 885; //885; // 1280 / 720 x = 312 y = 68
    int y = 420; //420; //1920 / 1080 x = 486 y = 102

    /*--- End Initialization Variable --------------------------------------------*/


    /*--- Main Loop --------------------------------------------------------------*/

    while (*program_launch && town_bool)
    {

        while (SDL_PollEvent(&event))
        {

            while (*program_launch == SDL_TRUE || (event.type == SDL_KEYDOWN && (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_UP])))
            {
                SDL_PollEvent(&event);


                if (event.type == SDL_QUIT || keyState[SDL_SCANCODE_ESCAPE])
                {
                    *program_launch = SDL_FALSE;
                }

                while (keyState[SDL_SCANCODE_RIGHT])
                {
                  for (int i = 0; i < 1; i++)
                    {
                        if(character_moving(/*Assassin, */render, tab_load_image->surface, tab_load_image, x, y, 2) == 0)  /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                        {
                            break;
                        }
                        else
                        {
                            East_Walk = 1;
                            frame_start =  SDL_GetTicks();

                            pos_Wind_town.x -= 25;
                            x += 25;


                            town->update(town, render, town->tile_set, pos_Wind_town);

                            Assassin->update(Assassin, render, Assassin->East_Walk, pos_Wind_Assassin);

                            render_frame(render);

                            if (SDL_RenderClear(render) != 0)
                            {
                                SDL_ExitWithError("Unable to clear rendering > town.c Line 131");
                            }
                        }
                    }
                    
                    SDL_PollEvent(&event);  
                }

                if (East_Walk == 1)
                {
                    Assassin->mov.x = 0;
                    Assassin->mov.y = 0;
                    town->update(town, render, town->tile_set, pos_Wind_town);
                    Assassin->update(Assassin, render, Assassin->East_Walk, pos_Wind_Assassin);
                    render_frame(render);
                    East_Walk = 0;
                }
                
                
                while (keyState[SDL_SCANCODE_LEFT])
                {
                    for (int i = 0; i < 1; i++)
                    {
                        if(character_moving(/*Assassin, */render, tab_load_image->surface, tab_load_image, x, y, 3) == 0)  /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                        {
                            break;
                        }
                        else
                        {
                            West_Walk = 1;
                            frame_start =  SDL_GetTicks();

                            pos_Wind_town.x += 25;
                            x -= 25;


                            town->update(town, render, town->tile_set, pos_Wind_town);

                            Assassin->update(Assassin, render, Assassin->West_Walk, pos_Wind_Assassin);

                            render_frame(render);

                            if (SDL_RenderClear(render) != 0)
                            {
                                SDL_ExitWithError("Unable to clear rendering > town.c Line 131");
                            }
                        }
                    }
                    
                    SDL_PollEvent(&event);  
                }

                if (West_Walk == 1)
                {
                    Assassin->mov.x = 0;
                    Assassin->mov.y = 0;
                    town->update(town, render, town->tile_set, pos_Wind_town);
                    Assassin->update(Assassin, render, Assassin->West_Walk, pos_Wind_Assassin);
                    render_frame(render);
                    West_Walk = 0;
                }
                

                while (keyState[SDL_SCANCODE_UP])
                {
                    for (int i = 0; i < 1; i++)
                    {
                        if(character_moving(/*Assassin, */render, tab_load_image->surface, tab_load_image, x, y, 0) == 0)  /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                        {
                            break;
                        }
                        else
                        {
                            South_Walk = 1;
                            frame_start =  SDL_GetTicks();

                            pos_Wind_town.y += 25;
                            y -= 25;


                            town->update(town, render, town->tile_set, pos_Wind_town);

                            Assassin->update(Assassin, render, Assassin->South_Walk, pos_Wind_Assassin);

                            render_frame(render);

                            if (SDL_RenderClear(render) != 0)
                            {
                                SDL_ExitWithError("Unable to clear rendering > town.c Line 131");
                            }
                        }
                    }

                    SDL_PollEvent(&event); 
                }    

                if (South_Walk == 1)
                {
                    Assassin->mov.x = 0;
                    Assassin->mov.y = 0;
                    town->update(town, render, town->tile_set, pos_Wind_town);
                    Assassin->update(Assassin, render, Assassin->South_Walk, pos_Wind_Assassin);
                    render_frame(render);
                    South_Walk = 0;
                }


                while (keyState[SDL_SCANCODE_DOWN])
                {
                    
                    for (int i = 0; i < 1; i++)
                    {
                        if(character_moving(/*Assassin, */render, tab_load_image->surface, tab_load_image, x, y, 1) == 0)  /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                        {
                            break;
                        }
                        else
                        {
                            North_Walk = 1;
                            frame_start =  SDL_GetTicks();

                            pos_Wind_town.y -= 25;
                            y += 25;


                            town->update(town, render, town->tile_set, pos_Wind_town);

                            Assassin->update(Assassin, render, Assassin->North_Walk, pos_Wind_Assassin);

                            render_frame(render);

                            if (SDL_RenderClear(render) != 0)
                            {
                                SDL_ExitWithError("Unable to clear rendering > town.c Line 189");
                            }
                        }

                    }

                    SDL_PollEvent(&event);
                }

                if (North_Walk == 1)
                {
                    Assassin->mov.x = 0;
                    Assassin->mov.y = 0;
                    town->update(town, render, town->tile_set, pos_Wind_town);
                    Assassin->update(Assassin, render, Assassin->North_Walk, pos_Wind_Assassin);
                    render_frame(render);
                    North_Walk = 0;
                }

                /*
                Uint8 * pixel_surf = pixel(surface, pos_Wind_town.x, pos_Wind_town.y);

                SDL_GetRGB(*pixel_surf, surface->format, &r, &g, &b);

                printf("Couleur : rouge = %i, vert = %i, bleu = %i", r, g, b);
                */
               
            }

        }

    }

    /*--- End Main Loop ----------------------------------------------------------*/


    /*--- Free Memory ------------------------------------------------------------*/

    town->free(&town);
    Assassin->free(&Assassin);

    /*--- End Free Memory --------------------------------------------------------*/

}