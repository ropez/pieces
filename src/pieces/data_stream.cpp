
#include "Pieces/DataStream"
#include "Pieces/TCPSocket"
#include "Pieces/IOException"
#include "Pieces/Debug"

#include <cstring>


namespace Pieces
{

DataStream::DataStream()
: m_readPtr(0)
, m_data()
, m_socket(0)
{
}


DataStream::DataStream(const ByteArray& data)
: m_readPtr(0)
, m_data(data)
, m_socket(0)
{
}


DataStream::DataStream(TCPSocket* socket)
: m_readPtr(0)
, m_data()
, m_socket(socket)
{
}


ByteArray DataStream::data() const
{
    return m_data;
}


TCPSocket* DataStream::socket() const
{
    return m_socket;
}


DataStream& DataStream::operator<<(bool v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator<<(char v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator<<(unsigned char v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator<<(short v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator<<(unsigned short v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator<<(int v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator<<(unsigned int v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator<<(long v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator<<(unsigned long v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator<<(float v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator<<(double v)
{
    ByteArray ba;
    encode(ba, v);
    writeBytes(ba);
    return *this;
}


DataStream& DataStream::operator>>(bool& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


DataStream& DataStream::operator>>(char& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


DataStream& DataStream::operator>>(unsigned char& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


DataStream& DataStream::operator>>(short& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


DataStream& DataStream::operator>>(unsigned short& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


DataStream& DataStream::operator>>(int& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


DataStream& DataStream::operator>>(unsigned int& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


DataStream& DataStream::operator>>(long& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


DataStream& DataStream::operator>>(unsigned long& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


DataStream& DataStream::operator>>(float& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


DataStream& DataStream::operator>>(double& v)
{
    ByteArray ba = readBytes(sizeof(v));
    decode(ba, v);
    return *this;
}


void DataStream::writeBytes(const ByteArray& ba)
{
    if (socket() != 0)
    {
        socket()->write(ba);
    }
    else
    {
        m_data.append(ba);
    }
}


ByteArray DataStream::readBytes(size_t size)
{
    while (m_readPtr + size > m_data.size())
    {
        if (socket() != 0)
        {
            ByteArray ba = socket()->read();

            if (ba.isEmpty())
            {
                throw IOException("Disconnected");
            }

            m_data.append(ba);
        }
        else
        {
            throw IOException("Read passed end of stream");
        }
    }

    ByteArray ba = m_data.middle(m_readPtr, size);
    m_readPtr += size;

    return ba;
}


DataStream& operator<<(DataStream& ds, const ByteArray& ba)
{
    ds << static_cast<unsigned int>(ba.size());
    ds.writeBytes(ba);

    return ds;
}


DataStream& operator>>(DataStream& ds, ByteArray& ba)
{
    int size;
    ds >> size;
    ba = ds.readBytes(size);

    return ds;
}


DataStream& operator<<(DataStream& ds, const std::string& str)
{
    ds << static_cast<unsigned int>(str.size());
    ds.writeBytes(ByteArray(str.data(), str.size()));

    return ds;
}


DataStream& operator<<(DataStream& ds, const char* str)
{
    size_t size = strlen(str);
    ds << static_cast<unsigned int>(size);
    ds.writeBytes(ByteArray(str, size));

    return ds;
}


DataStream& operator>>(DataStream& ds, std::string& str)
{
    str.clear();

    int size;
    ds >> size;
    const ByteArray ba = ds.readBytes(size);

    decode(ba, str);

    return ds;
}


void encode(ByteArray& ba, bool v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, char v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, unsigned char v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, short v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, unsigned short v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, int v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, unsigned int v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, long v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, unsigned long v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, float v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, double v)
{
    ba = ByteArray(&v, sizeof(v));
}


void encode(ByteArray& ba, const ByteArray& v)
{
    ba = v;
}


void encode(ByteArray& ba, const std::string& v)
{
    ba.clear();

    ba.append(v.data(), v.size());
}


void encode(ByteArray& ba, const char* str)
{
    ba.clear();

    size_t size = strlen(str);
    ba.append(str, size);
}


void decode(const ByteArray& ba, bool& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, char& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned char& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, short& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned short& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, int& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned int& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, long& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned long& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, float& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, double& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, ByteArray& v)
{
    v = ba;
}


void decode(const ByteArray& ba, std::string& v)
{
    v.resize(ba.size());

    for (size_t i = 0; i < ba.size(); ++i)
    {
        v[i] = ba[i];
    }
}

} // namespace Pieces
