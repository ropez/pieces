
#include "Pieces/InetAddress"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

namespace Pieces
{

/**
 * Default constructor
 * Will initiate to 0.0.0.0
 */

InetAddress::InetAddress()
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
	if( ( inet_aton(addr.c_str(), &m_inet_addr) ) == -1)
	{
		//No.. inform user
	}
}


/**
 * Resolve a host name and return the address
 */

InetAddress InetAddress::getHostByName(const std::string& name)
{
	//Resolve host
	struct hostent* host = gethostbyname(name.c_str());

	//Create the new InetAddress object with the host IP
	InetAddress addr(std::string(host->h_addr));
	
	return addr;
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
