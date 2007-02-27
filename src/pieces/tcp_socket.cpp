
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
}

ByteArray TCPSocket::read()
{
}

void TCPSocket::write(const ByteArray& data)
{
}


} // namespace Pieces
