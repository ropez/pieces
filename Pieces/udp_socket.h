
#ifndef PIECES_UDP_SOCKET_H
#define PIECES_UDP_SOCKET_H

#include "Pieces/UDPPacket"

namespace Pieces
{

class UDPSocket
{
public:

    UDPSocket();
    ~UDPSocket();

    UDPPacket receive();
    void send(const UDPPacket& packet);

};

} // namespace Pieces

#endif // PIECES_UDP_SOCKET_H
