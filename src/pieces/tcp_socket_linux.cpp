
#include "Pieces/TCPSocket"
#include "Pieces/TCPServer"
#include "Pieces/InetAddress"
#include "Pieces/IOException"
#include "Pieces/TimeoutException"
#include "Pieces/Debug"

#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


namespace Pieces
{


// This is a namespace without a name. It means that functions within this
// namespace are available locally in this file, and don't make conflicts with
// functions in other files that have the same name. It is the C++ equivalent
// to C functions declared as static
namespace
{

SocketAddress convert(const struct sockaddr_in* sock_addr)
{
    return SocketAddress(InetAddress(sock_addr->sin_addr.s_addr), sock_addr->sin_port);
}

}


class TCPSocketPrivate
{
public:

    // Default constructor.
    TCPSocketPrivate();

    int fd;

    SocketAddress peerAddress;
};


TCPSocketPrivate::TCPSocketPrivate()
: fd(-1)
, peerAddress()
{
}


TCPSocket::TCPSocket()
: d(new TCPSocketPrivate)
{
    // Create standard tcp socket file descriptor.
    d->fd = ::socket(AF_INET, SOCK_STREAM, 0);

    // Error checking
    if (d->fd < 0)
    {
        throw IOException("TCPSocket::TCPSocket", strerror(errno));
    }
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


void TCPSocket::close()
{
    ::close(d->fd);
}


bool TCPSocket::connect(const SocketAddress& addr)
{
    return connect(addr.getInetAddress(), addr.getPort());
}


bool TCPSocket::connect(const InetAddress& addr, port_t port)
{
    struct sockaddr_in sock_peer;

    // set up address struct used
    sock_peer.sin_family = AF_INET;
    sock_peer.sin_port = htons(port);
    sock_peer.sin_addr.s_addr = addr.toInt32();
    bzero(&(sock_peer.sin_zero), 8);

    // call connect
    int ret = ::connect(d->fd, reinterpret_cast<sockaddr*>(&sock_peer) , sizeof(sock_peer));

    if (ret < 0)
    {
        switch (errno)
        {
        case ENETUNREACH: // Network unreachable
        case ECONNREFUSED: // Connection refused
            // This does not qualify as an "exception"
            return false;
        default:
            // Other "real" error
            throw IOException("TCPSocket::connect", strerror(errno));
        }
    }

    // Connection OK
    d->peerAddress = convert(&sock_peer);

    return true;
}


ByteArray TCPSocket::read(size_t maxSize)
{
    ByteArray ba(maxSize);

    ssize_t size = ::read(d->fd, ba.data(), ba.size());

    if (size < 0)
    {
        switch (errno)
        {
        case EAGAIN:
            throw TimeoutException("TCPSocket::read", strerror(errno));
        default:
            throw IOException("TCPSocket::read", strerror(errno));
        }
    }

    // Return a byte-array of the actual read size
    return ByteArray(ba.constData(), size);
}


void TCPSocket::write(const ByteArray& data)
{
    ssize_t size = ::write(d->fd, data.data(), data.size());

    if (size < 0)
    {
        switch (errno)
        {
        case EAGAIN:
            throw TimeoutException("TCPSocket::write", strerror(errno));
        default:
            throw IOException("TCPSocket::write", strerror(errno));
        }
    }
}


unsigned long TCPSocket::getReadTimeout() const
{
    struct timeval tv;
    socklen_t len = sizeof(tv);
    ::getsockopt(d->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, &len);

    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


void TCPSocket::setReadTimeout(unsigned long msec)
{
    struct timeval tv;
    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;

    if (::setsockopt(d->fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
    {
        WARNING << "setReadTimeout failed: " << strerror(errno);
    }
}


unsigned long TCPSocket::getWriteTimeout() const
{
    struct timeval tv;
    socklen_t len = sizeof(tv);
    ::getsockopt(d->fd, SOL_SOCKET, SO_SNDTIMEO, &tv, &len);

    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


void TCPSocket::setWriteTimeout(unsigned long msec)
{
    struct timeval tv;
    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;

    if (::setsockopt(d->fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0)
    {
        WARNING << "setReadTimeout failed: " << strerror(errno);
    }
}



// TCPServer implementation

class TCPServerPrivate
{
public:
    TCPServerPrivate();

    int fd;
    int queueSize;
};


TCPServerPrivate::TCPServerPrivate()
: fd(-1)
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
    bzero(&(sock_addr.sin_zero), 8);

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


std::auto_ptr<TCPSocket> TCPServer::accept()
{
    std::auto_ptr<TCPSocketPrivate> data(new TCPSocketPrivate);

    struct sockaddr_in sock_peer;
    socklen_t len = sizeof(sock_peer);
    data->fd = ::accept(d->fd, reinterpret_cast<sockaddr*>(&sock_peer), &len);

    if (data->fd < 0)
    {
        throw IOException("TCPServer::accept", strerror(errno));
    }

    data->peerAddress = convert(&sock_peer);

    return std::auto_ptr<TCPSocket>(new TCPSocket(data.release()));
}


} // namespace Pieces
