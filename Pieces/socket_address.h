
#ifndef PIECES_SOCKET_ADDRESS_H
#define PIECES_SOCKET_ADDRESS_H

#include "Pieces/InetAddress"

// TODO: Move this
typedef unsigned short port_t;

namespace Pieces
{

class SocketAddress
{
public:

    SocketAddress();
    ~SocketAddress();

    SocketAddress(const InetAddress& addr, port_t port);

    SocketAddress(const SocketAddress& other);
    SocketAddress& operator=(const SocketAddress& other);

    InetAddress getInetAddress() const;
    void setInetAddress(const InetAddress& addr);

    port_t getPort() const;
    void setPort(port_t port);

private:
    InetAddress m_address;
    port_t m_port;
};

std::ostream& operator<<(std::ostream& os, const SocketAddress& sa);

} // namespace Pieces

#endif // PIECES_SOCKET_ADDRESS_H
