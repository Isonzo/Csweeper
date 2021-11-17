output: main.o mine.o
	gcc -lncurses mine.o main.o -o minesweeper

main.o: main.c
	gcc -c main.c

mine.o: mine.c mine.h
	gcc -c mine.c

clean:
	rm *.o minesweeper
