
#include "Pieces/NetworkEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

NetworkEvent::NetworkEvent(int type, const SocketAddress& sender)
: Event()
, m_type(type)
, m_sender(sender)
{
}


int NetworkEvent::type() const
{
    return m_type;
}


void NetworkEvent::setType(int type)
{
    m_type = type;
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
