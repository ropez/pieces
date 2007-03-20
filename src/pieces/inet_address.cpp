
#include "Pieces/InetAddress"

#include <cstring>

#if !defined WIN32
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

namespace Pieces
{

/**
 * Default constructor
 * Will initiate to 0.0.0.0
 */
InetAddress::InetAddress()
: m_inet_addr(stringToInAddr("0.0.0.0"))
{
}


InetAddress::InetAddress(unsigned long addr)
: m_inet_addr(addr)
{
}


/**
 * Create an InetAddress from a string
 * in the format "XXX.XXX.XXX.XXX"
 */
InetAddress::InetAddress(const std::string& addr)
: m_inet_addr(stringToInAddr(addr))
{
}

unsigned long InetAddress::stringToInAddr(const std::string &name)
{
    unsigned long ian = inet_addr(name.c_str());

    if(ian == INADDR_NONE)
    {
        //std::cout << "Error: " << WSAGetLastError() << std::endl;
    }

    return ian;
}

/**
 * Resolve a host name and return the address
 */
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


/**
 * Return a string representation of this address
 */
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
