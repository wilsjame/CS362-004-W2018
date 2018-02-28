/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

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

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	// ----------- TEST 1: All Gold treasure cards -------------
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// fill deck with gold
	for(i = 0;i < G.deckCount[thisPlayer];i++){
		G.deck[thisPlayer][i] = gold;
	}
	// copy to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	// Test the handcount is +2
	if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 2){
		printf("Error with the number of treasure cards drawn in test 1.\n");
		printf("Expected: %d Actual: %d\n",2,testG.handCount[thisPlayer] - G.handCount[thisPlayer]);
		E++;
	}
	// Test the top two cards in hand are gold cards.
	if(testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] != gold || testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] != gold){
		printf("Error with the cards at the top of the players hand in test 1.\n");
		printf("Expected: %d and %d Actual: %d and %d\n",gold,gold,testG.hand[thisPlayer][testG.handCount[thisPlayer]-1],testG.hand[thisPlayer][testG.handCount[thisPlayer]-2]);
		E++;
	}
	// Test that no cards were discarded
	if(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer]){
		printf("Error with the number of cards discarded in test 1.\n");
		printf("Expected: %d Actual: %d\n",0,testG.discardCount[thisPlayer]-G.discardCount[thisPlayer]);
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

	// ----------- TEST 2: All Silver treasure cards -------------
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// fill deck with silver
	for(i = 0;i < G.deckCount[thisPlayer];i++){
		G.deck[thisPlayer][i] = silver;
	}
	// copy to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	// Test the handcount is +2
	if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 2){
		printf("Error with the number of treasure cards drawn in test 2.\n");
		printf("Expected: %d Actual: %d\n",2,testG.handCount[thisPlayer] - G.handCount[thisPlayer]);
		E++;
	}
	// Test the top two cards in hand are silver cards.
	if(testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] != silver || testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] != silver){
		printf("Error with the cards at the top of the players hand in test 2.\n");
		printf("Expected: %d and %d Actual: %d and %d\n",silver,silver,testG.hand[thisPlayer][testG.handCount[thisPlayer]-1],testG.hand[thisPlayer][testG.handCount[thisPlayer]-2]);
		E++;
	}
	// Test that no cards were discarded
	if(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer]){
		printf("Error with the number of cards discarded in test 2.\n");
		printf("Expected: %d Actual: %d\n",0,testG.discardCount[thisPlayer]-G.discardCount[thisPlayer]);
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
	
	// ----------- TEST 3: All Copper treasure cards -------------
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// fill deck with copper
	for(i = 0;i < G.deckCount[thisPlayer];i++){
		G.deck[thisPlayer][i] = copper;
	}
	// copy to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	// Test the handcount is +2
	if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 2){
		printf("Error with the number of treasure cards drawn in test 3.\n");
		printf("Expected: %d Actual: %d\n",2,testG.handCount[thisPlayer] - G.handCount[thisPlayer]);
		E++;
	}
	// Test the top two cards in hand are copper cards.
	if(testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] != copper || testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] != copper){
		printf("Error with the cards at the top of the players hand in test 3.\n");
		printf("Expected: %d and %d Actual: %d and %d\n",copper,copper,testG.hand[thisPlayer][testG.handCount[thisPlayer]-1],testG.hand[thisPlayer][testG.handCount[thisPlayer]-2]);
		E++;
	}
	// Test that no cards were discarded
	if(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer]){
		printf("Error with the number of cards discarded in test 3.\n");
		printf("Expected: %d Actual: %d\n",0,testG.discardCount[thisPlayer]-G.discardCount[thisPlayer]);
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
	
	// ----------- TEST 4: No treasure cards -------------
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// fill deck with provinces
	for(i = 0;i < G.deckCount[thisPlayer];i++){
		G.deck[thisPlayer][i] = province;
	}
	// copy to test state
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	// Test the handcount is the same
	if(testG.handCount[thisPlayer] != G.handCount[thisPlayer]){
		printf("Error with the number of treasure cards drawn in test 4.\n");
		printf("Expected: %d Actual: %d\n",2,testG.handCount[thisPlayer] - G.handCount[thisPlayer]);
		E++;
	}
	// Test the top two cards in hand havent changed
	if(testG.hand[thisPlayer][testG.handCount[thisPlayer]-1] != G.hand[thisPlayer][G.handCount[thisPlayer]-1] || testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] != G.hand[thisPlayer][G.handCount[thisPlayer]-2]){
		printf("Error with the cards at the top of the players hand in test 4.\n");
		printf("Expected: %d and %d Actual: %d and %d\n",copper,copper,testG.hand[thisPlayer][testG.handCount[thisPlayer]-1],testG.hand[thisPlayer][testG.handCount[thisPlayer]-2]);
		E++;
	}
	// Test that all deck cards were discarded
	if(testG.discardCount[thisPlayer] != G.deckCount[thisPlayer]){
		printf("Error with the number of cards discarded in test 4.\n");
		printf("Expected: %d Actual: %d\n",0,testG.discardCount[thisPlayer]-G.discardCount[thisPlayer]);
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
	//print the number of errors and that testing is finished.
	printf("There were %d errors. Finished testing %s card.\n\n",E,TESTCARD);
	return 0;
}
