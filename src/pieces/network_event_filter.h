
#ifndef PIECES_NETWORK_EVENT_FILTER_H
#define PIECES_NETWORK_EVENT_FILTER_H

#include "Pieces/EventFilter"


namespace Pieces
{
class ConnectionManager;


/*
 * This class is used internally to handle network events.
 */
class NetworkEventFilter : public EventFilter
{
public:
    NetworkEventFilter(EventHandler* nextHandler, ConnectionManager* manager);

protected:
    virtual void handle(DisconnectedEvent* event);

private:
    DISABLE_COPY(NetworkEventFilter);

    ConnectionManager* m_manager;
};

} // namespace Pieces

#endif // PIECES_NETWORK_EVENT_FILTER_H
