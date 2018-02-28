/*
 * cardtest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"

int main() {
    int newCards = 0;
	 int newActions = 0;
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

	// ----------- TEST for great_hall --------------
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 1;
	newActions = 1;
	// Test that the number of actions has been increased by the appropriate amount.
	if(testG.numActions != G.numActions + newActions){
		printf("Error with the number of actions after card effect.\n");
		printf("Expected: %d Actual: %d\n", G.numActions + newActions,testG.numActions);
		E++;
	}
	// Test that the handCount has been altered to match the expected changes.
	if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded){
		printf("Error with the number of cards drawn by great_hall\n");
		printf("Expected: %d, Actual: %d\n",newCards,testG.handCount[thisPlayer]-(G.handCount[thisPlayer]-1));
		E++;
	}
	// Test that the deckCount has been altered to match the expected changes.
	if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards + shuffledCards){
		printf("Error with the number of cards removed from the deck.\n");
		printf("Expected: %d Actual: %d\n",newCards,G.deckCount[thisPlayer]-testG.deckCount[thisPlayer]);
		E++;
	}
	// Test that the top card on discard pile is great_hall to imply it has been discarded.
	if(testG.discard[thisPlayer][testG.discardCount[thisPlayer]-1] != great_hall){
		printf("Error with the top discard card.\n");
		printf("Expected: %d Actual: %d\n",great_hall,testG.discard[thisPlayer][testG.discardCount[thisPlayer]-1]);
		E++;
	}
	// Test if the discard count has been iterate to imply that a card was discarded.
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
	// Output the results tot eh tests
	printf("There were %d errors. Finished testing %s card.\n",E,TESTCARD);
	return 0;
}
