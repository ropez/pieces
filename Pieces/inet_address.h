
#ifndef PIECES_INET_ADDRESS_H
#define PIECES_INET_ADDRESS_H

#include <string>

#ifdef WIN32
#include <winsock2.h>
#elif
#include <netinet/in.h>
#endif


namespace Pieces
{

class InetAddress
{
public:
    // "any" address == 0.0.0.0
    InetAddress();
    ~InetAddress();

    // String in the form of "12.23.23.2"
    InetAddress(const std::string& addr);

    // Also need DNS functionality the creates InetAddress object, like
    static InetAddress getHostByName(const std::string& name);
    // .. or implemented in another "DNS" class?

    // String in the form of "12.23.23.2"
    std::string toString() const;


    // This class also need to be able to return the address as an integral number,
    // or the internal representation might be hidden and the other classes made friend classes.

private:
    in_addr stringToInAddr(const std::string& name);
    in_addr m_inet_addr;

};

} // namespace Pieces

#endif // PIECES_INET_ADDRESS_H
