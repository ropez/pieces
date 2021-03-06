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

#ifndef PIECES_SOCKET_ADDRESS_H
#define PIECES_SOCKET_ADDRESS_H

#include "Pieces/global"
#include "Pieces/InetAddress"



namespace pcs
{
class DataStream;


/**
 * \class SocketAddress socket_address.h <Pieces/SocketAddress>
 * \brief Represents a internet address and a port number.
 *
 * \author Robin Pedersen
 */
class SocketAddress
{
public:

    /**
     * Creates a socket-address with a default constructed (\em null) address,
     * and port number 0. (A \em null socket-address).
     */
    SocketAddress();

    /**
     * Destructor.
     */
    ~SocketAddress();

    /**
     * Creates a socket-address with a given \a address and \a port.
     */
    SocketAddress(const InetAddress& addr, port_t port);

    /**
     * Copy constructor.
     */
    SocketAddress(const SocketAddress& other);

    /**
     * Assignment operator.
     */
    SocketAddress& operator=(const SocketAddress& other);

    /**
     * Return true if this address is \em null, meaning that the internet
     * address is \a null and the port is 0.
     */
    bool isNull() const;

    /**
     * Returns the internet address.
     */
    InetAddress getInetAddress() const;

    /**
     * Set the internet address to \a addr.
     */
    void setInetAddress(const InetAddress& addr);

    /**
     * Returns the port number.
     */
    port_t getPort() const;

    /**
     * Set the port number to \a port.
     */
    void setPort(port_t port);

private:
    InetAddress m_address;
    port_t m_port;
};


/**
 * Compare two addresses by their numerical value.
 *
 * This provides a sorting of addresses so that it is possible to use binary
 * searching algorithms.
 *
 * \retval -1 if \a op1 is less than \a op2.
 * \retval 0 if \a op1 is equal to \a op2.
 * \retval 1 if \a op1 is greater them \a op2.
 *
 * \relates SocketAddress
 */
int compare(const SocketAddress& op1, const SocketAddress& op2);

/**
 * Returns true if \link compare(const SocketAddress&, const SocketAddress&) compare(op1, op2) \endlink == 0.
 *
 * \relates SocketAddress
 */
bool operator==(const SocketAddress& op1, const SocketAddress& op2);

/**
 * Returns true if \link compare(const SocketAddress&, const SocketAddress&) compare(op1, op2) \endlink != 0.
 *
 * \relates SocketAddress
 */
bool operator!=(const SocketAddress& op1, const SocketAddress& op2);

/**
 * Returns true if \link compare(const SocketAddress&, const SocketAddress&) compare(op1, op2) \endlink < 0.
 *
 * \relates SocketAddress
 */
bool operator<(const SocketAddress& op1, const SocketAddress& op2);

/**
 * Returns true if \link compare(const SocketAddress&, const SocketAddress&) compare(op1, op2) \endlink > 0.
 *
 * \relates SocketAddress
 */
bool operator>(const SocketAddress& op1, const SocketAddress& op2);

/**
 * Returns true if \link compare(const SocketAddress&, const SocketAddress&) compare(op1, op2) \endlink <= 0.
 *
 * \relates SocketAddress
 */
bool operator<=(const SocketAddress& op1, const SocketAddress& op2);

/**
 * Returns true if \link compare(const SocketAddress&, const SocketAddress&) compare(op1, op2) \endlink >= 0.
 *
 * \relates SocketAddress
 */
bool operator>=(const SocketAddress& op1, const SocketAddress& op2);

/**
 * Write the socket address \a sa to the data stream \a ds.
 *
 * \relates SocketAddress
 */
DataStream& operator<<(DataStream& ds, const SocketAddress& sa);

/**
 * Read the socket address \a sa from the data stream \a ds.
 *
 * \relates SocketAddress
 */
DataStream& operator>>(DataStream& ds, SocketAddress& sa);

/**
 * Write the socket address \a sa to the output stream \a os,
 * in text format (xxx.xxx.xxx.xxx:port).
 *
 * This is used for debugging.
 *
 * \see DebugStream
 * \relates SocketAddress
 */
std::ostream& operator<<(std::ostream& os, const SocketAddress& sa);

} // namespace pcs

#endif // PIECES_SOCKET_ADDRESS_H
