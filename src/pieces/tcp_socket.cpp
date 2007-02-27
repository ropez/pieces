
#include "Pieces/TCPSocket"
#include "Pieces/InetAddress"


namespace Pieces
{

TCPSocket::TCPSocket()
{
}

TCPSocket::~TCPSocket()
{
}

void TCPSocket::close()
{
}

bool TCPSocket::connect(const InetAddress& addr)
{
    bool dummy = false;
    return dummy;
}

ByteArray TCPSocket::read()
{
    ByteArray dummy;
    return dummy;
}

void TCPSocket::write(const ByteArray& data)
{
}


} // namespace Pieces
