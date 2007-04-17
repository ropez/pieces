
#include "Pieces/TimerEvent"
#include "Pieces/EventHandler"


namespace pcs
{

TimerEvent::TimerEvent(int timerId)
: Event()
, m_timerId(timerId)
{
}


TimerEvent::~TimerEvent()
{
}


AutoPointer<Event> TimerEvent::clone() const
{
    AutoPointer<TimerEvent> event(new TimerEvent(getTimerId()));

    return AutoPointer<Event>(event);
}


void TimerEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


int TimerEvent::getTimerId() const
{
    return m_timerId;
}

} // namespace pcs
