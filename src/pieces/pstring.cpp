

#include "pstring.h"

#include <iostream>
#include <iomanip>


PString::PString()
: std::string()
{
}


PString::PString(const std::string& other)
: std::string(other)
{
}


PString::PString(const char* data)
: std::string(data)
{
}


PString::PString(const char* data, unsigned int length)
: std::string(data, length)
{
}


const PString EMPTY_STRING = "";


std::istream& operator>>(std::istream& is, PString& s)
{
    s.resize(is.width());

    for (PString::iterator it = s.begin(); it != s.end(); ++it)
    {
        is >> *it;
    }

    return is;
}
