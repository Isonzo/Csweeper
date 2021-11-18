#include <stdbool.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Tile
{
	bool is_mine;
	bool is_flagged;
	bool is_pressed;
	char icon;
	int mines_around;
}Tile;

typedef struct Pos
{
	int y;
	int x;
}Pos;

// mine.c functions
Tile** generateMap(void);
void printMap(Tile** map);
void placeMines(Tile** map);
void getInput(char ch);
Pos* centerPosition(Pos* position);
void initCursor(Pos* position, Tile** map);
void updateCursor(Pos* cursor, Tile** map);

