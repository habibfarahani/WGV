

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deck.h"
#include "deck_utils.h"

/******************************************************************
 * function to dynamically allocates a deck object and assignes a name
 * and max size to the deck.
 *****************************************************************/
struct deck * createDeck(char *deckName, int maxSize)
{
    // Allocate a deck object.
    struct deck *pDeck = (struct deck *)malloc(sizeof(struct deck));

    if(pDeck)
    {
        strncpy(pDeck->name, deckName, MAX_NAME_LENGTH);
        pDeck->size = maxSize;
        pDeck->num = 0;
        pDeck->head = NULL;
        pDeck->tail = NULL;
        // Ensure there are no items in the deck
        if(OK == initDeck(pDeck))
        {
            return pDeck;
        }
    }

    return NULL;
}

/******************************************************************
 * Initializes a deck and empties all card contents but preserves the name
 * and max size.
 *****************************************************************/
int initDeck(struct deck *pDeck)
{
    if(pDeck)
    {
        if(pDeck->num)
        {
            struct card *pCardToDelete = pDeck->head;
            // free up all card objects if any
             while(pCardToDelete )
            {
                pDeck->head = pCardToDelete->next;

                free(pCardToDelete);

                pCardToDelete = pDeck->head;
                pDeck->num--;
            }

        }

        if(!pDeck->num)
        {
            pDeck->head = NULL;
            pDeck->tail = NULL;

            return OK;
        }

        printf("Invalid number for deck %d\n", pDeck->num);
    }

    return ERROR;

}

/******************************************************************
 * Assign a destination to a source deck.
 *****************************************************************/
int assignDeck(struct deck *pSrcDeck, struct deck *pDstDeck)
{
    if(pSrcDeck && pDstDeck)
    {
        struct card *pCardToAssign = pSrcDeck->tail;

        //  Initialize the destination deck first
        initDeck(pDstDeck);

        // For all cards in source deck, push them into the destination deck
        while(pCardToAssign )
        {
            push(pDstDeck, pCardToAssign->name, pCardToAssign->pos);

            pCardToAssign = pCardToAssign->previous;

        }


        return OK;
    }

    return ERROR;

}


/******************************************************************
 * Moves the contents of the source deck into destination deck
 * clearing source deck.
 *****************************************************************/
int moveDeck(struct deck *pSrcDeck, struct deck *pDstDeck)
{

    if(OK == assignDeck(pSrcDeck, pDstDeck))
    {
        initDeck(pSrcDeck);
    }

    return ERROR;

}

/******************************************************************
 * Compares two decks by comparing each individual card..
 *****************************************************************/
int compareDeck(struct deck *pSrcDeck, struct deck *pDstDeck)
{
    if(pSrcDeck && pDstDeck)
    {
        // Start from top of both decks
        struct card *pSrcCard = pSrcDeck->head;
        struct card *pDstCard = pDstDeck->head;
        int matched =  ERROR;

        // continue on until a mismatch is found
        while(pSrcCard && pDstCard && ((matched = compareCard(pSrcCard, pDstCard)) == OK))
        {
            pSrcCard = pSrcCard->next;
            pDstCard = pDstCard->next;
        }

        return matched;
    }

    return ERROR;

}

/******************************************************************
 * Return the max size of a deck, -1 = invalid deck
 *****************************************************************/
int deckSize(struct deck *pDeck)
{
    if(pDeck)
    {
        return pDeck->size;
    }

    return -1;


}

/******************************************************************
 * Return number of cards in a deck, -1 = invalid deck.
 *****************************************************************/
int deckNum(struct deck *pDeck)
{
    if(pDeck)
    {
        return pDeck->num;
    }

    return -1;


}


/******************************************************************
 * Frees up a deck and all its contents
 *****************************************************************/
int deleteDeck(struct deck *pDeck)
{
    if(pDeck)
    {
        initDeck(pDeck);

        free(pDeck);

        return OK;
    }

    return ERROR;
}


/******************************************************************
 * Check to see if a deck is empty
 *****************************************************************/
int empty(struct deck *pDeck)
{
    if(pDeck)
    {
        if((!pDeck->head) || (!pDeck->tail))
        {
            return OK;
        }
    }
    return ERROR;
}