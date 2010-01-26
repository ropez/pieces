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

#ifndef PIECES_TCP_SERVER_H
#define PIECES_TCP_SERVER_H

#include "Pieces/SocketAddress"
#include "Pieces/AutoPointer"


namespace pcs
{
class TCPSocket;
class TCPServerPrivate;


/**
 * \class TCPServer tcp_server.h <Pieces/TCPServer>
 * \brief Listening tcp socket.
 *
 * This class is an abstraction for a listening tcp socket.
 * Call listen() to start listening, then call accept() to accept
 * new connections.
 *
 * \author Robin Pedersen, Thomas Bakken, Joakim Simonsson
 */
class TCPServer
{
public:

    /**
     * Create a server.
     */
    TCPServer();

    /**
     * Close socket and release all resources.
     */
    ~TCPServer();

    /**
     * Listen on the given socket.
     */
    void listen(const SocketAddress& addr);

    /**
     * Listen to the given port, to receive connections to this port.
     *
     * \overload
     *
     * This is the same as listen(SocketAddress(InetAddress(), port)).
     */
    void listen(port_t port);

    /**
     * Returns the maximum queue size.
     *
     * The server will keep at most this number of pending connections
     * while waiting for the user to call accept.
     */
    int getQueueSize() const;

    /**
     * Set the maximum queue size.
     */
    void setQueueSize(int size);

    /**
     * Accept a connection.
     */
    AutoPointer<TCPSocket> accept();

private:
    DISABLE_COPY(TCPServer);

    TCPServerPrivate* d;
};

} // namespace pcs

#endif // PIECES_TCP_SERVER_H
