
#include "Pieces/InetAddress"


namespace Pieces
{

InetAddress::InetAddress()
{
}

InetAddress::InetAddress(const std::string& addr)
{
}

static InetAddress InetAddress::getHostByName(const std::string& name)
{
}

InetAddress::~InetAddress()
{
}

std::string InetAddress::toString() const
{
}

} // namespace Pieces
