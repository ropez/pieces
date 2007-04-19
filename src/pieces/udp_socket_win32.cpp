
#include "Pieces/UDPSocket"
#include "Pieces/Datagram"
#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"
#include "Pieces/IOException"
#include "Pieces/Debug"

#include <errno.h>
#include <winsock2.h>

namespace pcs
{

class UDPSocketPrivate
{
public:
    UDPSocketPrivate();

    SOCKET fd;
};


UDPSocketPrivate::UDPSocketPrivate()
: fd(INVALID_SOCKET)
{
}


UDPSocket::UDPSocket()
: d(new UDPSocketPrivate)
{
    // Create standard tcp socket file descriptor.
    d->fd = ::socket(AF_INET, SOCK_DGRAM, 0);

    // Error checking
    if (d->fd == INVALID_SOCKET)
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
    if(closesocket(d->fd) == SOCKET_ERROR)
    {
        std::cerr << "Error in UDPSocket::close()" << std::endl;
    }
}


void UDPSocket::bind(const SocketAddress& addr)
{
    // create sockaddr_in struct
    sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(addr.getPort());
    sock_addr.sin_addr.s_addr = addr.getInetAddress().toInt32();
    memset(&(sock_addr.sin_zero), 0, 8);

    int ret = ::bind(d->fd, reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr));
    if (ret == SOCKET_ERROR)
    {
        std::cerr << "Error in void UDPSocket::bind(const SocketAddress& addr) ErrorCode: " << WSAGetLastError() << std::endl;
        throw IOException("UDPSocket::bind", strerror(errno));
    }
}


void UDPSocket::bind(port_t port)
{
    bind(SocketAddress(InetAddress(), port));
}


Datagram UDPSocket::receive(size_t maxSize)
{
    ByteArray ba(maxSize);

    struct sockaddr_in sock_peer;
    int len = sizeof(sock_peer);

    int size = ::recvfrom(d->fd, reinterpret_cast<char*>(ba.data()), static_cast<int>(ba.size()), 0, reinterpret_cast<sockaddr*>(&sock_peer), &len);

    if (size == SOCKET_ERROR)
    {
        throw IOException("UDPSocket::receive", strerror(errno));
    }

    SocketAddress addr(InetAddress(sock_peer.sin_addr.s_addr), ntohs(sock_peer.sin_port));

    return Datagram(ByteArray(ba.constData(), size), addr);
}


void UDPSocket::send(const Datagram& packet)
{
    ByteArray data = packet.getData();
    SocketAddress addr = packet.getAddress();

    // create sockaddr_in struct
    sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(addr.getPort());
    sock_addr.sin_addr.s_addr = addr.getInetAddress().toInt32();
    memset(&(sock_addr.sin_zero), 0, 8);

    int size = ::sendto(d->fd, reinterpret_cast<char*>(data.data()), static_cast<int>(data.size()), 0, reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr));

    if(size == SOCKET_ERROR)
    {
        throw IOException("UDPSocket::send", strerror(errno));
    }
}


} // namespace pcs
