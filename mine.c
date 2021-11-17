#include "mine.h"
#include <curses.h>
#include <stdio.h>

int MAP_HEIGHT = 8;
int MAP_WIDTH = 12;

Tile** generateMap(void)
{
	Tile** map;
	map = malloc(MAP_HEIGHT * sizeof(Tile*));

	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		map[i] = malloc(MAP_WIDTH * sizeof(Tile));
	}

	for (int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_HEIGHT; ++j)
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
		for (int j = 0; j < MAP_HEIGHT; ++j)
		{
			mvaddch(i, j, map[i][j].icon);
		}
}

void placeMines(Tile** map)
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_HEIGHT; ++j)
		{
			if (rand() % 8 == 0)
			{
				map[i][j].is_mine = true;
				map[i][j].icon = '*';
			}
		}
}
