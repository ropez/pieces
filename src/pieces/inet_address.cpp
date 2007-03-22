
#include "Pieces/InetAddress"

#include <cstring>

#if defined(WIN32)
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

namespace Pieces
{

InetAddress::InetAddress()
: m_inet_addr(INADDR_ANY)
{
}


InetAddress::InetAddress(unsigned long addr)
: m_inet_addr(addr)
{
}


InetAddress::InetAddress(const std::string& addr)
: m_inet_addr(stringToInAddr(addr))
{
}


bool InetAddress::isNull() const
{
    return m_inet_addr == 0;
}


unsigned long InetAddress::stringToInAddr(const std::string &name)
{
    return inet_addr(name.c_str());
}


InetAddress InetAddress::getHostByName(const std::string& name)
{
    // Resolve host
    hostent* h = gethostbyname(name.c_str());

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


unsigned long InetAddress::toInt32() const
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


std::ostream& operator<<(std::ostream& os, const InetAddress& ia)
{
    return os << ia.toString();
}

} // namespace Pieces
