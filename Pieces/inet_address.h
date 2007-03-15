
#ifndef PIECES_INET_ADDRESS_H
#define PIECES_INET_ADDRESS_H

#include <string>
#include <ostream>


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
    // NOTE: Is this really necassary? Couldn't we let the constructor do this. / Joakim
    static InetAddress getHostByName(const std::string& name);
    // .. or implemented in another "DNS" class?

    // String in the form of "12.23.23.2"
    std::string toString() const;


    // This class also need to be able to return the address as an integral number,
    // or the internal representation might be hidden and the other classes made friend classes.


    unsigned int get() const
    {
        return m_inet_addr;
    }

private:
    unsigned long stringToInAddr(const std::string& name);
    unsigned long m_inet_addr;

};

std::ostream& operator<<(std::ostream& os, const InetAddress& ia);

} // namespace Pieces

#endif // PIECES_INET_ADDRESS_H
