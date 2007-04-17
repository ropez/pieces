
#ifndef PIECES_INET_ADDRESS_H
#define PIECES_INET_ADDRESS_H

#include <string>
#include <ostream>
#include <Pieces/DataStream>


namespace pcs
{

class InetAddress
{
public:

    /**
     * Default constructor
     *
     * Will initiate to 0.0.0.0 (null).
     */
    InetAddress();

    /**
     * Convert from a 32-bit address.
     */
    InetAddress(unsigned long addr);

    /**
     * Create an InetAddress from a string in the format "XXX.XXX.XXX.XXX".
     */
    InetAddress(const std::string& addr);

    /**
     * Return true if the address is 0.0.0.0.
     */
    bool isNull() const;

    /**
     * Resolve a host name and return the address.
     *
     * Returns a null address if not found.
     */
    static InetAddress getHostByName(const std::string& name);

    /**
     * Return a string representation of this address (XXX.XXX.XXX.XXX).
     */
    std::string toString() const;


    /**
     * Return the address as a 32-bit number.
     */
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

DataStream& operator<<(DataStream& ds, const InetAddress& ia);
DataStream& operator>>(DataStream& ds, InetAddress& ia);

std::ostream& operator<<(std::ostream& os, const InetAddress& ia);

} // namespace pcs

#endif // PIECES_INET_ADDRESS_H
