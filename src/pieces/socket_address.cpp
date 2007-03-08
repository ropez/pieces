
#include "Pieces/SocketAddress"


namespace Pieces
{

SocketAddress::SocketAddress()
: m_address()
, m_port(0)
{
}


SocketAddress::~SocketAddress()
{
}


SocketAddress::SocketAddress(const InetAddress& addr, unsigned short port)
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

InetAddress SocketAddress::getInetAddress() const
{
    return m_address;
}


unsigned short SocketAddress::getPort() const
{
    return m_port;
}

} // namespace Pieces
