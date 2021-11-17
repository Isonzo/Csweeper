#include "mine.h"
#include <time.h>
int main()
{	
	srand(time(NULL));
	char ch;
	Tile** board;
	int MAP_HEIGHT = 8;
	int MAP_WIDTH = 12;

	// ncurses init functions
	initscr();
	noecho();
	cbreak();

	board = generateMap();

	do
	{
		placeMines(board);
		printMap(board);
		refresh();
		if ((ch = getch()) == 'q')
			break;
	}	while (true);
	endwin();	

	return 0;
}
