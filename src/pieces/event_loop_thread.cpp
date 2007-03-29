
#include "Pieces/EventLoopThread"
#include "Pieces/EventLoop"


namespace Pieces
{

EventLoopThread::EventLoopThread(EventHandler* handler)
: m_handler(handler)
, m_eventLoop(new EventLoop)
{
}


EventLoopThread::~EventLoopThread()
{
    m_eventLoop->quit();
    join();

    delete m_eventLoop;
}


EventLoop* EventLoopThread::eventLoop() const
{
    return m_eventLoop;
}


void EventLoopThread::run()
{
    m_eventLoop->exec(m_handler);
}

} // namespace Pieces
