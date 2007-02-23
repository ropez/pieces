
#ifndef PIECES_PROPERTY_LIST_H
#define PIECES_PROPERTY_LIST_H

#include "ByteArray"
#include "DataStream"
#include "SharedData"
#include "SharedDataPointer"

#include <map>


namespace Pieces
{

class PropertyList
{
public:
    typedef std::map<int, ByteArray> map_t;

    PropertyList();
    ~PropertyList();

    void clear();
    int size() const;

    bool isEmpty() const;

    PropertyList& setProperty(int property, const ByteArray& value);
    ByteArray getProperty(int property, const ByteArray& defval = ByteArray()) const;

    template<typename T>
    PropertyList& set(int property, const T& value);

    template<typename T>
    T get(int property, const T& defval = T()) const;

    map_t::const_iterator begin() const;
    map_t::const_iterator end() const;

private:
    class Data : public SharedData
    {
    public:
        Data();
        Data(const Data& other);

        map_t properties;
    };

    SharedDataPointer<Data> d;
};


std::ostream& operator<<(std::ostream& os, const PropertyList& p);

DataStream& operator<<(DataStream& ds, const PropertyList& p);
DataStream& operator>>(DataStream& ds, PropertyList& p);


template<typename T>
PropertyList& PropertyList::set(int property, const T& value)
{
    ByteArray ba;
    encode(ba, value);
    return setProperty(property, ba);
}


template<typename T>
T PropertyList::get(int property, const T& defval) const
{
    // Lookup the value in the map.
    map_t::const_iterator it = d->properties.find(property);

    // See if it was found.
    if (it != d->properties.end())
    {
        T result;
        decode(it->second, result);
        return result;
    }
    else
    {
        return defval;
    }
}

void encode(ByteArray& ba, const PropertyList& v);
void decode(const ByteArray& ba, PropertyList& v);

} // namespace Pieces

#endif // PIECES_PROPERTY_LIST_H
