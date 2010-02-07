#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QtGui/QWidget>

namespace qchat
{
class StartWidgetPrivate;

class StartWidget : public QWidget
{
    Q_OBJECT;

public:
    StartWidget(QWidget* parent = 0);
    ~StartWidget();

signals:
    void startChat(const QString& nick, const QString& host, quint16 port);

protected slots:
    void onIdle();
    void onStartClicked();

private:
    Q_DISABLE_COPY(StartWidget);
    StartWidgetPrivate* d;
};

}

#endif
