
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

    // Convert from a low-level address
    InetAddress(unsigned long addr);

    // String in the form of "12.23.23.2"
    InetAddress(const std::string& addr);

    bool isNull() const;

    // Also need DNS functionality the creates InetAddress object, like
    // NOTE: Is this really necassary? Couldn't we let the constructor do this. / Joakim
    static InetAddress getHostByName(const std::string& name);
    // .. or implemented in another "DNS" class?

    // String in the form of "12.23.23.2"
    std::string toString() const;


    // This class also need to be able to return the address as an integral number,
    // or the internal representation might be hidden and the other classes made friend classes.


    unsigned long toInt32() const;

private:
    unsigned long stringToInAddr(const std::string& name);
    unsigned long m_inet_addr;

};

int compare(const InetAddress& op1, const InetAddress& op2);

bool operator==(const InetAddress& op1, const InetAddress& op2);
bool operator!=(const InetAddress& op1, const InetAddress& op2);
bool operator<(const InetAddress& op1, const InetAddress& op2);
bool operator>(const InetAddress& op1, const InetAddress& op2);
bool operator<=(const InetAddress& op1, const InetAddress& op2);
bool operator>=(const InetAddress& op1, const InetAddress& op2);

std::ostream& operator<<(std::ostream& os, const InetAddress& ia);

} // namespace Pieces

#endif // PIECES_INET_ADDRESS_H
