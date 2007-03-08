
#include "Pieces/TimerEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

TimerEvent::TimerEvent()
: Event(TIMER_EVENT)
{
}


TimerEvent::~TimerEvent()
{
}


void TimerEvent::trigger(EventHandler* h)
{
    h->handle(this);
}

} // namespace Pieces
