
#include "Pieces/UDPPacket"
#include "Pieces/ByteArray"
#include "Pieces/InetAddress"


namespace Pieces
{

UDPPacket::UDPPacket()
{
}


UDPPacket::UDPPacket(const ByteArray& data)
{
}


UDPPacket::UDPPacket(const ByteArray& data, const InetAddress& addr, port_t port)
{
}


UDPPacket::~UDPPacket()
{
}


UDPPacket::UDPPacket(const UDPPacket& other)
{
}


UDPPacket& UDPPacket::operator=(const UDPPacket& other)
{
}


port_t UDPPacket::getPort() const
{
    return 0;
}


void UDPPacket::setPort(port_t port)
{
}


InetAddress UDPPacket::getAddress() const
{
    return InetAddress();
}


void UDPPacket::setAddress(const InetAddress& adr)
{
}


ByteArray UDPPacket::getData() const
{
    return ByteArray();
}


void UDPPacket::setData(const ByteArray& data)
{
}

} // namespace Pieces
