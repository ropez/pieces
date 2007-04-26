
#include "Pieces/TCPConnectionManager"
#include "Pieces/TCPConnection"
#include "Pieces/TCPSocket"
#include "Pieces/TCPListenerThread"
#include "Pieces/SocketAddress"
#include "Pieces/Message"

#include "Pieces/EventLoop"

#include "Pieces/AutoPointer"
#include "Pieces/Exception"
#include "Pieces/InvalidKeyException"
#include "Pieces/Debug"

#include "OpenThreads/Thread"
#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"

#include <map>
#include <algorithm>


namespace pcs
{

using namespace OpenThreads;

class TCPConnectionManagerPrivate
{
public:
    TCPConnectionManagerPrivate();

    Mutex mutex;

    std::deque<msgpair_t>::iterator findId(msgid_t id);

    EventLoop* eventLoop;

    typedef std::map<SocketAddress, TCPConnection*> map_t;
    map_t connections;

    // History of messages that has been sent.
    // These are all sent to peers that connects to the host.
    std::deque<msgpair_t> messages;

    // Message id counter, increased by one before every new message is added
    msgid_t countId;

    AutoPointer<TCPListenerThread> listener;
};


TCPConnectionManagerPrivate::TCPConnectionManagerPrivate()
: mutex()
, eventLoop(0)
, connections()
, messages()
, countId(0)
, listener(0)
{
}


std::deque<msgpair_t>::iterator TCPConnectionManagerPrivate::findId(msgid_t id)
{
    // Comparison function
    MessageIdLess comp;

    // Binary search
    std::deque<msgpair_t>::iterator it = std::lower_bound(messages.begin(), messages.end(), id, comp);
    if (it != messages.end() && (*it).first == id)
    {
        // Found
        return it;
    }
    else
    {
        // Not found
        return messages.end();
    }
}


TCPConnectionManager::TCPConnectionManager(EventLoop* eventLoop)
: d(new TCPConnectionManagerPrivate)
{
    d->eventLoop = eventLoop;
}


TCPConnectionManager::~TCPConnectionManager()
{
    typedef TCPConnectionManagerPrivate::map_t::iterator iterator_t;

    // Delete all remaining connections
    for (iterator_t it = d->connections.begin(); it != d->connections.end(); ++it)
    {
        AutoPointer<TCPConnection> conn(it->second);
        it->second = 0;
    }

    delete d;
}


void TCPConnectionManager::startListening(port_t port)
{
    ScopedLock<Mutex> lock(d->mutex);

    d->listener = new TCPListenerThread(port, this);
    d->listener->start();
}


void TCPConnectionManager::stopListening()
{
    ScopedLock<Mutex> lock(d->mutex);

    // Stop and delete listener thread by replacing auto-pointer
    d->listener = 0;
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


msgid_t TCPConnectionManager::sendMessage(const Message& message)
{
    return sendMessage(message, 0);
}


msgid_t TCPConnectionManager::sendMessage(const Message& message, msgid_t originalId)
{
    typedef TCPConnectionManagerPrivate::map_t::iterator iterator_t;

    ScopedLock<Mutex> lock(d->mutex);

    msgpair_t msg(++d->countId, message);

    for (iterator_t it = d->connections.begin(); it != d->connections.end(); ++it)
    {
        TCPConnection* conn = it->second;

        conn->sendMessage(msg);
    }

    if (message.getFlags() & Message::FL_PERMANENT)
    {
        // Add to buffer, so that future connections get the message
        std::deque<msgpair_t>::iterator it = d->findId(originalId);
        if (it != d->messages.end())
        {
            // Remove original message from history
            d->messages.erase(it);
        }
        else
        {
            // Add message to history
            d->messages.push_back(msg);
        }
    }

    return d->countId;
}


void TCPConnectionManager::add(TCPConnection* connection)
{
    // Make sure we take ownership, in case the connection is refused
    AutoPointer<TCPConnection> conn(connection);

    ScopedLock<Mutex> lock(d->mutex);

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
    conn->startReceiving(d->eventLoop);
    conn->startSending(d->messages);

    d->connections[address] = conn.release();
}


void TCPConnectionManager::remove(const SocketAddress& address)
{
    typedef TCPConnectionManagerPrivate::map_t::iterator iterator_t;

    ScopedLock<Mutex> lock(d->mutex);

    iterator_t it = d->connections.find(address);

    if (it == d->connections.end())
        throw InvalidKeyException("TCPConnectionManager::remove", "Address not found");

    AutoPointer<TCPConnection> conn(it->second);
    d->connections.erase(it);

    // Connection is automatically deleted at the end of this scope.
    // Can do some final operations here, like sending goodbye message.
}

} // namespace pcs
