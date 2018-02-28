/*
 * randomadventurer.c
 *
 * Tests adventurer
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"
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

		initializeGame(2,kingdomCards(0,1,2,3,4,5,6,7,8,9),20,&pre);//ensures any weird errors dont occure. All pertenent input is still rnadom.
		pre.handCount[pre.whoseTurn] = rand()%(MAX_HAND-3)+1; //makes sure the handcount isnt too large (the function actually draws up to 3 cards). add one to not have hand empty.
		//fill hand with actual cards so that the getCost function will work.
		for(i = 0;i < pre.handCount[pre.whoseTurn];i++){
			pre.hand[pre.whoseTurn][i] = rand()%27;
		}

		pre.deckCount[pre.whoseTurn] = rand()%(MAX_DECK-1-pre.handCount[pre.whoseTurn]); // makes sure the deckcount isnt too large.
		for(i = 0;i < pre.deckCount[pre.whoseTurn];i++){
			pre.deck[pre.whoseTurn][i] = rand()%27;
		}

		pre.discardCount[pre.whoseTurn] = rand()%(MAX_DECK-1-pre.handCount[pre.whoseTurn]-pre.deckCount[pre.whoseTurn]);//makes sure the discardcount isnt too large.
		for(i = 0;i < pre.discardCount[pre.whoseTurn];i++){
			pre.discard[pre.whoseTurn][i] = rand()%27;
		}

		pre.playedCardCount = rand()%MAX_DECK; //makes sure that playedcardcount isn't too high for discard function.


		int handPos = rand()%(pre.handCount[pre.whoseTurn]); //sets the handposition of the card to actually be within the hand.
		memcpy(&post, &pre, sizeof(struct gameState)); //set up a gamestateto test on.
		int r;
		r = cardEffect(adventurer,choice,choice,choice,&post,handPos,&choice); //store the return value.
		if(r != 0){
			printf("failed return value.\n");
			error++; //track the number of errors for a final print statement.
		}
		else{ //given proper return value run the rest of the tests.
			//test that the number of cards is no more than plus one and no less than -1 given that you discard a card and gain up to two cards.
			if(post.handCount[pre.whoseTurn] > pre.handCount[pre.whoseTurn]+1 || (post.handCount[pre.whoseTurn]) < pre.handCount[pre.whoseTurn]-1){
				printf("error with the number of cards in the hand after run\n");
				error++;
			}

			if(post.playedCards[post.playedCardCount-1] != pre.hand[pre.whoseTurn][handPos]){
				printf("error with the card not being moved to playedCards for discard.\n");
				error++;
			}

			for(i = post.handCount[pre.whoseTurn]-1;i >= pre.handCount[pre.whoseTurn];i--){
				if(post.hand[pre.whoseTurn][i] != gold && post.hand[pre.whoseTurn][i] != silver && post.hand[pre.whoseTurn][i] != copper){
					printf("error with non treasure card added to hand");
					error++;
					break;
				}
			}

			//account for all the things that are expected to change in the gamestate.
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
