#ifndef _DECK_
#define _DECK_


#include "defs.h"
#include "card.h"


/******************************************************************
 * @structure implements a stack of cards object with a given name.
 * The head member always points to the item on top of the stack.
 * The tail member always points to the item in the bottom of the stack.
 *****************************************************************/
struct deck
{

    int num;                        //  Current number of cards in the stack
    int size;                       //  Maximum size that the deck can grow
    char name[MAX_NAME_LENGTH];     //  Name assigned to this deck, such as Hand or Table, etc
    struct card *head;              //  Element pointing to the top card.
    struct card *tail;              //  Element pointing to the bottom card
};

/******************************************************************
 * @function push creates a card with a given name and position and 
 * pushes it on a specified deck.
 * 
 * @param pDeck: Deck where the new card is going to be inserted
 * @param name:  name assigned to the card which specifies its type.
 * @param pos:   position in which this card is inserted in. 
 * 
 * @return: OK if string is a charcter array of numbers, ERROR otherwise.
 * 
 *****************************************************************/
int push(struct deck *pDeck, char *name, int pos);


/******************************************************************
 * @function pop removes a card from top of the deck stack and retruns it 
 * in a preallocated card and frees the origianl card.
 * 
 * @param pDeck: Deck where the card is going to be removed from.
 * @param pCard:  a preallocated (dynamically or statically) card.
 * 
 * @return: OK if string is a charcter array of numbers, ERROR otherwise.
 * 
 *****************************************************************/
int pop(struct deck *pDeck, struct card *pCard);


/******************************************************************
 * @function pushBottom creates a card with a given name and position and 
 * pushes in the bottom of a specified deck.
 * 
 * @param pDeck: Deck where the new card is going to be inserted
 * @param name:  name assigned to the card which specifies its type.
 * @param pos:   position in which this card is inserted in. 
 * 
 * @return: OK if string is a charcter array of numbers, ERROR otherwise.
 * 
 *****************************************************************/
int pushBottom(struct deck *pDeck, char *name, int pos);


/******************************************************************
 * @function print prints the components of a deck.
 * 
 * @return: OK if string is a charcter array of numbers, ERROR otherwise.
 * 
 *****************************************************************/
int print(struct deck *pDeck);



#endif  //  _DECK_
