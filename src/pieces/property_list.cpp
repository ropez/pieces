/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Pieces/PropertyList"
#include "Pieces/DataStream"
#include "Pieces/BufferStream"

#include <iostream>
#include <sstream>
#include <iomanip>


namespace pcs
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


void encode(ByteArray& ba, const PropertyList& p)
{
    ba.clear();
    BufferStream ds;
    ds << p;
    ba = ds.data();
}


void decode(const ByteArray& ba, PropertyList& p)
{
    BufferStream ds(ba);
    ds >> p;
}

} // namespace pcs
