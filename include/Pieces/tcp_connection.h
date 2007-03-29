
#ifndef PIECES_TCP_CONNECTION_H
#define PIECES_TCP_CONNECTION_H

#include "Pieces/global"


namespace Pieces
{
class TCPSocket;
class SocketAddress;
class EventLoop;
class ByteArray;
class TCPConnectionPrivate;


/**
 * \class TCPConnection
 * \brief A TCP connection.
 *
 * \author Robin Pedersen
 */
class TCPConnection
{
public:

    /**
     * This class takes ownership of the socket.
     */
    TCPConnection(TCPSocket* socket);

    /**
     * Disconnects and deletes the socket.
     */
    ~TCPConnection();

    /**
     * Calls getPeerAddress() on the socket.
     */
    SocketAddress getPeerAddress() const;

    void startReceiver(EventLoop* eventLoop);

    void sendMessage(int messageType, const ByteArray& data);

private:
    DISABLE_COPY(TCPConnection);

    TCPConnectionPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_CONNECTION_H
