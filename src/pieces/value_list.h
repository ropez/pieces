#ifndef PIECES_VALUE_LIST_H
#define PIECES_VALUE_LIST_H

#include "PString"
#include "SharedData"
#include "SharedDataPointer"

#include <sstream>
#include <iomanip>
#include <vector>

namespace Pieces
{

class ValueList
{
public:
    typedef std::vector<PString> PropertyList;

    ValueList();
    ~ValueList();

    int size() const;

    ValueList& addValue(const PString& value);
    PString getValue(int index) const;

    template<typename T>
    ValueList& add(const T& value);

    template<typename T>
    T get(int index) const;

    PropertyList::const_iterator begin() const;
    PropertyList::const_iterator end() const;

private:
    class Data : public SharedData
    {
    public:
        Data();
        Data(const Data& other);

        PropertyList values;
    };

    SharedDataPointer<Data> d;
};

std::ostream& operator<<(std::ostream& os, const ValueList& l);
std::istream& operator>>(std::istream& is, ValueList& l);


template<typename T>
ValueList& ValueList::add(const T& value)
{
    std::stringstream ss;
    ss << value;

    return addValue(ss.str());
}

template<typename T>
T ValueList::get(int index) const
{
    PString value = getValue(index);
    std::stringstream ss(value);

    T result;
    ss >> std::noskipws >> std::setw(value.length()) >> result;
    return result;
}

} // namespace Pieces

#endif // PIECES_VALUE_LIST_H
