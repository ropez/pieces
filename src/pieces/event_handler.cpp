
#include "Pieces/EventHandler"
#include "Pieces/Event"
#include "Pieces/TimerEvent"
#include "Pieces/GameEvent"
#include "Pieces/NetworkEvent"
#include "Pieces/MessageReceivedEvent"
#include "Pieces/ConnectedEvent"
#include "Pieces/DisconnectedEvent"
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

void EventHandler::handle(MessageReceivedEvent* event)
{
    // Fall back to default handler function
    NetworkEvent* e = event;
    handle(e);
}

void EventHandler::handle(ConnectedEvent* event)
{
    // Fall back to default handler function
    NetworkEvent* e = event;
    handle(e);
}

void EventHandler::handle(DisconnectedEvent* event)
{
    // Fall back to default handler function
    NetworkEvent* e = event;
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
