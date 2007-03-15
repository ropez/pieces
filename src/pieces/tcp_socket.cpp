
#include "Pieces/TCPSocket"
#include "Pieces/TCPServer"
#include "Pieces/InetAddress"
#include "Pieces/IOException"

#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


namespace Pieces
{


class TCPSocketPrivate
{
public:

    // Default constructor.
    TCPSocketPrivate();

    // connect socket to address
    bool connect(const InetAddress& addr, int port);

    int fd;
//     struct sockaddr_in sock_self;
    struct sockaddr_in sock_peer;
};

TCPSocketPrivate::TCPSocketPrivate()
: fd(-1)
{
//     // Setup address struct used by OS API
//     m_sock_self.sin_family = AF_INET;
//     m_sock_self.sin_port = htons(0);
//     m_sock_self.sin_addr.s_addr = INADDR_ANY;
//     bzero(&(m_sock_self.sin_zero), 8);
}


bool TCPSocketPrivate::connect(const InetAddress& addr, int port)
{
    // set up address struct used
    sock_peer.sin_family = AF_INET;
    sock_peer.sin_port = htons(port);
    sock_peer.sin_addr.s_addr = htonl(addr.get());
    bzero(&(sock_peer.sin_zero), 8);

    // call connect
    int ret = ::connect(fd, reinterpret_cast<sockaddr*>(&sock_peer) , sizeof(sock_peer));

    if (ret < 0)
        return false;

    return true;
}


TCPSocket::TCPSocket()
: d(new TCPSocketPrivate)
{
    // Create standard tcp socket file descriptor.
    d->fd = ::socket(AF_INET, SOCK_STREAM, 0);

    // Error checking
    if(d->fd < 0)
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
    delete d;
}

void TCPSocket::close()
{
    ::close(d->fd);
}

bool TCPSocket::connect(const SocketAddress& addr)
{
    return d->connect(addr.getInetAddress(), addr.getPort());
}

bool TCPSocket::connect(const InetAddress& addr, int port)
{
    return d->connect(addr, port);
}



ByteArray TCPSocket::read()
{
    ByteArray ba(0x100000);

    size_t size = ::read(d->fd, ba.data(), ba.size());

    if (size == 0)
    {
        // Disconnected
        throw IOException();
    }

    ba.resize(size);
    return ba;
}


void TCPSocket::write(const ByteArray& data)
{
    ::write(d->fd, data.data(), data.size());
}



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
    sockaddr_in remoteAddr;
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(addr.getPort());
    remoteAddr.sin_addr.s_addr = htonl(addr.getInetAddress().get());
    bzero(&(remoteAddr.sin_zero), 8);

    ::bind(d->fd, reinterpret_cast<sockaddr*>(&remoteAddr), sizeof(remoteAddr));
    ::listen(d->fd, d->queueSize);
}


std::auto_ptr<TCPSocket> TCPServer::accept()
{
    std::auto_ptr<TCPSocketPrivate> data(new TCPSocketPrivate);

    socklen_t len = sizeof(data->sock_peer);
    data->fd = ::accept(d->fd, reinterpret_cast<sockaddr*>(&data->sock_peer), &len);

    if (data->fd < 0)
    {
        throw IOException("TCPServer::accept", strerror(errno));
    }

    return std::auto_ptr<TCPSocket>(new TCPSocket(data.release()));
}


} // namespace Pieces
