/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
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

    printf ("TESTING supplyCount():\n");
    for (i = curse; i <= treasure_map; i++){
		 memset(&G,23,sizeof(struct gameState));
		 r = initializeGame(numPlayer,k,seed,&G);
		 if(r == -1){
			 printf("Error initializing the game");
		 }
		 G.supplyCount[i] = 12;
		 count = supplyCount(i,&G);
		 if(count != 12){
			 printf("Error on card %d\n",i);
			 j++;
		 }
    }
	 printf("There were %d errrors. End of testing for supplyCount().\n",j);
    return 0;
}
