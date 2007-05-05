
#ifndef PIECES_DISCONNECTED_EVENT_H
#define PIECES_DISCONNECTED_EVENT_H

#include "Pieces/NetworkEvent"


namespace pcs
{

/**
 * \class DisconnectedEvent
 * \brief A network-disconnect event.
 *
 * A Host or Peer receives this event when a network connection is removed
 * from the ConnectionManager.
 *
 * \author Tord Heimdal
 */
class DisconnectedEvent : public NetworkEvent
{
    friend class AutoPointer<DisconnectedEvent>;

public:

    /**
     * Constructor.
     */
    DisconnectedEvent(const SocketAddress& sender);

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

protected:
    virtual ~DisconnectedEvent();

private:
    DISABLE_COPY(DisconnectedEvent);
};

} // namespace pcs

#endif // PIECES_DISCONNECTED_EVENT_H
