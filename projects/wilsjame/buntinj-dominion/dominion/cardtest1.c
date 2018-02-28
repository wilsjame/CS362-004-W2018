/*
 * cardtest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
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

	// ----------- TEST for smithy --------------
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 3;
	// Test that the handCount has been altered to account for the added cards.
	if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded){
		printf("Error with the number of cards drawn by smithy\n");
		printf("Expected: %d, Actual: %d\n",newCards,testG.handCount[thisPlayer]-(G.handCount[thisPlayer]-1));
		E++;
	}
	// Test that the deckCount has been altered to account for the lost cards.
	if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards + shuffledCards){
		printf("Error with the number of cards removed from the deck.\n");
		printf("Expected: %d Actual: %d\n",newCards,G.deckCount[thisPlayer]-testG.deckCount[thisPlayer]);
		E++;
	}
	// Test that the smithy card is on top the discard pile to show it has been discarded.
	if(testG.discard[thisPlayer][testG.discardCount[thisPlayer]-1] != smithy){
		printf("Error with the top discard card.\n");
		printf("Expected: %d Actual: %d\n",smithy,testG.discard[thisPlayer][testG.discardCount[thisPlayer]-1]);
		E++;
	}
	// Test the discard count to ensure it acounts for the new discard.
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
