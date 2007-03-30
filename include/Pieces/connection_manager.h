
#ifndef PIECES_CONNECTION_MANAGER_H
#define PIECES_CONNECTION_MANAGER_H

#include "Pieces/global"


namespace Pieces
{
class TCPConnection;
class SocketAddress;
class Message;
class EventLoop;
class ByteArray;


/**
 * \class ConnectionManager
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
     */
    virtual void sendMessage(const Message& message) = 0;

    /**
     * Close and delete the connection to the given \a address.
     */
    virtual void remove(const SocketAddress& address) = 0;
};

} // namespace Pieces

#endif // PIECES_CONNECTION_MANAGER_H
