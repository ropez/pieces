
#ifndef STRING_H
#define STRING_H

#include <string>

class String : public std::string
{
public:
    String();
    String(const std::string& other);
    String(const char* data);
};

extern const String EMPTY_STRING;

#endif // STRING_H
