#include <Pieces/Application>
#include <Pieces/SocketAddress>
#include <Pieces/PeerThread>
#include <Pieces/AutoPointer>
#include <OpenThreads/Thread>
#include <Pieces/Debug>

#include <QtGui>

#include "global.h"
#include "startwidget.h"
#include "chatwidget.h"
#include "chatpeer.h"

using namespace pcs;


int main(int argc, char** argv)
{
    Application application(argc, argv);

    QApplication app(argc, argv);

    AutoPointer<StartWidget> startup(new StartWidget());
    AutoPointer<ChatWidget> widget(new ChatWidget());

    QObject::connect(startup.get(), SIGNAL(startChat(const QString&, const QString&, quint16)),
                     widget.get(), SLOT(startChat(const QString&, const QString&, quint16)));

    startup->show();

    return app.exec();
}
