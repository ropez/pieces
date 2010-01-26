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

#include "Pieces/SocketAddress"


namespace pcs
{

SocketAddress::SocketAddress()
: m_address()
, m_port(0)
{
}


SocketAddress::~SocketAddress()
{
}


SocketAddress::SocketAddress(const InetAddress& addr, port_t port)
: m_address(addr)
, m_port(port)
{
}


SocketAddress::SocketAddress(const SocketAddress& other)
: m_address(other.m_address)
, m_port(other.m_port)
{
}


SocketAddress& SocketAddress::operator=(const SocketAddress& other)
{
    m_address = other.m_address;
    m_port = other.m_port;

    return *this;
}


bool SocketAddress::isNull() const
{
    return m_address.isNull() && m_port == 0;
}


InetAddress SocketAddress::getInetAddress() const
{
    return m_address;
}


void SocketAddress::setInetAddress(const InetAddress& addr)
{
    m_address = addr;
}


port_t SocketAddress::getPort() const
{
    return m_port;
}


void SocketAddress::setPort(port_t port)
{
    m_port = port;
}


int compare(const SocketAddress& op1, const SocketAddress& op2)
{
    // Compare addresses
    int ret = compare(op1.getInetAddress(), op2.getInetAddress());
    if (ret == 0)
    {
        // Compare ports
        if (op1.getPort() < op2.getPort())
            ret = -1;
        if (op1.getPort() > op2.getPort())
            ret = 1;
    }
    return ret;
}


bool operator==(const SocketAddress& op1, const SocketAddress& op2)
{
    return compare(op1, op2) == 0;
}


bool operator!=(const SocketAddress& op1, const SocketAddress& op2)
{
    return compare(op1, op2) != 0;
}


bool operator<(const SocketAddress& op1, const SocketAddress& op2)
{
    return compare(op1, op2) < 0;
}


bool operator>(const SocketAddress& op1, const SocketAddress& op2)
{
    return compare(op1, op2) > 0;
}


bool operator<=(const SocketAddress& op1, const SocketAddress& op2)
{
    return compare(op1, op2) <= 0;
}


bool operator>=(const SocketAddress& op1, const SocketAddress& op2)
{
    return compare(op1, op2) >= 0;
}


bool operator!=(const SocketAddress& op1, const SocketAddress& op2);
bool operator<(const SocketAddress& op1, const SocketAddress& op2);
bool operator>(const SocketAddress& op1, const SocketAddress& op2);
bool operator<=(const SocketAddress& op1, const SocketAddress& op2);
bool operator>=(const SocketAddress& op1, const SocketAddress& op2);

DataStream& operator<<(DataStream& ds, const SocketAddress& sa)
{
    ds << sa.getInetAddress();
    ds << sa.getPort();
    return ds;
}

DataStream& operator>>(DataStream& ds, SocketAddress& sa)
{
    InetAddress ia;
    ds >> ia;

    port_t port = 0;
    ds >> port;

    sa.setInetAddress(ia);
    sa.setPort(port);

    return ds;
}


std::ostream& operator<<(std::ostream& os, const SocketAddress& sa)
{
    return os << sa.getInetAddress() << ":" << sa.getPort();
}

} // namespace pcs
