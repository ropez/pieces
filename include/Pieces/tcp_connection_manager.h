/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PIECES_TCP_CONNECTION_MANAGER_H
#define PIECES_TCP_CONNECTION_MANAGER_H

#include "Pieces/EventHandler"
#include "Pieces/ConnectionManager"


namespace pcs
{
class TCPConnectionManagerPrivate;


/**
 * \class TCPConnectionManager tcp_connection_manager.h <Pieces/TCPConnectionManager>
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
     * All events will be posted to the given event loop.
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
