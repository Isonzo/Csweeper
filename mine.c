#include "mine.h"
#include <curses.h>
#include <stdio.h>

int MAP_HEIGHT = 16;
int MAP_WIDTH = 16;

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
			if (rand() % 6 == 0)
			{
				map[i][j].is_mine = true;
			}
		}
}

bool getInput(char ch, Pos* cursor, Tile** map)
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
		case 'f':
			toggleFlag(cursor, map);
			break;
		case ' ':
			return selectTile(cursor, map);
	}
	return true;
}

void moveCursor(int new_y, int new_x, Pos* cursor)
{
	if (!(cursor->y + new_y < 0 || cursor->y + new_y >= MAP_HEIGHT))
		cursor->y += new_y;
	if (!(cursor->x + new_x < 0 || cursor->x + new_x >= MAP_WIDTH))
		cursor->x += new_x;
}

bool selectTile(Pos* cursor, Tile** map)
{
	if (is_tile_mine(cursor, map))
	{
		map[cursor->y][cursor->x].icon = '*';
		return false;
	}
	if (is_tile_flagged(cursor, map))
		return true;
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

	// If 0, automatically select all surrounding tiles
	if (mine_count == 0)
	{
	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
		{
		// Let's avoid repeat checks
		Pos temp_cursor = *cursor;
		temp_cursor.y += i;
		temp_cursor.x += j;
		if (is_in_bounds(&temp_cursor))
			if (map[temp_cursor.y][temp_cursor.x].icon == '#')
				selectTile(&temp_cursor, map);
		}
	}
	return true;
}

void toggleFlag(Pos* cursor, Tile** map)
{
	if (is_tile_flagged(cursor, map))
	{
		map[cursor->y][cursor->x].is_flagged = false;
		map[cursor->y][cursor->x].icon = '#';
	}
	else if (map[cursor->y][cursor->x].icon == '#')
	{
		map[cursor->y][cursor->x].is_flagged = true;
		map[cursor->y][cursor->x].icon = 'F';
	}
}

bool is_in_bounds(Pos* position)
{
	if ((position->y < 0 || position->y  >= MAP_HEIGHT))
		return false;
	if ((position->x < 0 || position->x  >= MAP_WIDTH))
		return false;
	return true;
}

bool is_tile_flagged(Pos* cursor, Tile** map)
{
	if (is_in_bounds(cursor))
		return map[cursor->y][cursor->x].is_flagged;
	return false;
}

bool is_tile_mine(Pos* cursor, Tile** map)
{
	if (is_in_bounds(cursor))
		return map[cursor->y][cursor->x].is_mine;
	return false;
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

bool isGameWon(Tile** map)
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (map[i][j].icon == '#')	
				return false;
			if (map[i][j].is_mine && !map[i][j].is_flagged)
			{
				return false;
			}
		}
	return true;
}
