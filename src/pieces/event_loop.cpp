
#include "Pieces/EventLoop"
#include "Pieces/EventHandler"
#include "Pieces/EventQueue"
#include "Pieces/Exception"
#include "Pieces/Debug"


namespace pcs
{

EventLoop::EventLoop()
: m_queue(new EventQueue)
{
}


EventLoop::~EventLoop()
{
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

        try
        {
            // Dispatch the event to the correct event-handler function
            e->dispatch(handler);
        }
        catch (const Exception& e)
        {
            PERROR << "Unhandled exception in event handler: " << e;
        }
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

} // namespace pcs
