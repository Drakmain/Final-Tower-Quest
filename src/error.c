#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>


/*!
 * 
 * \file error.c
 * \brief Gestion d'affichage des erreur
 * \author Enzo BRENNUS
 * 
 */


/*!
 *
 * \fn void SDL_ExitWithError(const char * message)
 * \brief Affichage du message d'erreur SDL.
 *
 * \param message est une chaîne de caractères contenant le message d'erreur.
 * 
 */

void SDL_ExitWithError(const char * message)
{

    SDL_Log("ERROR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}


/*!
 *
 * \fn void exit_with_error(const char * message)
 * \brief Affichage du message d'erreur.
 *
 * \param message est une chaîne de caractères contenant le message d'erreur.
 * 
 */

void exit_with_error(const char * message)
{
    
    printf("ERROR : %s",message);
    SDL_Quit();
    exit(EXIT_FAILURE);
}