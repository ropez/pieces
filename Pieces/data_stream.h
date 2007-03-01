
#ifndef PIECES_DATA_STREAM_H
#define PIECES_DATA_STREAM_H

#include "Pieces/ByteArray"

namespace Pieces
{

class DataStream
{
public:
    DataStream();

    explicit DataStream(const ByteArray& data);

    ByteArray data() const;

    DataStream& operator<<(bool v);
    DataStream& operator<<(char v);
    DataStream& operator<<(unsigned char v);
    DataStream& operator<<(short v);
    DataStream& operator<<(unsigned short v);
    DataStream& operator<<(int v);
    DataStream& operator<<(unsigned int v);
    DataStream& operator<<(long v);
    DataStream& operator<<(unsigned long v);
    DataStream& operator<<(float v);
    DataStream& operator<<(double v);

    DataStream& operator>>(bool& v);
    DataStream& operator>>(char& v);
    DataStream& operator>>(unsigned char& v);
    DataStream& operator>>(short& v);
    DataStream& operator>>(unsigned short& v);
    DataStream& operator>>(int& v);
    DataStream& operator>>(unsigned int& v);
    DataStream& operator>>(long& v);
    DataStream& operator>>(unsigned long& v);
    DataStream& operator>>(float& v);
    DataStream& operator>>(double& v);

    void writeBytes(const ByteArray& ba);
    ByteArray readBytes(int size);

private:

    int m_readPtr;
    ByteArray m_data;
};


DataStream& operator<<(DataStream& ds, const ByteArray& ba);
DataStream& operator>>(DataStream& ds, ByteArray& data);

void encode(ByteArray& ba, bool v);
void encode(ByteArray& ba, char v);
void encode(ByteArray& ba, unsigned char v);
void encode(ByteArray& ba, short v);
void encode(ByteArray& ba, unsigned short v);
void encode(ByteArray& ba, int v);
void encode(ByteArray& ba, unsigned int v);
void encode(ByteArray& ba, long v);
void encode(ByteArray& ba, unsigned long v);
void encode(ByteArray& ba, float v);
void encode(ByteArray& ba, double v);
void encode(ByteArray& ba, const ByteArray& v);

void decode(const ByteArray& ba, bool& v);
void decode(const ByteArray& ba, char& v);
void decode(const ByteArray& ba, unsigned char& v);
void decode(const ByteArray& ba, short& v);
void decode(const ByteArray& ba, unsigned short& v);
void decode(const ByteArray& ba, int& v);
void decode(const ByteArray& ba, unsigned int& v);
void decode(const ByteArray& ba, long& v);
void decode(const ByteArray& ba, unsigned long& v);
void decode(const ByteArray& ba, float& v);
void decode(const ByteArray& ba, double& v);
void decode(const ByteArray& ba, ByteArray& v);

} // namespace Pieces

#endif // PIECES_DATA_STREAM_H
