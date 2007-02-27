
#ifndef PIECES_TCP_SOCKET_H
#define PIECES_TCP_SOCKET_H

#include "Pieces/ByteArray"

namespace Pieces
{

class TCPSocket
{
public:

    TCPSocket();
    ~TCPSocket();

    void close();
    bool connect(const InetAddress& addr);

    ByteArray read();
    void write(const ByteArray& data);

private:
    // Disable copy operations

};

} // namespace Pieces

#endif // PIECES_TCP_SOCKET_H
