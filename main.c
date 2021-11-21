#include "mine.h"
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
	cursor->y = 8;
	cursor->x = 1;
	board = generateMap();
	placeMines(board);

	while (!game_won)
	{
		if (getInput(ch, cursor, board))
				{
					// update the board
					printMap(board);
					updateCursor(cursor, board);
					refresh();

					// Check if board state is a winning one
					game_won = isGameWon(board);
					if (game_won)
						break;
				}
		else
		{
			// If getInput is false, it means the player has lost.
			clear();
			printw("You've been blown to pieces...");
			getch();
			break;
		}

		if ((ch = getch()) == 'q')
			break;
	}
	// If player exited the loop having won, be sure to print out that they've won.
	if (game_won)
	{
		clear();
		printw("You won!");
		getch();
	}
	endwin();	

	return 0;
}
