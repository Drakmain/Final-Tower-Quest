#include <stdio.h>
#include <stdlib.h>

#include "..\lib\sauvegarder.h"

#include "..\lib\character.h"

/*!
 *
 * \file sauvegarder.c
 * \brief Gestion de la creation d'un perosnnage.
 * \author Jeremy BOURGOUIN
 *
 */

/*!
 *
 * \fn sauvegarde(game_t * game, character_t * character)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 *
 */

extern void sauvegarde(game_t *game, character_t *character)
{
    FILE *file;
    file = fopen(character->file_name_save, "w");
    if (file == NULL)
    {
        exit_with_error("Loading of a file failed > sauvegarder.c Line 36");
    }

    fprintf(file, "save_name: %s ;\n", character->save_name);
    fprintf(file, "charactere_name: %s ;\n", character->classe_name);

    fprintf(file, "position: %s ;\n", character->position);
    fprintf(file, "x: %d ;\n", character->x);
    fprintf(file, "y: %d ;\n", character->y);

    fprintf(file, "lvl: %d ;\n;", character->lvl);
    fprintf(file, "xp: %d ;\n", character->xp);
    fprintf(file, "life: %d ;\n", character->life);
    fprintf(file, "mana: %d ;\n", character->mana);

    fprintf(file, "vitalite: %d ;\n", character->vitalite);
    fprintf(file, "force: %d ;\n", character->force);
    fprintf(file, "intelligence: %d ;\n", character->intelligence);
    fprintf(file, "agilite: %d ;\n", character->agilite);
    fprintf(file, "defense: %d ;\n", character->defense);
    fprintf(file, "point_dispo: %d ;", character->points_dispo);

    fclose(file);
}
