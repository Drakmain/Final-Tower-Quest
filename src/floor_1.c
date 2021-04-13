#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>
#include <time.h>

#include "..\lib\floor_1.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\character.h"
#include "..\lib\colision.h"
#include "..\lib\menu_in_game.h"
#include "..\lib\combat.h"
#include "..\lib\combat_boss.h"
#include "..\lib\transition.h"
#include "..\lib\game_over.h"
#include "..\lib\affichage_message.h"
#include "..\lib\sauvegarder.h"

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
    srand(time(NULL));

    SDL_Texture *texture_render = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

    map_t *floor_1 = NULL;
    floor_1 = map_create(game->render, "floor_1");
    if (floor_1 == NULL)
    {
        exit_with_error("Cannot create a map_t object > floor_1.c Line 35");
    }

    SDL_bool *floor_1_bool = malloc(sizeof(SDL_bool));
    *floor_1_bool = SDL_TRUE;

    Uint8 r_character, g_character, b_character;
    Uint32 pixel_character;

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
    pos_Wind_floor_1.h = floor_1->tile_set.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_floor_1.w = floor_1->tile_set.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_floor_1.x = -character->x + (*game->WINDOWWIDTH)/2 - (*game->WINDOWWIDTH) * 71 / 1280 /2;
    pos_Wind_floor_1.y = -character->y + (*game->WINDOWHEIGHT)/2 - (*game->WINDOWHEIGHT) * 112 / 1280;
    printf("POUR LA MAP : HAUTEUR = %d et LARGEUR = %d \n", pos_Wind_floor_1.h, pos_Wind_floor_1.w);

    int East_Walk = 0;
    int West_Walk = 0;
    int South_Walk = 0;
    int North_Walk = 0;

    /*---texture transi map--------------------------------------------------------*/
    int opacite_transi = 0;

    SDL_Texture *transi = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));
    if (transi == NULL)
    {
        SDL_ExitWithError("probleme texture transi floor_1");
    }

    SDL_Rect pos_transi;
    pos_transi.x = 0;
    pos_transi.y = 0;
    pos_transi.w = (*game->WINDOWWIDTH);
    pos_transi.h = (*game->WINDOWHEIGHT);

    SDL_Rect rect_transi;
    rect_transi.x = pos_transi.x;
    rect_transi.y = pos_transi.y;
    rect_transi.w = pos_transi.w;
    rect_transi.h = pos_transi.h;

    SDL_SetRenderDrawColor(game->render, 0, 0, 0, opacite_transi);
    SDL_SetRenderTarget(game->render, transi);
    SDL_SetTextureBlendMode(transi, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(game->render, &rect_transi);
    SDL_SetRenderTarget(game->render, NULL);

    /*------------------------------------------------------------------------------------*/

    SDL_Surface *surface = NULL;

    switch (*game->WINDOWHEIGHT)
    {
    case WINDOWHEIGHT_720P:
        surface = SDL_LoadBMP("src\\tileset\\Maps\\floor_1_hitbox_720p.bmp");
        printf("Resolution : 720P\n");
        if (!surface)
        {
            SDL_ExitWithError("Loading of a BMP failed > floor_1.c Line 83");
        }
        break;

    case WINDOWHEIGHT_900P:
        surface = SDL_LoadBMP("src\\tileset\\Maps\\floor_1_hitbox_900p.bmp");
        printf("Resolution : 900P\n");
        if (!surface)
        {
            SDL_ExitWithError("Loading of a BMP failed > floor_1.c Line 91");
        }
        break;

    case WINDOWHEIGHT_1080P:
        surface = SDL_LoadBMP("src\\tileset\\Maps\\floor_1_hitbox_1080p.bmp");
        printf("Resolution : 1080P\n");
        if (!surface)
        {
            SDL_ExitWithError("Loading of a BMP failed > floor_1.c Line 99");
        }
        break;

    case WINDOWHEIGHT_1440P:
        surface = SDL_LoadBMP("src\\tileset\\Maps\\floor_1_hitbox_1440p.bmp");
        printf("Resolution : 1440P\n");
        if (!surface)
        {
            SDL_ExitWithError("Loading of a BMP failed > floor_1.c Line 107");
        }
        break;
    }

    pixel_character = getpixel(surface, character->x + pos_Wind_character.w/2 , character->y + pos_Wind_character.h - pos_Wind_character.h/7.5);
    SDL_GetRGB(pixel_character, surface->format, &r_character, &g_character, &b_character);

    /*--- End Initialization Variable --------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
    SDL_RenderCopy(game->render, character->texture, &character->North_Walk.rect, &pos_Wind_character);

    SDL_SetRenderTarget(game->render, texture_render);

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
    SDL_RenderCopy(game->render, character->texture, &character->North_Walk.rect, &pos_Wind_character);

    SDL_SetRenderTarget(game->render, NULL);

    for (int i = 255; i >= 0; i -= 5)
    {
        SDL_SetRenderDrawColor(game->render, 0, 0, 0, i);
        SDL_SetRenderTarget(game->render, transi);
        SDL_SetTextureBlendMode(transi, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(game->render, &rect_transi);
        SDL_SetRenderTarget(game->render, NULL);

        SDL_RenderClear(game->render);
        SDL_RenderCopy(game->render, texture_render, NULL, &pos_transi);
        SDL_RenderCopy(game->render, transi, NULL, &pos_transi);
        SDL_RenderPresent(game->render);
        SDL_Delay(10);
    }

    /*--- Main Loop --------------------------------------------------------------*/

    while (*game->program_launch && *floor_1_bool)
    {
        while (SDL_PollEvent(&event) && *floor_1_bool)
        {
            while ((*game->program_launch && *floor_1_bool) && (event.type == SDL_KEYDOWN && (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_ESCAPE])))
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

                if(character_moving(game, game->render, surface, character->x, character->y, 0) == 2  || character_moving(game, game->render, surface, character->x, character->y, 1) == 2 || character_moving(game, game->render, surface, character->x, character->y, 2) == 2 || character_moving(game, game->render, surface, character->x, character->y, 3) == 2)
                {
                    if(keyState[SDL_SCANCODE_E])
                    {
                        SDL_SetRenderTarget(game->render, texture_render);

                        SDL_RenderClear(game->render);

                        SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
                        SDL_RenderCopy(game->render, character->texture, &character->North_Walk.rect, &pos_Wind_character);

                        SDL_SetRenderTarget(game->render, NULL);

                        character->life = character->max_life;
                        character->mana = character->max_mana;
                        affichage_message(game, texture_render, "Vos points de vie et de mana ont ete regeneres.", -1);
                    }
                }

                while (keyState[SDL_SCANCODE_RIGHT] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    if(character_moving(game, game->render, surface, character->x, character->y, 2) == 2)
                    {
                        if(keyState[SDL_SCANCODE_E])
                        {
                            SDL_SetRenderTarget(game->render, texture_render);

                            SDL_RenderClear(game->render);

                            SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
                            SDL_RenderCopy(game->render, character->texture, &character->East_Walk.rect, &pos_Wind_character);

                            SDL_SetRenderTarget(game->render, NULL);

                            character->life = character->max_life;
                            character->mana = character->max_mana;
                            affichage_message(game, texture_render, "Vos points de vie et de mana ont ete regeneres.", -1);
                        }
                        break;
                    }
                    if (character_moving(game, game->render, surface, character->x, character->y, 2) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                    {
                        break;
                    }
                    else
                    {
                        East_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_floor_1.x -= (*game->WINDOWWIDTH) * 24 / 2560;
                        character->x += (*game->WINDOWWIDTH) * 24 / 2560;

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

                        pixel_character = getpixel(surface, character->x + pos_Wind_character.w/2 , character->y + pos_Wind_character.h - pos_Wind_character.h/7.5);
                        SDL_GetRGB(pixel_character, surface->format, &r_character, &g_character, &b_character);
                        printf("r : %d g : %d b : %d",r_character, g_character, b_character);
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
                    if(character_moving(game, game->render, surface, character->x, character->y, 3) == 2)
                    {
                        if(keyState[SDL_SCANCODE_E])
                        {
                            SDL_SetRenderTarget(game->render, texture_render);

                            SDL_RenderClear(game->render);

                            SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
                            SDL_RenderCopy(game->render, character->texture, &character->West_Walk.rect, &pos_Wind_character);

                            SDL_SetRenderTarget(game->render, NULL);

                            character->life = character->max_life;
                            character->mana = character->max_mana;
                            affichage_message(game, texture_render, "Vos points de vie et de mana ont ete regeneres.", -1);
                        }
                        break;
                    }
                    if (character_moving(game, game->render, surface, character->x, character->y, 3) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                    {
                        break;
                    }
                    else
                    {
                        West_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_floor_1.x += (*game->WINDOWWIDTH) * 24 / 2560;
                        character->x -= (*game->WINDOWWIDTH) * 24 / 2560;

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

                        pixel_character = getpixel(surface, character->x + pos_Wind_character.w/2 , character->y + pos_Wind_character.h - pos_Wind_character.h/7.5);
                        SDL_GetRGB(pixel_character, surface->format, &r_character, &g_character, &b_character);
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

                while (keyState[SDL_SCANCODE_DOWN] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    if(character_moving(game, game->render, surface, character->x, character->y, 1) == 2)
                    {
                        if(keyState[SDL_SCANCODE_E])
                        {
                            SDL_SetRenderTarget(game->render, texture_render);

                            SDL_RenderClear(game->render);

                            SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
                            SDL_RenderCopy(game->render, character->texture, &character->South_Walk.rect, &pos_Wind_character);

                            SDL_SetRenderTarget(game->render, NULL);

                            character->life = character->max_life;
                            character->mana = character->max_mana;
                            affichage_message(game, texture_render, "Vos points de vie et de mana ont ete regeneres.", -1);
                        }
                        break;
                    }
                    if (character_moving(game, game->render, surface, character->x, character->y, 1) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                    {
                        break;
                    }
                    else
                    {
                        South_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_floor_1.y -= (*game->WINDOWWIDTH) * 24 / 2560;
                        character->y += (*game->WINDOWWIDTH) * 24 / 2560;

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

                        pixel_character = getpixel(surface, character->x + pos_Wind_character.w/2, character->y + pos_Wind_character.h - pos_Wind_character.h/7.5);
                        SDL_GetRGB(pixel_character, surface->format, &r_character, &g_character, &b_character);
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

                while (keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_ESCAPE] && *floor_1_bool)
                {
                    if(character_moving(game, game->render, surface, character->x, character->y, 0) == 2)
                   {
                       if(keyState[SDL_SCANCODE_E])
                       {

                           SDL_SetRenderTarget(game->render, texture_render);

                           SDL_RenderClear(game->render);

                           SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
                           SDL_RenderCopy(game->render, character->texture, &character->North_Walk.rect, &pos_Wind_character);

                           SDL_SetRenderTarget(game->render, NULL);

                           character->life = character->max_life;
                           character->mana = character->max_mana;
                           affichage_message(game, texture_render, "Vos points de vie et de mana ont ete regeneres.", -1);
                       }
                       break;
                    }
                    if (character_moving(game, game->render, surface, character->x, character->y, 0) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                    {
                        break;
                    }
                    else if(r_character == 0 && g_character == 0 && b_character == 255)
                    {
                        SDL_SetRenderTarget(game->render, texture_render);

                        SDL_RenderClear(game->render);

                        SDL_RenderCopy(game->render, floor_1->texture, &floor_1->tile_set, &pos_Wind_floor_1);
                        SDL_RenderCopy(game->render, character->texture, &character->North_Walk.rect, &pos_Wind_character);

                        SDL_SetRenderTarget(game->render, NULL);
                        transition(game);
                        if(combat_boss(game, character, floor_1, texture_render, floor_1_bool))
                        {
                            *floor_1_bool = SDL_FALSE;
                            North_Walk = 0;
                            strcpy(character->position, "Etage_2");
                            sauvegarde(game, character);
                        }
                    }
                    else
                    {
                        North_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_floor_1.y += (*game->WINDOWWIDTH) * 24 / 2560;
                        character->y -= (*game->WINDOWWIDTH) * 24 / 2560;

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

                        pixel_character = getpixel(surface, character->x + pos_Wind_character.w/2 , character->y + pos_Wind_character.h - pos_Wind_character.h/7.5);
                        SDL_GetRGB(pixel_character, surface->format, &r_character, &g_character, &b_character);
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
            }
        }
    }
    for (int i = 0; i <= 255; i += 5)
    {
        SDL_SetRenderDrawColor(game->render, 0, 0, 0, i);
        SDL_SetRenderTarget(game->render, transi);
        SDL_SetTextureBlendMode(transi, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(game->render, &rect_transi);
        SDL_SetRenderTarget(game->render, NULL);

        SDL_RenderClear(game->render);
        SDL_RenderCopy(game->render, texture_render, NULL, &pos_transi);
        SDL_RenderCopy(game->render, transi, NULL, &pos_transi);
        SDL_RenderPresent(game->render);
        SDL_Delay(10);
    }

    /*--- End Main Loop ----------------------------------------------------------*/

    /*--- Free Memory ------------------------------------------------------------*/

    floor_1->free(&floor_1);

    SDL_FreeSurface(surface);

    /*--- End Free Memory --------------------------------------------------------*/
}
