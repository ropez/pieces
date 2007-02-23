#include "Pieces/PropertyList"

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


void PropertyList::clear()
{
    if (!isEmpty())
    {
        d = new Data;
    }
}


int PropertyList::size() const
{
    return static_cast<int>(d->properties.size());
}


bool PropertyList::isEmpty() const
{
    return d->properties.empty();
}


PropertyList& PropertyList::setProperty(int property, const ByteArray& value)
{
    d->properties[property] = value;
    return *this;
}


ByteArray PropertyList::getProperty(int property, const ByteArray& defval) const
{
    // Lookup the value in the map.
    map_t::const_iterator it = d->properties.find(property);

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


PropertyList::map_t::const_iterator PropertyList::begin() const
{
    return d->properties.begin();
}


PropertyList::map_t::const_iterator PropertyList::end() const
{
    return d->properties.end();
}


std::ostream& operator<<(std::ostream& os, const PropertyList& p)
{
    os << "(";

    for (PropertyList::map_t::const_iterator it = p.begin();
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


DataStream& operator<<(DataStream& ds, const PropertyList& p)
{
    ds << p.size();
    for (PropertyList::map_t::const_iterator it = p.begin(); it != p.end(); ++it)
    {
        int key = it->first;
        const ByteArray& value = it->second;
        ds << key << value;
    }
    return ds;
}


DataStream& operator>>(DataStream& ds, PropertyList& p)
{
    p.clear();

    int size = 0;
    ds >> size;
    while (size--)
    {
        int key = 0;
        ByteArray value;
        ds >> key >> value;
        p.setProperty(key, value);
    }
    return ds;
}


void encode(ByteArray& ba, const PropertyList& v)
{
    ba.clear();
    DataStream ds;
    ds << v;
    ba = ds.data();
}


void decode(const ByteArray& ba, PropertyList& v)
{
    DataStream ds(ba);
    ds >> v;
}

} // namespace Pieces
