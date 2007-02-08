
#include "byte_array.h"
#include "shared_data.h"

#include <algorithm>


namespace Pieces
{

class ByteArrayData : public SharedData
{
public:
    ByteArrayData()
    : SharedData()
    , size(0)
    , data(new char[size])
    {
    }

    ByteArrayData(const char* data, int size)
    : SharedData()
    , size(size)
    , data(new char[size])
    {
        std::copy(data, data + size, this->data);
    }

    ByteArrayData(const ByteArrayData& other)
    : SharedData()
    , size(other.size)
    , data(new char[size])
    {
        std::copy(other.data, other.data + size, data);
    }

    ByteArrayData& operator=(const ByteArrayData& other)
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

    ~ByteArrayData()
    {
        delete[] data;
    }

    int size;
    char* data;
};


ByteArray::ByteArray()
: d(new ByteArrayData)
{
}


ByteArray::ByteArray(const char* data, int size)
: d(new ByteArrayData(data, size))
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

} // namespace Pieces

