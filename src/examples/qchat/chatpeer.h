#ifndef CHATPEER_H
#define CHATPEER_H

#include <QtCore/QObject>
#include <Pieces/Peer>
#include <QtCore/QString>

namespace qchat
{

class ChatPeer : public QObject, public pcs::Peer
{
    Q_OBJECT

public:
    ChatPeer();

    void setNickName(const QString& nick);

    void sendChatMessage(const QString& msg);

signals:
    void message(const QString& nick, const QString& msg);

protected:
    virtual void handle(pcs::MessageReceivedEvent* event);

private:
    std::string m_nick;
};

}

#endif
