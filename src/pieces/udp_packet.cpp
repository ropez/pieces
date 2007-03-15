
#include "Pieces/UDPPacket"
#include "Pieces/ByteArray"
#include "Pieces/InetAddress"


namespace Pieces
{

UDPPacket::UDPPacket()
: d(new Data)
{
}


UDPPacket::UDPPacket(const ByteArray& data, const SocketAddress& addr)
: d(new Data(data, addr))
{
}


UDPPacket::UDPPacket(const ByteArray& data, const InetAddress& addr, port_t port)
: d(new Data(data, SocketAddress(addr, port)))
{
}


UDPPacket::~UDPPacket()
{
}


UDPPacket::UDPPacket(const UDPPacket& other)
{
    d = other.d;
}


UDPPacket& UDPPacket::operator=(const UDPPacket& other)
{
    d = other.d;

    return *this;
}


SocketAddress UDPPacket::getAddress() const
{
    return d->address;
}


void UDPPacket::setAddress(const SocketAddress& addr)
{
    d->address = addr;
}


ByteArray UDPPacket::getData() const
{
    return d->data;
}


void UDPPacket::setData(const ByteArray& data)
{
    d->data = data;
}


UDPPacket::Data::Data()
: SharedData()
, data()
, address()
{
}


UDPPacket::Data::Data(const ByteArray& data, const SocketAddress& addr)
: SharedData()
, data(data)
, address(addr)
{
}


UDPPacket::Data::Data(const Data& other)
: SharedData()
, data(other.data)
, address(other.address)
{
}


UDPPacket::Data& UDPPacket::Data::operator=(const Data& other)
{
    data = other.data;
    address = other.address;

    return *this;
}

} // namespace Pieces
