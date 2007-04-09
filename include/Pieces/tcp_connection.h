
#ifndef PIECES_TCP_CONNECTION_H
#define PIECES_TCP_CONNECTION_H

#include "Pieces/Message"
#include <deque>


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

    void startReceiving(EventLoop* eventLoop);

    void stopReceiving();

    /**
     * Start sending messages, starting with the given messages.
     */
    void startSending(const std::deque<msgpair_t>& messages);

    /**
     * Stop sending messages, and delete all pending messages.
     */
    void stopSending();

    /**
     * Add a message to sending queue.
     *
     * If sending is not started, this function does nothing.
     */
    void sendMessage(const msgpair_t& message);

private:
    DISABLE_COPY(TCPConnection);

    TCPConnectionPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_CONNECTION_H
