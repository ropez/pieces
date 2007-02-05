#include "piece.h"

#include <iostream>
#include <sstream>
#include <iomanip>


Piece::Piece()
: m_properties()
{
}


Piece::~Piece()
{
}


Piece& Piece::setProperty(const String& property, const String& value)
{
    m_properties[property] = value;
    return *this;
}


String Piece::getProperty(const String& property, const String& defval) const
{
    // Lookup the value in the map.
    PropertyTable::const_iterator it = m_properties.find(property);

    // See if it was found.
    if (it != m_properties.end())
    {
        return it->second;
    }
    else
    {
        return defval;
    }
}


PropertyTable::const_iterator Piece::begin() const
{
    return m_properties.begin();
}


PropertyTable::const_iterator Piece::end() const
{
    return m_properties.end();
}


std::ostream& operator<<(std::ostream& os, const Piece& p)
{
    os << "(";

    for (PropertyTable::const_iterator it = p.begin();
         it != p.end(); ++it)
    {
        const String& key = it->first;
        const String& value = it->second;

        os << ':' << key.size() << ':' << key;
        os << ':' << value.size() << ':' << value;
    }

    os << ")";
    return os;
}


std::istream& operator>>(std::istream& is, Piece& p)
{
    // Make sure we read whitespace
    is >> std::noskipws;

    // Read '('
    char c;
    is >> c;

    while (true)
    {
        // Read colon, or closing parenthesis
        is >> c;
        if (c != ':')
            break;

        int keyWidth = 0;
        is >> keyWidth;

        // Read colon
        is >> c;
        if (c != ':')
            break;

        String key;
        is >> std::setw(keyWidth) >> key;

        // Read colon
        is >> c;
        if (c != ':')
            break;

        int valueWidth = 0;
        is >> valueWidth;

        // Read colon
        is >> c;
        if (c != ':')
            break;

        String value;
        is >> std::setw(valueWidth) >> value;

        p.setProperty(key, value);
    }
    return is;
}

