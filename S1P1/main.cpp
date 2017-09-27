
#include <stdio.h>

#include "NumList.h"

int numbers[] = {72, 89,2,81,78, 89,289, 5, 17, 289, 89, 71, 89, 2, 81};


int main(char *argv[], int argc)
{
    NumberList myList;

    for(int i=0; i< (sizeof(numbers) / sizeof(int)); i++)
    {
        myList.insert(numbers[i]);
    }

    myList.print();

    NumberTally *pFirstUnique = myList.findUnique();

    if(pFirstUnique)
    {
        printf("First unique number is :%4d with count:%4d\n", pFirstUnique->getNumber(), pFirstUnique->getCount());
    }

    return 0;
}