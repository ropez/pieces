
#ifndef PIECES_UDP_SOCKET_H
#define PIECES_UDP_SOCKET_H

#include "Pieces/UDPPacket"

namespace Pieces
{
class SocketAddress;
class UDPSocketPrivate;


class UDPSocket
{
public:

    UDPSocket();
    ~UDPSocket();

    void close();
    void bind(const SocketAddress& addr);

    UDPPacket receive();
    void send(const UDPPacket& packet);

private:
    // Disable copy operations
    UDPSocket(const UDPSocket&);
    UDPSocket& operator=(const UDPSocket&);

    UDPSocketPrivate* d;
};

} // namespace Pieces

#endif // PIECES_UDP_SOCKET_H
