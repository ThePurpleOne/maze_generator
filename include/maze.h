/*
	* HEADER MAZE
	* Author : Jonas S.
	* Date   : 24/10/2021
	! DESCRIPTION
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "raylib.h"
#include "raymath.h"


#ifndef _MAZE_H_
#define _MAZE_H_


// DEFINES
#define CELL_SIZE 50
#define MAZE_WIDTH 1000
#define MAZE_HEIGHT 1000

enum walls{TOP, RIGHT, BOT, LEFT}; 


// STRUCT
typedef struct 
{
	uint64_t x, y;
}Coordinates;

typedef struct 
{
	Coordinates pos;
	bool visited;
	bool walls[4];
}Cell;

typedef struct maze
{
	uint64_t w, h;
	Cell maze[MAZE_WIDTH / CELL_SIZE][MAZE_HEIGHT / CELL_SIZE];
	Cell * current;
}Maze;


// PROTOTYPE FUNCTIONS
void showCell(Cell c);
void showMaze(Maze m);
Cell * getNeighbor(Maze * m, bool * stuck);
bool checkPossibilityOfCell(int64_t x, int64_t y);
void removeWallsBetweenCells(Cell * c1, Cell * c2);
#endif
