
#include "Pieces/EventFilter"
#include "Pieces/Event"


namespace pcs
{

EventFilter::EventFilter(EventHandler* nextHandler)
: m_nextHandler(nextHandler)
{
}


void EventFilter::handle(Event* event)
{
    event->dispatch(m_nextHandler);
}


} // namespace pcs
