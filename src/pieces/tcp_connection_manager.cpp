
#include "Pieces/TCPConnectionManager"
#include "Pieces/TCPConnection"
#include "Pieces/TCPSocket"
#include "Pieces/TCPListenerThread"
#include "Pieces/SocketAddress"
#include "Pieces/AutoPointer"
#include "Pieces/Exception"
#include "Pieces/Debug"

#include <map>


namespace Pieces
{

class TCPConnectionManagerPrivate
{
public:
    TCPConnectionManagerPrivate();

    typedef std::map<SocketAddress, TCPConnection*> map_t;
    map_t connections;

    AutoPointer<TCPListenerThread> listener;

    EventLoop* eventLoop;
};


TCPConnectionManagerPrivate::TCPConnectionManagerPrivate()
: connections()
, listener(0)
, eventLoop(0)
{
}


TCPConnectionManager::TCPConnectionManager(EventLoop* eventLoop)
: d(new TCPConnectionManagerPrivate)
{
    d->eventLoop = eventLoop;
}


TCPConnectionManager::~TCPConnectionManager()
{
    delete d;
}


void TCPConnectionManager::listen(port_t port)
{
    d->listener = new TCPListenerThread(port, this);
    d->listener->start();
}


void TCPConnectionManager::connectTo(const SocketAddress& address)
{
    // TODO: Fire up a thread to do this in the background, post event when connected

    try
    {
        AutoPointer<TCPSocket> sock(new TCPSocket);

        if (sock->connect(address))
        {
            add(new TCPConnection(sock.release()));
        }
    }
    catch (const Exception& e)
    {
        ERROR << e;
    }
}


void TCPConnectionManager::add(TCPConnection* connection)
{
    // Make sure we take ownership, in case the connection is refused
    AutoPointer<TCPConnection> conn(connection);

    // Test address
    SocketAddress address = conn->getPeerAddress();
    if (address.isNull())
    {
        WARNING << "Refused connection, no peer address";
        return;
    }

    if (d->connections.find(address) != d->connections.end())
    {
        WARNING << "Refused connection, already connected to that address";
    }

    // TODO: This is probably not the correct place to start receiving events
    conn->startReceiver(d->eventLoop);

    d->connections[address] = conn.release();
}


void TCPConnectionManager::remove(const SocketAddress& address)
{
    TCPConnectionManagerPrivate::map_t::iterator it = d->connections.find(address);

    if (it != d->connections.end())
    {
        AutoPointer<TCPConnection> conn(it->second);
        d->connections.erase(it);

        // Connection is automatically deleted at the end of this scope.
        // Can do some final operations here, like sending goodbye message.
    }
}

} // namespace Pieces
