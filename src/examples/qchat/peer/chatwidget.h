#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QtGui/QWidget>

class ChatPeer;
class ChatWidgetPrivate;

class ChatWidget : public QWidget
{
    Q_OBJECT;

public:
    ChatWidget(ChatPeer* peer, QWidget* parent = 0);
    ~ChatWidget();

public slots:
    void showMessage(const QString& msg);

protected slots:
    void send();

private:
    Q_DISABLE_COPY(ChatWidget);
    ChatWidgetPrivate* d;
};

#endif
