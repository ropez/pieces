#ifndef PIECES_VALUE_LIST_H
#define PIECES_VALUE_LIST_H

#include "Pieces/ByteArray"
#include "Pieces/DataStream"
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"

#include <vector>


namespace Pieces
{

class ValueList
{
public:
    typedef std::vector<ByteArray> list_t;

    ValueList();
    ~ValueList();

    void clear();
    int size() const;

    bool isEmpty() const;

    ValueList& addValue(const ByteArray& value);
    ByteArray getValue(int index) const;

    template<typename T>
    ValueList& add(const T& value);

    template<typename T>
    T get(int index) const;

    list_t::const_iterator begin() const;
    list_t::const_iterator end() const;

private:
    class Data : public SharedData
    {
    public:
        Data();
        Data(const Data& other);

        list_t values;
    };

    SharedDataPointer<Data> d;
};

std::ostream& operator<<(std::ostream& os, const ValueList& l);

DataStream& operator<<(DataStream& ds, const ValueList& l);
DataStream& operator>>(DataStream& ds, ValueList& l);


template<typename T>
ValueList& ValueList::add(const T& value)
{
    ByteArray ba;
    encode(ba, value);
    return addValue(ba);
}

template<typename T>
T ValueList::get(int index) const
{
    ByteArray ba = getValue(index);
    T result;
    decode(ba, result);
    return result;
}

void encode(ByteArray& ba, const ValueList& l);
void decode(const ByteArray& ba, ValueList& l);

} // namespace Pieces

#endif // PIECES_VALUE_LIST_H
