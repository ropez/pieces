
#include "Pieces/EventLoop"
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


void EventLoop::exec()
{
    while (true)
    {
        // Block while waiting for event
        Event e = m_queue->pop();

        // TODO: Check if this was a quit event

        processEvent(e);
    }
}


void EventLoop::quit()
{
    // TODO: Push quit event
}


void EventLoop::postEvent(const Event& e)
{
    m_queue->push(e);
}


void EventLoop::processEvent(const Event&)
{
    // Do nothing here
}

} // namespace Pieces
