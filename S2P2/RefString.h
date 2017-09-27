#ifndef __REF_STRING__
#define __REF_STRING__

#include <string>

class RefString : public std::string
{
public:
    // Creation methods using overloaded constructors
    RefString() : std::string()
    {
        m_ref = 1;
    }

    RefString(const char *pText)  : std::string(pText)
    {
        m_ref = 1;
    }

    RefString(const std::string &newString)  : std::string(newString)
    {
        m_ref = 1;
    }

    // Copy constructor
    RefString(const RefString &newString)
    {
        m_ref = newString.m_ref;
        assign(newString.c_str());
    }

    // MOVE constructor
    RefString(RefString &&newString)
    {
        m_ref = newString.m_ref;
        assign(std::move(newString));
    }


    //
    virtual ~RefString()
    {
        if(--m_ref <= 0)
        {
            clear();
        }
    }

    // Assignment operator
    RefString & operator = (const RefString &rhs)
    {
        // If not being assigned to itself
        if(this != &rhs)
        {
            m_ref = rhs.m_ref + 1;
            assign(rhs.c_str());
        }

        return *this;
    }

    RefString & operator = (const char *pText)
    {
        // If not being assigned to itself
        m_ref++;
        assign(pText);

        return *this;
    }

    RefString & operator = (const char c)
    {
        // If not being assigned to itself
        ++m_ref;
        assign(1, c);

        return *this;
    }

    RefString operator += (const RefString &str)
    {

        append(str.c_str());
        
        return *this;

    }


    void print()
    {
        printf("[%3d] String: %s\n", m_ref, std::string::c_str());
    }

    int m_ref;

};


#endif //__REF_STRING__

