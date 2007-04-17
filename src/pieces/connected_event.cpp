
#include "Pieces/ConnectedEvent"
#include "Pieces/EventHandler"


namespace pcs
{

ConnectedEvent::ConnectedEvent(const SocketAddress& sender)
: NetworkEvent(sender)
{
}


AutoPointer<Event> ConnectedEvent::clone() const
{
    AutoPointer<ConnectedEvent> event(new ConnectedEvent(getSenderAddress()));

    return AutoPointer<Event>(event);
}


void ConnectedEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


ConnectedEvent::~ConnectedEvent()
{
}

} // namespace pcs
