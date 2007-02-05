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


String List::at(int pos) const
{
    return m_data[pos];
}


List& List::append(const String& value)
{
    m_data.push_back(value);
    return *this;
}


PropertyList::const_iterator List::begin() const
{
    return m_data.begin();
}


PropertyList::const_iterator List::end() const
{
    return m_data.end();
}


std::ostream& operator<<(std::ostream& os, const List& l)
{
    os << "[";

    for (PropertyList::const_iterator it = l.begin();
         it != l.end(); ++it)
    {
        const String& value = *it;

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

        String value;
        is >> std::setw(valueWidth) >> value;

        l.append(value);
    }
    return is;
}

