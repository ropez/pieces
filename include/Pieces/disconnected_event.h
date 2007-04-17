
#ifndef PIECES_DISCONNECTED_EVENT_H
#define PIECES_DISCONNECTED_EVENT_H

#include "Pieces/NetworkEvent"


namespace pcs
{

/**
 * \class DisconnectedEvent
 * \brief A network-disconnect event.
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

    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

protected:
    virtual ~DisconnectedEvent();

private:
    DISABLE_COPY(DisconnectedEvent);
};

} // namespace pcs

#endif // PIECES_DISCONNECTED_EVENT_H
