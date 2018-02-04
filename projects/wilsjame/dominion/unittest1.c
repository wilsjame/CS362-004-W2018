/* unittest1.c
 * Unit test for isGameOver function from the dominion-base code, dominion.c.
 * Include the following lines in Makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 * 	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main()
{
	printf("Hello from unittest1!\n");

	return;
}

