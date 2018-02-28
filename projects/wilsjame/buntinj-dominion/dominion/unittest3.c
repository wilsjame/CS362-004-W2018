/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main() {
    int i;
    int cost;
	 int j = 0;
	 //array of costs obtained from dominion wiki
	 int costs[treasure_map+1] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};

    printf ("TESTING getCost():\n");
    for (i = curse - 1; i <= treasure_map+1; i++){//tests value for each card as well as the edge cases
		 														  //of -1 and 27 returning the error value -1.
		 cost = getCost(i);
		 if(cost == -1 && (i == treasure_map + 1 || i == curse - 1)){ //expected errors for i = -1 and 27
			 //printf("function caught bad input %d and returned -1\n",i);
		 }
		 else if(cost == -1){ //error for card value that is not in switch, should never trigger in good code
			 printf("Error value returned from function\n");
		 }
		 else if(cost != costs[i]){ //if returned cost is not equal to the cost from the wiki
			 printf("Error on card %d with cost = %d expected cost  of %d\n",i,cost,costs[i]);
			 j++;
		 }
    }
	 printf("There were %d errrors. End of testing for getCost().\n",j);
    return 0;
}
