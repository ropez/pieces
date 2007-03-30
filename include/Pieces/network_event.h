
#ifndef PIECES_NETWORK_EVENT_H
#define PIECES_NETWORK_EVENT_H

#include "Pieces/Event"
#include "Pieces/SocketAddress"
#include "Pieces/Message"


namespace Pieces
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
     * Type of event.
     */
    enum Type
    {
        DISCONNECTED,
        RECEIVED_MESSAGE
    };

    /**
     * Default message types.
     *
     * TODO: Move to Message
     */
    enum MessageType
    {
        NO_MESSAGE_TYPE
    };

    /**
     * Creates an event of the given type, from the given sender.
     */
    NetworkEvent(Type type, const SocketAddress& sender);

    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

    /**
     * Returns the event type.
     */
    Type type() const;

    /**
     * Returns the address of the process that sent the event.
     */
    SocketAddress getSenderAddress() const;

    void setMessage(const Message& message);

    Message getMessage() const;

protected:
    virtual ~NetworkEvent();

private:
    DISABLE_COPY(NetworkEvent);

    Type m_type;
    SocketAddress m_sender;
    Message m_message;
};

} // namespace Pieces

#endif // PIECES_NETWORK_EVENT_H
