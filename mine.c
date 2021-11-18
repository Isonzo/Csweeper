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

void getInput(char ch)
{
	switch (ch)
	{
		case 'j':
			break;
		case 'k':
			break;
		case 'l':
			break;
		case 'h':
			break;
	}
}

Pos* centerPosition(Pos* position)
{
	position->y = MAP_HEIGHT / 2;
	position->x = MAP_WIDTH / 2;

	return position;
}

void initCursor(Pos* cursor, Tile** map)
{
	cursor = centerPosition(cursor);
}

void updateCursor(Pos* cursor, Tile** map)
{
	map[cursor->y][cursor->x].icon = 'C';
}
