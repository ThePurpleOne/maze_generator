/*
	* CODE MAZE
	* Author : Jonas S.
	* Date   : 24/10/2021
	! MAZE GENERATION CODE
*/


#include "../include/maze.h"

#include <time.h>
#include <stdlib.h>

/**
 * @brief Draw a cell
 * 
 * @param c
 */
void showCell(Cell c)
{

	// Draw The core
	Color coreColor;
	if(c.visited){coreColor = Fade(RED, 0.4);}
	else{coreColor = Fade(BLUE, 0.4);}
	DrawRectangleRec((Rectangle){	.x=c.pos.x * CELL_SIZE, 
									.y=c.pos.y * CELL_SIZE,
									.width=CELL_SIZE,
									.height=CELL_SIZE,								
								}, 
								coreColor);

	// Draw the walls
	Color wallColor = WHITE;
	uint64_t xPos = c.pos.x * CELL_SIZE;
	uint64_t yPos = c.pos.y * CELL_SIZE;
	uint64_t thicc = CELL_SIZE / 10;

	if(c.walls[TOP])  
	{
		DrawLineEx((Vector2){xPos, yPos}, (Vector2){xPos + CELL_SIZE, yPos}, thicc, wallColor); 
	}
	if(c.walls[RIGHT])
	{ 
		DrawLineEx((Vector2){xPos + CELL_SIZE, yPos}, (Vector2){xPos + CELL_SIZE, yPos + CELL_SIZE}, thicc, wallColor); 
	}
	if(c.walls[BOT])  
	{ 
		DrawLineEx((Vector2){xPos, yPos + CELL_SIZE}, (Vector2){xPos + CELL_SIZE, yPos + CELL_SIZE}, thicc, wallColor); 
	}
	if(c.walls[LEFT])
	{
		DrawLineEx((Vector2){xPos, yPos}, (Vector2){xPos, yPos + CELL_SIZE}, thicc, wallColor); 
	}
}

/**
 * @brief Draw the whole maze
 * 
 * @param m
 */
void showMaze(Maze m)
{
	for (uint64_t x = 0; x < m.w; x++)
	{
		for (uint64_t y = 0; y < m.h; y++)
		{
			showCell(m.maze[x][y]);
		}
	}

}

/**
 * @brief Returns a pointer to a random possible neighbor from a mase struct
 * 
 * @param m
 * @return Cell
 */
Cell * getNeighbor(Maze * m, bool * stuck)
{
	// TODO : OPTIMIZE AND REFACTOR AF THAT UGLY SHIT

	Cell * neighbors[4];
	uint8_t numberOfValidNeighbors = 0;
	int64_t x, y; // temp x and y

	// ! Get the four neighbors
	// TOP
	x = m->current->pos.x;
	y = m->current->pos.y - 1;
	if( checkPossibilityOfCell(x, y) && (m->maze[x][y].visited == false) )
	{
		neighbors[numberOfValidNeighbors] = &m->maze[x][y];
		numberOfValidNeighbors++;
	}

	// RIGHT
	x = m->current->pos.x + 1;
	y = m->current->pos.y;
	if( checkPossibilityOfCell(x, y) && (m->maze[x][y].visited == false) )
	{
		neighbors[numberOfValidNeighbors] = &m->maze[x][y];
		numberOfValidNeighbors++;
	}

	// BOT
	x = m->current->pos.x;
	y = m->current->pos.y + 1;
	if( checkPossibilityOfCell(x, y) && (m->maze[x][y].visited == false) )
	{
		neighbors[numberOfValidNeighbors] = &m->maze[x][y];
		numberOfValidNeighbors++;
	}

	// LEFT
	x = m->current->pos.x - 1;
	y = m->current->pos.y;
	if( checkPossibilityOfCell(x, y) && (m->maze[x][y].visited == false) )
	{
		neighbors[numberOfValidNeighbors] = &m->maze[x][y];
		numberOfValidNeighbors++;
	}

	// ! returns a random one out of them if possible
	if( numberOfValidNeighbors > 0)
	{
		// printf("WORKING	 \n" );
		return neighbors[rand() % numberOfValidNeighbors];
	}
	else // ! Returns the same one if not possible
	{
		*stuck = true;
		return (m->current);
		//return NULL;
	}
}

/**
 * @brief Check if a certain coordinate is possible in the maze
 * 
 * @param x
 * @param y
 */
bool checkPossibilityOfCell(int64_t x, int64_t y)
{
	if( (x < 0) || (x > (MAZE_WIDTH / CELL_SIZE) - 1) || (y < 0) || (y > (MAZE_HEIGHT / CELL_SIZE) - 1) )
	{
		return false;
	}
	return true;
}  

/**
 * @brief Remove the wall between 2 cells
 * 
 * @param c1 Pointer to Cell
 * @param c2 Pointer to Cell
 */
void removeWallsBetweenCells(Cell * c1, Cell * c2)
{
	int16_t diffX = c1->pos.x - c2->pos.x;
	int16_t diffY = c1->pos.y - c2->pos.y;

	// REFERENTIEL C1
	if(diffY == 1) // TOP
	{
		c1->walls[TOP] = false;
		c2->walls[BOT] = false;
	}
	else if(diffY == -1) // BOT
	{
		c1->walls[BOT] = false;
		c2->walls[TOP] = false;
	}
	if(diffX == 1) // LEFT
	{	
		c1->walls[LEFT] = false;
		c2->walls[RIGHT] = false;
	}
	else if(diffX == -1) //RIGHT
	{
		c1->walls[RIGHT] = false;
		c2->walls[LEFT] = false;
	}
}
