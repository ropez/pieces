
#include "Pieces/DataBuffer"
#include "Pieces/IOException"


namespace Pieces
{

DataBuffer::DataBuffer()
: m_readPtr(0)
, m_data()
{
}


DataBuffer::DataBuffer(const ByteArray& data)
: m_readPtr(0)
, m_data(data)
{
}


ByteArray DataBuffer::data() const
{
    return m_data;
}


ByteArray DataBuffer::read(size_t maxSize)
{
    // Return empty array if size is 0
    if (maxSize == 0)
    {
        return ByteArray();
    }

    // Check for empty
    if (m_readPtr >= m_data.size())
    {
        throw IOException("Read passed end of buffer");
    }

    // Find size to read
    size_t size = std::min(m_data.size() - m_readPtr, maxSize);

    // Copy data
    ByteArray ba = m_data.middle(m_readPtr, size);
    m_readPtr += size;

    return ba;
}


void DataBuffer::write(const ByteArray& data)
{
    m_data.append(data);
}


void DataBuffer::flush()
{
    // Do nothing
}

} // namespace Pieces

