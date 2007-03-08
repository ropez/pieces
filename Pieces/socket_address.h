
#ifndef PIECES_SOCKET_ADDRESS_H
#define PIECES_SOCKET_ADDRESS_H

#include "Pieces/InetAddress"


namespace Pieces
{

class SocketAddress
{
public:

    SocketAddress();
    ~SocketAddress();

    SocketAddress(const InetAddress& addr, unsigned short port);

    SocketAddress(const SocketAddress& other);
    SocketAddress& operator=(const SocketAddress& other);

    InetAddress getInetAddress() const;
    unsigned short getPort() const;

private:
    InetAddress m_address;
    unsigned short m_port;
};

} // namespace Pieces

#endif // PIECES_SOCKET_ADDRESS_H
