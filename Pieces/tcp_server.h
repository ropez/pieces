
#ifndef PIECES_TCP_SERVER_H
#define PIECES_TCP_SERVER_H

#include "Pieces/TCPSocket"


namespace Pieces
{
class TCPServerPrivate;

class TCPServer
{
public:
    TCPServer();
    ~TCPServer();

    void listen(const SocketAddress& addr);
    // or maybe just listen(addr) ????

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
