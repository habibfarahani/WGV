#include "BinSearch.h"

#define GET_INDEX(x) (x-1)


bool search(thisArray &array, int key)
{
    int start = 0;
    int current = 0;
    int end = array.size();

    if(end)
    {
        current = (start + end) >> 1;

        while((array[current] != key) && (start <= GET_INDEX(end)))
        {
            if(array[current] > key)
            {
                end = current-1;
            }
            else
            {
                start = current + 1;
            }

            current = (start + end) >> 1;
        }

        if((start <= end) && (start < array.size()))
        {
            printf("FOUND %4d at location: %4d\n", key, current);
            return true;
        }
        else
        {
            printf("Did not find the number [%4d]\n", key);
        }

    }

    return false;


}