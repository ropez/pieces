
#include "Pieces/MessageReceivedEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

MessageReceivedEvent::MessageReceivedEvent(const SocketAddress& sender, const msgpair_t& msg)
: NetworkEvent(sender)
, m_msg(msg)
{
}


AutoPointer<Event> MessageReceivedEvent::clone() const
{
    AutoPointer<MessageReceivedEvent> event(new MessageReceivedEvent(getSenderAddress(), m_msg));

    return AutoPointer<Event>(event);
}


void MessageReceivedEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


msgid_t MessageReceivedEvent::getMessageId() const
{
    return m_msg.first;
}


Message MessageReceivedEvent::getMessage() const
{
    return m_msg.second;
}


MessageReceivedEvent::~MessageReceivedEvent()
{
}

} // namespace Pieces
