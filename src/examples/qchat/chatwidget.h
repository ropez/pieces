#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QtGui/QWidget>

namespace qchat
{
class ChatWidgetPrivate;

class ChatWidget : public QWidget
{
    Q_OBJECT;

public:
    ChatWidget(QWidget* parent = 0);
    ~ChatWidget();

public slots:
    void startChat(const QString& nick, const QString& host, quint16 port);
    void showMessage(const QString& nick, const QString& msg);

protected slots:
    void send();

private:
    Q_DISABLE_COPY(ChatWidget);
    ChatWidgetPrivate* d;
};

}

#endif
