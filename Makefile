all: main

main: main.o error.o map.o character.o town.o frame.o
	gcc  main.o error.o map.o character.o town.o frame.o -o bin/Final_Tower_Quest -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

test: test_map.o test_character.o error.o map.o character.o 
	gcc  test_map.o error.o map.o character.o -o bin/test_map -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2
	gcc  test_character.o error.o map.o character.o -o bin/test_character -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2


character.o: src/character.c
	gcc -c src/character.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

map.o: src/map.c
	gcc -c src/map.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

error.o: src/error.c
	gcc -c src/error.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

main.o: src/main.c
	gcc -c src/main.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

test_map.o: src/test_map.c
	gcc -c src/test_map.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

test_character.o: src/test_character.c
	gcc -c src/test_character.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

town.o: src/town.c
	gcc -c src/town.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

frame.o: src/frame.c
	gcc -c src/frame.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2


clean:
	del *.o

cleanall: clean
	del .\bin\*.exe