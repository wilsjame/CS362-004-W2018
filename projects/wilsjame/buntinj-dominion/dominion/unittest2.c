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

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int r,count;
	 int j = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING numHandCards():\n");
    for (i = 0; i < 2; i++){
		 memset(&G,23,sizeof(struct gameState));
		 r = initializeGame(numPlayer,k,seed,&G);
		 if(r == -1){
			 printf("Error initializing the game");
		 }
		 G.whoseTurn = i;
		 G.handCount[0] = 12;
		 G.handCount[1] = 2;
		 count = numHandCards(&G);
		 if(count != G.handCount[i]){
			 printf("Error on player %d\n",i+1);
			 j++;
		 }
    }
	 printf("There were %d errrors. End of testing for numHandCards().\n",j);
    return 0;
}
