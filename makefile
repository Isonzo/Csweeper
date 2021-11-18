output: main.o mine.o
	gcc -lncurses mine.o main.o -o minesweeper

debug: main.c mine.c
	gcc -lncurses mine.c main.c -g

main.o: main.c
	gcc -c main.c

mine.o: mine.c mine.h
	gcc -c mine.c

clean:
	rm *.o minesweeper
