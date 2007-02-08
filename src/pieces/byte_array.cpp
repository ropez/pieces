
#include "byte_array.h"

#include <algorithm>


namespace Pieces
{


ByteArray::ByteArray()
: d(new Data)
{
}


ByteArray::ByteArray(const char* data, int size)
: d(new Data(data, size))
{
}


ByteArray::ByteArray(const ByteArray& other)
: d(other.d)
{
}


ByteArray& ByteArray::operator=(const ByteArray& other)
{
    d = other.d;
    return *this;
}


ByteArray::~ByteArray()
{
}


int ByteArray::size() const
{
    return d->size;
}


char* ByteArray::data()
{
    return d->data;
}


const char* ByteArray::data() const
{
    return d->data;
}


ByteArray::Data::Data()
: SharedData()
, size(0)
, data(new char[size])
{
}


ByteArray::Data::Data(const char* data, int size)
: SharedData()
, size(size)
, data(new char[size])
{
    std::copy(data, data + size, this->data);
}


ByteArray::Data::Data(const Data& other)
: SharedData()
, size(other.size)
, data(new char[size])
{
    std::copy(other.data, other.data + size, data);
}


ByteArray::Data& ByteArray::Data::operator=(const Data& other)
{
    if (this != &other)
    {
        delete[] data;

        size = other.size;
        data = new char[size];
        std::copy(other.data, other.data + size, data);
    }
    return *this;
}


ByteArray::Data::~Data()
{
    delete[] data;
}

} // namespace Pieces

