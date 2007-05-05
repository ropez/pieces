
#ifndef PIECES_INET_ADDRESS_H
#define PIECES_INET_ADDRESS_H

#include <string>
#include <ostream>
#include <Pieces/DataStream>


namespace pcs
{


/**
 * \class InetAddress inet_address.h <Pieces/InetAddress>
 * \brief Represents an internet (IPv4) address.
 *
 * This class represents an IPv4 address in an operating system independant
 * manner, and is used by TCPSocket and UDPSocket.
 *
 * \see SocketAddress
 *
 * \author Thomas Bakken, Robin Pedersen
 */
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


/**
 * Compare two addresses by their numerical value.
 *
 * This provides a sorting of addresses so that it is possible to use binary
 * searching algorithms.
 *
 * \retval -1 if \a op1 is less than \a op2.
 * \retval 0 if \a op1 is equal to \a op2.
 * \retval 1 if \a op1 is greater them \a op2.
 *
 * \relates InetAddress
 */
int compare(const InetAddress& op1, const InetAddress& op2);

/**
 * Returns true if \link compare(const InetAddress&, const InetAddress&) compare(op1, op2) \endlink == 0.
 *
 * \relates InetAddress
 */
bool operator==(const InetAddress& op1, const InetAddress& op2);

/**
 * Returns true if \link compare(const InetAddress&, const InetAddress&) compare(op1, op2) \endlink != 0.
 *
 * \relates InetAddress
 */
bool operator!=(const InetAddress& op1, const InetAddress& op2);

/**
 * Returns true if \link compare(const InetAddress&, const InetAddress&) compare(op1, op2) \endlink < 0.
 *
 * \relates InetAddress
 */
bool operator<(const InetAddress& op1, const InetAddress& op2);

/**
 * Returns true if \link compare(const InetAddress&, const InetAddress&) compare(op1, op2) \endlink > 0.
 *
 * \relates InetAddress
 */
bool operator>(const InetAddress& op1, const InetAddress& op2);

/**
 * Returns true if \link compare(const InetAddress&, const InetAddress&) compare(op1, op2) \endlink <= 0.
 *
 * \relates InetAddress
 */
bool operator<=(const InetAddress& op1, const InetAddress& op2);

/**
 * Returns true if \link compare(const InetAddress&, const InetAddress&) compare(op1, op2) \endlink >= 0.
 *
 * \relates InetAddress
 */
bool operator>=(const InetAddress& op1, const InetAddress& op2);

/**
 * Write the internet address \a ia to the data stream \a ds.
 *
 * \relates InetAddress
 */
DataStream& operator<<(DataStream& ds, const InetAddress& ia);

/**
 * Read the internet address \a ia from the data stream \a ds.
 *
 * \relates InetAddress
 */
DataStream& operator>>(DataStream& ds, InetAddress& ia);

/**
 * Write the internet address \a ia to the output stream \a os,
 * in text format (xxx.xxx.xxx.xxx).
 *
 * This is used for debugging.
 *
 * \see DebugStream
 * \relates InetAddress
 */
std::ostream& operator<<(std::ostream& os, const InetAddress& ia);

} // namespace pcs

#endif // PIECES_INET_ADDRESS_H
