
#ifndef PIECES_CONNECTION_MANAGER_H
#define PIECES_CONNECTION_MANAGER_H

#include "Pieces/Message"


namespace pcs
{
class TCPConnection;
class SocketAddress;
class EventLoop;
class ByteArray;


/**
 * \class ConnectionManager connection_manager.h <Pieces/ConnectionManager>
 * \brief Interface for connection manager.
 *
 * Both a Host and a Peer have a connection manager.
 *
 * This interface provides functionality for setting up Pieces connections.
 * The listen() function is used by hosts to accept incoming connections,
 * and the connectTo() function is used by peers to connect to a given host
 * address.
 *
 * When connected, this interface provides functions to send and receive
 * pieces messages on a number of connections.
 *
 * \author Robin Pedersen
 */
class ConnectionManager
{
public:

    /**
     * Virtual destructor to make sure implementations are correctly deleted.
     */
    virtual ~ConnectionManager() {};

    /**
     * Start accepting incoming connections on the given port.
     */
    virtual void startListening(port_t port) = 0;

    /**
     * Stop accepting connections.
     */
    virtual void stopListening() = 0;

    /**
     * Create a new connection to the given address.
     *
     * This is typically used to connect a peer to a host.
     */
    virtual void connectTo(const SocketAddress& address) = 0;

    /**
     * Send a message on all connections.
     *
     * The message is added to a message history list, and sent on all
     * connections, even those that are established in the future.
     *
     * Returns the ID of the sent message.
     */
    virtual msgid_t sendMessage(const Message& message) = 0;

    /**
     * Send a message on all connections.
     *
     * \overload
     *
     * The value of \a originalId must refer to a message previously sent,
     * and the result after sending these two messages must be equivalent
     * to not sending any of them.
     *
     * If a message with \a originalId is found in the message history, the
     * original message is removed instead of adding this message to the
     * history. This is used to avoid that the message history keeps growing
     * if something is switced back and forth between two states. For instance
     * if a game object is created and removed repeatedly. Instead of adding
     * a remove message to the message history, the create message is deleted.
     *
     * If no message is found with \a originalId, the result is equivalent to
     * calling the overload with one parameter. The message is added to the
     * history.
     */
    virtual msgid_t sendMessage(const Message& message, msgid_t originalId) = 0;

    /**
     * Close and delete the connection to the given \a address.
     */
    virtual void remove(const SocketAddress& address) = 0;
};

} // namespace pcs

#endif // PIECES_CONNECTION_MANAGER_H
