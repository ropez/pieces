
#include "Pieces/EventHandler"
#include "Pieces/Event"
#include "Pieces/TimerEvent"
#include "Pieces/GameEvent"
#include "Pieces/NetworkEvent"
#include "Pieces/InputEvent"
#include "Pieces/GameDataEvent"


namespace Pieces
{

EventHandler::EventHandler()
{
}


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

void EventHandler::handle(NetworkEvent* event)
{
    // Fall back to default handler function
    Event* e = event;
    handle(e);
}

void EventHandler::handle(InputEvent* event)
{
    // Fall back to default handler function
    Event* e = event;
    handle(e);
}

void EventHandler::handle(GameDataEvent* event)
{
    // Fall back to default handler function
    Event* e = event;
    handle(e);
}

}
