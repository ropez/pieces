
#include "Pieces/EventHandler"
#include "Pieces/Event"
#include "Pieces/TimerEvent"
#include "Pieces/GameEvent"


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


void EventHandler::handle(GameEvent* event)
{
    // Fall back to default handler function
    Event* e = event;
    handle(e);
}

}
