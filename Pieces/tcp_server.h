
#ifndef PIECES_TCP_SERVER_H
#define PIECES_TCP_SERVER_H

#include "Pieces/SocketAddress"


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

    // Caller must delete this (maybe use auto_ptr?)
    std::auto_ptr<TCPSocket> accept();

private:
    // Disable copy operations
    TCPServer(const TCPServer&);
    TCPServer& operator=(const TCPServer&);

    TCPServerPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_SERVER_H
