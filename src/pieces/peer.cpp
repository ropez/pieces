
#include "Pieces/Peer"
#include "Pieces/Debug"
#include "Pieces/EventLoop"


namespace Pieces
{

class PeerPrivate
{
public:
    PeerPrivate();

    AutoPointer<EventLoop> eventLoop;
};


PeerPrivate::PeerPrivate()
: eventLoop(0)
{
}


Peer::Peer()
: EventHandler()
, d(new PeerPrivate)
{
    d->eventLoop = new EventLoop(this);
}


Peer::~Peer()
{
    delete d;
}


EventLoop* Peer::eventLoop()
{
    return d->eventLoop.get();
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
