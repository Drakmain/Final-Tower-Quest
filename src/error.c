#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

/*!
 * 
 * \file error.c
 * \brief Gestion d'affichage des erreur
 * \author Robin PAPILLON, Alexis BOUFFARD, Jeremy BOURGOUIN, Enzo BRENNUS
 * \version 0.1
 * \date 22/01/21
 * 
 */


/*!
 *
 * \fn void SDL_ExitWithError(const char *message)
 * \brief Affichage du message d'erreur.
 *
 * \param message Chaine de caractere contenant le message d'erreur.
 * 
 */

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERROR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}