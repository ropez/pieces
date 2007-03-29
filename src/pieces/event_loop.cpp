
#include "Pieces/EventLoop"
#include "Pieces/EventHandler"
#include "Pieces/EventQueue"


namespace Pieces
{

EventLoop::EventLoop()
: m_queue(new EventQueue)
{
}


EventLoop::~EventLoop()
{
    quit();
    delete m_queue;
}


void EventLoop::exec(EventHandler* handler)
{
    for (;;)
    {
        // Block while waiting for event
        AutoPointer<Event> e = m_queue->pop();

        // Quit when popping a 0 pointer
        if (e.isNull())
            break;

        // Dispatch the event to the correct event-handler function
        e->dispatch(handler);
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
