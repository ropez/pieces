
#include "Pieces/Peer"
#include "Pieces/Debug"
#include "Pieces/EventLoop"


namespace Pieces
{

Peer::Peer()
: EventHandler()
, m_eventLoop(0)
{
    m_eventLoop = new EventLoop(this);
}

Peer::~Peer()
{
    delete m_eventLoop;
}

EventLoop* Peer::eventLoop()
{
    return m_eventLoop;
}

void Peer::exec()
{
    debug() << "Peer running";
    eventLoop()->exec();
}


void Peer::quit()
{
    debug() << "Peer quitting";
    eventLoop()->quit();
}


void Peer::event(Event* /*event*/)
{
}

}
