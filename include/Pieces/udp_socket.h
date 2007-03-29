
#ifndef PIECES_UDP_SOCKET_H
#define PIECES_UDP_SOCKET_H

#include "Pieces/SocketAddress"


namespace Pieces
{
class Datagram;
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
     * Bind to the given socket address, to receive packets sent to this address.
     */
    void bind(const SocketAddress& addr);

    /**
     * Bind to the given port, to receive packets sent to this port.
     *
     * \overload
     *
     * This is the same as bind(SocketAddress(InetAddress(), port)).
     */
    void bind(port_t port);

    /**
     * Receive a packet.
     */
    Datagram receive(size_t maxSize);

    /**
     * Send a packet.
     */
    void send(const Datagram& packet);

private:
    DISABLE_COPY(UDPSocket);

    UDPSocketPrivate* d;
};

} // namespace Pieces

#endif // PIECES_UDP_SOCKET_H
