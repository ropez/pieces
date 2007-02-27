
#ifndef PIECES_TCP_SERVER_H
#define PIECES_TCP_SERVER_H

#include "Pieces/TCPSocket"


namespace Pieces
{

class TCPServer
{
public:
    TCPServer();
    ~TCPServer();

    void bind(const InetAddress& addr);
    void listen();
    // or maybe just listen(addr) ????

    int getQueueSize() const;
    void setQueueSize(int size);

    // Caller must delete this (maybe use auto_ptr?)
    TCPSocket* accept();

private:
    // Disable copy operations

};

} // namespace Pieces

#endif // PIECES_TCP_SERVER_H
