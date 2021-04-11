CFLAGS=-Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

all: main

main: main.o error.o map.o character.o frame.o town.o tower.o menu_accueil.o charger_partie.o nouvelle_partie.o options.o colision.o transition.o game_over.o creation_perso.o nom_sauvegarde.o game.o menu_in_game.o sauvegarder.o texte_confirmation.o caracteristiques.o combat.o commandes.o sac.o affichage_message.o attacks_character.o floor_1.o
	gcc  main.o error.o map.o character.o frame.o town.o tower.o menu_accueil.o charger_partie.o nouvelle_partie.o options.o colision.o transition.o game_over.o creation_perso.o nom_sauvegarde.o game.o menu_in_game.o sauvegarder.o texte_confirmation.o caracteristiques.o combat.o commandes.o sac.o affichage_message.o attacks_character.o floor_1.o -o bin/Final_Tower_Quest -I include -L lib $(CFLAGS)


test: test_map.o test_character.o error.o map.o character.o
	gcc  test_map.o error.o map.o character.o -o bin/test_map -I include -L lib $(CFLAGS)
	gcc  test_character.o error.o map.o character.o -o bin/test_character -I include -L lib $(CFLAGS)
	gcc  test_game.o error.o game.o -o bin/test_game -I include -L lib $(CFLAGS)


main.o: src/main.c
	gcc -c src/main.c -I include -L lib $(CFLAGS)

character.o: src/character.c
	gcc -c src/character.c -I include -L lib $(CFLAGS)

map.o: src/map.c
	gcc -c src/map.c -I include -L lib $(CFLAGS)

game.o: src/game.c
	gcc -c src/game.c -I include -L lib $(CFLAGS)

menu_accueil.o : src/menu_accueil.c
	gcc -c src/menu_accueil.c  -I include -L lib $(CFLAGS)

colision.o : src/colision.c
	gcc -c src/colision.c  -I include -L lib $(CFLAGS) -lSDL2_image

charger_partie.o: src/charger_partie.c
	gcc -c src/charger_partie.c -I include -L lib $(CFLAGS)

nouvelle_partie.o: src/nouvelle_partie.c
	gcc -c src/nouvelle_partie.c -I include -L lib $(CFLAGS)

floor_1.o: src/floor_1.c
	gcc -c src/floor_1.c -I include -L lib $(CFLAGS)

options.o: src/options.c
	gcc -c src/options.c -I include -L lib $(CFLAGS)

transition.o: src/transition.c
	gcc -c src/transition.c -I include -L lib $(CFLAGS)

game_over.o: src/game_over.c
	gcc -c src/game_over.c -I include -L lib $(CFLAGS)

combat.o: src/combat.c
	gcc -c src/combat.c -I include -L lib $(CFLAGS)

attacks_character.o: src/attacks_character.c
	gcc -c src/attacks_character.c -I include -L lib $(CFLAGS)

creation_perso.o: src/creation_perso.c
	gcc -c src/creation_perso.c  -I include -L lib $(CFLAGS)

nom_sauvegarde.o: src/nom_sauvegarde.c
	gcc -c src/nom_sauvegarde.c -I include -L lib $(CFLAGS)

error.o: src/error.c
	gcc -c src/error.c -I include -L lib $(CFLAGS)

frame.o: src/frame.c
	gcc -c src/frame.c -I include -L lib $(CFLAGS)

town.o: src/town.c
	gcc -c src/town.c -I include -L lib $(CFLAGS)

menu_in_game.o : src/menu_in_game.c
	gcc -c src/menu_in_game.c  -I include -L lib $(CFLAGS)

sac.o : src/sac.c
	gcc -c src/sac.c  -I include -L lib $(CFLAGS)

caracteristiques.o : src/caracteristiques.c
	gcc -c src/caracteristiques.c  -I include -L lib $(CFLAGS)

commandes.o : src/commandes.c
	gcc -c src/commandes.c  -I include -L lib $(CFLAGS)

sauvegarder.o : src/sauvegarder.c
	gcc -c src/sauvegarder.c  -I include -L lib $(CFLAGS)

tower.o: src/tower.c
	gcc -c src/tower.c -I include -L lib $(CFLAGS)

texte_confirmation.o : src/texte_confirmation.c
	gcc -c src/texte_confirmation.c  -I include -L lib $(CFLAGS)

affichage_message.o : src/affichage_message.c
	gcc -c src/affichage_message.c  -I include -L lib $(CFLAGS)


test_map.o: src/test/test_map.c
	gcc -c src/test/test_map.c -I include -L lib $(CFLAGS)

test_character.o: src/test/test_character.c
	gcc -c src/test/test_character.c -I include -L lib $(CFLAGS)

test_game.o: src/test/test_game.c
	gcc -c src/test/test_game.c -I include -L lib $(CFLAGS)


clean:
	del *.o

cleanall: clean
	del .\bin\*.exe
