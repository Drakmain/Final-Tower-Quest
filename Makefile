CFLAGS=-Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

all: main

main: main.o error.o map.o character.o frame.o town.o tower.o menu_accueil.o charger_partie.o nouvelle_partie.o options.o creation_perso.o game.o menu_in_game.o
	gcc  main.o error.o map.o character.o frame.o town.o tower.o menu_accueil.o charger_partie.o nouvelle_partie.o options.o creation_perso.o game.o menu_in_game.o -o bin/Final_Tower_Quest -I include -L lib $(CFLAGS) -lSDL2_ttf


test: test_map.o test_character.o test_game.o error.o map.o character.o
	gcc  test_map.o error.o map.o game.o -o bin/test_map -I include -L lib $(CFLAGS)
	gcc  test_character.o error.o character.o game.o -o bin/test_character -I include -L lib $(CFLAGS)
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

charger_partie.o: src/charger_partie.c
		gcc -c src/charger_partie.c -I include -L lib $(CFLAGS)

nouvelle_partie.o: src/nouvelle_partie.c
		gcc -c src/nouvelle_partie.c -I include -L lib $(CFLAGS)

options.o: src/options.c
		gcc -c src/options.c -I include -L lib $(CFLAGS)

creation_perso.o: src/creation_perso.c
	gcc -c src/creation_perso.c  -I include -L lib $(CFLAGS)

error.o: src/error.c
	gcc -c src/error.c -I include -L lib $(CFLAGS)

frame.o: src/frame.c
	gcc -c src/frame.c -I include -L lib $(CFLAGS)

town.o: src/town.c
	gcc -c src/town.c -I include -L lib $(CFLAGS)

menu_in_game.o : src/menu_in_game.c
	gcc -c src/menu_in_game.c  -I include -L lib $(CFLAGS)

tower.o: src/tower.c
	gcc -c src/tower.c -I include -L lib $(CFLAGS)


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
