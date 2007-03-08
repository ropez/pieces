
#include "Pieces/TimerEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

TimerEvent::TimerEvent()
: Event()
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
