#ifndef _DECK_UTILS_
#define _DECK_UTILS_

/******************************************************************
 * @function createDeck Creates an empty deck with a name and size.
 * 
 * @param deckName: Name of the deck.
 * @param maxSize: expected max size of the deck
 * 
 * @return: pointer to the created deck.
 * 
 *****************************************************************/
struct deck * createDeck(char *deckName, int maxSize);

/******************************************************************
 * @function initDeck initializes a given deck be removing all its cards
 * but maintining the name and maxsize.
 * 
 * @param pDeck: Deck to be initialized.
 * 
 * @return: OK if initialization is successful.
 * 
 *****************************************************************/
int initDeck(struct deck *pDeck);

/******************************************************************
 * @function deleteDeck deletes (frees) a given deck object.
 * 
 * @param pDeck: Deck to be freed.
 * 
 * @return: OK if successful. ERROR otherwise.
 * 
 *****************************************************************/
int deleteDeck(struct deck *pDeck);

/******************************************************************
 * @function assignDeck copies a source deck into a destination deck (assignment)
 * 
 * @param pSrcDeck: Deck to be copied from.
 * @param pDstDeck: Deck to be copied to.
 * 
 * @return: OK if successful. ERROR otherwise.
 * 
 *****************************************************************/
int assignDeck(struct deck *pSrcDeck, struct deck *pDstDeck);

/******************************************************************
 * @function moveDeck moves a source deck into a destination deck (assignment)
 * freeing the source deck.
 * 
 * @param pSrcDeck: Deck providing cards to be moved.
 * @param pDstDeck: Deck receiving moved cards.
 * 
 * @return: OK if successful. ERROR otherwise.
 * 
 *****************************************************************/
int moveDeck(struct deck *pSrcDeck, struct deck *pDstDeck);

/******************************************************************
 * @function compareDeck comapres every single card in source deck
 * and destination deck
 * 
 * @param pSrcDeck: deck to be compared aganist the second deck.
 * @param pDstDeck: deck to be compared aganist the first deck.
 * 
 * @return: OK if successful. ERROR otherwise.
 * 
 *****************************************************************/
int compareDeck(struct deck *pSrcDeck, struct deck *pDstDeck);

/******************************************************************
 * @function deckSize returns the max size that is assigned to a deck.
 * 
 * @param pDeck: deck reporting its max size.
 * 
 * @return: max size of the deck.
 * 
 *****************************************************************/
int deckSize(struct deck *pDeck);

/******************************************************************
 * @function deckNum returns the number of cards contained within the 
 * specified deck.
 * 
 * @param pDeck: deck reporting its number of cards.
 * 
 * @return: max size of the deck.
 * 
 *****************************************************************/
int deckNum(struct deck *pDeck);

/******************************************************************
 * @function empty determines whether a specified deck is empty or not
 * 
 * @param pDeck: deck to check.
 * 
 * @return: OK if the deck is empty, ERROR otherwise..
 * 
 *****************************************************************/
int empty(struct deck *pDeck);

#endif  //_DECK_UTILS_