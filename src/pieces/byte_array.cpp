
#include "byte_array.h"

#include <algorithm>


namespace Pieces
{


ByteArray::ByteArray()
: d(new Data)
{
}


ByteArray::ByteArray(int size)
: d(new Data(size))
{
}


ByteArray::ByteArray(const char* data, int size)
: d(new Data(data, size))
{
}


int ByteArray::size() const
{
    return d->size;
}


bool ByteArray::isEmpty() const
{
    return d->size == 0;
}


void ByteArray::clear()
{
    d = new Data;
}


void ByteArray::resize(int size)
{
    // Using a const reference to avoid deep copy of the old data
    const ByteArray& ref = *this;

    // Trivial case
    if (size == ref.size())
        return;

    // Temporary copy
    ByteArray tmp(size);
    std::copy(ref.data(), ref.data() + std::min(tmp.size(), ref.size()), tmp.data());

    // Let assignment operator handle the rest
    d = tmp.d;
}


char* ByteArray::data()
{
    return d->data;
}


const char* ByteArray::data() const
{
    return d->data;
}


char& ByteArray::operator[](int index)
{
    return d->data[index];
}


const char& ByteArray::operator[](int index) const
{
    return d->data[index];
}


ByteArray ByteArray::middle(int pos, int len) const
{
    if (pos < 0)
    {
        pos = 0;
    }

    const int max = size() - pos;
    const int s = (len < 0 || len > max) ? max : len;

    if (s == 0)
    {
        return ByteArray();
    }

    if (s == size())
    {
        return *this;
    }

    return ByteArray(data() + pos, s);
}


ByteArray ByteArray::left(int len) const
{
    return middle(0, len);
}


ByteArray ByteArray::right(int len) const
{
    return middle(size() - len, len);
}


ByteArray& ByteArray::append(const ByteArray& other)
{
    if (isEmpty())
    {
        d = other.d;
    }
    else
    {
        append(other.data(), other.size());
    }

    return *this;
}


ByteArray& ByteArray::append(const char* data, int size)
{
    if (size > 0)
    {
        // Using a const reference to avoid deep copy of the old data
        const ByteArray& ref = *this;

        // Temporary
        ByteArray tmp(ref.size() + size);
        std::copy(ref.data(), ref.data() + ref.size(), tmp.data());
        std::copy(data, data + size, tmp.data() + ref.size());

        // Let assignment operator handle the rest
        d = tmp.d;
    }

    return *this;
}


ByteArray& ByteArray::prepend(const ByteArray& other)
{
    if (isEmpty())
    {
        d = other.d;
    }
    else
    {
        prepend(other.data(), other.size());
    }

    return *this;
}


ByteArray& ByteArray::prepend(const char* data, int size)
{
    if (size > 0)
    {
        // Using a const reference to avoid deep copy of the old data
        const ByteArray& ref = *this;

        // Temporary
        ByteArray tmp(ref.size() + size);
        std::copy(data, data + size, tmp.data());
        std::copy(ref.data(), ref.data() + ref.size(), tmp.data() + ref.size());

        // Let assignment operator handle the rest
        d = tmp.d;
    }

    return *this;
}


void ByteArray::chopFront(int n)
{
    if (n > size())
    {
        clear();
    }
    else if (n > 0)
    {
        // Using a const reference to avoid deep copy of the old data
        const ByteArray& ref = *this;

        // Temporary
        ByteArray tmp(size() - n);
        std::copy(ref.data() + n, ref.data() + ref.size(), tmp.data());

        // Let assignment operator handle the rest
        d = tmp.d;
    }
}


void ByteArray::chopBack(int n)
{
    if (n > size())
    {
        clear();
    }
    else if (n > 0)
    {
        // Using a const reference to avoid deep copy of the old data
        const ByteArray& ref = *this;

        // Temporary
        ByteArray tmp(size() - n);
        std::copy(ref.data(), ref.data() + ref.size() - n, tmp.data());

        // Let assignment operator handle the rest
        d = tmp.d;
    }
}


ByteArray& ByteArray::operator+=(const ByteArray& other)
{
    return append(other);
}


ByteArray::Data::Data()
: SharedData()
, size(0)
, data(new char[size])
{
}


ByteArray::Data::Data(int size)
: SharedData()
, size(size)
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


bool operator==(const ByteArray& op1, const ByteArray& op2)
{
    if (op1.data() == op2.data())
        return true;

    if (op1.size() != op2.size())
        return false;

    return std::equal(op1.data(), op1.data() + op1.size(), op2.data());
}


bool operator!=(const ByteArray& op1, const ByteArray& op2)
{
    return !operator==(op1, op2);
}


ByteArray operator+(const ByteArray& op1, const ByteArray& op2)
{
    // Create array to return
    ByteArray retval;

    // Copy contents
    retval.append(op1);
    retval.append(op2);

    return retval;
}

} // namespace Pieces

