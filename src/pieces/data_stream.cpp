
#include "data_stream.h"

namespace Pieces
{

DataStream::DataStream()
: m_data()
{
}


DataStream::DataStream(const ByteArray& data)
: m_data(data)
{
}


ByteArray DataStream::data() const
{
    return m_data;
}


DataStream& DataStream::operator<<(int i)
{
    ByteArray ba(sizeof(int));
    int* p = reinterpret_cast<int*>(ba.data());
    *p = i;

    m_data += ba;

    return *this;
}


DataStream& DataStream::operator>>(int& i)
{
    // Reference to avoid deep copy
    const ByteArray& ref = m_data;

    const int* p = reinterpret_cast<const int*>(ref.data());
    i = *p;

    m_data = m_data.middle(sizeof(int));

    return *this;
}

} // namespace Pieces
