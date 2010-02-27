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

#include "Pieces/InetAddress"
#include "Pieces/DataStream"
#include "Pieces/Exception"
#include <cstring>

#if defined(WIN32)
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

namespace pcs
{

InetAddress::InetAddress()
: m_inet_addr(INADDR_ANY)
{
}


InetAddress::InetAddress(unsigned int addr)
: m_inet_addr(addr)
{
}


InetAddress::InetAddress(const std::string& addr)
: m_inet_addr(INADDR_ANY)
{
    if (::inet_aton(addr.c_str(), reinterpret_cast<in_addr*>(&m_inet_addr)) == 0)
        throw pcs::Exception("InetAddress", "Invalid address format");
}


bool InetAddress::isNull() const
{
    return m_inet_addr == 0;
}


InetAddress InetAddress::getHostByName(const std::string& name)
{
    // Resolve host
    struct hostent* h = gethostbyname(name.c_str());

    if (!h)
    {
        // null
        return InetAddress();
    }

    // Copy the first IP number in hostent to an in_addr
    in_addr addr;
    std::memcpy(&addr, h->h_addr_list[0], h->h_length);

    // Construct a temporary InetAddress with found IP number
    InetAddress ia(addr.s_addr);

    return ia;
}


std::string InetAddress::toString() const
{
    struct in_addr a;
    a.s_addr = m_inet_addr;
    return inet_ntoa(a);
}


unsigned int InetAddress::toInt32() const
{
    return m_inet_addr;
}


int compare(const InetAddress& op1, const InetAddress& op2)
{
    unsigned long n1 = op1.toInt32();
    unsigned long n2 = op2.toInt32();

    if (n1 < n2)
        return -1;
    if (n1 > n2)
        return 1;

    // Equal

    return 0;
}


bool operator==(const InetAddress& op1, const InetAddress& op2)
{
    return compare(op1, op2) == 0;
}


bool operator!=(const InetAddress& op1, const InetAddress& op2)
{
    return compare(op1, op2) != 0;
}


bool operator<(const InetAddress& op1, const InetAddress& op2)
{
    return compare(op1, op2) < 0;
}


bool operator>(const InetAddress& op1, const InetAddress& op2)
{
    return compare(op1, op2) > 0;
}


bool operator<=(const InetAddress& op1, const InetAddress& op2)
{
    return compare(op1, op2) <= 0;
}


bool operator>=(const InetAddress& op1, const InetAddress& op2)
{
    return compare(op1, op2) >= 0;
}

DataStream& operator<<(DataStream& ds, const InetAddress& ia)
{
    ds << ia.toInt32();
    return ds;
}

DataStream& operator>>(DataStream& ds, InetAddress& ia)
{
    unsigned int addr;
    ds >> addr;

    ia = InetAddress(addr);
    return ds;
}

std::ostream& operator<<(std::ostream& os, const InetAddress& ia)
{
    return os << ia.toString();
}

} // namespace pcs
