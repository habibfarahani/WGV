#include "defs.h"

/******************************************************************
 * @structure implements a card object in form a doubly linked list.
 * The last item in a deck will have a "next" member pointing to NULL 
 * indicating the end of the list.
 * The first item in the list will have a "previous" member pointing 
 * to NULL indicating the first entry.
 *****************************************************************/
struct card
{
    char name[MAX_NAME_LENGTH];         //  Name of the card indicating the card type.
    int  pos;                           //  Physical position of the card within deck (1 to DeckSize)
    struct card *next;                  //  Pointer pointing to next card, last card points to NULL.
    struct card *previous;              //  Pointer pointing to previous card, first card points to NULL.

};

/******************************************************************
 * @function compareCard compares two cards by matching their type(name) 
 * and position.
 * 
 * @param pCard1: Card to be compared.
 * @param pCard2: Card to be compared.
 * 
 * @return: OK if both cards are equal, ERROR otherwise.
 * 
 *****************************************************************/
int compareCard(struct card *pCard1, struct card *pCard2);