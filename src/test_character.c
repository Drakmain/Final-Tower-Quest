#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "character.h"
#include "error.h"


int main(int argc, char **argv)
{
    printf("Test de l'objet character: \n");

    character_t * character = NULL; 

    printf("Test d'existance sur un character_t inexistant\n");
    
    (character_exist(character) ? printf("-->KO\n") : printf ("-->OK\n"));


    printf("Creation de l'objet character...\n");

    character = character_create("src\\tileset\\FF6_Terra_Branford.txt");


    printf("Affichage des donnees de l'objet character: \n");

    printf("North Walk: h: %i, w: %i, x: %i, y: %i, limit: %i\n",character->North_Walk.rect.h, character->North_Walk.rect.w, character->North_Walk.rect.x, character->North_Walk.rect.y, character->North_Walk.limit);
    printf("South Walkh: %i, w: %i, x: %i, y: %i, limit: %i\n",character->South_Walk.rect.h, character->South_Walk.rect.w, character->South_Walk.rect.x, character->South_Walk.rect.y, character->South_Walk.limit);
    printf("Side Walk: h: %i, w: %i, x: %i, y: %i, limit: %i\n",character->Side_Walk.rect.h, character->Side_Walk.rect.w, character->Side_Walk.rect.x, character->Side_Walk.rect.y, character->Side_Walk.limit);
    printf("Win: h: %i, w: %i, x: %i, y: %i, limit: %i\n",character->Win.rect.h, character->Win.rect.w, character->Win.rect.x, character->Win.rect.y, character->Win.limit);


    printf("Destruction de l'objet character...");

    character->free(&character);
    
    return EXIT_SUCCESS;
}