
#include "Pieces/EventLoop"
#include "Pieces/EventHandler"
#include "Pieces/EventQueue"


namespace Pieces
{

namespace
{
const int EVENT_QUIT = -1;
}

EventLoop::EventLoop(EventHandler* handler)
: m_handler(handler)
, m_queue(new EventQueue)
{
}


EventLoop::~EventLoop()
{
    quit();
    delete m_queue;
}


void EventLoop::exec()
{
    while (true)
    {
        // Block while waiting for event
        std::auto_ptr<Event> e = m_queue->pop();

        // Quit when popping a 0 pointer
        if (e.get() == 0)
            break;

        e->trigger(m_handler);
    }
}


void EventLoop::quit()
{
    m_queue->push(0);
}


void EventLoop::postEvent(Event* e)
{
    if (e != 0)
    {
        m_queue->push(e);
    }
}

} // namespace Pieces
