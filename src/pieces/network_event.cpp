
#include "Pieces/NetworkEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

NetworkEvent::NetworkEvent(Type type, const SocketAddress& sender)
: Event()
, m_type(type)
, m_sender(sender)
, m_message()
{
}


AutoPointer<Event> NetworkEvent::clone() const
{
    AutoPointer<NetworkEvent> event(new NetworkEvent(type(), getSenderAddress()));

    event->setMessage(getMessage());

    return AutoPointer<Event>(event);
}


void NetworkEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


NetworkEvent::Type NetworkEvent::type() const
{
    return m_type;
}


SocketAddress NetworkEvent::getSenderAddress() const
{
    return m_sender;
}


void NetworkEvent::setMessage(const Message& message)
{
    m_message = message;
}


Message NetworkEvent::getMessage() const
{
    return m_message;
}


NetworkEvent::~NetworkEvent()
{
}

} // namespace Pieces
