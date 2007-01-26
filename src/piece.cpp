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



std::istream& operator>>(std::istream& is, Piece& p)
{
    // Read '('
    char c;
    is >> c;

    while (true)
    {
        // Read colon
        is >> c;

        int keyWidth = 0;
        is >> keyWidth;
        if (keyWidth == 0)
            break;

        // Read colon
        is >> c;

        // TODO: We can't keep this! It's too ugly, and not exception safe.
        char* buf = new char[keyWidth+1];
        is.read(buf, keyWidth);
        buf[keyWidth] = '\0';
        String key(buf);
        delete buf;
        buf = 0;

        // Read colon
        is >> c;

        int valueWidth = 0;
        is >> valueWidth;
        if (valueWidth == 0)
            break;

        // Read colon
        is >> c;

        buf = new char[valueWidth+1];
        is.read(buf, valueWidth);
        buf[valueWidth] = '\0';
        String value(buf);
        delete buf;
        buf = 0;

        p.setProperty(key, value);
    }

    // Read ')'
    is >> c;
    return is;
}


int main()
{
    Piece t;

    t.setProperty("Robin", "11");
    t.setProperty("angle", 2e23);
    t.setProperty("Documentation", "supercool stuff");

//     std::cout << t.getPropertyAsInt("Robin", 12) << std::endl;
    std::cout << t.getProperty("angle") << std::endl;

    std::cout << t << std::endl;
    std::stringstream ss;
    ss << t;
    Piece p;
    ss >> p;
    p.setProperty("sub-piece", t);
    std::cout << p << std::endl;
    std::cout << p.getPropertyAsPiece("sub-piece").getProperty("angle") << std::endl;
}

