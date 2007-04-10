
#ifndef PIECES_MESSAGE_RECEIVED_EVENT_H
#define PIECES_MESSAGE_RECEIVED_EVENT_H

#include "Pieces/NetworkEvent"
#include "Pieces/Message"


namespace Pieces
{

/**
 * \class DisconnectedEvent
 * \brief A network-message received event.
 *
 * \author Tord Heimdal
 */
class MessageReceivedEvent : public NetworkEvent
{
    friend class AutoPointer<MessageReceivedEvent>;

public:

    /**
     * Constructor.
     */
    MessageReceivedEvent(const SocketAddress& sender);

public:

    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

    void setMessage(const Message& message);

    Message getMessage() const;

protected:

    virtual ~MessageReceivedEvent();


private:
    DISABLE_COPY(MessageReceivedEvent);
    Message m_message;
};

} // namespace Pieces

#endif // PIECES_MESSAGE_RECEIVED_EVENT_H
