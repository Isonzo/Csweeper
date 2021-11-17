#include <stdbool.h>
#include <stdlib.h>

typedef struct Tile
{
	bool is_mine;
	bool is_flagged;
	bool is_pressed;
	char icon;
	int mines_around;
}Tile;

// mine.c functions
Tile** generateMap(void);
void printMap(Tile** map);

// externs
extern Tile ** board;
extern int MAP_HEIGHT;
extern int MAP_WIDTH;

