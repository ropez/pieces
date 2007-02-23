
#include "Pieces/EventLoop"

namespace Pieces
{

EventLoop::EventLoop()
: m_quit(false)
, m_queue()
{
}


EventLoop::~EventLoop()
{
}


void EventLoop::exec()
{
    while (true)
    {
        // TODO: Sleep while waiting for signal

        if (m_quit)
        {
            break;
        }

        // TODO: Critical section
        Event e = m_queue.front();
        m_queue.pop();
        // TODO: End critical section

        processEvent(e);
    }
}


void EventLoop::quit()
{
    m_quit = true;

    // TODO: Signal wake-up
}


void EventLoop::postEvent(const Event& e)
{
    // TODO: Critical section
    m_queue.push(e);

    // TODO: Signal wake-up
}


void EventLoop::processEvent(const Event&)
{
    // Do nothing here
}

} // namespace Pieces
