#include <QtGui>

#include "startwidget.h"


class StartWidgetPrivate
{
public:
    StartWidgetPrivate();

    QCheckBox* checkHost;
    QLineEdit* editHost;
    QLineEdit* editPort;
};


StartWidgetPrivate::StartWidgetPrivate()
: checkHost(0)
, editHost(0)
, editPort(0)
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

    QPushButton* btnStart = new QPushButton(tr("Start"));
    layout->addWidget(btnStart);

    connect(d->checkHost, SIGNAL(toggled(bool)), d->editHost, SLOT(setDisabled(bool)));
    connect(btnStart, SIGNAL(clicked()), this, SLOT(onStartClicked()));
}


StartWidget::~StartWidget()
{
    delete d;
}


void StartWidget::onStartClicked()
{
    QString host;
    if (!d->checkHost->isChecked())
    {
        host = d->editHost->text();
    }
    quint16 port = d->editPort->text().toUShort();

    emit startChat(host, port);
    close();
}
