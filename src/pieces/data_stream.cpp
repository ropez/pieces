
#include "data_stream.h"

#include <algorithm>


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


DataStream& DataStream::operator<<(bool i)
{
    write(reinterpret_cast<char*>(&i), sizeof(bool));

    return *this;
}


DataStream& DataStream::operator<<(char i)
{
    write(reinterpret_cast<char*>(&i), sizeof(char));

    return *this;
}


DataStream& DataStream::operator<<(unsigned char i)
{
    write(reinterpret_cast<char*>(&i), sizeof(unsigned int));

    return *this;
}


DataStream& DataStream::operator<<(short i)
{
    write(reinterpret_cast<char*>(&i), sizeof(short));

    return *this;
}


DataStream& DataStream::operator<<(unsigned short i)
{
    write(reinterpret_cast<char*>(&i), sizeof(unsigned short));

    return *this;
}


DataStream& DataStream::operator<<(int i)
{
    write(reinterpret_cast<char*>(&i), sizeof(int));

    return *this;
}


DataStream& DataStream::operator<<(unsigned int i)
{
    write(reinterpret_cast<char*>(&i), sizeof(unsigned int));

    return *this;
}


DataStream& DataStream::operator<<(long i)
{
    write(reinterpret_cast<char*>(&i), sizeof(long));

    return *this;
}


DataStream& DataStream::operator<<(unsigned long i)
{
    write(reinterpret_cast<char*>(&i), sizeof(unsigned long));

    return *this;
}


DataStream& DataStream::operator<<(float f)
{
    write(reinterpret_cast<char*>(&f), sizeof(float));

    return *this;
}


DataStream& DataStream::operator<<(double f)
{
    write(reinterpret_cast<char*>(&f), sizeof(double));

    return *this;
}


DataStream& DataStream::operator>>(bool& i)
{
    read(reinterpret_cast<char*>(&i), sizeof(bool));

    return *this;
}


DataStream& DataStream::operator>>(char& i)
{
    read(reinterpret_cast<char*>(&i), sizeof(char));

    return *this;
}


DataStream& DataStream::operator>>(unsigned char& i)
{
    read(reinterpret_cast<char*>(&i), sizeof(unsigned char));

    return *this;
}


DataStream& DataStream::operator>>(short& i)
{
    read(reinterpret_cast<char*>(&i), sizeof(short));

    return *this;
}


DataStream& DataStream::operator>>(unsigned short& i)
{
    read(reinterpret_cast<char*>(&i), sizeof(unsigned short));

    return *this;
}


DataStream& DataStream::operator>>(int& i)
{
    read(reinterpret_cast<char*>(&i), sizeof(int));

    return *this;
}


DataStream& DataStream::operator>>(unsigned int& i)
{
    read(reinterpret_cast<char*>(&i), sizeof(unsigned int));

    return *this;
}


DataStream& DataStream::operator>>(long& i)
{
    read(reinterpret_cast<char*>(&i), sizeof(long));

    return *this;
}


DataStream& DataStream::operator>>(unsigned long& i)
{
    read(reinterpret_cast<char*>(&i), sizeof(unsigned long));

    return *this;
}


DataStream& DataStream::operator>>(float& f)
{
    read(reinterpret_cast<char*>(&f), sizeof(float));

    return *this;
}


DataStream& DataStream::operator>>(double& f)
{
    read(reinterpret_cast<char*>(&f), sizeof(double));

    return *this;
}


void DataStream::write(const char* data, int size)
{
    m_data.append(data, size);
}


void DataStream::read(char* data, int size)
{
    // Reference to avoid deep copy
    const ByteArray& ref = m_data;

    // Read data
    const char* dataPtr = ref.data();
    std::copy(dataPtr, dataPtr + size, data);

    m_data.chopFront(size);
}

} // namespace Pieces
