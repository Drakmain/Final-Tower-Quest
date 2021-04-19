#include <stdio.h>
#include <stdlib.h>

#include "..\lib\sauvegarder.h"

#include "..\lib\character.h"

/*!
 *
 * \file sauvegarder.c
 * \brief Permet de sauvegarder.
 * \author Jeremy BOURGOUIN
 *
 */

/*!
 *
 * \fn sauvegarde(game_t *game, character_t *character)
 * \brief Fonction permettant de sauvegarder les données du personnage.
 *
 * \param game est un pointeur sur l'objet game_t du jeu.
 * \param character est un pointeur sur l'objet character_t actuel.
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

    fprintf(file, "lvl: %d ;\n", character->lvl);
    fprintf(file, "xp: %d ;\n", character->xp);
    fprintf(file, "max_life: %d ;\n", character->max_life);
    fprintf(file, "life: %d ;\n", character->life);
    fprintf(file, "max_mana: %d ;\n", character->max_mana);
    fprintf(file, "mana: %d ;\n", character->mana);

    fprintf(file, "vitalite: %d ;\n", character->vitalite);
    fprintf(file, "force: %d ;\n", character->puissance);
    fprintf(file, "intelligence: %d ;\n", character->intelligence);
    fprintf(file, "vitesse: %d ;\n", character->vitesse);
    fprintf(file, "agilite: %d ;\n", character->agilite);
    fprintf(file, "defense: %d ;\n", character->defense);
    fprintf(file, "point_dispo: %d ;\n", character->points_dispo);

    fprintf(file, "nb_petite_popo_soin: %d ;\n", character->nb_petite_popo_soin);
    fprintf(file, "nb_moyenne_popo_soin: %d ;\n", character->nb_moyenne_popo_soin);
    fprintf(file, "nb_petite_popo_mana: %d ;\n", character->nb_petite_popo_mana);
    fprintf(file, "nb_moyenne_popo_mana: %d ;\n", character->nb_moyenne_popo_mana);
    fprintf(file, "nb_popo_puissance: %d ;\n", character->nb_popo_puissance);
    fprintf(file, "nb_popo_agi: %d ;\n", character->nb_popo_agi);

    fclose(file);
}
