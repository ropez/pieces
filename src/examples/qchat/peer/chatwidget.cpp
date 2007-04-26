#include <QtGui>

#include "chatwidget.h"
#include "chatpeer.h"


class ChatWidgetPrivate
{
public:
    ChatWidgetPrivate();

    ChatPeer* peer;

    QListWidget* list;
    QLineEdit* line;
    QPushButton* button;
};


ChatWidgetPrivate::ChatWidgetPrivate()
: peer(0)
, list(0)
, line(0)
, button(0)
{
}


ChatWidget::ChatWidget(ChatPeer* peer, QWidget* parent)
: QWidget(parent)
, d(new ChatWidgetPrivate())
{
    d->peer = peer;

    QVBoxLayout* layout = new QVBoxLayout(this);

    d->list = new QListWidget();
    layout->addWidget(d->list);

    d->line = new QLineEdit();
    layout->addWidget(d->line);

    d->button = new QPushButton(tr("Send"));
    layout->addWidget(d->button);

    connect(d->button, SIGNAL(clicked()), this, SLOT(send()));
}


ChatWidget::~ChatWidget()
{
}


void ChatWidget::showMessage(const QString& msg)
{
    d->list->addItem(msg);
}


void ChatWidget::send()
{
    d->peer->sendChatMessage(d->line->text());
    d->line->clear();
}

