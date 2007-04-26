#include <Pieces/Application>
#include <Pieces/SocketAddress>
#include <Pieces/AutoPointer>
#include <OpenThreads/Thread>

#include <QtGui>

#include "global.h"
#include "chatwidget.h"
#include "chatpeer.h"

using namespace Pieces;


class ThreadRunningPeer : public OpenThreads::Thread
{
public:
    ThreadRunningPeer(Peer* peer)
    : m_peer(peer)
    {
    }

    ~ThreadRunningPeer()
    {
        m_peer->quit();
        join();
    }

protected:
    virtual void run()
    {
        m_peer->exec();
    }

private:
    Peer* m_peer;
};


int main(int argc, char** argv)
{
    Application application(argc, argv);

    QApplication app(argc, argv);

    AutoPointer<ChatPeer> peer(new ChatPeer());

    peer->connectTo(SocketAddress(InetAddress::getHostByName("localhost"), 2222));

    AutoPointer<ChatWidget> widget(new ChatWidget(peer.get()));

    QObject::connect(peer.get(), SIGNAL(message(const QString&)), widget.get(), SLOT(showMessage(const QString&)));


    ThreadRunningPeer th(peer.get());
    th.start();

    widget->show();

    return app.exec();
}
