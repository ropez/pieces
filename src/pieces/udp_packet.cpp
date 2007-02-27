
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

UDPPacket::UDPPacket(const ByteArray& data, const InetAddress& addr, short port)
{
}

UDPPacket::~UDPPacket()
{
}


// Copy operations (this class might use implicit sharing)
UDPPacket::UDPPacket(const UDPPacket& other)
{
}

//UDPPacket& operator=(const UDPPacket& other);

short UDPPacket::getPort() const
{
}

void UDPPacket::setPort(short port)
{
}

InetAddress UDPPacket::getAddress() const
{
}

void UDPPacket::setAddress(const InetAddress& adr)
{
}


ByteArray UDPPacket::getData() const
{
}

void UDPPacket::setData(const ByteArray& data)
{
}

} // namespace Pieces
