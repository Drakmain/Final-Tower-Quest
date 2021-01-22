all: main

main: main.o error.o animation.o
	gcc  main.o error.o animation.o -o bin/Final_Tower_Quest -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

animation.o: src/animation.c
	gcc -c src/animation.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

error.o: src/error.c
	gcc -c src/error.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

main.o: src/main.c
	gcc -c src/main.c -I include -L lib -Wall -lmingw32 -lSDL2main -lSDL2

clean:
	del *.o

cleanall: clean
	del .\bin\Final_Tower_Quest.exe