
#include "byte_array.h"

#include <algorithm>

namespace Pieces
{

ByteArray::ByteArray()
: m_size(0)
, m_data(new char[0])
{
}

ByteArray::ByteArray(const char* data, int size)
: m_size(size)
, m_data(new char[size])
{
    std::copy(data, data + size, m_data);
}

int ByteArray::size() const
{
    return m_size;
}

char* ByteArray::data()
{
    return m_data;
}

const char* ByteArray::data() const
{
    return m_data;
}

} // namespace Pieces

