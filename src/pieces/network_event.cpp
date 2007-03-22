
#include "Pieces/NetworkEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

NetworkEvent::NetworkEvent(Type type, const SocketAddress& sender)
: Event()
, m_type(type)
, m_messageType(NO_MESSAGE_TYPE)
, m_data()
, m_sender(sender)
{
}


AutoPointer<Event> NetworkEvent::clone() const
{
    AutoPointer<NetworkEvent> event(new NetworkEvent(type(), getSenderAddress()));

    event->setMessageType(getMessageType());
    event->setData(getData());

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


void NetworkEvent::setMessageType(int messageType)
{
    m_messageType = messageType;
}


int NetworkEvent::getMessageType() const
{
    return m_messageType;
}


void NetworkEvent::setData(const ByteArray& data)
{
    m_data = data;
}


ByteArray NetworkEvent::getData() const
{
    return m_data;
}


NetworkEvent::~NetworkEvent()
{
}

} // namespace Pieces
