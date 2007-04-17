
#ifndef PIECES_NETWORK_EVENT_H
#define PIECES_NETWORK_EVENT_H

#include "Pieces/Event"
#include "Pieces/SocketAddress"
#include "Pieces/Message"


namespace pcs
{


/**
 * \class NetworkEvent
 * \brief A network-specific event.
 *
 * \author Tord Heimdal
 */
class NetworkEvent : public Event
{
    friend class AutoPointer<NetworkEvent>;

public:

    /**
     * Creates an event of the given type, from the given sender.
     */
    NetworkEvent(const SocketAddress& sender);

    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

    /**
     * Returns the address of the process that sent the event.
     */
    SocketAddress getSenderAddress() const;

protected:
    virtual ~NetworkEvent();

private:
    DISABLE_COPY(NetworkEvent);

    SocketAddress m_sender;
};

} // namespace pcs

#endif // PIECES_NETWORK_EVENT_H
