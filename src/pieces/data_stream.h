
#ifndef PIECES_DATA_STREAM_H
#define PIECES_DATA_STREAM_H

#include "ByteArray"

namespace Pieces
{

class DataStream
{
public:
    DataStream();

    explicit DataStream(const ByteArray& data);

    ByteArray data() const;

    DataStream& operator<<(int i);

    DataStream& operator>>(int& i);

private:
    ByteArray m_data;
};

} // namespace Pieces

#endif // PIECES_DATA_STREAM_H
