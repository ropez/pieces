
#include "Pieces/DisconnectedEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

DisconnectedEvent::DisconnectedEvent(const SocketAddress& sender)
: NetworkEvent(sender)
{
}

AutoPointer<Event> DisconnectedEvent::clone() const
{
    AutoPointer<DisconnectedEvent> event(new DisconnectedEvent(getSenderAddress()));

    return AutoPointer<Event>(event);
}


void DisconnectedEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


DisconnectedEvent::~DisconnectedEvent()
{
}


} // namespace Pieces
