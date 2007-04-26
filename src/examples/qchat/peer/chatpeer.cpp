#include "global.h"
#include "chatpeer.h"
#include "chatwidget.h"

#include <Pieces/MessageReceivedEvent>
#include <Pieces/Debug>

using namespace Pieces;

ChatWidget* widget;


ChatPeer::ChatPeer()
: Peer()
, m_nick()
{
}

void ChatPeer::setNickName(const QString& nick)
{
    m_nick = nick.toStdString();
}


void ChatPeer::sendChatMessage(const QString& msg)
{
    Message message(TYPE_CHAT_MESSAGE);

    message.set(PR_CHAT_TEXT, msg.toStdString());

    sendMessage(message);
}

void ChatPeer::handle(MessageReceivedEvent* event)
{
    Message m = event->getMessage();

    if (m.getMessageType() == TYPE_CHAT_MESSAGE)
    {
        std::string msg = m.get<std::string>(PR_CHAT_TEXT);

        emit message(QString::fromStdString(msg));
    }
}
