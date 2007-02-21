#include "ValueList"

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


ValueList::PropertyList::const_iterator ValueList::begin() const
{
    return d->values.begin();
}


ValueList::PropertyList::const_iterator ValueList::end() const
{
    return d->values.end();
}


std::ostream& operator<<(std::ostream& os, const ValueList& l)
{
    os << "[";

    for (ValueList::PropertyList::const_iterator it = l.begin();
         it != l.end(); ++it)
    {
        if (it != l.begin())
            os << ' ';

        const ByteArray& value = *it;
        os << value;
    }

    os << "]";
    return os;
}

} // namespace Pieces
