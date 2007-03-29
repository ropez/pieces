
#include "NetworkEventFilter"
#include "Pieces/NetworkEvent"
#include "Pieces/Debug"
#include "Pieces/ConnectionManager"


namespace Pieces
{

NetworkEventFilter::NetworkEventFilter(EventHandler* nextHandler, ConnectionManager* manager)
: EventFilter(nextHandler)
, m_manager(manager)
{
}


void NetworkEventFilter::handle(NetworkEvent* event)
{
    switch (event->type())
    {
    case NetworkEvent::DISCONNECTED:
        {
            PDEBUG << "Disconnected " << event->getSenderAddress();
            m_manager->remove(event->getSenderAddress());
        }
        break;
    default:
        break;
    }

    // Forward all events
    EventFilter::handle(event);
}

} // namespace Pieces
