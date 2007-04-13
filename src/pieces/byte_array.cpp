
#include "Pieces/ByteArray"
#include "Pieces/IOException"

#include <cstring>
#include <sstream>
#include <iomanip>


namespace Pieces
{


ByteArray::ByteArray()
: d(new Data)
{
}


ByteArray::ByteArray(size_t size)
: d(new Data(size))
{
}


ByteArray::ByteArray(const void* data, size_t size)
: d(new Data(data, size))
{
}


size_t ByteArray::size() const
{
    return d->size;
}


size_t ByteArray::allocated() const
{
    return d->allocated;
}


bool ByteArray::isEmpty() const
{
    return d->size == 0;
}


void ByteArray::clear()
{
    d = new Data;
}


void ByteArray::resize(size_t size)
{
    // Trivial case
    if (size == this->size())
        return;

    // Check if we need to reallocate
    if (size > allocated())
    {
        // Temporary copy
        ByteArray tmp(size);
        std::memcpy(tmp.data(), constData(), std::min(tmp.size(), this->size()));

        // Let assignment operator handle the rest
        d = tmp.d;
    }
    else
    {
        // Detach and set new size
        d->size = size;
    }
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


ByteArray::byte_t& ByteArray::operator[](size_t index)
{
    return d->data[index];
}


const ByteArray::byte_t& ByteArray::operator[](size_t index) const
{
    return d->data[index];
}


ByteArray ByteArray::middle(size_t pos, size_t len) const
{
    const size_t max = size() - pos;
    const size_t s = (len > max) ? max : len;

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


ByteArray& ByteArray::append(const void* data, size_t size)
{
    if (size > 0)
    {
        size_t old_size = this->size();

        // Make room for the append
        resize(this->size() + size);

        // Copy new data
        std::memcpy(this->data() + old_size, data, size);
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


ByteArray& ByteArray::prepend(const void* data, size_t size)
{
    if (size > 0)
    {
        // Temporary
        ByteArray tmp(this->size() + size);

        // Copy contents
        std::memcpy(tmp.data(), data, size);
        std::memcpy(tmp.data() + this->size(), this->constData(), this->size());

        // Let assignment operator handle the rest
        d = tmp.d;
    }
    return *this;
}


void ByteArray::chopFront(size_t n)
{
    if (n > size())
    {
        clear();
    }
    else if (n > 0)
    {
        // Temporary
        ByteArray tmp(size() - n);
        std::memcpy(tmp.data(), constData() + n, size() - n);

        // Let assignment operator handle the rest
        d = tmp.d;
    }
}


void ByteArray::chopBack(size_t n)
{
    if (n > size())
    {
        clear();
    }
    else if (n > 0)
    {
        // Temporary
        ByteArray tmp(size() - n);
        std::memcpy(tmp.data(), constData(), size() - n);

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
, allocated(0)
, size(0)
, data(new byte_t[0])
{
}


ByteArray::Data::Data(size_t size)
: SharedData()
, allocated(0)
, size(size)
, data(0)
{
    allocate(size);
}


ByteArray::Data::Data(const void* data, size_t size)
: SharedData()
, allocated(0)
, size(size)
, data(0)
{
    allocate(size);
    std::memcpy(this->data, data, size);
}


ByteArray::Data::Data(const Data& other)
: SharedData()
, allocated(other.allocated)
, size(other.size)
, data(new byte_t[allocated])
{
    std::memcpy(this->data, other.data, other.size);
}


ByteArray::Data& ByteArray::Data::operator=(const Data& other)
{
    if (this != &other)
    {
        delete[] data;

        allocated = other.allocated;
        size = other.size;
        data = new byte_t[allocated];

        std::memcpy(this->data, other.data, other.size);
    }
    return *this;
}


ByteArray::Data::~Data()
{
    delete[] data;
}


void ByteArray::Data::allocate(size_t size)
{
    // Test for super-large size (2 GB)
    if (size & 0x80000000)
        throw IOException("ByteArray::Data::allocate", "Size too large");

    size_t wanted = 1;
    while (wanted < size)
    {
        // NOTE: This can't overflow, and it will terminate. ~RP

        // double the wanted size
        wanted <<= 1;
    }

    // Reallocate if the current allocated size is different
    if (allocated != wanted)
    {
        delete[] data;
        data = 0;
        allocated = 0;

        data = new byte_t[wanted];
        allocated = wanted;
    }
}


bool operator==(const ByteArray& op1, const ByteArray& op2)
{
    if (op1.size() != op2.size())
        return false;

    if (op1.data() == op2.data())
        return true;

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
    for (size_t i = 0; i < ba.size(); ++i)
    {
        ss << std::setw(2) << static_cast<int>(ba[i]);
    }

    return os << ss.str();
}

} // namespace Pieces
