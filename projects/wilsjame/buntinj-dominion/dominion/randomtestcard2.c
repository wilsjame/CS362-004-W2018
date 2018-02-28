/*
 * randomcardtest2.c
 *
 * Tests salvager
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "salvager"
#define iterations 2000

int main(){
	int i,n;
	int error = 0;
//	srand(time(NULL));
	int choice2 = 0; //Use for the second two choices and bonus as they don't matter in the salvager card.
	printf("TESTING %s.\n",TESTCARD);
	printf("RANDOM TESTS.\n");

	for(n = 0; n < iterations; n++){
		srand(time(NULL));
		struct gameState pre,post;
		for(i = 0;i < sizeof(struct gameState); i++){
			((char*)&pre)[i] = rand()%256;
		}
		//set up the gamestate to be under "sane" conditions
		pre.whoseTurn = rand()%2; //sets the turn to be one of two players.
		pre.numPlayers = 2; //playdom uses two players, so I will too.
		pre.handCount[pre.whoseTurn] = rand()%MAX_HAND+1; //makes sure the handcount isnt too large (need room to draw a card). add one to not have hand empty.
		//fill hand with actual cards so that the getCost function will work.
		for(i = 0;i < pre.handCount[pre.whoseTurn];i++){
			pre.hand[pre.whoseTurn][i] = rand()%27;
		}

		pre.deckCount[pre.whoseTurn] = rand()%MAX_DECK; // makes sure the deckcount isnt too large.
		pre.discardCount[pre.whoseTurn] = rand()%MAX_DECK; //makes sure the discardcount isnt too large.
		pre.playedCardCount = rand()%MAX_DECK; //makes sure that playedcardcount isn't too high for discard function.
		int handPos = rand()%(pre.handCount[pre.whoseTurn]); //sets the handposition of the card to actually be within the hand.
		int choice1 = rand()%(pre.handCount[pre.whoseTurn]); //sets the first choice variable to be a card in the hand.
		while(choice1 == handPos){//ensure you aren't trashing the played card.
			printf("loop");
			choice1 = rand()%(pre.handCount[pre.whoseTurn]);
		}
		memcpy(&post, &pre, sizeof(struct gameState)); //set up a gamestateto test on.
		int r;
		r = cardEffect(salvager,choice1,choice2,choice2,&post,handPos,&choice2); //store the return value.
		if(r != 0){
			printf("failed return value.\n");
			error++; //track the number of errors for a final print statement.
		}
		else{ //given proper return value run the rest of the tests.
			//test that the number of cards is the down by two due to discard and trash.
			if(pre.handCount[pre.whoseTurn] != (post.handCount[pre.whoseTurn]+2)){
				printf("error with the number of cards in the hand after run\n");
				error++;
			}
			
			if(pre.numBuys != (post.numBuys-1)){ //if the number of buys were not changed by plus 1.
				printf("error with the number of actions not being incresed properly.\n");
				error++;
			}
			//ensure the coins are increased by the cost of the trashed card.
			if(pre.coins != post.coins - getCost(pre.hand[pre.whoseTurn][choice1])){
					printf("error with addition of trash card cost to coins.\n");
					error++;
			}
			//cant test discard as it is broken. testing played cards instead.
			if(pre.playedCardCount != post.playedCardCount-1){
				printf("error with move of salvager to played card pile.\n");
				error++;
			}

			//test that salvager is at top of played cards
			if(post.playedCards[post.playedCardCount-1] != pre.hand[pre.whoseTurn][handPos]){
				printf("error with top of playedCards not being played card.\n");
				error++;
			}

			//account for all the things that are expected to change in the gamestate.
			pre.numBuys = post.numBuys;
			pre.coins = post.coins;

		//	memcpy(pre.deck[pre.whoseTurn],post.deck[pre.whoseTurn],sizeof(int)*MAX_DECK);
		//	pre.deckCount[pre.whoseTurn] = post.deckCount[pre.whoseTurn];

			memcpy(pre.hand[pre.whoseTurn],post.hand[pre.whoseTurn],sizeof(int)*(MAX_HAND));
			pre.handCount[pre.whoseTurn] = post.handCount[pre.whoseTurn];

			memcpy(pre.discard[pre.whoseTurn],post.discard[pre.whoseTurn],sizeof(int)*MAX_DECK);
			pre.discardCount[pre.whoseTurn] = post.discardCount[pre.whoseTurn];

			memcpy(pre.playedCards,post.playedCards,sizeof(int)*MAX_DECK);
			pre.playedCardCount = post.playedCardCount;

			if(memcmp(&pre,&post,sizeof(struct gameState)) != 0){ //check that nothing that wasn't expected change changed.
				printf("error with the parts of gamestate that shouldn't change.\n");
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
