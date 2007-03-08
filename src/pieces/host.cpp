
#include "Pieces/Host"
#include "Pieces/Debug"
#include "Pieces/EventLoop"


namespace Pieces
{

Host::Host()
: EventHandler()
, m_eventLoop(0)
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


void Host::event(const Event& event)
{
    if (event.isUserDefined())
    {
        userDefinedEvent(event);
    }
}

} // namespace Pieces
