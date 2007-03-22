
#include "Pieces/TCPSocket"
#include "Pieces/TCPServer"
#include "Pieces/InetAddress"
#include "Pieces/IOException"
#include "Pieces/TimeoutException"
#include "Pieces/DisconnectedException"
#include "Pieces/Debug"

#include <winsock2.h>
#include <io.h>



namespace Pieces
{

class TCPSocketPrivate
{
public:// namespace Pieces

    // Default constructor.
    TCPSocketPrivate();

    SOCKET fd;

    ByteArray sendbuf;

    SocketAddress peerAddress;
};


TCPSocketPrivate::TCPSocketPrivate()
: fd(UINT_MAX)
, sendbuf()
, peerAddress()
{
}


TCPSocket::TCPSocket()
: d(new TCPSocketPrivate)
{
    open();
}



TCPSocket::TCPSocket(TCPSocketPrivate* data)
: d(data)
{
}


TCPSocket::~TCPSocket()
{
    close();
    delete d;
}


void TCPSocket::open()
{
    // Create standard tcp socket file descriptor.
    d->fd = ::socket(AF_INET, SOCK_STREAM, 0);

    // Error checking
    if (d->fd < 0)
    {
        throw IOException("TCPSocket::open", strerror(errno));
    }
}


void TCPSocket::close()
{
    if (d->fd != -1)
    {
        try
        {
            flush();
        }
        catch (const Exception& e)
        {
            PWARNING << e;
        }

        if(closesocket(d->fd) == SOCKET_ERROR)
        {
            std::cerr << "Unable to close socket" << std::endl;
        }
        
        d->fd = UINT_MAX;
    }
}


bool TCPSocket::connect(const SocketAddress& addr)
{
    struct sockaddr_in sock_peer;

    // set up address struct used
    sock_peer.sin_family = AF_INET;
    sock_peer.sin_port = htons(addr.getPort());
    sock_peer.sin_addr.s_addr = addr.getInetAddress().toInt32();
    memset(&(sock_peer.sin_zero), 0, 8);

    // call connect
    int ret = ::connect(d->fd, reinterpret_cast<sockaddr*>(&sock_peer) , sizeof(sock_peer));

    if (ret < 0)
    {
        // TODO: DO WINDOWS SPECIFIC ERROR TESTING
        throw IOException("TCPSocket::connect", strerror(errno));
    }

    // Connection OK
    d->peerAddress = addr;

    return true;
}


bool TCPSocket::connect(const InetAddress& addr, port_t port)
{
    return connect(SocketAddress(addr, port));
}


SocketAddress TCPSocket::getPeerAddress() const
{
    return d->peerAddress;
}


ByteArray TCPSocket::read(size_t maxSize)
{
    ByteArray ba(maxSize);

    // Return empty array if size is 0
    if (maxSize == 0)
    {
        return ba;
    }

    // Read from socket
    int size = recv(d->fd, reinterpret_cast<char*>(ba.data()), static_cast<int>(ba.size()), 0);

    // Check for errors
    if (size < 0)
    {
        // TODO: DO WINDOWS SPECIFIC ERROR TESTING
        throw IOException("TCPSocket::read", strerror(errno));
    }

    // If size is 0, means the socket is disconnected
    if (size == 0)
    {
        throw DisconnectedException("TCPSocket::read", "Disconnected");
    }

    // Return a byte-array of the actual read size
    return ByteArray(ba.constData(), size);
}


void TCPSocket::write(const ByteArray& data)
{
    d->sendbuf.append(data);
}


void TCPSocket::send(const ByteArray& data)
{
    write(data);
    flush();
}


void TCPSocket::flush()
{
    size_t sent = 0;
    while (sent < d->sendbuf.size())
    {
        int size = ::send(d->fd, reinterpret_cast<char*>(d->sendbuf.data()), static_cast<unsigned int>(d->sendbuf.size()), 0);

        if (size < 0)
        {
            // TODO: DO WINDOWS SPECIFIC ERROR TESTING
            throw IOException("TCPSocket::flush", strerror(errno));
        }
        sent += size;
    }
    d->sendbuf.clear();
}


unsigned long TCPSocket::getReadTimeout() const
{
    struct timeval tv;
    int len = sizeof(tv);
    ::getsockopt(d->fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, &len);

    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


void TCPSocket::setReadTimeout(unsigned long msec)
{
    struct timeval tv;
    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;

    if (::setsockopt(d->fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv)) < 0)
    {
        PWARNING << "setReadTimeout failed: " << strerror(errno);
    }
}


unsigned long TCPSocket::getWriteTimeout() const
{
    struct timeval tv;
    int len = sizeof(tv);
    ::getsockopt(d->fd, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, &len);

    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


void TCPSocket::setWriteTimeout(unsigned long msec)
{
    struct timeval tv;
    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;

    if (::setsockopt(d->fd, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(tv)) < 0)
    {
        PWARNING << "setReadTimeout failed: " << strerror(errno);
    }
}



// TCPServer implementation

class TCPServerPrivate
{
public:
    TCPServerPrivate();

    SOCKET fd;
    int queueSize;
};


TCPServerPrivate::TCPServerPrivate()
: fd(UINT_MAX)
, queueSize(10)
{
}


TCPServer::TCPServer()
: d(new TCPServerPrivate)
{
    // Create standard tcp socket file descriptor.
    d->fd = ::socket(AF_INET, SOCK_STREAM, 0);

    // Error checking
    if (d->fd < 0)
    {
        throw IOException("TCPSocket::TCPSocket", strerror(errno));
    }
}


TCPServer::~TCPServer()
{
    delete d;
}



int TCPServer::getQueueSize() const
{
    return d->queueSize;
}


void TCPServer::setQueueSize(int size)
{
    d->queueSize = size;
}


void TCPServer::listen(const SocketAddress& addr)
{
    // create sockaddr_in struct
    sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(addr.getPort());
    sock_addr.sin_addr.s_addr = htonl(addr.getInetAddress().toInt32());
    memset(&(sock_addr.sin_zero), 0, 8);

    int ret = ::bind(d->fd, reinterpret_cast<sockaddr*>(&sock_addr), sizeof(sock_addr));
    if (ret < 0)
    {
        throw IOException("TCPServer::listen", strerror(errno));
    }

    ret = ::listen(d->fd, d->queueSize);
    if (ret < 0)
    {
        throw IOException("TCPServer::listen", strerror(errno));
    }
}


void TCPServer::listen(port_t port)
{
    listen(SocketAddress(InetAddress(), port));
}


AutoPointer<TCPSocket> TCPServer::accept()
{
    AutoPointer<TCPSocketPrivate> data(new TCPSocketPrivate);

    struct sockaddr_in sock_peer;
    int len = sizeof(sock_peer);
    data->fd = ::accept(d->fd, reinterpret_cast<sockaddr*>(&sock_peer), &len);

    if (data->fd < 0)
    {
        throw IOException("TCPServer::accept", strerror(errno));
    }

    data->peerAddress.setInetAddress(InetAddress(sock_peer.sin_addr.s_addr));
    data->peerAddress.setPort(ntohs(sock_peer.sin_port));

    return AutoPointer<TCPSocket>(new TCPSocket(data.release()));
}


} // namespace Pieces
