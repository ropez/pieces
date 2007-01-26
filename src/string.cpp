

#include "string.h"


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
