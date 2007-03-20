
#ifndef PIECES_NETWORK_EVENT_H
#define PIECES_NETWORK_EVENT_H

#include "Pieces/Event"
#include "Pieces/SocketAddress"

namespace Pieces
{


/**
 * \class NetworkEvent
 * \brief A network-specific event.
 *
 *
 *
 *
 * \author Tord Heimdal
 */
class NetworkEvent : public Event
{
public:

    enum Type
    {
        DISCONNECTED,
        RECEIVED_MESSAGE
    };

    /**
     * Creates an event of the given type, from the given sender.
     */
    NetworkEvent(Type type, const SocketAddress& sender);

    /**
     * Returns the event type.
     */
    Type type() const;

    /**
     * Returns the address of the process that sent the event.
     */
    SocketAddress getSenderAddress() const;

protected:
    virtual ~NetworkEvent();

    virtual void dispatch(EventHandler* h);

private:
    Type m_type;
    SocketAddress m_sender;
};

} // namespace Pieces

#endif // PIECES_NETWORK_EVENT_H
