
#include "Pieces/Host"
#include "Pieces/Debug"
#include "Pieces/EventLoop"


namespace Pieces
{

Host::Host()
: EventHandler()
, m_eventLoop(0)
, m_accepting(false)
{
    m_eventLoop = new EventLoop(this);
}


Host::~Host()
{
    delete m_eventLoop;
}


EventLoop* Host::eventLoop()
{
    return m_eventLoop;
}


void Host::exec()
{
    debug() << "Host running";
    eventLoop()->exec();
}


void Host::quit()
{
    debug() << "Host quitting";
    eventLoop()->quit();
}


bool Host::isAcceptingConnections() const
{
    return m_accepting;
}


void Host::setAcceptingConnections(bool v)
{
    // TODO: Do something with listening socket, or just keep it listening?
    m_accepting = v;
}


void Host::handle(Event* event)
{
    if (event->isUserDefined())
    {
        userDefinedEvent(event);
    }
}


void Host::handle(TimerEvent* /*event*/)
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
