
#include "Pieces/NetworkEvent"
#include "Pieces/EventHandler"


namespace pcs
{

NetworkEvent::NetworkEvent(const SocketAddress& sender)
: Event()
, m_sender(sender)
{
}


AutoPointer<Event> NetworkEvent::clone() const
{
    AutoPointer<NetworkEvent> event(new NetworkEvent(getSenderAddress()));

    return AutoPointer<Event>(event);
}


void NetworkEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


SocketAddress NetworkEvent::getSenderAddress() const
{
    return m_sender;
}


NetworkEvent::~NetworkEvent()
{
}

} // namespace pcs
