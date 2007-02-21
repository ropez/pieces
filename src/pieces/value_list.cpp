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


ValueList& ValueList::addValue(const PString& value)
{
    d->values.push_back(value);
    return *this;
}


PString ValueList::getValue(int index) const
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
        const PString& value = *it;

        os << ':' << value.size() << ':' << value;
    }

    os << "]";
    return os;
}


std::istream& operator>>(std::istream& is, ValueList& l)
{
    // Make sure we read whitespace
    is >> std::noskipws;

    // Read '['
    char c;
    is >> c;

    while (true)
    {
        // Read colon, or closing bracket
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

        l.addValue(value);
    }
    return is;
}

} // namespace Pieces
