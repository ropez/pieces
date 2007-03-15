
#ifndef PIECES_TCP_SOCKET_H
#define PIECES_TCP_SOCKET_H

#include "Pieces/ByteArray"
#include "Pieces/InetAddress"

namespace Pieces
{

class TCPSocket
{
public:

    // Default contructor
    TCPSocket();
    
    // Destructor
    ~TCPSocket();

    // close file descriptor
    void close();
    
    // connect to address
    bool connect(const SocketAddress& addr);
    bool connect(const InetAddress& addr, int port);

    // read from socket
    ByteArray read();
    
    // write to socket
    void write(const ByteArray& data);

private:
    TCPSocketPrivate* d;
    
};

} // namespace Pieces

#endif // PIECES_TCP_SOCKET_H
