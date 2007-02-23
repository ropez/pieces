#include "Pieces/ValueList"

#include <iostream>
#include <sstream>
#include <iomanip>

namespace Pieces
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
    DataStream ds;
    ds << l;
    ba = ds.data();
}


void decode(const ByteArray& ba, ValueList& l)
{
    DataStream ds(ba);
    ds >> l;
}

} // namespace Pieces
