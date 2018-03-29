// You are given a deck containing N cards.  While holding the deck:

// 1. Take the top card off the deck and set it on the table
// 2. Take the next card off the top and put it on the bottom of the deck
// in your hand.
// 3. Continue steps 1 and 2 until all cards are on the table.  This is a
// round.
// 4. Pick up the deck from the table and repeat steps 1-3 until the deck
// is in the original order.

// Write a program to determine how many rounds it will take to put a
// deck back into the original order.  This will involve creating a data
// structure to represent the order of the cards. Do not use an array.
// This program should be written in C only. It should take a number of
// cards in the deck as a command line argument and write the result to
// stdout.  Please ensure the program compiles and runs correctly (no
// pseudo-code).  This isn't a trick question; it should be fairly
// straightforward.


// Assumptions:
//  1. The cards on the table are stacked on top of each other.
//  2. The cards are pushed on the bottom of the stack


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "deck.h"
#include "shuffle.h"
#include "deck_utils.h"


/******************************************************************
 * @function isValidNumber checks to see if the content of string is a
 * valid number 
 * 
 * @return: OK if string is a charcter array of numbers, ERROR otherwise.
 * 
 *****************************************************************/
int isValidNumber(const char *string)
{
    if(string)
    {
       
        while(*string)
        {
            if(!isdigit(*string))
            {
                return ERROR;
            }

            string++;
        }

        return OK;
    }

    return ERROR;
}


/******************************************************************
 * @function constructSample Creates a deck of unique cards 
 * 
 * @return: none.
 * 
 *****************************************************************/
void constructSample(struct deck *pDeck, int number)
{
    int i;

    for(i=0; i<number; i++)
    {
        char name[MAX_NAME_LENGTH];
//        snprintf(name, MAX_NAME_LENGTH, "%3d", (i+1));
        snprintf(name, MAX_NAME_LENGTH, "C:%4d", (i+1));

        push(pDeck, name, (i+1));
    }

}



void usage()
{
    printf("Wrong number of arguments\n");
    printf("USAGE:  deck option(s)\n");
    printf("option(s) are:\n");
    printf("\t-n number: number of cards in the deck (greater than 1)\n");
}


int main(int argc, char *argv[])
{
    int numberOfCards = 0;
    int i = 1;
    int parsing = OK;

//  We need exactly three arguments <binary Name> <option:-n> <number: of cards ina  deck>
    if(argc != 3)
    {
        usage();
        exit(-1);
    }

//  Parse the parameter
    while((i < argc) && (OK == parsing))
    {
        if(!strncmp("-n", argv[i], 2))
        {
            i++;
            if(OK == isValidNumber(argv[i]))
            {
                numberOfCards = atol(argv[i]);
            }
            else
            {
                parsing = ERROR;
            }
        }
        else
        {
            parsing = ERROR;
        }
        i++;

    }

//  If parsing succeeded then 
    if(OK == parsing)
    {
        if(numberOfCards > 1)
        {
            // Create an original deck
            struct deck *pOriginalDeck = createDeck("Original Deck", numberOfCards);

            // Construct a sample set
            constructSample(pOriginalDeck, numberOfCards);

            // Call shuffle to shufflethe deck based on rules above and print number of iterations
            printf("Number of Iterations = %d\n", shuffle(pOriginalDeck));

            // Delete the deck and leave.
            deleteDeck(pOriginalDeck);
        }
        else
        {
            printf("ERROR: Number of cards [%d] should be greater than 1\n", numberOfCards);

        }

    }
    else
    {
        usage();
    }
    

    return 0;
}