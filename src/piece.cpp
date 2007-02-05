#include "piece.h"

#include <iostream>
#include <sstream>
#include <iomanip>


Piece::Piece()
: m_properties()
{
}


Piece::~Piece()
{
}


void Piece::setProperty(const String& property, const String& value)
{
    m_properties[property] = value;
}


void Piece::setProperty(const String& property, int value)
{
    std::stringstream ss;
    ss << value;

    setProperty(property, ss.str());
}


void Piece::setProperty(const String& property, double value)
{
    std::stringstream ss;
    ss << value;

    setProperty(property, ss.str());
}


void Piece::setProperty(const String& property, const Piece& value)
{
    std::stringstream ss;
    ss << value;

    setProperty(property, ss.str());
}


String Piece::getProperty(const String& property, const String& defval) const
{
    // Lookup the value in the map.
    PropertyTable::const_iterator it = m_properties.find(property);

    // See if it was found.
    if (it != m_properties.end())
    {
        return it->second;
    }
    else
    {
        return defval;
    }
}


int Piece::getPropertyAsInt(const String& property, int defval) const
{
    // Lookup the value in the map.
    PropertyTable::const_iterator it = m_properties.find(property);

    // See if it was found.
    if (it != m_properties.end())
    {
        std::stringstream ss(it->second);

        int result = defval;
        ss >> result;
        return result;
    }
    else
    {
        return defval;
    }
}


double Piece::getPropertyAsDouble(const String& property, double defval) const
{
    // Lookup the value in the map.
    PropertyTable::const_iterator it = m_properties.find(property);

    // See if it was found.
    if (it != m_properties.end())
    {
        std::stringstream ss(it->second);

        double result = defval;
        ss >> result;
        return result;
    }
    else
    {
        return defval;
    }
}


Piece Piece::getPropertyAsPiece(const String& property, const Piece& defval) const
{
    // Lookup the value in the map.
    PropertyTable::const_iterator it = m_properties.find(property);

    // See if it was found.
    if (it != m_properties.end())
    {
        std::stringstream ss(it->second);

        Piece result = defval;
        ss >> result;
        return result;
    }
    else
    {
        return defval;
    }
}


PropertyTable::const_iterator Piece::begin() const
{
    return m_properties.begin();
}


PropertyTable::const_iterator Piece::end() const
{
    return m_properties.end();
}


std::ostream& operator<<(std::ostream& os, const Piece& p)
{
    os << "(";

    for (PropertyTable::const_iterator it = p.begin();
         it != p.end(); ++it)
    {
        const String& key = it->first;
        const String& value = it->second;

        os << ':' << key.size() << ':' << key;
        os << ':' << value.size() << ':' << value;
    }

    os << ")";
    return os;
}


std::istream& operator>>(std::istream& is, String& s)
{
    s.resize(is.width());

    for (String::iterator it = s.begin(); it != s.end(); ++it)
    {
        is >> *it;
    }

    return is;
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

        String key;
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

        String value;
        is >> std::setw(valueWidth) >> value;

        p.setProperty(key, value);
    }
    return is;
}


int main()
{
    Piece t;

    t.setProperty("robin", "");
    t.setProperty("angle", 2e23);
    t.setProperty("documentation", "supercool stuff");

//     std::cout << t.getPropertyAsInt("Robin", 12) << std::endl;
    std::cout << t.getProperty("angle") << std::endl;

    std::cout << t << std::endl;
    std::stringstream ss;
    ss << t;
    Piece p;
    ss >> p;
    p.setProperty("a-sub-piece", t);
    std::cout << p << std::endl;
    std::cout << p.getPropertyAsPiece("sub-piece").getProperty("angle") << std::endl;
}

