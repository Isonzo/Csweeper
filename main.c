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
	bool game_won = false;

	// ncurses init functions
	initscr();
	noecho();
	cbreak();

	// minesweeper init functions
	cursor->y = 1;
	cursor->x = 1;
	board = generateMap();
	placeMines(board);

	while (!game_won)
	{
		if (getInput(ch, cursor, board))
				{
					printMap(board);
					updateCursor(cursor, board);
					refresh();
					game_won = isGameWon(board);
				}
		else
		{
			clear();
			printw("You've been blown to pieces...");
			getch();
			break;
		}
		if ((ch = getch()) == 'q')
			break;
	}
	if (game_won)
	{
		clear();
		printw("You won!");
		getch();
	}
	endwin();	

	return 0;
}
