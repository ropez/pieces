
#ifndef PIECES_TCP_SOCKET_H
#define PIECES_TCP_SOCKET_H

#include "Pieces/ByteArray"
#include "Pieces/InetAddress"

namespace Pieces
{

class TCPSocket
{
public:

    TCPSocket();
    ~TCPSocket();

    // close file descriptor
    void close();
    
    // connect to address
    bool connect(const InetAddress& addr);

    // read from socket
    ByteArray read();
    
    // write to socket
    void write(const ByteArray& data);

private:
    int m_sockFd;

};

} // namespace Pieces

#endif // PIECES_TCP_SOCKET_H
