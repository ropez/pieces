
#include "Pieces/ByteArray"

#include <cstring>
#include <sstream>
#include <iomanip>


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


ByteArray::ByteArray(const void* data, int size)
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
    // Trivial case
    if (size == this->size())
        return;

    // Temporary copy
    ByteArray tmp(size);
    memcpy(tmp.data(), constData(), std::min(tmp.size(), this->size()));

    // Let assignment operator handle the rest
    d = tmp.d;
}


ByteArray::byte_t* ByteArray::data()
{
    return d->data;
}


const ByteArray::byte_t* ByteArray::data() const
{
    return d->data;
}


const ByteArray::byte_t* ByteArray::constData() const
{
    return d->data;
}


ByteArray::byte_t& ByteArray::operator[](int index)
{
    return d->data[index];
}


const ByteArray::byte_t& ByteArray::operator[](int index) const
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


ByteArray& ByteArray::append(byte_t byte)
{
    return append(&byte, 1);
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


ByteArray& ByteArray::append(const void* data, int size)
{
    if (size > 0)
    {
        // Temporary
        ByteArray tmp(this->size() + size);
        memcpy(tmp.data(), constData(), this->size());
        memcpy(tmp.data() + this->size(), data, size);

        // Let assignment operator handle the rest
        d = tmp.d;
    }
    return *this;
}


ByteArray& ByteArray::prepend(byte_t byte)
{
    return prepend(&byte, 1);
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


ByteArray& ByteArray::prepend(const void* data, int size)
{
    if (size > 0)
    {
        // Temporary
        ByteArray tmp(this->size() + size);

        // Copy contents
        memcpy(tmp.data(), data, size);
        memcpy(tmp.data() + this->size(), this->constData(), this->size());

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
        // Temporary
        ByteArray tmp(size() - n);
        memcpy(tmp.data(), constData() + n, size() - n);

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
        // Temporary
        ByteArray tmp(size() - n);
        memcpy(tmp.data(), constData(), size() - n);

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
, data(new byte_t[size])
{
}


ByteArray::Data::Data(int size)
: SharedData()
, size(size)
, data(new byte_t[size])
{
}


ByteArray::Data::Data(const void* data, int size)
: SharedData()
, size(size)
, data(new byte_t[size])
{
    memcpy(this->data, data, size);
}


ByteArray::Data::Data(const Data& other)
: SharedData()
, size(other.size)
, data(new byte_t[size])
{
    memcpy(this->data, other.data, other.size);
}


ByteArray::Data& ByteArray::Data::operator=(const Data& other)
{
    if (this != &other)
    {
        delete[] data;

        size = other.size;
        data = new byte_t[other.size];
        memcpy(this->data, other.data, other.size);
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

    return (memcmp(op1.data(), op2.data(), op1.size()) == 0);
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


std::ostream& operator<<(std::ostream& os, const ByteArray& ba)
{
    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for (int i = 0; i < ba.size(); ++i)
    {
        ss << std::setw(2) << static_cast<int>(ba[i]);
    }

    return os << ss.str();
}

} // namespace Pieces

