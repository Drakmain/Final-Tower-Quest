#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "character.h"
#include "error.h"


int main(int argc, char** argv)
{
    
    printf("Test de l'objet character: \n");

    character_t* character = NULL;

    printf("Test d'existance sur un character_t inexistant\n");

    (character_exist(character) ? printf("-->KO\n") : printf("-->OK\n"));


    printf("Creation de l'objet character...\n");

    character = character_create(NULL, "src\\tileset\\FF6_Terra_Branford.bmp", "src\\tileset\\FF6_Terra_Branford.txt");
        
    
    printf("Affichage des donnees de l'objet character: \n");

    printf("%n, %n, %n, %n, %n;\n", &character->North_Walk.rect.x, &character->North_Walk.rect.y, &character->North_Walk.rect.w, &character->North_Walk.rect.h, &character->North_Walk.limit);
    printf("%n, %n, %n, %n, %n;\n", &character->South_Walk.rect.x, &character->South_Walk.rect.y, &character->South_Walk.rect.w, &character->South_Walk.rect.h, &character->South_Walk.limit);
    printf("%n, %n, %n, %n, %n;\n", &character->West_Walk.rect.x, &character->West_Walk.rect.y, &character->West_Walk.rect.w, &character->West_Walk.rect.h, &character->West_Walk.limit);
    printf("%n, %n, %n, %n, %n;\n", &character->East_Walk.rect.x, &character->East_Walk.rect.y, &character->East_Walk.rect.w, &character->East_Walk.rect.h, &character->East_Walk.limit);
    printf("%n, %n, %n, %n, %n;\n", &character->Win.rect.x, &character->Win.rect.y, &character->Win.rect.w, &character->Win.rect.h, &character->Win.limit);


    printf("Destruction de l'objet character...");

    character->free(&character);

    return EXIT_SUCCESS;
}