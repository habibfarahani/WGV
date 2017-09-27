
#include <stdio.h>


#include "BinSearch.h"



thisArray sortedArray = {1,  3,  4,  5,  7,  9,  10,  15,  17,  27,  39,
                                   40, 43, 48, 52, 59, 60, 61,  68,  70,  89, 101,
                                   117, 128, 135, 138, 143, 149, 160, 176, 278, 467 };

int main(char *argv[], int argc)
{

    search(sortedArray, 160);
    search(sortedArray, 60);
    search(sortedArray, 1);
    search(sortedArray, 467);
    search(sortedArray, 61);
    search(sortedArray, 59);
    search(sortedArray, 959);
    return 0;
}