#include <stdio.h>
#include <stdlib.h>

#include "..\lib\transition.h"

/*!
 *
 * \file transition.c
 * \brief Gestion des transitions avant les comabts.
 * \author Alexis BOUFFARD, Enzo BRENNUS.
 *
 */

/*!
 *
 * \fn transition(game_t *game)
 * \brief Permet la gestion de la premier map du jeu (town).
 *
 * \param game est un pointeur sur l'objet game_t du jeu.
 *
 */

extern void transition(game_t *game)
{
    /*--- Initialization Variable ------------------------------------------------*/

    int rand_nb;

    /*--- End Initialization Variable --------------------------------------------*/

    /*--- Creation rectangle 1 pour transition 1---------------------------------------------*/

    SDL_Surface *surf_rectangle1 = NULL;
    surf_rectangle1 = SDL_LoadBMP("src\\image\\rectangle.bmp");
    if (surf_rectangle1 == NULL)
    {
        SDL_ExitWithError("probleme chargement rectangle1 > transition.c");
    }

    SDL_Texture *rectangle1 = SDL_CreateTextureFromSurface(game->render, surf_rectangle1);
    if (rectangle1 == NULL)
    {
        SDL_ExitWithError("probleme texture rectangle1 > transition.c");
    }

    SDL_Rect pos_rectangle1;
    pos_rectangle1.x = -(*game->WINDOWWIDTH);
    pos_rectangle1.y = 0;
    pos_rectangle1.w = (*game->WINDOWWIDTH);
    pos_rectangle1.h = (*game->WINDOWHEIGHT) / 4;

    /*----------------------------------------------------------------------------*/

    /*--- Creation rectangle 2 pour transition 1---------------------------------------------------*/

    SDL_Surface *surf_rectangle2 = NULL;
    surf_rectangle2 = SDL_LoadBMP("src\\image\\rectangle.bmp");
    if (surf_rectangle2 == NULL)
    {
        SDL_ExitWithError("probleme chargement rectangle2 > transition.c");
    }

    SDL_Texture *rectangle2 = SDL_CreateTextureFromSurface(game->render, surf_rectangle2);
    if (rectangle2 == NULL)
    {
        SDL_ExitWithError("probleme texture rectangle2 > transition.c");
    }

    SDL_Rect pos_rectangle2;
    pos_rectangle2.x = (*game->WINDOWWIDTH);
    pos_rectangle2.y = (*game->WINDOWHEIGHT) / 4;
    pos_rectangle2.w = (*game->WINDOWWIDTH);
    pos_rectangle2.h = (*game->WINDOWHEIGHT) / 4;

    /*----------------------------------------------------------------------------*/

    /*--- Creation rectangle 3 pour transition 1---------------------------------------------------*/

    SDL_Surface *surf_rectangle3 = NULL;
    surf_rectangle3 = SDL_LoadBMP("src\\image\\rectangle.bmp");
    if (surf_rectangle3 == NULL)
    {
        SDL_ExitWithError("probleme chargement rectangle3 > transition.c");
    }

    SDL_Texture *rectangle3 = SDL_CreateTextureFromSurface(game->render, surf_rectangle3);
    if (rectangle3 == NULL)
    {
        SDL_ExitWithError("probleme texture rectangle3 > transition.c");
    }

    SDL_Rect pos_rectangle3;
    pos_rectangle3.x = -(*game->WINDOWWIDTH);
    pos_rectangle3.y = (*game->WINDOWHEIGHT) * 270 * 2 / 1080;
    pos_rectangle3.w = (*game->WINDOWWIDTH);
    pos_rectangle3.h = (*game->WINDOWHEIGHT) / 4;

    /*----------------------------------------------------------------------------*/

    /*--- Creation rectangle 4 pour transition 1 ---------------------------------------------------*/

    SDL_Surface *surf_rectangle4 = NULL;
    surf_rectangle4 = SDL_LoadBMP("src\\image\\rectangle.bmp");
    if (surf_rectangle4 == NULL)
    {
        SDL_ExitWithError("probleme chargement rectangle4 > transition.c");
    }

    SDL_Texture *rectangle4 = SDL_CreateTextureFromSurface(game->render, surf_rectangle4);
    if (rectangle4 == NULL)
    {
        SDL_ExitWithError("probleme texture rectangle4 > transition.c");
    }

    SDL_Rect pos_rectangle4;
    pos_rectangle4.x = (*game->WINDOWWIDTH);
    pos_rectangle4.y = (*game->WINDOWHEIGHT) * 270 * 3 / 1080;
    pos_rectangle4.w = (*game->WINDOWWIDTH);
    pos_rectangle4.h = (*game->WINDOWHEIGHT) / 4;

    /*----------------------------------------------------------------------------*/

    /*--- Creation triangle 1 pour transition 2 ---------------------------------------------------*/

    SDL_Surface *surf_triangle1 = NULL;
    surf_triangle1 = SDL_LoadBMP("src\\image\\triangle1.bmp");
    if (surf_triangle1 == NULL)
    {
        SDL_ExitWithError("probleme chargement triangle1 > transition.c");
    }

    SDL_Texture *triangle1 = SDL_CreateTextureFromSurface(game->render, surf_triangle1);
    if (triangle1 == NULL)
    {
        SDL_ExitWithError("probleme texture triangle1 > transition.c");
    }

    SDL_Rect pos_triangle1;
    pos_triangle1.x = -(*game->WINDOWWIDTH);
    pos_triangle1.y = 0;
    pos_triangle1.w = (*game->WINDOWWIDTH);
    pos_triangle1.h = (*game->WINDOWHEIGHT);

    /*----------------------------------------------------------------------------*/

    /*--- Creation triangle 2 pour transition 2 ---------------------------------------------------*/

    SDL_Surface *surf_triangle2 = NULL;
    surf_triangle2 = SDL_LoadBMP("src\\image\\triangle2.bmp");
    if (surf_triangle2 == NULL)
    {
        SDL_ExitWithError("probleme chargement triangle2 > transition.c");
    }

    SDL_Texture *triangle2 = SDL_CreateTextureFromSurface(game->render, surf_triangle2);
    if (triangle2 == NULL)
    {
        SDL_ExitWithError("probleme texture triangle2 > transition.c");
    }

    SDL_Rect pos_triangle2;
    pos_triangle2.x = (*game->WINDOWWIDTH);
    pos_triangle2.y = 0;
    pos_triangle2.w = (*game->WINDOWWIDTH);
    pos_triangle2.h = (*game->WINDOWHEIGHT);

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier1 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier1 = NULL;
    surf_damier1 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier1 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier1 > transition.c");
    }

    SDL_Texture *damier1 = SDL_CreateTextureFromSurface(game->render, surf_damier1);
    if (damier1 == NULL)
    {
        SDL_ExitWithError("probleme texture damier1 > transition.c");
    }

    SDL_Rect pos_damier1;
    pos_damier1.x = (*game->WINDOWWIDTH) * 640 / 1920;
    pos_damier1.y = (*game->WINDOWHEIGHT) * 0 / 1080;
    pos_damier1.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier1.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier2 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier2 = NULL;
    surf_damier2 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier2 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier2 > transition.c");
    }

    SDL_Texture *damier2 = SDL_CreateTextureFromSurface(game->render, surf_damier2);
    if (damier2 == NULL)
    {
        SDL_ExitWithError("probleme texture damier2 > transition.c");
    }

    SDL_Rect pos_damier2;
    pos_damier2.x = (*game->WINDOWWIDTH) * 0 / 1920;
    pos_damier2.y = (*game->WINDOWHEIGHT) * 180 / 1080;
    pos_damier2.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier2.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier3 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier3 = NULL;
    surf_damier3 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier3 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier3 > transition.c");
    }

    SDL_Texture *damier3 = SDL_CreateTextureFromSurface(game->render, surf_damier3);
    if (damier3 == NULL)
    {
        SDL_ExitWithError("probleme texture damier3 > transition.c");
    }

    SDL_Rect pos_damier3;
    pos_damier3.x = (*game->WINDOWWIDTH) * 1280 / 1920;
    pos_damier3.y = (*game->WINDOWHEIGHT) * 360 / 1080;
    pos_damier3.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier3.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier4 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier4 = NULL;
    surf_damier4 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier4 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier4 > transition.c");
    }

    SDL_Texture *damier4 = SDL_CreateTextureFromSurface(game->render, surf_damier4);
    if (damier4 == NULL)
    {
        SDL_ExitWithError("probleme texture damier4 > transition.c");
    }

    SDL_Rect pos_damier4;
    pos_damier4.x = (*game->WINDOWWIDTH) * 320 / 1920;
    pos_damier4.y = (*game->WINDOWHEIGHT) * 540 / 1080;
    pos_damier4.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier4.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier5 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier5 = NULL;
    surf_damier5 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier5 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier5 > transition.c");
    }

    SDL_Texture *damier5 = SDL_CreateTextureFromSurface(game->render, surf_damier5);
    if (damier5 == NULL)
    {
        SDL_ExitWithError("probleme texture damier5 > transition.c");
    }

    SDL_Rect pos_damier5;
    pos_damier5.x = (*game->WINDOWWIDTH) * 1600 / 1920;
    pos_damier5.y = (*game->WINDOWHEIGHT) * 540 / 1080;
    pos_damier5.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier5.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier6 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier6 = NULL;
    surf_damier6 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier6 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier6 > transition.c");
    }

    SDL_Texture *damier6 = SDL_CreateTextureFromSurface(game->render, surf_damier6);
    if (damier6 == NULL)
    {
        SDL_ExitWithError("probleme texture damier6 > transition.c");
    }

    SDL_Rect pos_damier6;
    pos_damier6.x = (*game->WINDOWWIDTH) * 960 / 1920;
    pos_damier6.y = (*game->WINDOWHEIGHT) * 720 / 1080;
    pos_damier6.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier6.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier7 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier7 = NULL;
    surf_damier7 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier7 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier7 > transition.c");
    }

    SDL_Texture *damier7 = SDL_CreateTextureFromSurface(game->render, surf_damier7);
    if (damier7 == NULL)
    {
        SDL_ExitWithError("probleme texture damier7 > transition.c");
    }

    SDL_Rect pos_damier7;
    pos_damier7.x = (*game->WINDOWWIDTH) * 0 / 1920;
    pos_damier7.y = (*game->WINDOWHEIGHT) * 0 / 1080;
    pos_damier7.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier7.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier8 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier8 = NULL;
    surf_damier8 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier8 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier8 > transition.c");
    }

    SDL_Texture *damier8 = SDL_CreateTextureFromSurface(game->render, surf_damier8);
    if (damier8 == NULL)
    {
        SDL_ExitWithError("probleme texture damier8 > transition.c");
    }

    SDL_Rect pos_damier8;
    pos_damier8.x = (*game->WINDOWWIDTH) * 1280 / 1920;
    pos_damier8.y = (*game->WINDOWHEIGHT) * 0 / 1080;
    pos_damier8.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier8.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier9 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier9 = NULL;
    surf_damier9 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier9 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier9 > transition.c");
    }

    SDL_Texture *damier9 = SDL_CreateTextureFromSurface(game->render, surf_damier9);
    if (damier9 == NULL)
    {
        SDL_ExitWithError("probleme texture damier9 > transition.c");
    }

    SDL_Rect pos_damier9;
    pos_damier9.x = (*game->WINDOWWIDTH) * 640 / 1920;
    pos_damier9.y = (*game->WINDOWHEIGHT) * 360 / 1080;
    pos_damier9.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier9.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier10 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier10 = NULL;
    surf_damier10 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier10 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier10 > transition.c");
    }

    SDL_Texture *damier10 = SDL_CreateTextureFromSurface(game->render, surf_damier10);
    if (damier10 == NULL)
    {
        SDL_ExitWithError("probleme texture damier10 > transition.c");
    }

    SDL_Rect pos_damier10;
    pos_damier10.x = (*game->WINDOWWIDTH) * 0 / 1920;
    pos_damier10.y = (*game->WINDOWHEIGHT) * 540 / 1080;
    pos_damier10.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier10.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier11 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier11 = NULL;
    surf_damier11 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier11 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier11 > transition.c");
    }

    SDL_Texture *damier11 = SDL_CreateTextureFromSurface(game->render, surf_damier11);
    if (damier11 == NULL)
    {
        SDL_ExitWithError("probleme texture damier11 > transition.c");
    }

    SDL_Rect pos_damier11;
    pos_damier11.x = (*game->WINDOWWIDTH) * 1600 / 1920;
    pos_damier11.y = (*game->WINDOWHEIGHT) * 720 / 1080;
    pos_damier11.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier11.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier12 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier12 = NULL;
    surf_damier12 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier12 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier12 > transition.c");
    }

    SDL_Texture *damier12 = SDL_CreateTextureFromSurface(game->render, surf_damier12);
    if (damier12 == NULL)
    {
        SDL_ExitWithError("probleme texture damier12 > transition.c");
    }

    SDL_Rect pos_damier12;
    pos_damier12.x = (*game->WINDOWWIDTH) * 640 / 1920;
    pos_damier12.y = (*game->WINDOWHEIGHT) * 900 / 1080;
    pos_damier12.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier12.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier13 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier13 = NULL;
    surf_damier13 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier13 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier13 > transition.c");
    }

    SDL_Texture *damier13 = SDL_CreateTextureFromSurface(game->render, surf_damier13);
    if (damier13 == NULL)
    {
        SDL_ExitWithError("probleme texture damier13 > transition.c");
    }

    SDL_Rect pos_damier13;
    pos_damier13.x = (*game->WINDOWWIDTH) * 320 / 1920;
    pos_damier13.y = (*game->WINDOWHEIGHT) * 180 / 1080;
    pos_damier13.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier13.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier14 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier14 = NULL;
    surf_damier14 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier14 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier14 > transition.c");
    }

    SDL_Texture *damier14 = SDL_CreateTextureFromSurface(game->render, surf_damier14);
    if (damier14 == NULL)
    {
        SDL_ExitWithError("probleme texture damier14 > transition.c");
    }

    SDL_Rect pos_damier14;
    pos_damier14.x = (*game->WINDOWWIDTH) * 1600 / 1920;
    pos_damier14.y = (*game->WINDOWHEIGHT) * 180 / 1080;
    pos_damier14.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier14.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier15 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier15 = NULL;
    surf_damier15 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier15 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier15 > transition.c");
    }

    SDL_Texture *damier15 = SDL_CreateTextureFromSurface(game->render, surf_damier15);
    if (damier15 == NULL)
    {
        SDL_ExitWithError("probleme texture damier15 > transition.c");
    }

    SDL_Rect pos_damier15;
    pos_damier15.x = (*game->WINDOWWIDTH) * 640 / 1920;
    pos_damier15.y = (*game->WINDOWHEIGHT) * 540 / 1080;
    pos_damier15.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier15.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier16 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier16 = NULL;
    surf_damier16 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier16 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier16 > transition.c");
    }

    SDL_Texture *damier16 = SDL_CreateTextureFromSurface(game->render, surf_damier16);
    if (damier16 == NULL)
    {
        SDL_ExitWithError("probleme texture damier16 > transition.c");
    }

    SDL_Rect pos_damier16;
    pos_damier16.x = (*game->WINDOWWIDTH) * 320 / 1920;
    pos_damier16.y = (*game->WINDOWHEIGHT) * 720 / 1080;
    pos_damier16.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier16.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier17 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier17 = NULL;
    surf_damier17 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier17 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier17 > transition.c");
    }

    SDL_Texture *damier17 = SDL_CreateTextureFromSurface(game->render, surf_damier17);
    if (damier17 == NULL)
    {
        SDL_ExitWithError("probleme texture damier17 > transition.c");
    }

    SDL_Rect pos_damier17;
    pos_damier17.x = (*game->WINDOWWIDTH) * 0 / 1920;
    pos_damier17.y = (*game->WINDOWHEIGHT) * 900 / 1080;
    pos_damier17.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier17.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier18 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier18 = NULL;
    surf_damier18 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier18 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier18 > transition.c");
    }

    SDL_Texture *damier18 = SDL_CreateTextureFromSurface(game->render, surf_damier18);
    if (damier18 == NULL)
    {
        SDL_ExitWithError("probleme texture damier18 > transition.c");
    }

    SDL_Rect pos_damier18;
    pos_damier18.x = (*game->WINDOWWIDTH) * 1280 / 1920;
    pos_damier18.y = (*game->WINDOWHEIGHT) * 900 / 1080;
    pos_damier18.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier18.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier19 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier19 = NULL;
    surf_damier19 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier19 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier19 > transition.c");
    }

    SDL_Texture *damier19 = SDL_CreateTextureFromSurface(game->render, surf_damier19);
    if (damier19 == NULL)
    {
        SDL_ExitWithError("probleme texture damier19 > transition.c");
    }

    SDL_Rect pos_damier19;
    pos_damier19.x = (*game->WINDOWWIDTH) * 1600 / 1920;
    pos_damier19.y = (*game->WINDOWHEIGHT) * 0 / 1080;
    pos_damier19.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier19.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier20 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier20 = NULL;
    surf_damier20 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier20 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier20 > transition.c");
    }

    SDL_Texture *damier20 = SDL_CreateTextureFromSurface(game->render, surf_damier20);
    if (damier20 == NULL)
    {
        SDL_ExitWithError("probleme texture damier20 > transition.c");
    }

    SDL_Rect pos_damier20;
    pos_damier20.x = (*game->WINDOWWIDTH) * 960 / 1920;
    pos_damier20.y = (*game->WINDOWHEIGHT) * 180 / 1080;
    pos_damier20.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier20.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier21 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier21 = NULL;
    surf_damier21 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier21 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier21 > transition.c");
    }

    SDL_Texture *damier21 = SDL_CreateTextureFromSurface(game->render, surf_damier21);
    if (damier21 == NULL)
    {
        SDL_ExitWithError("probleme texture damier21 > transition.c");
    }

    SDL_Rect pos_damier21;
    pos_damier21.x = (*game->WINDOWWIDTH) * 0 / 1920;
    pos_damier21.y = (*game->WINDOWWIDTH) * 360 / 1920;
    pos_damier21.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier21.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier22 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier22 = NULL;
    surf_damier22 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier22 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier22 > transition.c");
    }

    SDL_Texture *damier22 = SDL_CreateTextureFromSurface(game->render, surf_damier22);
    if (damier22 == NULL)
    {
        SDL_ExitWithError("probleme texture damier22 > transition.c");
    }

    SDL_Rect pos_damier22;
    pos_damier22.x = (*game->WINDOWWIDTH) * 960 / 1920;
    pos_damier22.y = (*game->WINDOWHEIGHT) * 540 / 1080;
    pos_damier22.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier22.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier23 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier23 = NULL;
    surf_damier23 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier23 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier23 > transition.c");
    }

    SDL_Texture *damier23 = SDL_CreateTextureFromSurface(game->render, surf_damier23);
    if (damier23 == NULL)
    {
        SDL_ExitWithError("probleme texture damier23 > transition.c");
    }

    SDL_Rect pos_damier23;
    pos_damier23.x = (*game->WINDOWWIDTH) * 1280 / 1920;
    pos_damier23.y = (*game->WINDOWHEIGHT) * 720 / 1080;
    pos_damier23.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier23.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier24 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier24 = NULL;
    surf_damier24 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier24 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier24 > transition.c");
    }

    SDL_Texture *damier24 = SDL_CreateTextureFromSurface(game->render, surf_damier24);
    if (damier24 == NULL)
    {
        SDL_ExitWithError("probleme texture damier24 > transition.c");
    }

    SDL_Rect pos_damier24;
    pos_damier24.x = (*game->WINDOWWIDTH) * 320 / 1920;
    pos_damier24.y = (*game->WINDOWHEIGHT) * 900 / 1080;
    pos_damier24.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier24.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier25 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier25 = NULL;
    surf_damier25 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier25 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier25 > transition.c");
    }

    SDL_Texture *damier25 = SDL_CreateTextureFromSurface(game->render, surf_damier25);
    if (damier25 == NULL)
    {
        SDL_ExitWithError("probleme texture damier25 > transition.c");
    }

    SDL_Rect pos_damier25;
    pos_damier25.x = (*game->WINDOWWIDTH) * 320 / 1920;
    pos_damier25.y = (*game->WINDOWHEIGHT) * 0 / 1080;
    pos_damier25.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier25.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier26 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier26 = NULL;
    surf_damier26 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier26 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier26 > transition.c");
    }

    SDL_Texture *damier26 = SDL_CreateTextureFromSurface(game->render, surf_damier26);
    if (damier26 == NULL)
    {
        SDL_ExitWithError("probleme texture damier26 > transition.c");
    }

    SDL_Rect pos_damier26;
    pos_damier26.x = (*game->WINDOWWIDTH) * 960 / 1920;
    pos_damier26.y = (*game->WINDOWHEIGHT) * 0 / 1080;
    pos_damier26.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier26.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier27 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier27 = NULL;
    surf_damier27 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier27 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier27 > transition.c");
    }

    SDL_Texture *damier27 = SDL_CreateTextureFromSurface(game->render, surf_damier27);
    if (damier27 == NULL)
    {
        SDL_ExitWithError("probleme texture damier27 > transition.c");
    }

    SDL_Rect pos_damier27;
    pos_damier27.x = (*game->WINDOWWIDTH) * 1280 / 1920;
    pos_damier27.y = (*game->WINDOWHEIGHT) * 180 / 1080;
    pos_damier27.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier27.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier28 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier28 = NULL;
    surf_damier28 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier28 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier28 > transition.c");
    }

    SDL_Texture *damier28 = SDL_CreateTextureFromSurface(game->render, surf_damier28);
    if (damier28 == NULL)
    {
        SDL_ExitWithError("probleme texture damier28 > transition.c");
    }

    SDL_Rect pos_damier28;
    pos_damier28.x = (*game->WINDOWWIDTH) * 320 / 1920;
    pos_damier28.y = (*game->WINDOWHEIGHT) * 360 / 1080;
    pos_damier28.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier28.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier29 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier29 = NULL;
    surf_damier29 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier29 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier29 > transition.c");
    }

    SDL_Texture *damier29 = SDL_CreateTextureFromSurface(game->render, surf_damier29);
    if (damier29 == NULL)
    {
        SDL_ExitWithError("probleme texture damier29 > transition.c");
    }

    SDL_Rect pos_damier29;
    pos_damier29.x = (*game->WINDOWWIDTH) * 1280 / 1920;
    pos_damier29.y = (*game->WINDOWHEIGHT) * 540 / 1080;
    pos_damier29.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier29.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier30 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier30 = NULL;
    surf_damier30 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier30 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier30 > transition.c");
    }

    SDL_Texture *damier30 = SDL_CreateTextureFromSurface(game->render, surf_damier30);
    if (damier30 == NULL)
    {
        SDL_ExitWithError("probleme texture damier30 > transition.c");
    }

    SDL_Rect pos_damier30;
    pos_damier30.x = (*game->WINDOWWIDTH) * 640 / 1920;
    pos_damier30.y = (*game->WINDOWHEIGHT) * 720 / 1080;
    pos_damier30.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier30.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier31 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier31 = NULL;
    surf_damier31 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier31 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier31 > transition.c");
    }

    SDL_Texture *damier31 = SDL_CreateTextureFromSurface(game->render, surf_damier31);
    if (damier31 == NULL)
    {
        SDL_ExitWithError("probleme texture damier31 > transition.c");
    }

    SDL_Rect pos_damier31;
    pos_damier31.x = (*game->WINDOWWIDTH) * 640 / 1920;
    pos_damier31.y = (*game->WINDOWHEIGHT) * 180 / 1080;
    pos_damier31.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier31.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier32 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier32 = NULL;
    surf_damier32 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier32 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier32 > transition.c");
    }

    SDL_Texture *damier32 = SDL_CreateTextureFromSurface(game->render, surf_damier32);
    if (damier32 == NULL)
    {
        SDL_ExitWithError("probleme texture damier32 > transition.c");
    }

    SDL_Rect pos_damier32;
    pos_damier32.x = (*game->WINDOWWIDTH) * 960 / 1920;
    pos_damier32.y = (*game->WINDOWHEIGHT) * 360 / 1080;
    pos_damier32.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier32.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier33 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier33 = NULL;
    surf_damier33 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier33 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier33 > transition.c");
    }

    SDL_Texture *damier33 = SDL_CreateTextureFromSurface(game->render, surf_damier33);
    if (damier33 == NULL)
    {
        SDL_ExitWithError("probleme texture damier33 > transition.c");
    }

    SDL_Rect pos_damier33;
    pos_damier33.x = (*game->WINDOWWIDTH) * 1600 / 1920;
    pos_damier33.y = (*game->WINDOWHEIGHT) * 360 / 1080;
    pos_damier33.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier33.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier34 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier34 = NULL;
    surf_damier34 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier34 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier34 > transition.c");
    }

    SDL_Texture *damier34 = SDL_CreateTextureFromSurface(game->render, surf_damier34);
    if (damier34 == NULL)
    {
        SDL_ExitWithError("probleme texture damier34 > transition.c");
    }

    SDL_Rect pos_damier34;
    pos_damier34.x = (*game->WINDOWWIDTH) * 0 / 1920;
    pos_damier34.y = (*game->WINDOWHEIGHT) * 720 / 1080;
    pos_damier34.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier34.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier35 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier35 = NULL;
    surf_damier35 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier35 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier35 > transition.c");
    }

    SDL_Texture *damier35 = SDL_CreateTextureFromSurface(game->render, surf_damier35);
    if (damier35 == NULL)
    {
        SDL_ExitWithError("probleme texture damier35 > transition.c");
    }

    SDL_Rect pos_damier35;
    pos_damier35.x = (*game->WINDOWWIDTH) * 960 / 1920;
    pos_damier35.y = (*game->WINDOWHEIGHT) * 900 / 1080;
    pos_damier35.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier35.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation damier36 pour transition 3 ---------------------------------------------------*/

    SDL_Surface *surf_damier36 = NULL;
    surf_damier36 = SDL_LoadBMP("src\\image\\damier.bmp");
    if (surf_damier36 == NULL)
    {
        SDL_ExitWithError("probleme chargement damier36 > transition.c");
    }

    SDL_Texture *damier36 = SDL_CreateTextureFromSurface(game->render, surf_damier36);
    if (damier36 == NULL)
    {
        SDL_ExitWithError("probleme texture damier36 > transition.c");
    }

    SDL_Rect pos_damier36;
    pos_damier36.x = (*game->WINDOWWIDTH) * 1600 / 1920;
    pos_damier36.y = (*game->WINDOWHEIGHT) * 900 / 1080;
    pos_damier36.w = (*game->WINDOWWIDTH) * 325 / 1920;
    pos_damier36.h = (*game->WINDOWHEIGHT) * 185 / 1080;

    /*----------------------------------------------------------------------------*/

    /*--- Creation Store1 pour transition 4 ---------------------------------------------------*/
    SDL_Surface *surf_store1 = NULL;
    surf_store1 = SDL_LoadBMP("src\\image\\Store.bmp");
    if (surf_store1 == NULL)
    {
        SDL_ExitWithError("probleme chargement store1 > transition.c");
    }

    SDL_Texture *store1 = SDL_CreateTextureFromSurface(game->render, surf_store1);
    if (store1 == NULL)
    {
        SDL_ExitWithError("probleme texture store1 > transition.c");
    }

    SDL_Rect pos_store1;
    pos_store1.x = 0;
    pos_store1.y = 0;
    pos_store1.w = (*game->WINDOWWIDTH) * 240 / 1920;
    pos_store1.h = (*game->WINDOWHEIGHT);
    /*----------------------------------------------------------------------------*/

    /*--- Creation Store2 pour transition 4 ---------------------------------------------------*/
    SDL_Surface *surf_store2 = NULL;
    surf_store2 = SDL_LoadBMP("src\\image\\Store.bmp");
    if (surf_store2 == NULL)
    {
        SDL_ExitWithError("probleme chargement store2 > transition.c");
    }

    SDL_Texture *store2 = SDL_CreateTextureFromSurface(game->render, surf_store2);
    if (store2 == NULL)
    {
        SDL_ExitWithError("probleme texture store2 > transition.c");
    }

    SDL_Rect pos_store2;
    pos_store2.x = (*game->WINDOWHEIGHT) * 240 / 1080;
    pos_store2.y = 0;
    pos_store2.w = (*game->WINDOWWIDTH) * 240 / 1920;
    pos_store2.h = (*game->WINDOWHEIGHT);
    /*----------------------------------------------------------------------------*/

    /*--- Creation Store3 pour transition 4 ---------------------------------------------------*/
    SDL_Surface *surf_store3 = NULL;
    surf_store3 = SDL_LoadBMP("src\\image\\Store.bmp");
    if (surf_store3 == NULL)
    {
        SDL_ExitWithError("probleme chargement store3 > transition.c");
    }

    SDL_Texture *store3 = SDL_CreateTextureFromSurface(game->render, surf_store3);
    if (store3 == NULL)
    {
        SDL_ExitWithError("probleme texture store3 > transition.c");
    }

    SDL_Rect pos_store3;
    pos_store3.x = (*game->WINDOWHEIGHT) * 480 / 1080;
    pos_store3.y = 0;
    pos_store3.w = (*game->WINDOWWIDTH) * 240 / 1920;
    pos_store3.h = (*game->WINDOWHEIGHT);
    /*----------------------------------------------------------------------------*/

    /*--- Creation Store4 pour transition 4 ---------------------------------------------------*/
    SDL_Surface *surf_store4 = NULL;
    surf_store4 = SDL_LoadBMP("src\\image\\Store.bmp");
    if (surf_store4 == NULL)
    {
        SDL_ExitWithError("probleme chargement store4 > transition.c");
    }

    SDL_Texture *store4 = SDL_CreateTextureFromSurface(game->render, surf_store4);
    if (store4 == NULL)
    {
        SDL_ExitWithError("probleme texture store4 > transition.c");
    }

    SDL_Rect pos_store4;
    pos_store4.x = (*game->WINDOWHEIGHT) * 720 / 1080;
    pos_store4.y = 0;
    pos_store4.w = (*game->WINDOWWIDTH) * 240 / 1920;
    pos_store4.h = (*game->WINDOWHEIGHT);
    /*----------------------------------------------------------------------------*/

    /*--- Creation Store5 pour transition 4 ---------------------------------------------------*/
    SDL_Surface *surf_store5 = NULL;
    surf_store5 = SDL_LoadBMP("src\\image\\Store.bmp");
    if (surf_store5 == NULL)
    {
        SDL_ExitWithError("probleme chargement store5 > transition.c");
    }

    SDL_Texture *store5 = SDL_CreateTextureFromSurface(game->render, surf_store5);
    if (store5 == NULL)
    {
        SDL_ExitWithError("probleme texture store5 > transition.c");
    }

    SDL_Rect pos_store5;
    pos_store5.x = (*game->WINDOWHEIGHT) * 960 / 1080;
    pos_store5.y = 0;
    pos_store5.w = (*game->WINDOWWIDTH) * 240 / 1920;
    pos_store5.h = (*game->WINDOWHEIGHT);
    /*----------------------------------------------------------------------------*/

    /*--- Creation Store6 pour transition 4 ---------------------------------------------------*/
    SDL_Surface *surf_store6 = NULL;
    surf_store6 = SDL_LoadBMP("src\\image\\Store.bmp");
    if (surf_store6 == NULL)
    {
        SDL_ExitWithError("probleme chargement store6 > transition.c");
    }

    SDL_Texture *store6 = SDL_CreateTextureFromSurface(game->render, surf_store6);
    if (store6 == NULL)
    {
        SDL_ExitWithError("probleme texture store6 > transition.c");
    }

    SDL_Rect pos_store6;
    pos_store6.x = (*game->WINDOWHEIGHT) * 1200 / 1080;
    pos_store6.y = 0;
    pos_store6.w = (*game->WINDOWWIDTH) * 240 / 1920;
    pos_store6.h = (*game->WINDOWHEIGHT);
    /*----------------------------------------------------------------------------*/

    /*--- Creation Store7 pour transition 4 ---------------------------------------------------*/
    SDL_Surface *surf_store7 = NULL;
    surf_store7 = SDL_LoadBMP("src\\image\\Store.bmp");
    if (surf_store7 == NULL)
    {
        SDL_ExitWithError("probleme chargement store7 > transition.c");
    }

    SDL_Texture *store7 = SDL_CreateTextureFromSurface(game->render, surf_store7);
    if (store7 == NULL)
    {
        SDL_ExitWithError("probleme texture store7 > transition.c");
    }

    SDL_Rect pos_store7;
    pos_store7.x = (*game->WINDOWHEIGHT) * 1440 / 1080;
    pos_store7.y = 0;
    pos_store7.w = (*game->WINDOWWIDTH) * 240 / 1920;
    pos_store7.h = (*game->WINDOWHEIGHT);
    /*----------------------------------------------------------------------------*/

    /*--- Creation Store8 pour transition 4 ---------------------------------------------------*/
    SDL_Surface *surf_store8 = NULL;
    surf_store8 = SDL_LoadBMP("src\\image\\Store.bmp");
    if (surf_store8 == NULL)
    {
        SDL_ExitWithError("probleme chargement store8 > transition.c");
    }

    SDL_Texture *store8 = SDL_CreateTextureFromSurface(game->render, surf_store8);
    if (store8 == NULL)
    {
        SDL_ExitWithError("probleme texture store8 > transition.c");
    }

    SDL_Rect pos_store8;
    pos_store8.x = (*game->WINDOWHEIGHT) * 1680 / 1080;
    pos_store8.y = 0;
    pos_store8.w = (*game->WINDOWWIDTH) * 240 / 1920;
    pos_store8.h = (*game->WINDOWHEIGHT);
    /*----------------------------------------------------------------------------*/


    rand_nb = rand()%4;
    if(rand_nb == 0) {
        for (int i = 0; i < 42; i++)
        {
            pos_rectangle1.x += (*game->WINDOWHEIGHT) * 50 / 1080;
            pos_rectangle2.x -= (*game->WINDOWHEIGHT) * 50 / 1080;
            pos_rectangle3.x += (*game->WINDOWHEIGHT) * 50 / 1080;
            pos_rectangle4.x -= (*game->WINDOWHEIGHT) * 50 / 1080;

            SDL_RenderCopy(game->render, rectangle1, NULL, &pos_rectangle1);
            SDL_RenderCopy(game->render, rectangle2, NULL, &pos_rectangle2);
            SDL_RenderCopy(game->render, rectangle3, NULL, &pos_rectangle3);
            SDL_RenderCopy(game->render, rectangle4, NULL, &pos_rectangle4);

            SDL_RenderPresent(game->render);
            SDL_Delay(30);
        }
    }
    else if(rand_nb == 1){
        for (int i = 0; i < 42 ; i++)
        {
            pos_triangle1.x += (*game->WINDOWHEIGHT) * 50 / 1080;
            pos_triangle2.x -= (*game->WINDOWHEIGHT) * 50 / 1080;

            SDL_RenderCopy(game->render, triangle1, NULL, &pos_triangle1);
            SDL_RenderCopy(game->render, triangle2, NULL, &pos_triangle2);

            SDL_RenderPresent(game->render);
            SDL_Delay(30);
        }

    }
    else if(rand_nb == 2){

            SDL_RenderCopy(game->render, damier1, NULL, &pos_damier1);
            SDL_RenderCopy(game->render, damier2, NULL, &pos_damier2);
            SDL_RenderCopy(game->render, damier3, NULL, &pos_damier3);
            SDL_RenderCopy(game->render, damier4, NULL, &pos_damier4);
            SDL_RenderCopy(game->render, damier5, NULL, &pos_damier5);
            SDL_RenderCopy(game->render, damier6, NULL, &pos_damier6);
            SDL_Delay(200);
            SDL_RenderPresent(game->render);


            SDL_RenderCopy(game->render, damier7, NULL, &pos_damier7);
            SDL_RenderCopy(game->render, damier8, NULL, &pos_damier8);
            SDL_RenderCopy(game->render, damier9, NULL, &pos_damier9);
            SDL_RenderCopy(game->render, damier10, NULL, &pos_damier10);
            SDL_RenderCopy(game->render, damier11, NULL, &pos_damier11);
            SDL_RenderCopy(game->render, damier12, NULL, &pos_damier12);
            SDL_Delay(200);
            SDL_RenderPresent(game->render);


            SDL_RenderCopy(game->render, damier13, NULL, &pos_damier13);
            SDL_RenderCopy(game->render, damier14, NULL, &pos_damier14);
            SDL_RenderCopy(game->render, damier15, NULL, &pos_damier15);
            SDL_RenderCopy(game->render, damier16, NULL, &pos_damier16);
            SDL_RenderCopy(game->render, damier17, NULL, &pos_damier17);
            SDL_RenderCopy(game->render, damier18, NULL, &pos_damier18);
            SDL_Delay(200);
            SDL_RenderPresent(game->render);


            SDL_RenderCopy(game->render, damier19, NULL, &pos_damier19);
            SDL_RenderCopy(game->render, damier20, NULL, &pos_damier20);
            SDL_RenderCopy(game->render, damier21, NULL, &pos_damier21);
            SDL_RenderCopy(game->render, damier22, NULL, &pos_damier22);
            SDL_RenderCopy(game->render, damier23, NULL, &pos_damier23);
            SDL_RenderCopy(game->render, damier24, NULL, &pos_damier24);
            SDL_Delay(200);
            SDL_RenderPresent(game->render);


            SDL_RenderCopy(game->render, damier25, NULL, &pos_damier25);
            SDL_RenderCopy(game->render, damier26, NULL, &pos_damier26);
            SDL_RenderCopy(game->render, damier27, NULL, &pos_damier27);
            SDL_RenderCopy(game->render, damier28, NULL, &pos_damier28);
            SDL_RenderCopy(game->render, damier29, NULL, &pos_damier29);
            SDL_RenderCopy(game->render, damier30, NULL, &pos_damier30);
            SDL_Delay(200);
            SDL_RenderPresent(game->render);


            SDL_RenderCopy(game->render, damier31, NULL, &pos_damier31);
            SDL_RenderCopy(game->render, damier32, NULL, &pos_damier32);
            SDL_RenderCopy(game->render, damier33, NULL, &pos_damier33);
            SDL_RenderCopy(game->render, damier34, NULL, &pos_damier34);
            SDL_RenderCopy(game->render, damier35, NULL, &pos_damier35);
            SDL_RenderCopy(game->render, damier36, NULL, &pos_damier36);
            SDL_Delay(200);
            SDL_RenderPresent(game->render);
            SDL_Delay(300);

    }
    else if(rand_nb == 3){

            SDL_RenderCopy(game->render, store1, NULL, &pos_store1);
            SDL_RenderCopy(game->render, store8, NULL, &pos_store8);
            SDL_Delay(250);
            SDL_RenderPresent(game->render);

            SDL_RenderCopy(game->render, store2, NULL, &pos_store2);
            SDL_RenderCopy(game->render, store7, NULL, &pos_store7);
            SDL_Delay(250);
            SDL_RenderPresent(game->render);

            SDL_RenderCopy(game->render, store3, NULL, &pos_store3);
            SDL_RenderCopy(game->render, store6, NULL, &pos_store6);
            SDL_Delay(250);
            SDL_RenderPresent(game->render);

            SDL_RenderCopy(game->render, store4, NULL, &pos_store4);
            SDL_RenderCopy(game->render, store5, NULL, &pos_store5);
            SDL_Delay(250);
            SDL_RenderPresent(game->render);
            SDL_Delay(300);
    }

    SDL_RenderPresent(game->render);

    /*--- Free Memory ------------------------------------------------------------*/

    SDL_FreeSurface(surf_rectangle1);
    SDL_FreeSurface(surf_rectangle2);
    SDL_FreeSurface(surf_rectangle3);
    SDL_FreeSurface(surf_rectangle4);
    SDL_FreeSurface(surf_triangle1);
    SDL_FreeSurface(surf_triangle2);
    SDL_FreeSurface(surf_damier1);
    SDL_FreeSurface(surf_damier2);
    SDL_FreeSurface(surf_damier3);
    SDL_FreeSurface(surf_damier4);
    SDL_FreeSurface(surf_damier5);
    SDL_FreeSurface(surf_damier6);
    SDL_FreeSurface(surf_damier7);
    SDL_FreeSurface(surf_damier8);
    SDL_FreeSurface(surf_damier9);
    SDL_FreeSurface(surf_damier10);
    SDL_FreeSurface(surf_damier11);
    SDL_FreeSurface(surf_damier12);
    SDL_FreeSurface(surf_damier13);
    SDL_FreeSurface(surf_damier14);
    SDL_FreeSurface(surf_damier15);
    SDL_FreeSurface(surf_damier16);
    SDL_FreeSurface(surf_damier17);
    SDL_FreeSurface(surf_damier18);
    SDL_FreeSurface(surf_damier19);
    SDL_FreeSurface(surf_damier20);
    SDL_FreeSurface(surf_damier21);
    SDL_FreeSurface(surf_damier22);
    SDL_FreeSurface(surf_damier23);
    SDL_FreeSurface(surf_damier24);
    SDL_FreeSurface(surf_damier25);
    SDL_FreeSurface(surf_damier26);
    SDL_FreeSurface(surf_damier27);
    SDL_FreeSurface(surf_damier28);
    SDL_FreeSurface(surf_damier29);
    SDL_FreeSurface(surf_damier30);
    SDL_FreeSurface(surf_damier31);
    SDL_FreeSurface(surf_damier32);
    SDL_FreeSurface(surf_damier33);
    SDL_FreeSurface(surf_damier34);
    SDL_FreeSurface(surf_damier35);
    SDL_FreeSurface(surf_damier36);
    SDL_FreeSurface(surf_store1);
    SDL_FreeSurface(surf_store2);
    SDL_FreeSurface(surf_store3);
    SDL_FreeSurface(surf_store4);
    SDL_FreeSurface(surf_store5);
    SDL_FreeSurface(surf_store6);
    SDL_FreeSurface(surf_store7);
    SDL_FreeSurface(surf_store8);



    SDL_DestroyTexture(rectangle1);
    SDL_DestroyTexture(rectangle2);
    SDL_DestroyTexture(rectangle3);
    SDL_DestroyTexture(rectangle4);
    SDL_DestroyTexture(triangle1);
    SDL_DestroyTexture(triangle2);
    SDL_DestroyTexture(damier1);
    SDL_DestroyTexture(damier2);
    SDL_DestroyTexture(damier3);
    SDL_DestroyTexture(damier4);
    SDL_DestroyTexture(damier5);
    SDL_DestroyTexture(damier6);
    SDL_DestroyTexture(damier7);
    SDL_DestroyTexture(damier8);
    SDL_DestroyTexture(damier9);
    SDL_DestroyTexture(damier10);
    SDL_DestroyTexture(damier11);
    SDL_DestroyTexture(damier12);
    SDL_DestroyTexture(damier13);
    SDL_DestroyTexture(damier14);
    SDL_DestroyTexture(damier15);
    SDL_DestroyTexture(damier16);
    SDL_DestroyTexture(damier17);
    SDL_DestroyTexture(damier18);
    SDL_DestroyTexture(damier19);
    SDL_DestroyTexture(damier20);
    SDL_DestroyTexture(damier21);
    SDL_DestroyTexture(damier22);
    SDL_DestroyTexture(damier23);
    SDL_DestroyTexture(damier24);
    SDL_DestroyTexture(damier25);
    SDL_DestroyTexture(damier26);
    SDL_DestroyTexture(damier27);
    SDL_DestroyTexture(damier28);
    SDL_DestroyTexture(damier29);
    SDL_DestroyTexture(damier30);
    SDL_DestroyTexture(damier31);
    SDL_DestroyTexture(damier32);
    SDL_DestroyTexture(damier33);
    SDL_DestroyTexture(damier34);
    SDL_DestroyTexture(damier35);
    SDL_DestroyTexture(damier36);
    SDL_DestroyTexture(store1);
    SDL_DestroyTexture(store2);
    SDL_DestroyTexture(store3);
    SDL_DestroyTexture(store4);
    SDL_DestroyTexture(store5);
    SDL_DestroyTexture(store6);
    SDL_DestroyTexture(store7);
    SDL_DestroyTexture(store8);



    /*--- End Free Memory --------------------------------------------------------*/
}
