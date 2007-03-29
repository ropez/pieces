
#ifndef PIECES_TCP_SERVER_H
#define PIECES_TCP_SERVER_H

#include "Pieces/SocketAddress"
#include "Pieces/AutoPointer"


namespace Pieces
{
class TCPSocket;
class TCPServerPrivate;

class TCPServer
{
public:
    TCPServer();
    ~TCPServer();

    void listen(const SocketAddress& addr);

    /**
     * Listen to the given port, to receive connections to this port.
     *
     * \overload
     *
     * This is the same as listen(SocketAddress(InetAddress(), port)).
     */
    void listen(port_t port);

    int getQueueSize() const;
    void setQueueSize(int size);

    /**
     * Accept a connection.
     */
    AutoPointer<TCPSocket> accept();

private:
    DISABLE_COPY(TCPServer);

    TCPServerPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_SERVER_H
