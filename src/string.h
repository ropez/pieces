
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

#endif // STRING_H
