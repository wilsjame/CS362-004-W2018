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
	 int verdict;
    int seed = 1000;
    int numPlayer = 2;
    int r;
	 int j = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING isGameOver():\n");
	 //initialize gamestateto be used for testing
	 memset(&G,23,sizeof(struct gameState));
	 r = initializeGame(numPlayer,k,seed,&G);
	 if(r == -1){
		 printf("Error initializing the game");
		 return -1;
	 }
	 //set all supplycounts to 1 so that game is not over by the rules of dominion.
    for (i = curse; i <= treasure_map; i++){
		 G.supplyCount[i] = 1;
    }
	 verdict = isGameOver(&G);
	 if(verdict != 0){
		 printf("Error when all supplycounts are greater than zero.\n");
		 j++;
	 }

	 //Game should be over with province supply set to 0
    for (i = curse; i <= treasure_map; i++){//ensure that all supply counts are preset to 1.
		 G.supplyCount[i] = 1;
    }
	 G.supplyCount[province] = 0;
	 verdict = isGameOver(&G);
	 if(verdict != 1){
		 printf("Error when province is equal to zero.\n");
		 j++;
	 }

	 //Game should be over with three cards supplys all set to 0
    for (i = curse; i <= treasure_map; i++){//ensure that all supply counts are preset to 1.
		 G.supplyCount[i] = 1;
    }
	 G.supplyCount[12] = 0;
	 G.supplyCount[13] = 0;
	 G.supplyCount[14] = 0;
	 verdict = isGameOver(&G);
	 if(verdict != 1){
		 printf("Error when three supplycounts are zero.\n");
		 j++;
	 }
	 
	 //Game should be over with all supply counts set to 0
    for (i = curse; i <= treasure_map; i++){//ensure that all supply counts are preset to 0.
		 G.supplyCount[i] = 0;
    }
	 verdict = isGameOver(&G);
	 if(verdict != 1){
		 printf("Error when all supplycounts are zero.\n");
		 j++;
	 }
	 
	 //Game should be over with the first three supply counts set to 0
    for (i = curse; i <= treasure_map; i++){//ensure that all supply counts are preset to 1.
		 G.supplyCount[i] = 1;
    }
	 for(i = curse;i < curse+3;i++){
		 G.supplyCount[i] = 0;
	 }
	 verdict = isGameOver(&G);
	 if(verdict != 1){
		 printf("Error when the first three supplycounts are zero.\n");
		 j++;
	 }
	 
	 //Game should be over with the last three supply cards set to 0
    for (i = curse; i <= treasure_map; i++){//ensure that all supply counts are preset to 1.
		 G.supplyCount[i] = 1;
    }
	 for(i = treasure_map;i > treasure_map-3;i--){
		 G.supplyCount[i] = 0;
	 }
	 verdict = isGameOver(&G);
	 if(verdict != 1){
		 printf("Error when the last three supplycounts are zero.\n");
		 j++;
	 }
	 
	 //Game should not be over with the first two supply counts set to 0
    for (i = curse; i <= treasure_map; i++){//ensure that all supply counts are preset to 1.
		 G.supplyCount[i] = 1;
    }
	 for(i = curse;i < curse+2;i++){
		 G.supplyCount[i] = 0;
	 }
	 verdict = isGameOver(&G);
	 if(verdict != 0){
		 printf("Error when the first two supplycounts are zero.\n");
		 j++;
	 }
	 
	 //Game should not be over with the last two supply counts set to 0
    for (i = curse; i <= treasure_map; i++){//ensure that all supply counts are preset to 1.
		 G.supplyCount[i] = 1;
    }
	 for(i = treasure_map;i > treasure_map-2;i--){
		 G.supplyCount[i] = 0;
	 }
	 verdict = isGameOver(&G);
	 if(verdict != 0){
		 printf("Error when the last two supplycounts are zero.\n");
		 j++;
	 }
	 
	 //Game should not be over with the first supply count set to zero
    for (i = curse; i <= treasure_map; i++){//ensure that all supply counts are preset to 1.
		 G.supplyCount[i] = 1;
    }
	 G.supplyCount[curse] = 0;
	 verdict = isGameOver(&G);
	 if(verdict != 0){
		 printf("Error when the first supplycount is zero.\n");
		 j++;
	 }
	 
	 //Game should not be over with the last supply count set to zero
    for (i = curse; i <= treasure_map; i++){//ensure that all supply counts are preset to 1.
		 G.supplyCount[i] = 1;
    }
	 G.supplyCount[treasure_map] = 0;
	 verdict = isGameOver(&G);
	 if(verdict != 0){
		 printf("Error when the last supplycount is zero.\n");
		 j++;
	 }
	 
	 printf("There were %d errrors. End of testing for isGameOver().\n",j);
    return 0;
}
