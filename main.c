#include "mine.h"
#include <time.h>

void initNcurses(void);
Tile** initMine(Pos* cursor, Tile** board);
void updateGame(Pos* cursor, Tile** board);
void badEndGame(void);
void goodEndGame(void);

int main()
{	
	srand(time(NULL));
	char ch = '0';
	Tile** board;
	Pos* cursor;
	bool game_won = false;

	initNcurses();
	board = initMine(cursor, board);

	while (!game_won)
	{
		if (getInput(ch, cursor, board))
				{
					updateGame(cursor, board);
					// Check if board state is a winning one
					game_won = isGameWon(board);
					if (game_won)
						break;
				}
		else
		{
			// If getInput is false, it means the player has lost.
			badEndGame();
			break;
		}

		if ((ch = getch()) == 'q')
			break;
	}
	// If player exited the loop having won, be sure to print out that they've won.
	if (game_won)
		goodEndGame();
	endwin();	

	return 0;
}

// ncurses init functions
void initNcurses(void)
{ initscr();
	noecho();
	cbreak();
}

// minesweeper init functions
Tile** initMine(Pos* cursor, Tile** board)
{
	cursor->y = 8;
	cursor->x = 8;
	board = generateMap();
	placeMines(board);

	return board;
}
// update the board
void updateGame(Pos* cursor, Tile** board)
{
	printMap(board);
	updateCursor(cursor, board);
	refresh();
}

void badEndGame(void)
{
	clear();
	printw("You've been blown to pieces...");
	getch();
}

void goodEndGame(void)
{
		clear();
		printw("You won!");
		getch();
}
