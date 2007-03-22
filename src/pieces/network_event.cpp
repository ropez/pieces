
#include "Pieces/NetworkEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

NetworkEvent::NetworkEvent(Type type, const SocketAddress& sender)
: Event()
, m_type(type)
, m_messageType(NO_MESSAGE_TYPE)
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


void NetworkEvent::setMessageType(int messageType)
{
    m_messageType = messageType;
}


int NetworkEvent::getMessageType() const
{
    return m_messageType;
}


NetworkEvent::~NetworkEvent()
{
}


void NetworkEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}

} // namespace Pieces
