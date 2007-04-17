
#ifndef PIECES_MESSAGE_RECEIVED_EVENT_H
#define PIECES_MESSAGE_RECEIVED_EVENT_H

#include "Pieces/NetworkEvent"
#include "Pieces/Message"


namespace pcs
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
    MessageReceivedEvent(const SocketAddress& sender, const msgpair_t& msg);

    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

    msgid_t getMessageId() const;
    Message getMessage() const;

protected:

    virtual ~MessageReceivedEvent();


private:
    DISABLE_COPY(MessageReceivedEvent);
    msgpair_t m_msg;
};

} // namespace pcs

#endif // PIECES_MESSAGE_RECEIVED_EVENT_H
