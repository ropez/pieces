
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

    DataStream& operator<<(bool i);
    DataStream& operator<<(char i);
    DataStream& operator<<(unsigned char i);
    DataStream& operator<<(short i);
    DataStream& operator<<(unsigned short i);
    DataStream& operator<<(int i);
    DataStream& operator<<(unsigned int i);
    DataStream& operator<<(long i);
    DataStream& operator<<(unsigned long i);
    DataStream& operator<<(float f);
    DataStream& operator<<(double f);

    DataStream& operator>>(bool& i);
    DataStream& operator>>(char& i);
    DataStream& operator>>(unsigned char& i);
    DataStream& operator>>(short& i);
    DataStream& operator>>(unsigned short& i);
    DataStream& operator>>(int& i);
    DataStream& operator>>(unsigned int& i);
    DataStream& operator>>(long& i);
    DataStream& operator>>(unsigned long& i);
    DataStream& operator>>(float& f);
    DataStream& operator>>(double& f);

private:

    void write(const char* data, int size);
    void read(char* data, int size);

    ByteArray m_data;
};

} // namespace Pieces

#endif // PIECES_DATA_STREAM_H
