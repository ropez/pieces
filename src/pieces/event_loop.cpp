
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
        Event e = m_queue->pop();

        // Check if this was a quit event
        if (e.type() == EVENT_QUIT)
            break;

        m_handler->event(e);
    }
}


void EventLoop::quit()
{
    m_queue->push(Event(EVENT_QUIT));
}


void EventLoop::postEvent(const Event& e)
{
    m_queue->push(e);
}

} // namespace Pieces
