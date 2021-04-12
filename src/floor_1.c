#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "..\lib\floor_1.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\character.h"
#include "..\lib\colision.h"
#include "..\lib\menu_in_game.h"
#include "..\lib\combat.h"
#include "..\lib\transition.h"
#include "..\lib\game_over.h"

/*!
 *
 * \file floor_1.c
 * \brief Gestion de la map floor_1.
 * \author Enzo BRENNUS
 *
 */

#define CHANCE_CBT 1

/*!
 *
 * \fn floor_1(game_t *game, character_t *character)
 * \brief Permet la gestion de la premier map du jeu (floor_1).
 *
 * \param game A FINIR.
 * \param character A FINIR.
 *
 */

extern void floor_1(game_t *game, character_t *character)
{
    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Texture *texture_render = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

    map_t *floor_1 = NULL;
    floor_1 = map_create(game->render, "floor_1");
    if (floor_1 == NULL)
    {
        exit_with_error("Cannot create a map_t object > floor_1.c Line 35");
    }

    SDL_bool *floor_1_bool = malloc(sizeof(SDL_bool));
    *floor_1_bool = SDL_TRUE;

    load_image_t tab_load_image[NB_IMAGE];
    chargement_image(tab_load_image);

    SDL_Surface *surface = NULL;
    /*
    surface = SDL_LoadBMP("src\\tileset\\Maps\\floor_1_hitbox.bmp");
    if (!surface)
    {
        SDL_ExitWithError("Loading of a BMP failed > character.c Line 123");
    }
    */
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    int rand_combat;

    SDL_Event event;

    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_character.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    printf("HAUTEUR = %d et LARGEUR = %d \n", pos_Wind_character.h, pos_Wind_character.w);
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 2;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2;

    SDL_Rect pos_Wind_floor_1;
    pos_Wind_floor_1.x = floor_1->tile_set.x + 0;
    pos_Wind_floor_1.y = floor_1->tile_set.y - 1000;
    pos_Wind_floor_1.h = floor_1->tile_set.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_floor_1.w = floor_1->tile_set.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    printf("POUR LA MAP : HAUTEUR = %d et LARGEUR = %d \n", pos_Wind_floor_1.h, pos_Wind_floor_1.w);

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

    SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
    SDL_RenderCopy(game->render, character->texture, &character->South_Walk.rect, &pos_Wind_character);

    SDL_RenderPresent(game->render);

    SDL_SetRenderTarget(game->render, texture_render);

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
    SDL_RenderCopy(game->render, character->texture, &character->South_Walk.rect, &pos_Wind_character);

    SDL_SetRenderTarget(game->render, NULL);

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && *floor_1_bool)
    {
        while (SDL_PollEvent(&event))
        {
            while ((*game->program_launch && *floor_1_bool) || (event.type == SDL_KEYDOWN && (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_ESCAPE])))
            {
                SDL_PollEvent(&event);

                /*--- Event to Exit Program ------------------------------------------*/

                if (event.type == SDL_QUIT)
                {
                    (*game->program_launch) = SDL_FALSE;
                }

                /*--- End Event to Exit Program --------------------------------------*/

                /*--- Event to enter in game menu ------------------------------------*/

                if (keyState[SDL_SCANCODE_ESCAPE])
                {
                    menu_in_game(game, floor_1_bool, character, texture_render);
                    while (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
                        SDL_PollEvent(&event);
                }

                /*--- End Event to enter in game menu --------------------------------*/

                SDL_RenderClear(game->render);

                SDL_RenderCopy(game->render, texture_render, NULL, NULL);

                SDL_RenderPresent(game->render);

                while (keyState[SDL_SCANCODE_RIGHT] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    for (int i = 0; i < 3; i++)
                    {
                        East_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_floor_1.x -= (*game->WINDOWWIDTH) * 24 / 2560;
                        x -= (*game->WINDOWWIDTH) * 24 / 2560;;

                        floor_1->update(floor_1, game->render, floor_1->tile_set, pos_Wind_floor_1);

                        character->update(character, game->render, character->East_Walk, pos_Wind_character);

                        render_frame(game->render);

                        rand_combat = rand() % 101;
                        printf("rand_combat: %i\n", rand_combat);
                        if (rand_combat >= 0 && rand_combat <= CHANCE_CBT)
                        {
                            transition(game);
                            combat(game, character, floor_1, texture_render, floor_1_bool);
                            break;
                        }

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > floor_1.c Line 102");
                        }
                    }

                    SDL_PollEvent(&event);
                }

                if (East_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    floor_1->update(floor_1, game->render, floor_1->tile_set, pos_Wind_floor_1);
                    character->update(character, game->render, character->East_Walk, pos_Wind_character);
                    render_frame(game->render);

                    SDL_SetRenderTarget(game->render, texture_render);

                    SDL_RenderClear(game->render);

                    SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
                    SDL_RenderCopy(game->render, character->texture, &character->East_Walk.rect, &pos_Wind_character);

                    SDL_SetRenderTarget(game->render, NULL);

                    East_Walk = 0;
                }

                while (keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    for (int i = 0; i < 3; i++)
                    {
                        West_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_floor_1.x += (*game->WINDOWWIDTH) * 24 / 2560;
                        x += (*game->WINDOWWIDTH) * 24 / 2560;;

                        floor_1->update(floor_1, game->render, floor_1->tile_set, pos_Wind_floor_1);

                        character->update(character, game->render, character->West_Walk, pos_Wind_character);

                        render_frame(game->render);

                        rand_combat = rand() % 101;
                        printf("rand_combat: %i\n", rand_combat);
                        if (rand_combat >= 0 && rand_combat <= CHANCE_CBT)
                        {
                            transition(game);
                            combat(game, character, floor_1, texture_render, floor_1_bool);
                            break;
                        }

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > floor_1.c Line 131");
                        }
                    }

                    SDL_PollEvent(&event);
                }

                if (West_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    floor_1->update(floor_1, game->render, floor_1->tile_set, pos_Wind_floor_1);
                    character->update(character, game->render, character->West_Walk, pos_Wind_character);
                    render_frame(game->render);

                    SDL_SetRenderTarget(game->render, texture_render);

                    SDL_RenderClear(game->render);

                    SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
                    SDL_RenderCopy(game->render, character->texture, &character->West_Walk.rect, &pos_Wind_character);

                    SDL_SetRenderTarget(game->render, NULL);

                    West_Walk = 0;
                }

                while (keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    for (int i = 0; i < 3; i++)
                    {
                        North_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_floor_1.y += (*game->WINDOWWIDTH) * 24 / 2560;
                        y += (*game->WINDOWWIDTH) * 24 / 2560;;

                        floor_1->update(floor_1, game->render, floor_1->tile_set, pos_Wind_floor_1);

                        character->update(character, game->render, character->North_Walk, pos_Wind_character);

                        render_frame(game->render);

                        rand_combat = rand() % 101;
                        printf("rand_combat: %i\n", rand_combat);
                        if (rand_combat >= 0 && rand_combat <= CHANCE_CBT)
                        {
                            transition(game);
                            combat(game, character, floor_1, texture_render, floor_1_bool);
                            break;
                        }

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering, floor_1.c Line 160");
                        }
                    }

                    SDL_PollEvent(&event);
                }

                if (North_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    floor_1->update(floor_1, game->render, floor_1->tile_set, pos_Wind_floor_1);
                    character->update(character, game->render, character->North_Walk, pos_Wind_character);
                    render_frame(game->render);

                    SDL_SetRenderTarget(game->render, texture_render);

                    SDL_RenderClear(game->render);

                    SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
                    SDL_RenderCopy(game->render, character->texture, &character->North_Walk.rect, &pos_Wind_character);

                    SDL_SetRenderTarget(game->render, NULL);

                    North_Walk = 0;
                }

                while (keyState[SDL_SCANCODE_DOWN] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    for (int i = 0; i < 3; i++)
                    {
                        South_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_floor_1.y -= (*game->WINDOWWIDTH) * 24 / 2560;
                        y -= (*game->WINDOWWIDTH) * 24 / 2560;;

                        floor_1->update(floor_1, game->render, floor_1->tile_set, pos_Wind_floor_1);

                        character->update(character, game->render, character->South_Walk, pos_Wind_character);

                        render_frame(game->render);

                        rand_combat = rand() % 101;
                        printf("rand_combat: %i\n", rand_combat);
                        if (rand_combat >= 0 && rand_combat <= CHANCE_CBT)
                        {
                            transition(game);
                            combat(game, character, floor_1, texture_render, floor_1_bool);
                            break;
                        }

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > floor_1.c Line 189");
                        }
                    }

                    SDL_PollEvent(&event);
                }

                if (South_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;
                    floor_1->update(floor_1, game->render, floor_1->tile_set, pos_Wind_floor_1);
                    character->update(character, game->render, character->South_Walk, pos_Wind_character);
                    render_frame(game->render);

                    SDL_SetRenderTarget(game->render, texture_render);

                    SDL_RenderClear(game->render);

                    SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
                    SDL_RenderCopy(game->render, character->texture, &character->South_Walk.rect, &pos_Wind_character);

                    SDL_SetRenderTarget(game->render, NULL);

                    South_Walk = 0;
                }

                character->x = x;
                character->y = y;
            }
        }
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    floor_1->free(&floor_1);

    /*--- End Free Memory --------------------------------------------------------*/
}
