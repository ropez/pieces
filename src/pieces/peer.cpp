
#include "Pieces/Peer"
#include "Pieces/Debug"
#include "Pieces/EventLoop"
#include "Pieces/TCPConnectionManager"


namespace Pieces
{

class PeerPrivate
{
public:
    PeerPrivate();

    AutoPointer<EventLoop> eventLoop;
    AutoPointer<TCPConnectionManager> connectionManager;
};


PeerPrivate::PeerPrivate()
: eventLoop(0)
, connectionManager(0)
{
}


Peer::Peer()
: EventHandler()
, d(new PeerPrivate)
{
    d->eventLoop = new EventLoop(this);
    d->connectionManager = new TCPConnectionManager(eventLoop());
}


Peer::~Peer()
{
    delete d;
}


EventLoop* Peer::eventLoop()
{
    return d->eventLoop.get();
}


ConnectionManager* Peer::connectionManager() const
{
    return d->connectionManager.get();
}


void Peer::postEvent(Event* e)
{
    eventLoop()->postEvent(e);
}


void Peer::exec()
{
    DEBUG << "Peer running";
    eventLoop()->exec();
}


void Peer::quit()
{
    DEBUG << "Peer quitting";
    eventLoop()->quit();
}


void Peer::handle(Event*)
{
}

}
