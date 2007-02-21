#include "PropertyList"

#include <iostream>
#include <sstream>
#include <iomanip>


namespace Pieces
{

PropertyList::Data::Data()
{
}


PropertyList::Data::Data(const Data& other)
: SharedData()
, properties(other.properties)
{
}


PropertyList::PropertyList()
: d(new Data)
{
}


PropertyList::~PropertyList()
{
}


PropertyList& PropertyList::setProperty(int property, const ByteArray& value)
{
    d->properties[property] = value;
    return *this;
}


ByteArray PropertyList::getProperty(int property, const ByteArray& defval) const
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


PropertyList::PropertyTable::const_iterator PropertyList::begin() const
{
    return d->properties.begin();
}


PropertyList::PropertyTable::const_iterator PropertyList::end() const
{
    return d->properties.end();
}


std::ostream& operator<<(std::ostream& os, const PropertyList& p)
{
    os << "(";

    for (PropertyList::PropertyTable::const_iterator it = p.begin();
         it != p.end(); ++it)
    {
        if (it != p.begin())
            os << ' ';

        int key = it->first;
        const ByteArray& value = it->second;

        os << key << ':' << value;
    }

    os << ")";
    return os;
}

} // namespace Pieces
