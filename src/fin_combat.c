#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "..\lib\combat.h"

#include "..\lib\frame.h"
#include "..\lib\map.h"
#include "..\lib\fin_combat.h"
#include "..\lib\affichage_message.h"

/*!
 *
 * \file fin_combat.c
 * \brief A FINIR.
 * \author Jeremy BOURGOUIN
 *
 */

/*!
 *
 * \fn combat(game_t *game, character_t *character, map_t *map, int nb_enemie_combat, int rand_enemie)
 * \brief A FINIR.
 *
 * \param game A FINIR.
 * \param character A FINIR.
 * \param map A FINIR.
 * \param nb_enemie_combat A FINIR.
 * \param rand_enemie A FINIR.
 *
 */

 extern
 void fin_combat(game_t *game, character_t *character, SDL_Texture * texture_render_combat, map_t *map, int nb_enemie_combat, int rand_enemie[])
{
    srand(time(NULL));

    /*--- Initialization Variable ------------------------------------------------*/
    int random_drop_potions;
    int nb_total_xp;

    if(nb_enemie_combat == 1)
    {
        nb_total_xp = map->enemies[rand_enemie[0]].exp;
        affichage_message(game, texture_render_combat, "Vous avez gagne %d xp.", nb_total_xp);

        character->xp += nb_total_xp;
        if(character->xp + character->tab_xp_max[character->lvl - 1] > character->tab_xp_max[character->lvl])
        {
            character->xp = character->xp + character->tab_xp_max[character->lvl - 1] - character->tab_xp_max[character->lvl];
            affichage_message(game, texture_render_combat, "Vous avez gagne un niveau.", -1);
            character->lvl++;
            affichage_message(game, texture_render_combat, "Vous avez obtenu 3 points de compétence.", -1);
            character->points_dispo += 3;
        }

        if(strcmp(map->name,"floor_1") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 4)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 8)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 14)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 20)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
        }

        else if(strcmp(map->name,"floor_2") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 4)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 8)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 13)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 14)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 19)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 20)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_3") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 4)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 8)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 12)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 14)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 18)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 20)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_4") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 4)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 8)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 11)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 14)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 17)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 20)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_5") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 4)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 8)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 10)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 14)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 20)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }


    }

    else if(nb_enemie_combat == 2)
    {
        nb_total_xp = map->enemies[rand_enemie[0]].exp + map->enemies[rand_enemie[1]].exp;
        affichage_message(game, texture_render_combat, "Vous avez gagne %d xp.", nb_total_xp);
        character->xp += nb_total_xp;
        if(character->lvl == 50)affichage_message(game, texture_render_combat, "Vous etes au summum, vous ne pouvez plus gagnez d'xp.", -1);
        if(character->xp + character->tab_xp_max[character->lvl - 1] > character->tab_xp_max[character->lvl])
        {
            character->xp = character->xp + character->tab_xp_max[character->lvl - 1] - character->tab_xp_max[character->lvl];
            affichage_message(game, texture_render_combat, "Vous avez gagne un niveau.", -1);
            character->lvl++;
            affichage_message(game, texture_render_combat, "Vous avez obtenu 3 points de compétence.", -1);
            character->points_dispo += 3;
        }

        if(strcmp(map->name,"floor_1") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 8)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 28)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 40)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
        }

        else if(strcmp(map->name,"floor_2") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 8)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 26)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 28)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 38)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 40)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_3") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 8)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 24)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 28)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 36)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 40)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_4") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 8)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 22)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 28)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 34)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 40)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_5") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 8)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 20)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 28)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 32)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 40)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }
    }

    else if(nb_enemie_combat == 3)
    {
        nb_total_xp = map->enemies[rand_enemie[0]].exp + map->enemies[rand_enemie[1]].exp + map->enemies[rand_enemie[2]].exp;
        affichage_message(game, texture_render_combat, "Vous avez gagne %d xp.", nb_total_xp);
        character->xp += nb_total_xp;
        if(character->xp + character->tab_xp_max[character->lvl - 1] > character->tab_xp_max[character->lvl])
        {
            character->xp = character->xp + character->tab_xp_max[character->lvl - 1] - character->tab_xp_max[character->lvl];
            affichage_message(game, texture_render_combat, "Vous avez gagne un niveau.", -1);
            character->lvl++;
            affichage_message(game, texture_render_combat, "Vous avez obtenu 3 points de compétence.", -1);
            character->points_dispo += 3;
        }

        if(strcmp(map->name,"floor_1") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 12)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 24)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 42)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 60)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
        }

        else if(strcmp(map->name,"floor_2") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 12)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 24)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 39)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 42)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 57)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 60)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_3") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 12)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 24)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 36)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 42)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 54)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 60)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_4") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 12)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 24)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 33)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 42)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 51)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 60)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_5") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 12)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 24)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 30)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 42)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 48)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 60)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }
    }

    else if(nb_enemie_combat == 4)
    {
        nb_total_xp = map->enemies[rand_enemie[0]].exp + map->enemies[rand_enemie[1]].exp + map->enemies[rand_enemie[2]].exp + map->enemies[rand_enemie[3]].exp;
        affichage_message(game, texture_render_combat, "Vous avez gagne %d xp.", nb_total_xp);
        character->xp += nb_total_xp;
        if(character->xp + character->tab_xp_max[character->lvl - 1] > character->tab_xp_max[character->lvl])
        {
            character->xp = character->xp + character->tab_xp_max[character->lvl - 1] - character->tab_xp_max[character->lvl];
            affichage_message(game, texture_render_combat, "Vous avez gagne un niveau.", -1);
            character->lvl++;
            affichage_message(game, texture_render_combat, "Vous avez obtenu 3 points de compétence.", -1);
            character->points_dispo += 3;
        }

        if(strcmp(map->name,"floor_1") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 32)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 56)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 80)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
        }

        else if(strcmp(map->name,"floor_2") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 32)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 52)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 56)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 76)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 80)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_3") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 32)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 48)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 56)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 72)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 80)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_4") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 32)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 44)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 56)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 68)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 80)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }

        else if(strcmp(map->name,"floor_5") == 0)
        {
            random_drop_potions = rand()%100;
            if(random_drop_potions < 16)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion de puissance.", -1);
                character->nb_popo_puissance++;
            }
            else if(random_drop_potions < 32)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une potion d'agilite.", -1);
                character->nb_popo_agi++;
            }
            else if(random_drop_potions < 40)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de soin.", -1);
                character->nb_petite_popo_soin++;
            }
            else if(random_drop_potions < 56)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de soin.", -1);
                character->nb_moyenne_popo_soin++;
            }
            else if(random_drop_potions < 64)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une petite potion de mana.", -1);
                character->nb_petite_popo_mana++;
            }
            else if(random_drop_potions < 80)
            {
                affichage_message(game, texture_render_combat, "Vous avez obtenue une moyenne potion de mana.", -1);
                character->nb_moyenne_popo_mana++;
            }

        }
    }
    /*--- Free Memory ------------------------------------------------------------*/


    /*--- End Free Memory --------------------------------------------------------*/
}