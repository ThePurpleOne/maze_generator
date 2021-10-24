/*
	* HEADER JSTACK
	* Author : Jonas S.
	* Date   : 24/10/2021
	! BASIC STACK IMPLEMENTATION
*/


#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/maze.h"

#ifndef _JSTACK_H_
#define _JSTACK_H_

// STRUCT
typedef struct
{	
	uint64_t max;
	int64_t top;
	Cell ** stack;
}Jstack;


// DEFINES

// PROTOTYPE FUNCTIONS

Jstack * createStack(uint64_t max);
bool stackIsFull(Jstack * st);
bool stackIsEmpty(Jstack * st);
void stackPush(Jstack * st, Cell * item);
Cell * stackPop(Jstack * st);
Cell * stackPeek(Jstack * st);
void printStack(Jstack st);
#endif