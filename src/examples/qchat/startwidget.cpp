#include <QtGui>

#include "startwidget.h"

namespace qchat
{

class StartWidgetPrivate
{
public:
    StartWidgetPrivate();

    QCheckBox* checkHost;
    QLineEdit* editHost;
    QLineEdit* editPort;

    QLineEdit* editNick;

    QPushButton* buttonStart;
};


StartWidgetPrivate::StartWidgetPrivate()
: checkHost(0)
, editHost(0)
, editPort(0)
, editNick(0)
, buttonStart(0)
{
}


StartWidget::StartWidget(QWidget* parent)
: QWidget(parent)
, d(new StartWidgetPrivate)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    {
        d->checkHost = new QCheckBox(tr("Run as host"));
        layout->addWidget(d->checkHost);
    }

    {
        QHBoxLayout* hl = new QHBoxLayout();
        layout->addLayout(hl);

        d->editHost = new QLineEdit();
        hl->addWidget(new QLabel(tr("Host")));
        hl->addWidget(d->editHost);

        d->editPort = new QLineEdit();
        hl->addWidget(new QLabel(tr("Port")));
        hl->addWidget(d->editPort);

        // Force valid port number
        d->editPort->setValidator(new QIntValidator(0, 0xffff, this));
    }

    {
        QHBoxLayout* hl = new QHBoxLayout();
        layout->addLayout(hl);

        d->editNick = new QLineEdit();
        hl->addWidget(new QLabel(tr("Nick")));
        hl->addWidget(d->editNick);
    }

    d->buttonStart = new QPushButton(tr("Start"));
    layout->addWidget(d->buttonStart);

    connect(d->checkHost, SIGNAL(toggled(bool)), d->editHost, SLOT(setDisabled(bool)));
    connect(d->buttonStart, SIGNAL(clicked()), this, SLOT(onStartClicked()));

    QTimer* idleTimer = new QTimer(this);
    idleTimer->start(0);
    connect(idleTimer, SIGNAL(timeout()), this, SLOT(onIdle()));
}


StartWidget::~StartWidget()
{
    delete d;
}


void StartWidget::onIdle()
{
    d->buttonStart->setEnabled((d->checkHost->isChecked() || !d->editHost->text().isEmpty()) &&
                               !d->editPort->text().isEmpty() && !d->editNick->text().isEmpty());
}


void StartWidget::onStartClicked()
{
    QString nick = d->editNick->text();

    QString host;
    if (!d->checkHost->isChecked())
    {
        host = d->editHost->text();
    }
    quint16 port = d->editPort->text().toUShort();

    emit startChat(nick, host, port);
    close();
}

}
