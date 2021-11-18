#include "mine.h"
#include <curses.h>
#include <stdio.h>
#include <time.h>
int main()
{	
	srand(time(NULL));
	char ch = '0';
	Tile** board;
	Pos* cursor;

	// ncurses init functions
	initscr();
	noecho();
	cbreak();

	// minesweeper init functions
	cursor->y = 1;
	cursor->x = 1;
	board = generateMap();
	placeMines(board);

	while (true)
	{
		getInput(ch, cursor, board);
		printw("%d, %d", cursor->x, cursor->y);
		printMap(board);
		updateCursor(cursor, board);
		refresh();
		if ((ch = getch()) == 'q')
			break;
	}
	endwin();	

	return 0;
}
