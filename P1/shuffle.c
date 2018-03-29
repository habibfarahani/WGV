
#include <stdio.h>

#include "shuffle.h"
#include "deck_utils.h"

/******************************************************************
 * Shuffles a deck by:
 * 1. Placing a pulled card (from top of the deck) on the table (a new stack)
 * 2. Placing the next pulled card to the bottom of the deck in hand.
 * 3. Continue steps 1 and 2 untill all the cards are transfered to the table.
 *****************************************************************/
static int shuffleDeck(struct deck *pHandDeck, struct deck *pTableDeck)
{
    if(pHandDeck && pTableDeck)
    {
        int index = 0;
        // Start by clearning any remnents of deck on the table
        initDeck(pTableDeck);

        // While there are still cards in hand continue this operation
        while(!empty(pHandDeck))
        {
            struct card cardToShuffle;

            //  Remove a card from deck in hand
            if(OK == pop(pHandDeck, &cardToShuffle))
            {
                // if it is an odd number card (1, 3, 5, etc) place the card in the bottom
                // of the deck in hand.
                if((index & 0x1) == 0x01)
                {
                    pushBottom(pHandDeck, cardToShuffle.name, (pHandDeck->num + 1));
//                    print(pHandDeck);
//                    print(pTableDeck);
                }
                else
                {
                    // If it is an even inde (0, 2, 4, etc), pleace the card in the stack on the table.
                    push(pTableDeck, cardToShuffle.name, (pTableDeck->num + 1));
                }

                index++;

            }

        }


    }
    

    return ERROR;
}



int shuffle(struct deck *pDeck)
{
    int numberOfIterations = 0;

    if(pDeck)
    {
        // Create two empty deck objects, one represents the deck in hand and the
        // other represents the deck on the table
        struct deck *pTableDeck = createDeck("Table Deck", deckSize(pDeck));
        struct deck *pHandDeck  = createDeck("Hand  Deck", deckSize(pDeck));

        // Assign the original deck to the hand (starting point while preserving the 
        // original deck for comparison)
        assignDeck(pDeck, pHandDeck);

//        print(pHandDeck);
        if(pHandDeck && pTableDeck)
        {
            do
            {
                // Shuffle the deck in hand.
                // By the time this function returns all contants of hand deck are 
                // shuffled to table deck 
                shuffleDeck(pHandDeck, pTableDeck);

                // Pick up the table deck
                moveDeck(pTableDeck, pHandDeck);

                // printf("numberOfIterations:%4d\n", numberOfIterations);
                //print(pHandDeck);
                numberOfIterations++;

                // If hand deck is the same as the original deck (pDeck) then we are 
                // done.  Exit form the loop
            }while(ERROR == compareDeck(pDeck, pHandDeck));
        }

        // Delete hand and table decks
        deleteDeck(pTableDeck);
        deleteDeck(pHandDeck);
    }

    return numberOfIterations;
}
