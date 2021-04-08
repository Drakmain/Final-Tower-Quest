#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "..\lib\town.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\character.h"
#include "..\lib\colision.h"
#include "..\lib\menu_in_game.h"
#include "..\lib\combat.h"
#include "..\lib\transition.h"

/*!
 *
 * \file town.c
 * \brief Gestion de la map town.
 * \author Enzo BRENNUS
 *
 */

#define MULTIPLIER 7.5

/*!
 *
 * \fn town(game_t * game, character_t * character)
 * \brief Permet la gestion de la premier map du jeu (town).
 *
 * \param game A FINIR.
 * \param character A FINIR.
 *
 */

extern void town(game_t *game, character_t *character)
{
    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Texture *texture_render = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

    map_t *town = NULL;
    town = map_create(game->render, "src\\tileset\\Maps\\town.bmp", "src\\tileset\\Maps\\town.txt");
    if (town == NULL)
    {
        exit_with_error("Cannot create a map_t object > town.c Line 35");
    }

    SDL_bool *town_bool = malloc(sizeof(SDL_bool));
    *town_bool = SDL_TRUE;

    load_image_t tab_load_image[NB_IMAGE];
    chargement_image(tab_load_image);

    SDL_Surface *surface = NULL;

    surface = SDL_LoadBMP("src\\tileset\\Maps\\town_hitbox.bmp");
    if (!surface)
    {
        SDL_ExitWithError("Loading of a BMP failed > character.c Line 123");
    }

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_character.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    printf("HAUTEUR = %d et LARGEUR = %d \n", pos_Wind_character.h, pos_Wind_character.w);
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 2;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2;

    SDL_Rect pos_Wind_town;
    pos_Wind_town.x = town->tile_set.x + 0;
    pos_Wind_town.y = town->tile_set.y - 1000;
    pos_Wind_town.h = town->tile_set.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_town.w = town->tile_set.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    printf("POUR LA MAP : HAUTEUR = %d et LARGEUR = %d \n", pos_Wind_town.h, pos_Wind_town.w);

    int East_Walk = 0;
    int West_Walk = 0;
    int South_Walk = 0;
    int North_Walk = 0;

    /*int x = town->tile_set.w - (*WINDOWHEIGHT / 2);
    int y = town->tile_set.h - (*WINDOWWIDTH / 2);*/
    int x = 885 - 200;  //885; // 1280 / 720 x = 312 y = 68
    int y = 420 + 1000; //420; //1920 / 1080 x = 486 y = 102

    /*--- End Initialization Variable --------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, town->texture, &town->tile_set, &pos_Wind_town);
    SDL_RenderCopy(game->render, character->texture, &character->South_Walk.rect, &pos_Wind_character);

    SDL_RenderPresent(game->render);

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && *town_bool)
    {
        while (SDL_PollEvent(&event))
        {
            while ((*game->program_launch && *town_bool) || (event.type == SDL_KEYDOWN && (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_ESCAPE])))
            {
                SDL_PollEvent(&event);

                SDL_SetRenderTarget(game->render, texture_render);

                SDL_RenderClear(game->render);

                SDL_RenderCopy(game->render, town->texture, &town->tile_set, &pos_Wind_town);
                SDL_RenderCopy(game->render, character->texture, &character->mov, &pos_Wind_character);

                SDL_SetRenderTarget(game->render, NULL);

                /*--- Event to Exit Program ------------------------------------------*/

                if (event.type == SDL_QUIT)
                {
                    (*game->program_launch) = SDL_FALSE;
                }

                /*--- End Event to Exit Program --------------------------------------*/

                /*--- Event to enter in game menu ------------------------------------*/

                if (keyState[SDL_SCANCODE_ESCAPE])
                {
                    menu_in_game(game, town_bool, character, texture_render);
                    while (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
                        SDL_PollEvent(&event);
                }
                
                /*--- End Event to enter in game menu --------------------------------*/

                if (keyState[SDL_SCANCODE_SPACE])
                {
                    transition(game, texture_render);

                    combat(game, character, town, texture_render);
                }

                while (keyState[SDL_SCANCODE_RIGHT] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (character_moving(game->render, tab_load_image->surface, tab_load_image, x, y, 2) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                        {
                            break;
                        }
                        else
                        {
                            East_Walk = 1;

                            frame_start = SDL_GetTicks();

                            pos_Wind_town.x -= (*game->WINDOWWIDTH) * 25 / 2560;
                            x -= 25;

                            town->update(town, game->render, town->tile_set, pos_Wind_town);

                            character->update(character, game->render, character->East_Walk, pos_Wind_character);

                            render_frame(game->render);

                            if (SDL_RenderClear(game->render) != 0)
                            {
                                SDL_ExitWithError("Unable to clear rendering > town.c Line 102");
                            }
                        }
                    }

                    SDL_PollEvent(&event);
                }

                if (East_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    town->update(town, game->render, town->tile_set, pos_Wind_town);
                    character->update(character, game->render, character->East_Walk, pos_Wind_character);
                    render_frame(game->render);
                    East_Walk = 0;
                }

                while (keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (character_moving(game->render, tab_load_image->surface, tab_load_image, x, y, 3) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                        {
                            break;
                        }
                        else
                        {
                            West_Walk = 1;

                            frame_start = SDL_GetTicks();

                            pos_Wind_town.x += (*game->WINDOWWIDTH) * 25 / 2560;
                            x += 25;

                            town->update(town, game->render, town->tile_set, pos_Wind_town);

                            character->update(character, game->render, character->West_Walk, pos_Wind_character);

                            render_frame(game->render);

                            if (SDL_RenderClear(game->render) != 0)
                            {
                                SDL_ExitWithError("Unable to clear rendering > town.c Line 131");
                            }
                        }
                    }

                    SDL_PollEvent(&event);
                }

                if (West_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    town->update(town, game->render, town->tile_set, pos_Wind_town);
                    character->update(character, game->render, character->West_Walk, pos_Wind_character);
                    render_frame(game->render);
                    West_Walk = 0;
                }

                while (keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (character_moving(game->render, tab_load_image->surface, tab_load_image, x, y, 0) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                        {
                            break;
                        }
                        else
                        {
                            North_Walk = 1;

                            frame_start = SDL_GetTicks();

                            pos_Wind_town.y += (*game->WINDOWWIDTH) * 25 / 2560;
                            y += 25;

                            town->update(town, game->render, town->tile_set, pos_Wind_town);

                            character->update(character, game->render, character->North_Walk, pos_Wind_character);

                            render_frame(game->render);

                            if (SDL_RenderClear(game->render) != 0)
                            {
                                SDL_ExitWithError("Unable to clear rendering, town.c Line 160");
                            }
                        }
                    }

                    SDL_PollEvent(&event);
                }

                if (North_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    town->update(town, game->render, town->tile_set, pos_Wind_town);
                    character->update(character, game->render, character->North_Walk, pos_Wind_character);
                    render_frame(game->render);
                    North_Walk = 0;
                }

                while (keyState[SDL_SCANCODE_DOWN] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (character_moving(game->render, tab_load_image->surface, tab_load_image, x, y, 1) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                        {
                            break;
                        }
                        else
                        {
                            South_Walk = 1;

                            frame_start = SDL_GetTicks();

                            pos_Wind_town.y -= (*game->WINDOWWIDTH) * 25 / 2560;
                            y -= 25;

                            town->update(town, game->render, town->tile_set, pos_Wind_town);

                            character->update(character, game->render, character->South_Walk, pos_Wind_character);

                            render_frame(game->render);

                            if (SDL_RenderClear(game->render) != 0)
                            {
                                SDL_ExitWithError("Unable to clear rendering > town.c Line 189");
                            }
                        }
                    }

                    SDL_PollEvent(&event);
                }

                if (South_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    town->update(town, game->render, town->tile_set, pos_Wind_town);
                    character->update(character, game->render, character->South_Walk, pos_Wind_character);
                    render_frame(game->render);
                    South_Walk = 0;
                }
            }
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    town->free(&town);

    /*--- End Free Memory --------------------------------------------------------*/
}
