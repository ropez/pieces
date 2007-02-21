#include "list.h"

#include <iostream>
#include <sstream>
#include <iomanip>


List::List()
: m_data()
{
}


List::~List()
{
}


int List::size() const
{
    return static_cast<int>(m_data.size());
}


List& List::addValue(const PString& value)
{
    m_data.push_back(value);
    return *this;
}


PString List::getValue(int index) const
{
    return m_data[index];
}


List::PropertyList::const_iterator List::begin() const
{
    return m_data.begin();
}


List::PropertyList::const_iterator List::end() const
{
    return m_data.end();
}


std::ostream& operator<<(std::ostream& os, const List& l)
{
    os << "[";

    for (List::PropertyList::const_iterator it = l.begin();
         it != l.end(); ++it)
    {
        const PString& value = *it;

        os << ':' << value.size() << ':' << value;
    }

    os << "]";
    return os;
}


std::istream& operator>>(std::istream& is, List& l)
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

