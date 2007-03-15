
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
    void setInetAddress(const InetAddress& addr);

    unsigned short getPort() const;
    void setPort(unsigned short port);

private:
    InetAddress m_address;
    unsigned short m_port;
};

std::ostream& operator<<(std::ostream& os, const SocketAddress& sa);

} // namespace Pieces

#endif // PIECES_SOCKET_ADDRESS_H
