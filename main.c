#include "mine.h"
#include <stdio.h>
#include <time.h>
int main()
{	
	srand(time(NULL));
	char ch;
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

	do
	{
		if ((ch = getch()) == 'q')
			break;
		printMap(board);
		getInput(ch, cursor);
		printw("%d, %d", cursor->x, cursor->y);
		updateCursor(cursor, board);
		refresh();
	}	while (true);
	endwin();	

	return 0;
}
