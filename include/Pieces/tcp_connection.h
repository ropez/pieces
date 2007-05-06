
#ifndef PIECES_TCP_CONNECTION_H
#define PIECES_TCP_CONNECTION_H

#include "Pieces/Message"
#include <deque>


namespace pcs
{
class TCPSocket;
class SocketAddress;
class EventLoop;
class ByteArray;
class TCPConnectionPrivate;


/**
 * \class TCPConnection tcp_connection.h <Pieces/TCPConnection>
 * \brief A TCP connection.
 *
 * \internal
 * It is unlikely that users of Pieces will have to use this class directly.
 *
 * This class is used internally by the TCPConnectionManager to represent a
 * connection. It maintains background threads for both sending and receiving
 * messages.
 *
 * Once the sender thread has been started, messages can be sent with sendMessage().
 * Also, once the receiver thread has been started, When receiving messages, a MessageReceivedEvent is posted to the
 * given event loop.
 *
 * The class is designed to close connections and stop background threads
 * gracefully, by simply deleting the class instance.
 *
 * \see ConnectionManager, TCPConnectionManager
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

    /**
     * Start receiver thread.
     */
    void startReceiving(EventLoop* eventLoop);

    /**
     * Stop receiver thread.
     */
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

} // namespace pcs

#endif // PIECES_TCP_CONNECTION_H
