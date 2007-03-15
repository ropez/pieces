
#ifndef PIECES_TCP_SOCKET_H
#define PIECES_TCP_SOCKET_H

#include "Pieces/ByteArray"
#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"

namespace Pieces
{

class TCPSocketPrivate;

class TCPSocket
{
    friend class TCPServer;

public:

    // Default contructor
    TCPSocket();

    // Destructor
    ~TCPSocket();

    // close file descriptor
    void close();

    // connect to address
    bool connect(const SocketAddress& addr);
    bool connect(const InetAddress& addr, port_t port);

    SocketAddress getPeerAddress() const;

    // read from socket
    ByteArray read();

    // write to socket
    void write(const ByteArray& data);

private:

    TCPSocket(TCPSocketPrivate* data);
    TCPSocketPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_SOCKET_H
