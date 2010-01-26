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

#ifndef PIECES_UDP_SOCKET_H
#define PIECES_UDP_SOCKET_H

#include "Pieces/SocketAddress"


namespace pcs
{
class Datagram;
class UDPSocketPrivate;


/**
 * \class UDPSocket udp_socket.h <Pieces/UDPSocket>
 * \brief OS independant UDP network socket.
 *
 * This class provides a simple OS indepenent interface for sending and
 * receiving datagrams over UDP.
 *
 * \author Robin Pedersen, Tord Heimdal, Thomas Bakken, Joakim Simonsson, Borge Jacobsen
 */
class UDPSocket
{
public:

    /**
     * Default constructor.
     */
    UDPSocket();

    /**
     * Destructor (calls close()).
     */
    ~UDPSocket();

    /**
     * Close the socket.
     */
    void close();

    /**
     * Bind to the given socket address, to receive packets sent to this address.
     */
    void bind(const SocketAddress& addr);

    /**
     * Bind to the given port, to receive packets sent to this port.
     *
     * \overload
     *
     * This is the same as bind(SocketAddress(InetAddress(), port)).
     */
    void bind(port_t port);

    /**
     * Receive a packet.
     */
    Datagram receive(size_t maxSize);

    /**
     * Send a packet.
     */
    void send(const Datagram& packet);

private:
    DISABLE_COPY(UDPSocket);

    UDPSocketPrivate* d;
};

} // namespace pcs

#endif // PIECES_UDP_SOCKET_H
