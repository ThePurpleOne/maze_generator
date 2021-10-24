/*
	* CODE MAIN FOR MAZE CREATION
	* Author : Jonas S.
	* Date   : 24/10/2021
	! Maze generation using backtracking algo
	! source : 
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


#include "raylib.h"
#include "raymath.h"
#include "../include/maze.h"
#include "../include/jstack.h"


int main()
{
	// Get random seed
	srand(time(NULL));

	InitWindow(MAZE_WIDTH, MAZE_HEIGHT, "Maze generation");
	
	SetTargetFPS(10);

	// ! INIT MAZE
	// ? INIT WIDTH AND HEIGHT OF THE MAZE 
	Maze m1 = {.w=MAZE_WIDTH / CELL_SIZE, .h=MAZE_HEIGHT / CELL_SIZE};
	
	// ? INIT CELLS IN MAZE
	for (uint64_t x = 0; x < m1.w; x++)
	{
		for (uint64_t y = 0; y < m1.h; y++)
		{
			m1.maze[x][y] = (Cell){	.pos=(Coordinates){x, y},
									.visited=false,
									.walls={true, true, true, true}	
									};
		}
	}

	// ? INIT THE CURRENT CELL
	m1.maze[0][0].visited = true;	
	m1.current = &m1.maze[0][0];
	
	// ! END INIT MAZE

	Cell * pNextCell;
	Jstack * st = createStack(MAZE_WIDTH / CELL_SIZE * MAZE_HEIGHT / CELL_SIZE);
	bool stucked = 0;

	while (!WindowShouldClose())
	{
		BeginDrawing(); // ! DRAWING
		DrawFPS(10, 10); 
		ClearBackground(LIGHTGRAY);

		// UPDATE
		pNextCell = getNeighbor(&m1, &stucked);
		if(!stucked)
		{
			pNextCell->visited = true;
			stackPush(st, m1.current);
			removeWallsBetweenCells(m1.current, pNextCell);
			m1.current = pNextCell;

		}
		else
		{
			if(!stackIsEmpty(st))
			{
				m1.current = stackPop(st);
			}
		}
		stucked = 0;

		// printf("STACK TOP %ld\n",st->top );
		// printf("Xp : %ld | Yp : %ld \n", m1.current->pos.x, m1.current->pos.y);

		// DRAW
		showMaze(m1);

		EndDrawing(); // ! END DRAWING
	}

	CloseWindow();

	return 0;
}

// 1. CREATE 2D ARRAY OF CELLS UNVISITED
// 2. SET A CURRENT ONE
// 3. MARK IT AS VISITED
// 4. NOT STUCK? (FOR MY CASE, I RETURN THE CURRENT CELL WHEN STUCKED) 
	//a. GET RANDOM UNVISITED NEIGHBOR
	//b. PUSH CURRENT CELL TO STACK
	//c. REMOVE WALLS BETWEEN CURRENT AND NEXT CELL
	//d. SET THE CURRENT CELL WITH NEXT 
	//e. MARK IT AS VISITED
// 5. STUCKED (CURRENT CELL == NEIGHBOR CELL)
	//a. POP A CELL FROM STACK
	//b. MAKE IT CURRENT CELL AND TRY AGAIN