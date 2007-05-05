
#ifndef PIECES_NETWORK_EVENT_H
#define PIECES_NETWORK_EVENT_H

#include "Pieces/Event"
#include "Pieces/SocketAddress"
#include "Pieces/Message"


namespace pcs
{


/**
 * \class NetworkEvent network_event.h <Pieces/NetworkEvent>
 * \brief A network-specific event.
 *
 * This is a base class for network-related events. They all have the common
 * property that they contain the address that identifies the socket.
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

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h);

    /**
     * Returns the address of the process that sent the event.
     */
    SocketAddress getSenderAddress() const;

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~NetworkEvent();

private:
    DISABLE_COPY(NetworkEvent);

    SocketAddress m_sender;
};

} // namespace pcs

#endif // PIECES_NETWORK_EVENT_H
