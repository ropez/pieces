/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Pieces/UDPSocket"
#include "Pieces/Datagram"
#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"
#include "Pieces/IOException"
#include "Pieces/Debug"

#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


namespace pcs
{

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
    sock_addr.sin_addr.s_addr = addr.getInetAddress().toInt32();
    bzero(&(sock_addr.sin_zero), 8);

    int ret = ::bind(d->fd, reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr));
    if (ret < 0)
    {
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
    socklen_t len = sizeof(sock_peer);

    ssize_t size = ::recvfrom(d->fd, ba.data(), ba.size(), 0, reinterpret_cast<sockaddr*>(&sock_peer), &len);

    if (size < 0)
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
    bzero(&(sock_addr.sin_zero), 8);

    ssize_t size = ::sendto(d->fd, data.data(), data.size(), 0, reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr));

    if (size < 0)
    {
        throw IOException("UDPSocket::send", strerror(errno));
    }
}


} // namespace pcs
