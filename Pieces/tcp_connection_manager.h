
#ifndef PIECES_TCP_CONNECTION_MANAGER_H
#define PIECES_TCP_CONNECTION_MANAGER_H

#include "Pieces/global"


namespace Pieces
{
class TCPConnection;
class SocketAddress;
class EventLoop;
class ByteArray;


// TODO: Move this to a different file
class ConnectionManager
{
public:
    virtual ~ConnectionManager() {};

    /**
     * Start accepting incoming connections on the given port.
     */
    virtual void listen(port_t port) = 0;

    /**
     * Create a new connection to the given address.
     *
     * This is typically used to connect a peer to a host.
     */
    virtual void connectTo(const SocketAddress& address) = 0;

    /**
     * Send a message on all connections.
     */
    virtual void sendMessage(int messageType, const ByteArray& data) = 0;

    /**
     * Close and delete the connection to the given \a address.
     */
    virtual void remove(const SocketAddress& address) = 0;
};


class TCPConnectionManagerPrivate;


/**
 * \class TCPConnectionManager
 * \brief Manages TCP connections.
 *
 * \author Robin Pedersen
 */
class TCPConnectionManager : public ConnectionManager
{
public:

    /**
     * Constructor.
     *
     * TODO: eventloop parameter should probably be removed later, and add some function to start receiving data after connected.
     */
    TCPConnectionManager(EventLoop* eventLoop);

    /**
     * Close and delete all connections.
     */
    virtual ~TCPConnectionManager();

    /**
     * Start accepting incoming connections on the given port.
     */
    virtual void listen(port_t port);

    /**
     * Create a new connection to the given address.
     *
     * This is typically used to connect a peer to a host.
     */
    virtual void connectTo(const SocketAddress& address);

    /**
     * Send a message on all connections.
     */
    virtual void sendMessage(int messageType, const ByteArray& data);

    /**
     * Close the connection to the given \a address.
     */
    virtual void remove(const SocketAddress& address);

    /**
     * This class takes ownership of the connection.
     */
    void add(TCPConnection* connection);

private:
    // Disable copy operations
    TCPConnectionManager(const TCPConnectionManager&);
    TCPConnectionManager& operator=(const TCPConnectionManager&);

    TCPConnectionManagerPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_CONNECTION_MANAGER_H
