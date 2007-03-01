
#include "Pieces/DataStream"

#include <cstring>


namespace Pieces
{

DataStream::DataStream()
: m_readPtr(0)
, m_data()
{
}


DataStream::DataStream(const ByteArray& data)
: m_readPtr(0)
, m_data(data)
{
}


ByteArray DataStream::data() const
{
    return m_data;
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
    m_data.append(ba);
}


ByteArray DataStream::readBytes(int size)
{
    if (size > m_data.size() - m_readPtr)
        throw "error";

    ByteArray ba = m_data.middle(m_readPtr, size);
    m_readPtr += size;

    return ba;
}


DataStream& operator<<(DataStream& ds, const ByteArray& ba)
{
    ds << ba.size();
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
    ds << str.size();
    ds.writeBytes(ByteArray(str.data(), str.size()));

    return ds;
}


DataStream& operator<<(DataStream& ds, const char* str)
{
    int size = strlen(str);
    ds << size;
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

    int size = strlen(str);
    ba.append(str, size);
}


void decode(const ByteArray& ba, bool& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, char& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned char& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, short& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned short& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, int& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned int& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, long& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned long& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, float& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, double& v)
{
    if (ba.size() != sizeof(v))
        throw "error";

    memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, ByteArray& v)
{
    v = ba;
}


void decode(const ByteArray& ba, std::string& v)
{
    v.resize(ba.size());

    for (int i = 0; i < ba.size(); ++i)
    {
        v[i] = ba[i];
    }
}

} // namespace Pieces
