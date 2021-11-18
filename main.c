#include "mine.h"
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
	//initCursor();

	do
	{
		if ((ch = getch()) == 'q')
			break;
		getInput(ch);
		placeMines(board);
		printMap(board);
		updateCursor(cursor, board);
		refresh();
	}	while (true);
	endwin();	

	return 0;
}
