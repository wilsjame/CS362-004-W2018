/*
 * randomcardtest1.c
 *
 * Tests great_hall
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "great_hall"
#define iterations 2000

int main(){
	int i,n;
	int error = 0;
	srand(time(NULL));
	int choice = 0; //Use for all three choices and bonus as they don't matter in the great_hall card.
	printf("TESTING %s.\n",TESTCARD);
	printf("RANDOM TESTS.\n");

	for(n = 0; n < iterations; n++){
		struct gameState pre,post;
		for(i = 0;i < sizeof(struct gameState); i++){
			((char*)&pre)[i] = rand()%256;
		}
		//set up the gamestate to be under "sane" conditions
		pre.whoseTurn = rand()%2; //sets the turn to be one of two players.
		pre.numPlayers = 2; //playdom uses two players, so I will too.
		pre.handCount[pre.whoseTurn] = rand()%(MAX_HAND-1)+1; //makes sure the handcount isnt too large (need room to draw a card). add one to not have hand empty.
		pre.deckCount[pre.whoseTurn] = rand()%MAX_DECK; // makes sure the deckcount isnt too large.
		pre.discardCount[pre.whoseTurn] = rand()%MAX_DECK; //makes sure the discardcount isnt too large.
		pre.playedCardCount = rand()%MAX_DECK; //makes sure that playedcardcount isn't too high for discard function.
		int handPos = rand()%(pre.handCount[pre.whoseTurn]); //sets the handposition of the card to actually be within the hand.
		memcpy(&post, &pre, sizeof(struct gameState)); //set up a gamestateto test on.
		int r;
		r = cardEffect(great_hall,choice,choice,choice,&post,handPos,&choice); //store the return value.
		if(r != 0){
			printf("failed return value.\n");
			error++; //track the number of errors for a final print statement.
		}
		else{ //given proper return value run the rest of the tests.
			//test that the number of cards is the same given one is discarded and one is drawn
			if(pre.handCount[pre.whoseTurn] != (post.handCount[pre.whoseTurn])){
				printf("error with the number of cards in the hand after run\n");
				error++;
			}
			if(pre.deckCount[pre.whoseTurn] > 0){//if there was a card to take from the deck
				//ensure card drawn came from the top of the deck.
				if((pre.deck[pre.whoseTurn][pre.deckCount[pre.whoseTurn]-1]) != (post.hand[pre.whoseTurn][handPos])){
					printf("error with card on top of hand not being card that was on top of deck.\n");
					error++;
				}
			}
			if(pre.numActions != (post.numActions-1)){ //if the number of actions were not changed by plus 1.
				printf("error with the number of actions not being incresed properly.\n");
				error++;
			}
			int d = pre.handCount[pre.whoseTurn];
			//account for all the things that are expected to change in the gamestate.
			pre.numActions = post.numActions;

			memcpy(pre.deck[pre.whoseTurn],post.deck[pre.whoseTurn],sizeof(int)*MAX_DECK);
			pre.deckCount[pre.whoseTurn] = post.deckCount[pre.whoseTurn];

			memcpy(pre.hand[pre.whoseTurn],post.hand[pre.whoseTurn],sizeof(int)*(MAX_HAND));
			pre.handCount[pre.whoseTurn] = post.handCount[pre.whoseTurn];

			memcpy(pre.discard[pre.whoseTurn],post.discard[pre.whoseTurn],sizeof(int)*MAX_DECK);
			pre.discardCount[pre.whoseTurn] = post.discardCount[pre.whoseTurn];

			memcpy(pre.playedCards,post.playedCards,sizeof(int)*MAX_DECK);
			pre.playedCardCount = post.playedCardCount;

			if(memcmp(&pre,&post,sizeof(struct gameState)) != 0){ //check that nothing that wasn't expected change changed.
				printf("error with the parts of gamestate that shouldn't change.\n");
				printf("deckCount: %d\n",d);
				error++;
			}
		}
	}
	if(error == 0){
		printf("ALL TESTS PASSED\n");
	}else{
		printf("There were %d errors in testing the code %d times\n",error,iterations);
	}
	return 0;
}
