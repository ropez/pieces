
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

    void setMessageType(int messageType);

    int getMessageType() const;

    void setData(const ByteArray& data);
    ByteArray getData() const;

protected:
    virtual ~NetworkEvent();

private:
    DISABLE_COPY(NetworkEvent);
    Type m_type;
    int m_messageType;
    ByteArray m_data;
    SocketAddress m_sender;
};

} // namespace Pieces

#endif // PIECES_NETWORK_EVENT_H
