
#include "NetworkEventFilter"
#include "Pieces/DisconnectedEvent"
#include "Pieces/Debug"
#include "Pieces/ConnectionManager"


namespace Pieces
{

NetworkEventFilter::NetworkEventFilter(EventHandler* nextHandler, ConnectionManager* manager)
: EventFilter(nextHandler)
, m_manager(manager)
{
}


void NetworkEventFilter::handle(DisconnectedEvent* event)
{
    PDEBUG << "Disconnected " << event->getSenderAddress();
    m_manager->remove(event->getSenderAddress());

    // Forward all events
    EventFilter::handle(event);
}

} // namespace Pieces
