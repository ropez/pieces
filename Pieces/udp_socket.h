
#ifndef PIECES_UDP_SOCKET_H
#define PIECES_UDP_SOCKET_H

#include "Pieces/UDPPacket"

namespace Pieces
{
class SocketAddress;
class UDPSocketPrivate;


/**
 * \class UDPSocket
 * \brief OS independant UDP network socket.
 *
 * \author Robin Pedersen, Tord Heimdal, Thomas Bakken, Joakim Simonsson, Borge Jacobsen
 */
class UDPSocket
{
public:

    /**
     * Default constructor.
     */
    UDPSocket();

    /**
     * Destructor (calls close()).
     */
    ~UDPSocket();

    /**
     * Close the socket.
     */
    void close();

    /**
     * Bind to the given address, to receive packets sent to this address.
     */
    void bind(const SocketAddress& addr);

    /**
     * Receive a packet.
     */
    UDPPacket receive(size_t maxSize);

    /**
     * Send a packet.
     */
    void send(const UDPPacket& packet);

private:
    // Disable copy operations
    UDPSocket(const UDPSocket&);
    UDPSocket& operator=(const UDPSocket&);

    UDPSocketPrivate* d;
};

} // namespace Pieces

#endif // PIECES_UDP_SOCKET_H
