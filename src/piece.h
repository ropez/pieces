
#ifndef PIECE_H
#define PIECE_H

#include "String"
#include "PropertyTable"

#include <sstream>
#include <iomanip>

class Piece
{
public:

    Piece();
    virtual ~Piece();

    void setProperty(const String& property, const String& value);
    String getProperty(const String& property, const String& defval = EMPTY_STRING) const;

    template<typename T>
    void set(const String& property, const T& value);

    template<typename T>
    T get(const String& property, const T& defval = T()) const;

    PropertyTable::const_iterator begin() const;
    PropertyTable::const_iterator end() const;

private:
    PropertyTable m_properties;
};

std::ostream& operator<<(std::ostream& os, const Piece& p);
std::istream& operator>>(std::istream& is, Piece& p);


template<typename T>
void Piece::set(const String& property, const T& value)
{
    std::stringstream ss;
    ss << value;

    setProperty(property, ss.str());
}


template<typename T>
T Piece::get(const String& property, const T& defval) const
{
    // Lookup the value in the map.
    PropertyTable::const_iterator it = m_properties.find(property);

    // See if it was found.
    if (it != m_properties.end())
    {
        std::stringstream ss(it->second);

        T result = defval;
        ss >> std::noskipws >> std::setw(it->second.length()) >> result;
        return result;
    }
    else
    {
        return defval;
    }
}

#endif // PIECE_H
