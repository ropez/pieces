
#ifndef PIECES_TCP_CONNECTION_MANAGER_H
#define PIECES_TCP_CONNECTION_MANAGER_H

#include "Pieces/EventHandler"
#include "Pieces/ConnectionManager"


namespace pcs
{
class TCPConnectionManagerPrivate;


/**
 * \class TCPConnectionManager
 * \brief Manages TCP connections.
 *
 * Connection manager implementation using TCP connections.
 *
 * \author Robin Pedersen
 */
class TCPConnectionManager : public ConnectionManager
{
public:

    /**
     * Constructor.
     *
     * TODO: eventloop parameter should probably be removed later, and add some
     * function to start receiving data after connected.
     */
    TCPConnectionManager(EventLoop* eventLoop);

    /**
     * Close and delete all connections.
     */
    virtual ~TCPConnectionManager();

    /**
     * Start accepting incoming connections on the given port.
     */
    virtual void startListening(port_t port);

    /**
     * Stop accepting connections.
     */
    virtual void stopListening();

    /**
     * Create a new connection to the given address.
     *
     * This is typically used to connect a peer to a host.
     */
    virtual void connectTo(const SocketAddress& address);

    /**
     * Send a message on all connections.
     */
    virtual msgid_t sendMessage(const Message& message);

    /**
     * Send a message on all connections.
     */
    virtual msgid_t sendMessage(const Message& message, msgid_t originalId);

    /**
     * Close the connection to the given \a address.
     */
    virtual void remove(const SocketAddress& address);

    /**
     * This class takes ownership of the connection.
     */
    void add(TCPConnection* connection);

private:
    DISABLE_COPY(TCPConnectionManager);

    TCPConnectionManagerPrivate* d;
};

} // namespace pcs

#endif // PIECES_TCP_CONNECTION_MANAGER_H
