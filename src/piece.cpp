#include "piece.h"

#include <iostream>
#include <sstream>
#include <iomanip>


Piece::Piece()
: m_properties()
{
}


Piece::Piece(const String& str)
: m_properties()
{
    *this = fromString(str);
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


String Piece::toString() const
{
    std::stringstream ss;

    ss << "(";

    for (PropertyTable::const_iterator it = m_properties.begin();
         it != m_properties.end(); ++it)
    {
        const String& key = it->first;
        const String& value = it->second;

        ss << key.size() << ':' << key;
        ss << value.size() << ':' << value;
    }

    ss << ")";
    return ss.str();
}

Piece Piece::fromString(const String& str)
{
    std::stringstream ss(str);

    // Read '('
    char c;
    ss >> c;

    Piece p;
    while (true)
    {
        int keyWidth = 0;
        ss >> keyWidth;
        if (keyWidth == 0)
            break;

        // TODO: Skip whitespace doesn't work!
        String key;
        ss >> c >> std::setw(keyWidth) >> std::skipws >> key;

        int valueWidth = 0;
        ss >> valueWidth;
        if (valueWidth == 0)
            break;

        String value;
        ss >> c >> std::setw(valueWidth) >> std::skipws >> value;

        p.setProperty(key, value);
    }

    // Read ')'
    ss >> c;

    return p;
}


int main()
{
    Piece t;

    t.setProperty("Robin", "11");
    t.setProperty("angle", 2e23);
    t.setProperty("Documentation", "supercool:");

//     std::cout << t.getPropertyAsInt("Robin", 12) << std::endl;
    std::cout << t.getProperty("angle") << std::endl;

    std::cout << t.toString() << std::endl;
    std::cout << Piece::fromString(t.toString()).toString() << std::endl;
}

