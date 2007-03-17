
#ifndef PIECES_TCP_SOCKET_H
#define PIECES_TCP_SOCKET_H

#include "Pieces/ByteArray"
#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"

namespace Pieces
{
class TCPSocketPrivate;


/**
 * \class TCPSocket
 * \brief OS independant TCP network socket.
 *
 * \author Robin Pedersen, Tord Heimdal, Thomas Bakken, Joakim Simonsson, Borge Jacobsen
 */
class TCPSocket
{
    friend class TCPServer;

public:

    /**
     * Default contructor
     */
    TCPSocket();

    /**
     * Destructor (calls close()).
     */
    ~TCPSocket();

    /**
     * Close the socket.
     */
    void close();

    /**
     * Connect to the given address.
     */
    bool connect(const SocketAddress& addr);

    /**
     * Connect to the given address.
     */
    bool connect(const InetAddress& addr, port_t port);

    /**
     * Get the address to the peer connected to the socket.
     */
    SocketAddress getPeerAddress() const;

    /**
     * Read from socket.
     */
    ByteArray read(size_t maxSize);

    /**
     * Write to socket.
     */
    void write(const ByteArray& data);

    unsigned long getReadTimeout() const;
    void setReadTimeout(unsigned long msec);


    unsigned long getWriteTimeout() const;
    void setWriteTimeout(unsigned long msec);


private:
    // Disable copy operations
    TCPSocket(const TCPSocket&);
    TCPSocket& operator=(const TCPSocket&);

    // Constructor used by TCPServer::accept()
    TCPSocket(TCPSocketPrivate* data);

    TCPSocketPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_SOCKET_H
