/*
	* CODE JSTACK
	* Author : Jonas S.
	* Date   : 24/10/2021
	! BASIC STACK IMPLEMENTATION FOR CELLS
*/

#include <stdio.h>
#include "../include/jstack.h"
#include "../include/maze.h"

Jstack * createStack(uint64_t max)
{
	// idk 
	Jstack * st = (Jstack * )malloc(sizeof(Jstack));
	st->max = max;
	st->top = -1; //Base value when empty
	st->stack = (Cell **)malloc(st->max * sizeof(Cell*));
	return st;
}

/**
 * @brief Stack is full, max capacity reached
 * 
 * @param st Pointer to Stack struct 
 * @return uint64_t
 */
bool stackIsFull(Jstack * st)
{
	return (st->top == (int64_t)st->max -1);
}

/**
 * @brief Stack is empty, still base value in
 * 
 * @param st Pointer to Stack struct 
 * @return uint64_t
 */
bool stackIsEmpty(Jstack * st)
{
	if(st->top < 0)
	{
		return true;
	}
	return false;
	// return (st->top == (int64_t)-1);
}

/**
 * @brief Add an item on the stack
 * 
 * @param st Pointer to Stack struct 
 * @param item
 */
void stackPush(Jstack * st, Cell * item)
{
	if(stackIsFull(st)){return;}
	st->stack[++st->top] = item;
}

/**
 * @brief Pop the last item added (returns it)
 * 
 * @param st Pointer to Stack struct 
 * @return uint64_t
 */
Cell * stackPop(Jstack * st)
{
	if(stackIsEmpty(st)){return 0;}
	Cell *buffer = st->stack[st->top--];
	return buffer;
	// return st->stack[st->top--];
}

/**
 * @brief Returns the item without poping it
 * 
 * @param st
 * @return uint64_t
 */
Cell * stackPeek(Jstack * st)
{
	if(stackIsEmpty(st)){return 0;}
	return st->stack[st->top];
}

void printStack(Jstack st)
{
	for (int i = 0; i < st.top; i++)
	{
		printf("ITEM %d : xP : %ld yP %ld \n", i, st.stack[i]->pos.x, st.stack[i]->pos.y );
	}
}





