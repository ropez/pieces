
#include "Pieces/BufferStream"
#include "Pieces/DataBuffer"


namespace Pieces
{

BufferStream::BufferStream()
: DataStream()
, m_buf(new DataBuffer())
{
    setTarget(m_buf);
}



BufferStream::BufferStream(const ByteArray& data)
: DataStream(new DataBuffer(data))
, m_buf(new DataBuffer(data))
{
    setTarget(m_buf);
}


BufferStream::~BufferStream()
{
    setTarget(0);
    delete m_buf;
}


ByteArray BufferStream::data() const
{
    return m_buf->data();
}

} // namespace Pieces
