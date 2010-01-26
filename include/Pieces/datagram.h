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

#ifndef PIECES_DATAGRAM_H
#define PIECES_DATAGRAM_H

#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ByteArray"
#include "Pieces/SocketAddress"


namespace pcs
{


/**
 * \class Datagram datagram.h <Pieces/Datagram>
 * \brief A packet in the UDP protocol.
 *
 * A datagram conatains an address of a remote computer, and the payload.
 *
 * \author Robin Pedersen
 */
class Datagram
{
public:

    /**
     * Create an empty datagram.
     */
    Datagram();

    /**
     * Create a datagram with the given \a data and \a addr.
     */
    Datagram(const ByteArray& data, const SocketAddress& addr);

    /**
     * Create a datagram with the given \a data, \a addr and \a port.
     */
    Datagram(const ByteArray& data, const InetAddress& addr, port_t port);

    /**
     * Copy constructor.
     */
    Datagram(const Datagram& other);

    /**
     * Assignment operator.
     */
    Datagram& operator=(const Datagram& other);

    /**
     * Destructor.
     */
    ~Datagram();

    /**
     * Returns the address of the remote host.
     *
     * If this is a received datagram, this is the address of the sender.
     * If it is an outgoing datagram, this is the address of the receiver.
     */
    SocketAddress getAddress() const;

    /**
     * Set the address to \a addr.
     */
    void setAddress(const SocketAddress& addr);

    /**
     * Returns a copy of the payload.
     */
    ByteArray getData() const;

    /**
     * Set the payload to \a data.
     */
    void setData(const ByteArray& data);

private:
    class Data : public SharedData
    {
    public:
        Data();
        Data(const ByteArray& data, const SocketAddress& addr);

        Data(const Data& other);
        Data& operator=(const Data& other);

        ByteArray data;
        SocketAddress address;
    };

    SharedDataPointer<Data> d;
};

} // namespace pcs

#endif // PIECES_DATAGRAM_H
