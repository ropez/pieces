#include "global.h"
#include "chatpeer.h"
#include "chatwidget.h"

#include <Pieces/MessageReceivedEvent>
#include <Pieces/Debug>

using namespace pcs;

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

    message.set(PR_CHAT_NICK, m_nick);
    message.set(PR_CHAT_TEXT, msg.toStdString());

    sendMessage(message);
}


void ChatPeer::handle(MessageReceivedEvent* event)
{
    Message m = event->getMessage();

    if (m.getMessageType() == TYPE_CHAT_MESSAGE)
    {
        std::string nick = m.get<std::string>(PR_CHAT_NICK);
        std::string msg = m.get<std::string>(PR_CHAT_TEXT);

        emit message(QString::fromStdString(nick), QString::fromStdString(msg));
    }
}
