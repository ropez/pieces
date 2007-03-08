
#include "Pieces/EventHandler"
#include "Pieces/Event"
#include "Pieces/TimerEvent"


namespace Pieces
{

EventHandler::~EventHandler()
{
}


void EventHandler::handle(Event*)
{
}


void EventHandler::handle(TimerEvent* event)
{
    // Fall back to default handler function
    Event* e = event;
    handle(e);
}

}
