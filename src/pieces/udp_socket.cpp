
#include "Pieces/UDPSocket"
#include "Pieces/InetAddress"
#include "Pieces/IOException"
#include "Pieces/Debug"

#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


namespace Pieces
{

namespace
{

SocketAddress convert(const struct sockaddr_in* sock_addr)
{
    return SocketAddress(InetAddress(sock_addr->sin_addr.s_addr), sock_addr->sin_port);
}

}

class UDPSocketPrivate
{
public:
    UDPSocketPrivate();

    int fd;
};


UDPSocketPrivate::UDPSocketPrivate()
: fd(-1)
{
}


UDPSocket::UDPSocket()
: d(new UDPSocketPrivate)
{
    // Create standard tcp socket file descriptor.
    d->fd = ::socket(AF_INET, SOCK_DGRAM, 0);

    // Error checking
    if (d->fd < 0)
    {
        throw IOException("UDPSocket::UDPSocket", strerror(errno));
    }
}


UDPSocket::~UDPSocket()
{
    close();
    delete d;
}


void UDPSocket::close()
{
    ::close(d->fd);
}


void UDPSocket::bind(const SocketAddress& addr)
{
    // create sockaddr_in struct
    sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(addr.getPort());
    sock_addr.sin_addr.s_addr = htonl(addr.getInetAddress().toInt32());
    bzero(&(sock_addr.sin_zero), 8);

    int ret = ::bind(d->fd, reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr));
    if (ret < 0)
    {
        throw IOException("TCPServer::listen", strerror(errno));
    }
}


UDPPacket UDPSocket::receive()
{
    ByteArray ba(0x100000);

    struct sockaddr_in sock_peer;
    socklen_t len = sizeof(sock_peer);
    ssize_t size = ::recvfrom(d->fd, ba.data(), ba.size(), 0, reinterpret_cast<sockaddr*>(&sock_peer), &len);

    if (size < 0)
    {
        throw IOException("TCPSocket::read", strerror(errno));
    }

    SocketAddress addr = convert(&sock_peer);

    ba.resize(size);
    return UDPPacket(ba, addr);
}


void UDPSocket::send(const UDPPacket& packet)
{
    ByteArray data = packet.getData();
    SocketAddress addr = packet.getAddress();

    // create sockaddr_in struct
    sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(addr.getPort());
    sock_addr.sin_addr.s_addr = htonl(addr.getInetAddress().toInt32());
    bzero(&(sock_addr.sin_zero), 8);

    ssize_t size = ::sendto(d->fd, data.data(), data.size(), 0, reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr));

    if (size < 0)
    {
        throw IOException("TCPSocket::write", strerror(errno));
    }
}


} // namespace Pieces
