CFLAGS=-Wall -lmingw32 -lSDL2main -lSDL2

all: main

main: main.o error.o map.o character.o frame.o town.o tower.o menu_accueil.o charger_partie.o nouvelle_partie.o options.o creation_perso.o
	gcc  main.o error.o map.o character.o frame.o town.o tower.o menu_accueil.o charger_partie.o nouvelle_partie.o options.o creation_perso.o -o bin/Final_Tower_Quest -I include -L lib $(CFLAGS) -lSDL2_ttf


test: test_map.o test_character.o error.o map.o character.o 
	gcc  test_map.o error.o map.o character.o -o bin/test_map -I include -L lib $(CFLAGS)
	gcc  test_character.o error.o map.o character.o -o bin/test_character -I include -L lib $(CFLAGS)

main.o: src/main.c
	gcc -c src/main.c -I include -L lib $(CFLAGS)

character.o: src/character.c
	gcc -c src/character.c -I include -L lib $(CFLAGS)

map.o: src/map.c
	gcc -c src/map.c -I include -L lib $(CFLAGS)

menu_accueil.o : src/menu_accueil.c
	gcc -c src/menu_accueil.c  -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

charger_partie.o: src/charger_partie.c
		gcc -c src/charger_partie.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

nouvelle_partie.o: src/nouvelle_partie.c
		gcc -c src/nouvelle_partie.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

options.o: src/options.c
		gcc -c src/options.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

creation_perso.o: src/creation_perso.c
	gcc -c src/creation_perso.c  -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

error.o: src/error.c
	gcc -c src/error.c -I include -L lib $(CFLAGS)

frame.o: src/frame.c
	gcc -c src/frame.c -I include -L lib $(CFLAGS)

town.o: src/town.c
	gcc -c src/town.c -I include -L lib $(CFLAGS)

tower.o: src/tower.c
	gcc -c src/tower.c -I include -L lib $(CFLAGS)


test_map.o: src/test_map.c
	gcc -c src/test_map.c -I include -L lib $(CFLAGS)

test_character.o: src/test_character.c
	gcc -c src/test_character.c -I include -L lib $(CFLAGS)


clean:
	del *.o

cleanall: clean
	del .\bin\*.exe