#include "../src/global.h"
#include "chathost.h"

#include <Pieces/MessageReceivedEvent>
#include <Pieces/Debug>

using namespace Pieces;


ChatHost::ChatHost()
: Host()
{
}


void ChatHost::handle(MessageReceivedEvent* event)
{
    Message message = event->getMessage();

    if (message.getMessageType() == TYPE_CHAT_MESSAGE)
    {
        message.setFlags(Message::FL_PERMANENT);

        // Send to all peers
        sendMessage(message);
    }
}
