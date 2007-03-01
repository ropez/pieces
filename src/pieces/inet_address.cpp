
#include "Pieces/InetAddress"
#include <iostream>
#ifndef WIN32
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
:m_inet_addr()
{
    inet_aton("0.0.0.0", &m_inet_addr);
}


/**
 * Create an InetAddress from a string
 * in the format "XXX.XXX.XXX.XXX"
 */

InetAddress::InetAddress(const std::string& addr)
{
    //is IP address valid?
    m_inet_addr = stringToInAddr(addr);
    //if(m_inet_addr.S_un == -1)
    {
        //No.. inform user
    }
}

in_addr InetAddress::stringToInAddr(const std::string &name)
{
#ifdef WIN32
    unsigned long ian = inet_addr(name.c_str());

    if(ian == INADDR_NONE)
    {
        std::cout << "Error: " << WSAGetLastError() << std::endl;
    }

    in_addr ia;
    memcpy(&ia, &ian, sizeof(unsigned long));
    return ia;
#elif
    in_addr ia;
    inet_aton(name.c_str(), &ia);
    return ia;
#endif
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
    memcpy(&addr, h->h_addr_list[0], h->h_length);
    
    // Construct a temporary InetAddress with found IP number
    InetAddress ia(inet_ntoa(addr));

    return ia;
}


/**
 * Return a string representation of this address
 */

std::string InetAddress::toString() const
{
    return inet_ntoa(m_inet_addr);
}


/**
 * Destructor
 */

InetAddress::~InetAddress()
{

}

}
