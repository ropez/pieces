
#ifndef PIECES_PROPERTY_LIST_H
#define PIECES_PROPERTY_LIST_H

#include "PString"
#include "SharedData"
#include "SharedDataPointer"

#include <sstream>
#include <iomanip>
#include <map>


namespace Pieces
{

class PropertyList
{
public:
    typedef std::map<PString, PString> PropertyTable;

    PropertyList();
    ~PropertyList();

    PropertyList& setProperty(const PString& property, const PString& value);
    PString getProperty(const PString& property, const PString& defval = EMPTY_STRING) const;

    template<typename T>
    PropertyList& set(const PString& property, const T& value);

    template<typename T>
    T get(const PString& property, const T& defval = T()) const;

    PropertyTable::const_iterator begin() const;
    PropertyTable::const_iterator end() const;

private:
    class Data : public SharedData
    {
    public:
        Data();
        Data(const Data& other);

        PropertyTable properties;
    };

    SharedDataPointer<Data> d;
};

std::ostream& operator<<(std::ostream& os, const PropertyList& p);
std::istream& operator>>(std::istream& is, PropertyList& p);


template<typename T>
PropertyList& PropertyList::set(const PString& property, const T& value)
{
    std::stringstream ss;
    ss << value;

    return setProperty(property, ss.str());
}


template<typename T>
T PropertyList::get(const PString& property, const T& defval) const
{
    // Lookup the value in the map.
    PropertyTable::const_iterator it = d->properties.find(property);

    // See if it was found.
    if (it != d->properties.end())
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

} // namespace Pieces

#endif // PIECES_PROPERTY_LIST_H
