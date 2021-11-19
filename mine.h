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
bool getInput(char ch, Pos * cursor, Tile** map);
bool is_in_bounds(Pos* position);
bool is_tile_flagged(Pos* cursor, Tile** map);
bool is_tile_mine(Pos* cursor, Tile** map);
void moveCursor(int y, int x, Pos* cursor);
bool selectTile(Pos* cursor, Tile** map);
void toggleFlag(Pos* cursor, Tile** map);
bool is_tile_mine(Pos* cursor, Tile** map);
Pos* centerPosition(Pos* position);
void updateCursor(Pos* cursor, Tile** map);

