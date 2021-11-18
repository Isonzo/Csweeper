#include "mine.h"
#include <curses.h>
#include <stdio.h>

int MAP_HEIGHT = 12;
int MAP_WIDTH = 20;

Tile** generateMap(void)
{
	Tile** map;
	map = malloc(MAP_HEIGHT * sizeof(Tile*));

	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		map[i] = malloc(MAP_WIDTH * sizeof(Tile));
	}

	for (int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			map[i][j].is_mine = false;
			map[i][j].is_flagged = false;
			map[i][j].is_pressed = false;
			map[i][j].icon = '#';
		}

	return map;
}

void printMap(Tile** map)
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			mvaddch(i, j, map[i][j].icon);
		}
}

void placeMines(Tile** map)
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (rand() % 8 == 0)
			{
				map[i][j].is_mine = true;
				map[i][j].icon = '*';
			}
		}
}

void getInput(char ch, Pos* cursor, Tile** map)
{
	switch (ch)
	{
		case 'j':
			moveCursor(1, 0, cursor);
			break;
		case 'k':
			moveCursor(-1, 0, cursor);
			break;
		case 'l':
			moveCursor(0, 1, cursor);
			break;
		case 'h':
			moveCursor(0, -1, cursor);
			break;
		case ' ':
			selectTile(cursor, map);
			break;
	}
}

void moveCursor(int new_y, int new_x, Pos* cursor)
{
	if (!(cursor->y + new_y < 0 || cursor->y + new_y >= MAP_HEIGHT))
		cursor->y += new_y;
	if (!(cursor->x + new_x < 0 || cursor->x + new_x >= MAP_WIDTH))
		cursor->x += new_x;
}

void selectTile(Pos* cursor, Tile** map)
{
	if (is_tile_mine(cursor, map))
		return; // TODO: Game over!
	int mine_count = 0;
	// check surrounding tiles and take appropiate action
	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
		{
			Pos temp_cursor = *cursor;
			temp_cursor.y += i;
			temp_cursor.x += j;
			if (is_tile_mine(&temp_cursor, map))
			{
				mine_count += 1;
			}
		}
	char total_surround_mines = mine_count + '0';
	map[cursor->y][cursor->x].icon = total_surround_mines;
}

bool is_tile_mine(Pos* cursor, Tile** map)
{
	if ((cursor->y < 0 || cursor->y  >= MAP_HEIGHT))
		return false;
	if ((cursor->x < 0 || cursor->x  >= MAP_WIDTH))
		return false;
	return map[cursor->y][cursor->x].is_mine;
}

Pos* centerPosition(Pos* position)
{
	position->y = MAP_HEIGHT / 2;
	position->x = MAP_WIDTH / 2;

	return position;
}

void updateCursor(Pos* cursor, Tile** map)
{
	move(cursor->y, cursor->x);
}
