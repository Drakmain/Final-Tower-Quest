#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

#include "..\lib\tower.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\character.h"
#include "..\lib\colision.h"
#include "..\lib\menu_in_game.h"
#include "..\lib\combat.h"
#include "..\lib\transition.h"
#include "..\lib\sauvegarder.h"

/*!
 *
 * \file tower.c
 * \brief Gestion de la map tower.
 * \author Enzo BRENNUS, Jeremy BOURGOUIN, Robin PAPILLON.
 *
 */

/*!
 *
 * \fn tower(game_t *game, character_t *character)
 * \brief A FINIR.
 *
 * \param game est un pointeur sur l'objet game_t du jeu.
 * \param character est un pointeur sur l'objet character_t actuel.
 *
 */

extern void tower(game_t *game, character_t *character)
{
    /*--- Initialization Variable ------------------------------------------------*/

    SDL_Texture *texture_render = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));

    map_t *tower = NULL;
    tower = map_create(game->render, "tower");
    if (tower == NULL)
    {
        exit_with_error("Cannot create a map_t object > tower.c Line 36");
    }

    SDL_bool *tower_bool = malloc(sizeof(SDL_bool));
    *tower_bool = SDL_TRUE;

    Uint8 r_character, g_character, b_character;
    Uint32 pixel_character;

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    SDL_Rect pos_Wind_character;
    pos_Wind_character.h = character->North_Walk.rect.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_character.w = character->North_Walk.rect.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    printf("PERSO : HAUTEUR = %d et LARGEUR = %d \n", pos_Wind_character.h, pos_Wind_character.w);
    pos_Wind_character.x = ((*game->WINDOWWIDTH) - pos_Wind_character.w) / 2;
    pos_Wind_character.y = ((*game->WINDOWHEIGHT) - pos_Wind_character.h) / 2;

    SDL_Rect pos_Wind_tower;
    pos_Wind_tower.h = tower->tile_set.h * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_tower.w = tower->tile_set.w * (*game->WINDOWWIDTH) * 7.5 / 2560;
    pos_Wind_tower.x = -character->x + (*game->WINDOWWIDTH) / 2 - (*game->WINDOWWIDTH) * 71 / 1280 / 2;
    pos_Wind_tower.y = -character->y + (*game->WINDOWHEIGHT) / 2 - (*game->WINDOWHEIGHT) * 112 / 1280;

    printf("POUR LA MAP : HAUTEUR = %d et LARGEUR = %d \n", pos_Wind_tower.h, pos_Wind_tower.w);

    int East_Walk = 0;
    int West_Walk = 0;
    int South_Walk = 0;
    int North_Walk = 0;

    /*---texture fond cadre sac--------------------------------------------------------*/

    int opacite_transi = 0;

    SDL_Texture *transi = SDL_CreateTexture(game->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (*game->WINDOWWIDTH), (*game->WINDOWHEIGHT));
    if (transi == NULL)
    {
        SDL_ExitWithError("probleme texture transi tower");
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
        surface = SDL_LoadBMP("src\\tileset\\Maps\\tower_hitbox_720p.bmp");
        printf("Resolution : 720P\n");
        if (!surface)
        {
            SDL_ExitWithError("Loading of a BMP failed > tower.c Line 83");
        }
        break;

    case WINDOWHEIGHT_900P:
        surface = SDL_LoadBMP("src\\tileset\\Maps\\tower_hitbox_900p.bmp");
        printf("Resolution : 900P\n");
        if (!surface)
        {
            SDL_ExitWithError("Loading of a BMP failed > tower.c Line 91");
        }
        break;

    case WINDOWHEIGHT_1080P:
        surface = SDL_LoadBMP("src\\tileset\\Maps\\tower_hitbox_1080p.bmp");
        printf("Resolution : 1080P\n");
        if (!surface)
        {
            SDL_ExitWithError("Loading of a BMP failed > tower.c Line 99");
        }
        break;

    case WINDOWHEIGHT_1440P:
        surface = SDL_LoadBMP("src\\tileset\\Maps\\tower_hitbox_1440p.bmp");
        printf("Resolution : 1440P\n");
        if (!surface)
        {
            SDL_ExitWithError("Loading of a BMP failed > tower.c Line 107");
        }
        break;
    }

    pixel_character = getpixel(surface, character->x + pos_Wind_character.w / 2, character->y + pos_Wind_character.h - pos_Wind_character.h / 7.5);
    SDL_GetRGB(pixel_character, surface->format, &r_character, &g_character, &b_character);

    /*--- End Initialization Variable --------------------------------------------*/

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, tower->texture, &tower->tile_set, &pos_Wind_tower);
    SDL_RenderCopy(game->render, character->texture, &character->North_Walk.rect, &pos_Wind_character);

    SDL_SetRenderTarget(game->render, texture_render);

    SDL_RenderClear(game->render);

    SDL_RenderCopy(game->render, tower->texture, &tower->tile_set, &pos_Wind_tower);
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

    while (*game->program_launch && *tower_bool)
    {
        while (SDL_PollEvent(&event) && *tower_bool)
        {
            while ((*game->program_launch && *tower_bool) && (event.type == SDL_KEYDOWN && (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_ESCAPE])))
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
                    menu_in_game(game, tower_bool, character, texture_render);

                    while (keyState[SDL_SCANCODE_ESCAPE] && event.type == SDL_KEYDOWN)
                        SDL_PollEvent(&event);
                }

                /*--- End Event to enter in game menu --------------------------------*/

                while (keyState[SDL_SCANCODE_RIGHT] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    if (character_moving(game, game->render, surface, character->x, character->y, 2) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                    {
                        break;
                    }
                    else
                    {
                        East_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_tower.x -= (*game->WINDOWWIDTH) * 24 / 2560;
                        character->x += (*game->WINDOWWIDTH) * 24 / 2560;

                        tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);

                        character->update(character, game->render, character->East_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > tower.c Line 102");
                        }

                        pixel_character = getpixel(surface, character->x + pos_Wind_character.w / 2, character->y + pos_Wind_character.h - pos_Wind_character.h / 7.5);
                        SDL_GetRGB(pixel_character, surface->format, &r_character, &g_character, &b_character);
                    }

                    SDL_PollEvent(&event);
                }

                if (East_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;

                    tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);
                    character->update(character, game->render, character->East_Walk, pos_Wind_character);
                    render_frame(game->render);

                    SDL_SetRenderTarget(game->render, texture_render);

                    SDL_RenderClear(game->render);

                    SDL_RenderCopy(game->render, tower->texture, &tower->tile_set, &pos_Wind_tower);
                    SDL_RenderCopy(game->render, character->texture, &character->East_Walk.rect, &pos_Wind_character);

                    SDL_SetRenderTarget(game->render, NULL);

                    East_Walk = 0;
                }

                while (keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    if (character_moving(game, game->render, surface, character->x, character->y, 3) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                    {
                        break;
                    }
                    else
                    {
                        West_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_tower.x += (*game->WINDOWWIDTH) * 24 / 2560;
                        character->x -= (*game->WINDOWWIDTH) * 24 / 2560;

                        tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);

                        character->update(character, game->render, character->West_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > tower.c Line 131");
                        }

                        pixel_character = getpixel(surface, character->x + pos_Wind_character.w / 2, character->y + pos_Wind_character.h - pos_Wind_character.h / 7.5);
                        SDL_GetRGB(pixel_character, surface->format, &r_character, &g_character, &b_character);
                    }

                    SDL_PollEvent(&event);
                }

                if (West_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;

                    tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);
                    character->update(character, game->render, character->West_Walk, pos_Wind_character);
                    render_frame(game->render);

                    SDL_SetRenderTarget(game->render, texture_render);

                    SDL_RenderClear(game->render);

                    SDL_RenderCopy(game->render, tower->texture, &tower->tile_set, &pos_Wind_tower);
                    SDL_RenderCopy(game->render, character->texture, &character->West_Walk.rect, &pos_Wind_character);

                    SDL_SetRenderTarget(game->render, NULL);

                    West_Walk = 0;
                }

                while (keyState[SDL_SCANCODE_DOWN] && !keyState[SDL_SCANCODE_ESCAPE])
                {
                    if (character_moving(game, game->render, surface, character->x, character->y, 1) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                    {
                        break;
                    }
                    else
                    {
                        South_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_tower.y -= (*game->WINDOWWIDTH) * 24 / 2560;
                        character->y += (*game->WINDOWWIDTH) * 24 / 2560;

                        tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);

                        character->update(character, game->render, character->South_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering > tower.c Line 189");
                        }

                        pixel_character = getpixel(surface, character->x + pos_Wind_character.w / 2, character->y + pos_Wind_character.h - pos_Wind_character.h / 7.5);
                        SDL_GetRGB(pixel_character, surface->format, &r_character, &g_character, &b_character);
                    }

                    SDL_PollEvent(&event);
                }

                if (South_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;

                    tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);
                    character->update(character, game->render, character->South_Walk, pos_Wind_character);
                    render_frame(game->render);

                    SDL_SetRenderTarget(game->render, texture_render);

                    SDL_RenderClear(game->render);

                    SDL_RenderCopy(game->render, tower->texture, &tower->tile_set, &pos_Wind_tower);
                    SDL_RenderCopy(game->render, character->texture, &character->South_Walk.rect, &pos_Wind_character);

                    SDL_SetRenderTarget(game->render, NULL);

                    South_Walk = 0;
                }
                while (keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_ESCAPE] && *tower_bool)
                {
                    if (character_moving(game, game->render, surface, character->x, character->y, 0) == 0) /*0 --> up, 1 --> down,2 --> right,3 --> left*/
                    {
                        break;
                    }
                    else if (r_character == 0 && g_character == 0 && b_character == 255)
                    {
                        SDL_SetRenderTarget(game->render, texture_render);

                        SDL_RenderClear(game->render);

                        SDL_RenderCopy(game->render, tower->texture, &tower->tile_set, &pos_Wind_tower);
                        SDL_RenderCopy(game->render, character->texture, &character->North_Walk.rect, &pos_Wind_character);

                        SDL_SetRenderTarget(game->render, NULL);

                        *tower_bool = SDL_FALSE;
                        North_Walk = 0;
                        strcpy(character->position, "Etage_1");
                        character->x = (*game->WINDOWWIDTH) * 1764 / 1280;
                        character->y = (*game->WINDOWWIDTH) * 3684 / 1280;
                        sauvegarde(game, character);
                    }
                    else
                    {
                        North_Walk = 1;

                        frame_start = SDL_GetTicks();

                        pos_Wind_tower.y += (*game->WINDOWWIDTH) * 24 / 2560;
                        character->y -= (*game->WINDOWWIDTH) * 24 / 2560;

                        tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);

                        character->update(character, game->render, character->North_Walk, pos_Wind_character);

                        render_frame(game->render);

                        if (SDL_RenderClear(game->render) != 0)
                        {
                            SDL_ExitWithError("Unable to clear rendering, tower.c Line 160");
                        }

                        pixel_character = getpixel(surface, character->x + pos_Wind_character.w / 2, character->y + pos_Wind_character.h - pos_Wind_character.h / 7.5);
                        SDL_GetRGB(pixel_character, surface->format, &r_character, &g_character, &b_character);
                    }

                    SDL_PollEvent(&event);
                }

                if (North_Walk == 1)
                {
                    character->mov.x = 0;
                    character->mov.y = 0;

                    tower->update(tower, game->render, tower->tile_set, pos_Wind_tower);
                    character->update(character, game->render, character->North_Walk, pos_Wind_character);
                    render_frame(game->render);

                    SDL_SetRenderTarget(game->render, texture_render);

                    SDL_RenderClear(game->render);

                    SDL_RenderCopy(game->render, tower->texture, &tower->tile_set, &pos_Wind_tower);
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

    tower->free(&tower);

    SDL_FreeSurface(surface);

    SDL_DestroyTexture(transi);

    /*--- End Free Memory --------------------------------------------------------*/
}
