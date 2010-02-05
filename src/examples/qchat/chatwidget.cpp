#include <QtGui>

#include <Pieces/AutoPointer>
#include <Pieces/HostThread>
#include <Pieces/PeerThread>
#include <Pieces/SocketAddress>
#include <Pieces/Debug>

#include "chatwidget.h"
#include "chathost.h"
#include "chatpeer.h"


class ChatWidgetPrivate
{
public:
    ChatWidgetPrivate();

    pcs::AutoPointer<ChatHost> host;
    pcs::AutoPointer<ChatPeer> peer;

    pcs::AutoPointer<pcs::HostThread> thHost;
    pcs::AutoPointer<pcs::PeerThread> thPeer;

    QListWidget* list;
    QLineEdit* line;
    QPushButton* button;
};


ChatWidgetPrivate::ChatWidgetPrivate()
: host(0)
, peer(0)
, list(0)
, line(0)
, button(0)
{
}


ChatWidget::ChatWidget(QWidget* parent)
: QWidget(parent)
, d(new ChatWidgetPrivate())
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    d->list = new QListWidget();
    layout->addWidget(d->list);

    d->line = new QLineEdit();
    layout->addWidget(d->line);

    d->button = new QPushButton(tr("Send"));
    layout->addWidget(d->button);

    connect(d->button, SIGNAL(clicked()), this, SLOT(send()));
    connect(d->line, SIGNAL(returnPressed()), this, SLOT(send()));
}


ChatWidget::~ChatWidget()
{
}


void ChatWidget::startChat(const QString& nick, const QString& host, quint16 port)
{
    d->peer = new ChatPeer();
    d->peer->setNickName(nick);

    if (host.isEmpty())
    {
        // Start host
        d->host = new ChatHost();
        d->host->startListening(port);

        d->thHost = new pcs::HostThread(d->host.get());
        d->thHost->start();

        // Connect to localhost
        pcs::SocketAddress address(pcs::InetAddress::getHostByName("localhost"), port);

        d->peer->connectTo(address);
    }
    else
    {
        // Connect to a different host
        pcs::SocketAddress address(pcs::InetAddress::getHostByName(host.toStdString()), port);

        PDEBUG << "Connecting to " << address;

        d->peer->connectTo(address);
    }

    connect(d->peer.get(), SIGNAL(message(const QString&, const QString&)), this, SLOT(showMessage(const QString&, const QString&)));

    d->thPeer = new pcs::PeerThread(d->peer.get());
    d->thPeer->start();

    show();
}


void ChatWidget::showMessage(const QString& nick, const QString& msg)
{
    d->list->addItem(nick + ": " + msg);
}


void ChatWidget::send()
{
    d->peer->sendChatMessage(d->line->text());
    d->line->clear();
}

