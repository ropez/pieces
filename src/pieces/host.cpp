
#include "Pieces/Host"
#include "Pieces/Debug"
#include "Pieces/EventLoop"
#include "Pieces/TCPConnectionManager"


namespace Pieces
{

Host::Host()
: EventHandler()
, m_eventLoop(0)
, m_connectionManager(0)
, m_accepting(false)
{
    m_eventLoop = new EventLoop(this);
    m_connectionManager = new TCPConnectionManager(m_eventLoop);
}


Host::~Host()
{
    delete m_eventLoop;
    delete m_connectionManager;
}


EventLoop* Host::eventLoop() const
{
    return m_eventLoop;
}


TCPConnectionManager* Host::connectionManager() const
{
    return m_connectionManager;
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
    return m_accepting;
}


void Host::setAcceptingConnections(bool v)
{
    // TODO: Do something with listening socket, or just keep it listening?
    m_accepting = v;
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
