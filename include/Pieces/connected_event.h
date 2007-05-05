
#ifndef PIECES_CONNECTED_EVENT_H
#define PIECES_CONNECTED_EVENT_H

#include "Pieces/NetworkEvent"


namespace pcs
{

/**
 * \class ConnectedEvent connected_event.h <Pieces/ConnectedEvent>
 * \brief A network-connect event.
 *
 * Both the Host and the Peer receives a ConnectedEvent after a new connection
 * is added to the ConnectionManager.
 *
 * \todo This is not implemented.
 *
 * \author Tord Heimdal
 */
class ConnectedEvent : public NetworkEvent
{
    friend class AutoPointer<ConnectedEvent>;

public:

    /**
     * Constructor.
     */
    ConnectedEvent(const SocketAddress& sender);

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h);

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~ConnectedEvent();


private:
    DISABLE_COPY(ConnectedEvent);
};

} // namespace pcs

#endif // PIECES_CONNECTED_EVENT_H
