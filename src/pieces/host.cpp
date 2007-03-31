
#include "Pieces/Host"
#include "Pieces/Debug"
#include "Pieces/EventLoop"
#include "Pieces/GameDataSender"
#include "Pieces/TCPConnectionManager"

#include "NetworkEventFilter"



namespace Pieces
{

class HostPrivate
{
public:
    HostPrivate();

    AutoPointer<EventLoop> eventLoop;
    AutoPointer<TCPConnectionManager> connectionManager;
    AutoPointer<GameDataSender> sender;

    AutoPointer<NetworkEventFilter> networkEventFilter;
};


HostPrivate::HostPrivate()
: eventLoop(0)
, connectionManager(0)
, sender(0)
, networkEventFilter(0)
{
}


Host::Host()
: EventHandler()
, d(new HostPrivate)
{
    d->eventLoop = new EventLoop();
    d->connectionManager = new TCPConnectionManager(eventLoop());
    d->networkEventFilter = new NetworkEventFilter(this, d->connectionManager.get());
}


Host::~Host()
{
    delete d;
}


EventLoop* Host::eventLoop() const
{
    return d->eventLoop.get();
}


ConnectionManager* Host::connectionManager() const
{
    return d->connectionManager.get();
}


GameDataSender* Host::sender()
{
    // Lazy instantiation
    if (d->sender.isNull())
    {
        d->sender = new GameDataSender();
    }
    return d->sender.get();
}


void Host::startListening(port_t port)
{
    connectionManager()->startListening(port);
}


void Host::stopListening()
{
    connectionManager()->stopListening();
}


void Host::postEvent(Event* e)
{
    eventLoop()->postEvent(e);
}


void Host::exec()
{
    PDEBUG << "Host running";
    eventLoop()->exec(d->networkEventFilter.get());
}


void Host::quit()
{
    PDEBUG << "Host quitting";
    eventLoop()->quit();
}


void Host::handle(Event* /*event*/)
{
}


void Host::peerConnected(PeerInfo* /*info*/)
{
    // TODO: Anything to do if user haven't implemented this?
}


void Host::peerDisconnected(PeerInfo* /*info*/)
{
    // TODO: Anything to do if user haven't implemented this?
}

} // namespace Pieces
