#include "piece.h"

#include <iostream>
#include <sstream>
#include <iomanip>


namespace Pieces
{


Piece::Data::Data()
{
}


Piece::Data::Data(const Data& other)
: SharedData()
, properties(other.properties)
{
}



Piece::Piece()
: d(new Data)
{
}


Piece::~Piece()
{
}


Piece& Piece::setProperty(const PString& property, const PString& value)
{
    d->properties[property] = value;
    return *this;
}


PString Piece::getProperty(const PString& property, const PString& defval) const
{
    // Lookup the value in the map.
    PropertyTable::const_iterator it = d->properties.find(property);

    // See if it was found.
    if (it != d->properties.end())
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
    return d->properties.begin();
}


PropertyTable::const_iterator Piece::end() const
{
    return d->properties.end();
}


std::ostream& operator<<(std::ostream& os, const Piece& p)
{
    os << "(";

    for (PropertyTable::const_iterator it = p.begin();
         it != p.end(); ++it)
    {
        const PString& key = it->first;
        const PString& value = it->second;

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

        PString key;
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

        PString value;
        is >> std::setw(valueWidth) >> value;

        p.setProperty(key, value);
    }
    return is;
}

} // namespace Pieces
