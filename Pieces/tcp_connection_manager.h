
#ifndef PIECES_TCP_CONNECTION_MANAGER_H
#define PIECES_TCP_CONNECTION_MANAGER_H

#include "Pieces/global"


namespace Pieces
{
class TCPConnection;
class SocketAddress;
class EventLoop;
class TCPConnectionManagerPrivate;


/**
 * \class TCPConnectionManager
 * \brief Manages TCP connections.
 *
 * \author Robin Pedersen
 */
class TCPConnectionManager
{
public:

    /**
     * Constructor.
     *
     * TODO: eventloop should probably be deleted later, and add some function to start receiving data after connected.
     */
    TCPConnectionManager(EventLoop* eventLoop);
    ~TCPConnectionManager();

    /**
     * Start accepting incoming connections on the given port.
     */
    void listen(port_t port);

    /**
     * This class takes ownership of the connection.
     */
    void add(TCPConnection* connection);

    void remove(const SocketAddress& address);

private:
    // Disable copy operations
    TCPConnectionManager(const TCPConnectionManager&);
    TCPConnectionManager& operator=(const TCPConnectionManager&);

    TCPConnectionManagerPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_CONNECTION_MANAGER_H
