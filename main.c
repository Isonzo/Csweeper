#include <stdio.h>
#include "mine.h"
#include <ncurses.h>
int main()
{	
	char ch;
	Tile **board;
	int MAP_HEIGHT = 8;
	int MAP_WIDTH = 12;
	initscr();
	noecho();
	nocbreak();
	board = generateMap();
	refresh();
	while (true)
	{
		if ((ch = getch()) == 'q')
			break;
		printMap(board);
		refresh();
	}
	endwin();	

	return 0;
}
