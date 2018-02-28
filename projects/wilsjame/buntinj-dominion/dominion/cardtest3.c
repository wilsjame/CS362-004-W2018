/*
 * cardtest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "outpost"

int main() {
	int i;
	 int E = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST for outpost --------------
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(outpost, choice1, choice2, choice3, &testG, handpos, &bonus);
	// Test that the outpostplayed variable has been iterated to signal an extra turn.
	if(testG.outpostPlayed != G.outpostPlayed + 1){
		printf("Error with the value of outpostPlayed after card effect.\n");
		printf("Expected: %d Actual: %d\n", G.outpostPlayed + 1,testG.outpostPlayed);
		E++;
	}
	// Test that the top card on the discard pile is outpost
	if(testG.discard[thisPlayer][testG.discardCount[thisPlayer]-1] != outpost){
		printf("Error with the top discard card.\n");
		printf("Expected: %d Actual: %d\n",outpost,testG.discard[thisPlayer][testG.discardCount[thisPlayer]-1]);
		E++;
	}
	// Test that the discard count has been incremented.
	if(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer]+1){
		printf("Error with the number of cards discarded.\n");
		printf("Expected: %d Actual: %d\n",1,testG.discardCount[thisPlayer]-G.discardCount[thisPlayer]);
		E++;
	}
	// Tests for the retention of other players state.
	if(testG.discardCount[thisPlayer+1] != G.discardCount[thisPlayer+1]){
		printf("Error with the discardCount of the second player.\n");
		E++;
	}
	for(i = 0;i < testG.discardCount[thisPlayer+1];i++){
		if(testG.discard[thisPlayer+1][i] != G.discard[thisPlayer+1][i]){
			printf("Error with the card at the %d location of the second players discard.\n",i);
			E++;
		}
	}
	for(i = 0;i < testG.deckCount[thisPlayer+1];i++){
		if(testG.deck[thisPlayer+1][i] != G.deck[thisPlayer+1][i]){
			printf("Error with the card at %d location of the second players deck.\n",i);
			E++;
		}
	}
	if(testG.deckCount[thisPlayer+1] != G.deckCount[thisPlayer+1]){
		printf("Error with the deckCount of the second player.\n");
		E++;
	}
	for(i = 0;i < testG.handCount[thisPlayer+1];i++){
		if(testG.hand[thisPlayer+1][i] != G.hand[thisPlayer+1][i]){
			printf("Error with the card at %d location of the second players hand.\n",i);
			E++;
		}
	}
	if(testG.handCount[thisPlayer+1] != G.handCount[thisPlayer+1]){
		printf("Error with the handCount of the second player.\n");
		E++;
	}
	// Test for the retention of Kingdom card piles
	for(i = 0;i < 10;i++){
		if(testG.supplyCount[k[i]] != G.supplyCount[k[i]]){
			printf("Error with the %d kingdom card.\n",i);
			E++;
		}
	}
	// Test for the retention of Victory Card piles
	for(i = curse;i <= province;i++){
		if(testG.supplyCount[i] != G.supplyCount[i]){
			printf("Error with the %d victory card.\n",i);
			E++;
		}
	}
	// Output the results of the tests.
	printf("There were %d errors. Finished testing %s card.\n",E,TESTCARD);
	return 0;
}
