

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deck.h"
#include "deck_utils.h"




/******************************************************************
 * function create a card with a given name and position on top of the stack 
 *****************************************************************/
int push(struct deck *pDeck, char *name, int pos)
{
    // If deck and name are valid
    if(pDeck && name)
    {

        // Allocate  acard
        struct card *pCard = (struct card *)malloc(sizeof(struct card));

        if((pCard) && (pDeck->num < pDeck->size))
        {
            // Copy the name of the card and its position in the new card
            strncpy(pCard->name, name, MAX_NAME_LENGTH);
            pCard->pos = pos;

            // Initialize both pointers 
            pCard->previous = NULL;
            pCard->next = NULL;

            // If the deck is empty, then both head and tail should point to the same card
            if( OK == empty(pDeck))
            {
                pDeck->head = pCard;
                pDeck->tail = pCard;
            }
            else
            {
                // If deck is not empty the the previous pointer of the card
                // in head is going to point to new card and head of deck points to it
                pDeck->head->previous = pCard;
                pCard->next = pDeck->head;
                pDeck->head = pCard;
            }
            // Increment numbers in the deck
            pDeck->num++;

            return OK;
        }
    }

    return ERROR;
}

/******************************************************************
 * function pops a card and copies in a preallocated card (pCard) from the top
 *****************************************************************/
int pop(struct deck *pDeck, struct card *pCard)
{
    // are deck and card valid
    if(pDeck && pCard)
    {
        // If deck is not empty remove the top element.
        if(!empty(pDeck))
        {
            struct card *pCardtoPop = pDeck->head;

            // Copy the card at the head to the passed card object.
            strncpy(pCard->name, pCardtoPop->name, MAX_NAME_LENGTH);
            pCard->pos = pCardtoPop->pos;

            // free the top card
            free(pCardtoPop);
            // Readjust the deck
            if(pDeck->head == pDeck->tail)
            {
                pDeck->head = NULL;
                pDeck->tail = NULL;
            }
            else
            {
                pDeck->head = pDeck->head->next;
                pDeck->head->previous = NULL;

            }
            // decrement the number of elements
            if(pDeck->num)
            {
                pDeck->num--;
            }

            if(!pDeck->tail)
            {
                pDeck->head = NULL;
            }


            return OK;
        }
    }

    return ERROR;

}



/******************************************************************
 * function pushes a card to the bottom of the card stack (not a normal stack operation)
 *****************************************************************/
int pushBottom(struct deck *pDeck, char *name, int pos)
{
    //  Dynamically allocate the card with a given name and position within the stack
    struct card *pCard = (struct card *)malloc(sizeof(struct card));

    // If both card and stack are valid
    if(pDeck && pCard)
    {
        strncpy(pCard->name, name, MAX_NAME_LENGTH);
        pCard->previous = NULL;
        pCard->next = NULL;
        pCard->pos = pos;

        // Insert the card where the tail pointer of the stack is pointing to
        // Bottom of the stack
        if( OK == empty(pDeck))
        {
            pDeck->head = pCard;
            pDeck->tail = pCard;
        }
        else
        {
            pDeck->tail->next = pCard;
            pCard->previous = pDeck->tail;
            pDeck->tail = pCard;
        }
        pDeck->num++;

        return OK;
        
    }

    return ERROR;
}






int print(struct deck *pDeck)
{
    if(pDeck)
    {
        if(!empty(pDeck))
        {
//            printf("Deck: %s  max: %d num: %d\n", pDeck->name, pDeck->size, pDeck->num);

            struct card *pCardToPrint = pDeck->head;
            printf("Deck:%s [", pDeck->name);

            while(pCardToPrint )
            {
//                printf("\t card: %s @ %4d\n", pCardToPrint->name, pCardToPrint->pos);
                printf("%s,", pCardToPrint->name);
                pCardToPrint = pCardToPrint->next;
            }

            printf("]\n");

            // pCardToPrint = pDeck->tail;

            // while(pCardToPrint )
            // {
            //     printf("\t card: %s @ %4d\n", pCardToPrint->name, pCardToPrint->pos);
            //     pCardToPrint = pCardToPrint->previous;
            // }
        }
        else
        {
            printf("Deck: %s  Is Empty\n", pDeck->name);
        }

        //while

    }

    return ERROR;


}


