
#include "Pieces/EventLoop"
#include "Pieces/EventHandler"
#include "Pieces/EventQueue"
#include "Pieces/Debug"


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

        // Check if this was a quit event
        if (e->type() == EVENT_QUIT)
            break;

        m_handler->event(e.get());
    }
}


void EventLoop::quit()
{
    m_queue->push(new Event(EVENT_QUIT));
}


void EventLoop::postEvent(Event* e)
{
    m_queue->push(e);
}

} // namespace Pieces
