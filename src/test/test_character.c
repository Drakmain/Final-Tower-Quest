#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "..\lib\character.h"

#include "..\lib\game.h"
#include "..\lib\error.h"

int main(int argc, char** argv)
{

    game_t * game = NULL;
    printf("/*--- Startup SDL -------*/\n");
    game = game_create();
    if (game == NULL)
    {
        exit_with_error("Cannot create a game_t object > test_character.c Line 15");
    }
    
    printf("Test de l'objet character: \n");

    character_t* character = NULL;

    printf("Test d'existance sur un character_t inexistant\n");

    (character_exist(character) ? printf("-->KO\n") : printf("-->OK\n"));


    printf("Creation de l'objet character...\n");

    character = character_create(game->render, "save//save3.txt");
        
    
    printf("Affichage des donnees de l'objet character: \n");

    printf("RGB: %i, %i, %i;\n", character->R, character->G, character->B);
    printf("North_Walk: %i, %i, %i, %i, %i;\n", character->North_Walk.rect.x, character->North_Walk.rect.y, character->North_Walk.rect.w, character->North_Walk.rect.h, character->North_Walk.limit);
    printf("East_Walk: %i, %i, %i, %i, %i;\n", character->East_Walk.rect.x, character->East_Walk.rect.y, character->East_Walk.rect.w, character->East_Walk.rect.h, character->East_Walk.limit);
    printf("South_Walk :%i, %i, %i, %i, %i;\n", character->South_Walk.rect.x, character->South_Walk.rect.y, character->South_Walk.rect.w, character->South_Walk.rect.h, character->South_Walk.limit);
    printf("West_Walk: %i, %i, %i, %i, %i;\n", character->West_Walk.rect.x, character->West_Walk.rect.y, character->West_Walk.rect.w, character->West_Walk.rect.h, character->West_Walk.limit);
    printf("Damage_Taken: %i, %i, %i, %i;\n", character->Damage_Taken.x, character->Damage_Taken.y, character->Damage_Taken.w, character->Damage_Taken.h);
    printf("Weak: %i, %i, %i, %i;\n", character->Weak.x, character->Weak.y, character->Weak.w, character->Weak.h);
    printf("Dead: %i, %i, %i, %i;\n", character->Dead.x, character->Dead.y, character->Dead.w, character->Dead.h);


    printf("Destruction de l'objet character...\n\n");

    character->free(&character);


    game->free(&game);

    return EXIT_SUCCESS;
}