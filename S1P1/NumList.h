#ifndef __NUMBER_LIST__
#define __NUMBER_LIST__

class NumberTally
{
public:
    NumberTally(int num)
    {
        m_number = num;
        m_count = 1;
    }

    virtual ~NumberTally()
    {
        m_count = 0;
        m_number = 0;
    }

    int getCount()
    {
        return m_count;
    }

    int getNumber()
    {
        return m_number;
    }
    NumberTally& operator++()
    {
        m_count++;
        return *this;
    }

    bool operator==(const NumberTally& b)
    {
        return (b.m_number == m_number);
    }

//private:
    int m_count;
    int m_number;
};


#include <list>
using namespace std;

class NumberList
{

public:
    NumberList()
    {
        
    }

    virtual ~NumberList();

    bool insert(int number);

    void print();

    NumberTally *findUnique(int occurance = 1);

private:


    std::list<NumberTally> m_numList;

};

#endif //__NUMBER_LIST__

