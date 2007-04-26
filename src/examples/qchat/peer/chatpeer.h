#ifndef CHATPEER_H
#define CHATPEER_H

#include <QtCore/QObject>
#include <Pieces/Peer>
#include <QtCore/QString>


class ChatPeer : public QObject, public Pieces::Peer
{
    Q_OBJECT

public:
    ChatPeer();

    void setNickName(const QString& nick);

    void sendChatMessage(const QString& msg);

signals:
    void message(const QString& msg);

protected:
    virtual void handle(Pieces::MessageReceivedEvent* event);

private:
    std::string m_nick;
};

#endif
