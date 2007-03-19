
#include "Pieces/NetworkEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

NetworkEvent::NetworkEvent(int type)
: Event()
, m_type(type)
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


NetworkEvent::~NetworkEvent()
{
}


void NetworkEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}

} // namespace Pieces
