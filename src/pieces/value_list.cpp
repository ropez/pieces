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
#include "Pieces/ValueList"
#include "Pieces/DataStream"
#include "Pieces/BufferStream"
#include "Pieces/InvalidKeyException"

#include <iostream>
#include <sstream>
#include <iomanip>

namespace pcs
{

ValueList::Data::Data()
{
}


ValueList::Data::Data(const Data& other)
: SharedData()
, values(other.values)
{
}


ValueList::ValueList()
: d(new Data)
{
}


ValueList::~ValueList()
{
}


void ValueList::clear()
{
    if (!isEmpty())
    {
        d = new Data;
    }
}


bool ValueList::isEmpty() const
{
    return d->values.empty();
}


int ValueList::size() const
{
    return static_cast<int>(d->values.size());
}


ValueList& ValueList::addValue(const ByteArray& value)
{
    d->values.push_back(value);
    return *this;
}


ByteArray ValueList::getValue(int index) const
{
    if (index < 0 || index >= size())
        throw InvalidKeyException("ValueList::getValue", "Invalid index");

    return d->values[index];
}


ValueList::list_t::const_iterator ValueList::begin() const
{
    return d->values.begin();
}


ValueList::list_t::const_iterator ValueList::end() const
{
    return d->values.end();
}


std::ostream& operator<<(std::ostream& os, const ValueList& l)
{
    os << "[";

    for (ValueList::list_t::const_iterator it = l.begin(); it != l.end(); ++it)
    {
        if (it != l.begin())
            os << ' ';

        const ByteArray& value = *it;
        os << value;
    }

    os << "]";
    return os;
}


DataStream& operator<<(DataStream& ds, const ValueList& l)
{
    ds << l.size();
    for (ValueList::list_t::const_iterator it = l.begin(); it != l.end(); ++it)
    {
        const ByteArray& value = *it;
        ds << value;
    }
    return ds;
}


DataStream& operator>>(DataStream& ds, ValueList& l)
{
    l.clear();

    int size = 0;
    ds >> size;
    while (size--)
    {
        ByteArray value;
        ds >> value;
        l.addValue(value);
    }
    return ds;
}


void encode(ByteArray& ba, const ValueList& l)
{
    ba.clear();
    BufferStream ds;
    ds << l;
    ba = ds.data();
}


void decode(const ByteArray& ba, ValueList& l)
{
    BufferStream ds(ba);
    ds >> l;
}

} // namespace pcs
