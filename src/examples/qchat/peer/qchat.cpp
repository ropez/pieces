#include <Pieces/Application>
#include <Pieces/SocketAddress>
#include <Pieces/PeerThread>
#include <Pieces/AutoPointer>
#include <OpenThreads/Thread>
#include <Pieces/Debug>

#include <QtGui>

#include "global.h"
#include "chatwidget.h"
#include "chatpeer.h"

using namespace pcs;


int main(int argc, char** argv)
{
    Application application(argc, argv);

    QApplication app(argc, argv);

    AutoPointer<ChatPeer> peer(new ChatPeer());

    std::string host = "localhost";
    pcs::port_t listenPort = 3333;

    if(pcs::app->argc() > 1)
    {
      host = pcs::app->arg(1);
    }

    if(pcs::app->argc() > 2)
    {
      std::stringstream ss(pcs::app->arg(2));
      ss >> listenPort;
    }

    pcs::SocketAddress sa(pcs::InetAddress::getHostByName(host), 2222);

    PDEBUG << "Connecting to " << sa;

    peer->connectTo(sa);

    AutoPointer<ChatWidget> widget(new ChatWidget(peer.get()));

    QObject::connect(peer.get(), SIGNAL(message(const QString&)), widget.get(), SLOT(showMessage(const QString&)));


    PeerThread th(peer.get());
    th.start();

    widget->show();

    return app.exec();
}
