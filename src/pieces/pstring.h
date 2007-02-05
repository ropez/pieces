
#ifndef PSTRING_H
#define PSTRING_H

#include <string>
#include <iostream>

class PString : public std::string
{
public:
    PString();
    PString(const std::string& other);
    PString(const char* data);
    PString(const char* data, unsigned int length);
};

extern const PString EMPTY_STRING;

std::istream& operator>>(std::istream& is, PString& s);

#endif // STRING_H
