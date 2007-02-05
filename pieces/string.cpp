

#include "string.h"

#include <iostream>
#include <iomanip>


String::String()
: std::string()
{
}


String::String(const std::string& other)
: std::string(other)
{
}


String::String(const char* data)
: std::string(data)
{
}


String::String(const char* data, unsigned int length)
: std::string(data, length)
{
}


const String EMPTY_STRING = "";


std::istream& operator>>(std::istream& is, String& s)
{
    s.resize(is.width());

    for (String::iterator it = s.begin(); it != s.end(); ++it)
    {
        is >> *it;
    }

    return is;
}
