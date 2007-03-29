
#include "Pieces/TCPConnectionManager"
#include "Pieces/TCPConnection"
#include "Pieces/TCPSocket"
#include "Pieces/TCPListenerThread"
#include "Pieces/SocketAddress"

#include "Pieces/EventLoop"

#include "Pieces/AutoPointer"
#include "Pieces/Exception"
#include "Pieces/Debug"

#include "OpenThreads/Thread"
#include <map>


namespace Pieces
{

class TCPConnectionManagerPrivate
{
public:
    TCPConnectionManagerPrivate();

    EventLoop* eventLoop;

    typedef std::map<SocketAddress, TCPConnection*> map_t;
    map_t connections;

    AutoPointer<TCPListenerThread> listener;
};


TCPConnectionManagerPrivate::TCPConnectionManagerPrivate()
: eventLoop(0)
, connections()
, listener(0)
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
        PERROR << e;
    }
}


void TCPConnectionManager::sendMessage(int messageType, const ByteArray& data)
{
    typedef TCPConnectionManagerPrivate::map_t::iterator iterator_t;

    for (iterator_t it = d->connections.begin(); it != d->connections.end(); ++it)
    {
        TCPConnection* conn = it->second;

        conn->sendMessage(messageType, data);
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
        PWARNING << "Refused connection, no peer address";
        return;
    }

    if (d->connections.find(address) != d->connections.end())
    {
        PWARNING << "Refused connection, already connected to that address";
        return;
    }

    // Start receiving network events on the event loop
    conn->startReceiver(d->eventLoop);

    d->connections[address] = conn.release();
}


void TCPConnectionManager::remove(const SocketAddress& address)
{
    typedef TCPConnectionManagerPrivate::map_t::iterator iterator_t;

    iterator_t it = d->connections.find(address);

    if (it != d->connections.end())
    {
        AutoPointer<TCPConnection> conn(it->second);
        d->connections.erase(it);

        // Connection is automatically deleted at the end of this scope.
        // Can do some final operations here, like sending goodbye message.
    }
}

} // namespace Pieces
