#include "piece.h"

#include <iostream>
#include <sstream>


Piece::Piece()
: m_properties()
{
    std::cout << "Constructing a piece." << std::endl;
}


Piece::~Piece()
{
    std::cout << "Destructing a piece." << std::endl;
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


int main()
{
    Piece t;

    t.setProperty("Robin", "11");
    t.setProperty("angle", 2e23);

//     std::cout << t.getPropertyAsInt("Robin", 12) << std::endl;
    std::cout << t.getProperty("angle") << std::endl;
}

