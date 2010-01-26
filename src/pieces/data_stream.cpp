/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Pieces/DataStream"
#include "Pieces/StreamTarget"
#include "Pieces/DataBuffer"
#include "Pieces/IOException"
#include "Pieces/Debug"

#include <cstring>


namespace pcs
{

DataStream::DataStream()
: m_target(0)
{
}


DataStream::DataStream(StreamTarget* target)
: m_target(target)
{
}


DataStream::~DataStream()
{
}


StreamTarget* DataStream::target() const
{
    return m_target;
}


void DataStream::setTarget(StreamTarget* t)
{
    m_target = t;
}


DataStream& DataStream::operator<<(DataStream& (*foo)(DataStream&))
{
    foo(*this);
    return *this;
}


DataStream& DataStream::operator>>(DataStream& (*foo)(DataStream&))
{
    foo(*this);
    return *this;
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
    if (!target())
        throw IOException("DataStream::writeBytes", "Null target");

    target()->write(ba);
}


ByteArray DataStream::readBytes(size_t size)
{
    if (!target())
        throw IOException("DataStream::readBytes", "Null target");

    ByteArray data;

    // Read until there is enough data, or exception
    while (data.size() < size)
    {
        data += target()->read(size - data.size());
    }

    return data;
}


void DataStream::flush()
{
    if (!target())
        throw IOException("DataStream::flush", "Null target");

    target()->flush();
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

    std::memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, char& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    std::memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned char& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    std::memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, short& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    std::memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned short& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    std::memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, int& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    std::memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned int& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    std::memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, long& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    std::memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, unsigned long& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    std::memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, float& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    std::memcpy(&v, ba.data(), sizeof(v));
}


void decode(const ByteArray& ba, double& v)
{
    if (ba.size() != sizeof(v))
        throw IOException("Invalid input");

    std::memcpy(&v, ba.data(), sizeof(v));
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


DataStream& flush(DataStream& ds)
{
    ds.flush();
    return ds;
}

} // namespace pcs
