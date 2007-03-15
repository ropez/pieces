
#include "Pieces/UDPSocket"


namespace Pieces
{

UDPSocket::UDPSocket()
{
}

UDPSocket::~UDPSocket()
{
}

UDPPacket UDPSocket::receive()
{
    return UDPPacket();
}

void UDPSocket::send(const UDPPacket& packet)
{
}


} // namespace Pieces
