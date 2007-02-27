
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
    ByteArray baDummy;
    UDPPacket dummy(baDummy);
    return dummy;
}

void UDPSocket::send(const UDPPacket& packet)
{
}


} // namespace Pieces
