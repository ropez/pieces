
#include "Pieces/Host"
#include "Pieces/Debug"
#include "Pieces/EventLoop"
#include "Pieces/TCPConnectionManager"


namespace Pieces
{

class HostPrivate
{
public:
    HostPrivate();

    AutoPointer<EventLoop> eventLoop;
    AutoPointer<TCPConnectionManager> connectionManager;

    bool accepting;
};


HostPrivate::HostPrivate()
: eventLoop(0)
, connectionManager(0)
, accepting(false)
{
}


Host::Host()
: EventHandler()
, d(new HostPrivate)
{
    d->eventLoop = new EventLoop(this);
    d->connectionManager = new TCPConnectionManager(eventLoop());
}


Host::~Host()
{
    delete d;
}


EventLoop* Host::eventLoop() const
{
    return d->eventLoop.get();
}


TCPConnectionManager* Host::connectionManager() const
{
    return d->connectionManager.get();
}


void Host::postEvent(Event* e)
{
    eventLoop()->postEvent(e);
}


void Host::exec()
{
    DEBUG << "Host running";
    eventLoop()->exec();
}


void Host::quit()
{
    DEBUG << "Host quitting";
    eventLoop()->quit();
}


bool Host::isAcceptingConnections() const
{
    return d->accepting;
}


void Host::setAcceptingConnections(bool v)
{
    // TODO: Do something with listening socket, or just keep it listening?
    d->accepting = v;
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
