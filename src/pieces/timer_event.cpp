
#include "Pieces/TimerEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

TimerEvent::TimerEvent(int timerId)
: Event()
, m_timerId(timerId)
{
}


TimerEvent::~TimerEvent()
{
}


int TimerEvent::getTimerId() const
{
    return m_timerId;
}


void TimerEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}

} // namespace Pieces
