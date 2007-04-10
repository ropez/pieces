
#include "Pieces/MessageReceivedEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

MessageReceivedEvent::MessageReceivedEvent(const SocketAddress& sender)
: NetworkEvent(sender)
, m_message()
{
}


AutoPointer<Event> MessageReceivedEvent::clone() const
{
    AutoPointer<MessageReceivedEvent> event(new MessageReceivedEvent(getSenderAddress()));

    event->setMessage(getMessage());

    return AutoPointer<Event>(event);
}


void MessageReceivedEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


void MessageReceivedEvent::setMessage(const Message& message)
{
    m_message = message;
}


Message MessageReceivedEvent::getMessage() const
{
    return m_message;
}


MessageReceivedEvent::~MessageReceivedEvent()
{
}

} // namespace Pieces
