#include <stdio.h>
#include "NumList.h"
#include <iostream>
#include <iterator>
#include <algorithm>



NumberList::~NumberList()
{


}

bool NumberList::insert(int number)
{
    NumberTally *pFoundNum = NULL;
    NumberTally num(number);
    std::list<NumberTally>::iterator it = std::find(m_numList.begin(), m_numList.end(), num);


    if(it != m_numList.end())
    {
        pFoundNum = &(*it);
        ++*pFoundNum;
    }
    else
    {
        pFoundNum = new NumberTally(number);
        if(!pFoundNum)
        {
            return false;
        }
        m_numList.push_back(*pFoundNum);
    }

}

NumberTally *NumberList::findUnique(int occurance)
{
    int count = 1;
    NumberTally *pFoundNum = NULL;
    
    std::list<NumberTally>::iterator it = std::find_if(m_numList.begin(), m_numList.end(), [](NumberTally &obj) {
                                                                                                    return obj.getCount() == 1;});

     if(it != m_numList.end())
     {
         pFoundNum = &(*it);
     }

    return pFoundNum;
}


void NumberList::print()
{
    std::list<NumberTally>::iterator it = m_numList.begin();
    while(it != m_numList.end())
    {
        NumberTally *pFoundNum = &(*it);
        
        printf("Num: %4d Count:%4d\n", pFoundNum->getNumber(), pFoundNum->getCount());
        
        it++;
    }
}
