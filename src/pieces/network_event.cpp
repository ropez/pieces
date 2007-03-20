
#include "Pieces/NetworkEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

NetworkEvent::NetworkEvent(Type type, const SocketAddress& sender)
: Event()
, m_type(type)
, m_sender(sender)
{
}


NetworkEvent::Type NetworkEvent::type() const
{
    return m_type;
}


SocketAddress NetworkEvent::getSenderAddress() const
{
    return m_sender;
}


NetworkEvent::~NetworkEvent()
{
}


void NetworkEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}

} // namespace Pieces
