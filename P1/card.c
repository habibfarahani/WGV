
#include <string.h>

#include "card.h"

/******************************************************************
 * function to compare 2 cards and return OK if both cards are equal (same name and position)
 *****************************************************************/
int compareCard(struct card *pCard1, struct card *pCard2)
{
    if((pCard1->pos != pCard2->pos) ||
        strncmp(pCard1->name, pCard2->name, MAX_NAME_LENGTH))
    {
//        printf("[%s][%s]{%4d}{%4d}\n", pCard1->name, pCard2->name, pCard1->pos, pCard2->pos);
        return ERROR;
    }

    return OK;
}
